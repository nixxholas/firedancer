#include "fd_vm_test.h"
#include "../context/fd_exec_epoch_ctx.h"
#include "../context/fd_exec_slot_ctx.h"
#include "../context/fd_exec_txn_ctx.h"
#include "../../vm/test_vm_util.h"

int
fd_vm_syscall_noop( void * _vm,
                    ulong arg0,
                    ulong arg1,
                    ulong arg2,
                    ulong arg3,
                    ulong arg4,
                    ulong* _ret){
  /* TODO: have input message determine CUs to deduct? 
  fd_vm_t * vm = (fd_vm_t *) _vm;
  vm->cu = vm->cu - 5;
  */
  
  (void) _vm;
  (void) arg0;
  (void) arg1;
  (void) arg2;
  (void) arg3;
  (void) arg4;
  (void) _ret;
  return 0;
}

ulong
fd_exec_vm_validate_test_run( fd_exec_instr_test_runner_t * runner,
                              void const *                  input_,
                              void **                       output_,
                              void *                        output_buf,
                              ulong                         output_bufsz ) {
  (void) runner; /* unused, for wrapper compat */
  fd_exec_test_full_vm_context_t const * input  = fd_type_pun_const( input_ );
  fd_exec_test_validate_vm_effects_t **  output = fd_type_pun( output_ );

  if( FD_UNLIKELY( !input->has_vm_ctx ) ) {
    return 0UL;
  }

  int rej_callx_r10 = 0;
  if( input->has_features ) {
    for( ulong i=0UL; i < input->features.features_count; i++ ) {
      if( input->features.features[i] == TEST_VM_REJECT_CALLX_R10_FEATURE_PREFIX ) {
        rej_callx_r10 = 1;
        break;
      }
    }
  }
  fd_exec_instr_ctx_t * ctx = test_vm_minimal_exec_instr_ctx( fd_libc_alloc_virtual(), rej_callx_r10 );

  FD_TEST( output_bufsz >= sizeof(fd_exec_test_validate_vm_effects_t) );

  /* Capture outputs */
  FD_SCRATCH_ALLOC_INIT( l, output_buf );

  fd_exec_test_validate_vm_effects_t * effects =
    FD_SCRATCH_ALLOC_APPEND( l, alignof(fd_exec_test_validate_vm_effects_t),
                                sizeof (fd_exec_test_validate_vm_effects_t) );
  FD_SCRATCH_ALLOC_FINI( l, 1UL );

  fd_valloc_t valloc = fd_scratch_virtual();
  do{
    fd_exec_test_vm_context_t const * vm_ctx = &input->vm_ctx;

    /* Follows prost/solfuzz-agave behavior for empty bytes field */
    uchar * rodata = NULL;
    ulong rodata_sz = 0UL;
    if( FD_LIKELY( vm_ctx->rodata ) ) {
      rodata = vm_ctx->rodata->bytes;
      rodata_sz = vm_ctx->rodata->size;
    }

    ulong * text = (ulong *) (rodata + vm_ctx->rodata_text_section_offset);    
    ulong text_cnt = vm_ctx->rodata_text_section_length / 8UL;

    fd_vm_t * vm = fd_vm_join( fd_vm_new( fd_valloc_malloc( valloc, fd_vm_align(), fd_vm_footprint() ) ) );
    FD_TEST( vm );

    fd_vm_init(
      vm,
      ctx,
      0, /* heap_max */
      0, /* cu_avail */
      rodata,
      rodata_sz,
      text,
      text_cnt,
      vm_ctx->rodata_text_section_offset,
      vm_ctx->rodata_text_section_length,
      0, /* entry_pc, not used in validate at the moment */
      NULL, /* calldests */
      NULL, /* syscalls */
      NULL, /* trace */
      NULL, /* sha */
      NULL, /* mem regions */
      0,    /* mem regions count */
      NULL, /* mem regions accs */
      0     /* is deprecated */
    );
    effects->result = fd_vm_validate( vm );

    fd_valloc_free( valloc, fd_vm_delete( fd_vm_leave( vm ) ) );

  } while(0);
  

  /* Run vm validate and capture result */
  
  effects->success = (effects->result == FD_VM_SUCCESS);
  *output = effects;
  
  test_vm_exec_instr_ctx_delete( ctx );
  return sizeof (fd_exec_test_validate_vm_effects_t);
}


ulong
fd_exec_vm_interp_test_run( fd_exec_instr_test_runner_t *         runner,
                            fd_exec_test_syscall_context_t const *input,
                            fd_exec_test_syscall_effects_t      **output,
                            void *                                output_buf,
                            ulong                                 output_bufsz ) {
  (void) runner; /* unused, for wrapper compat */

  if( !( input->has_vm_ctx && input->has_syscall_invocation ) ) {
    /* FIXME: syscall_invocation can be optional... */
    return 0UL;
  }

  fd_valloc_t valloc = fd_scratch_virtual();

  /* Create effects */
  ulong output_end = (ulong) output_buf + output_bufsz;
  FD_SCRATCH_ALLOC_INIT( l, output_buf );
  fd_exec_test_syscall_effects_t * effects =
    FD_SCRATCH_ALLOC_APPEND( l, alignof(fd_exec_test_syscall_effects_t),
                                sizeof (fd_exec_test_syscall_effects_t) );
  if( FD_UNLIKELY( _l > output_end ) ) {
    return 0UL;
  }

do{
  /* Setup regions */
  if ( !input->vm_ctx.rodata ) {
    break;
  }
  uchar * rodata = input->vm_ctx.rodata->bytes;
  ulong rodata_sz = input->vm_ctx.rodata->size;

  

  /* Concatenate the input data regions into the flat input memory region */
  ulong input_data_sz = 0;
  for ( ulong i=0; i<input->vm_ctx.input_data_regions_count; i++ ) {
    if( !input->vm_ctx.input_data_regions[i].content ) {
      continue;
    }
    input_data_sz += input->vm_ctx.input_data_regions[i].content->size;
  }
  uchar * input_data = fd_valloc_malloc( valloc, alignof(uchar), input_data_sz );
  uchar * input_data_ptr = input_data;
  for ( ulong i=0; i<input->vm_ctx.input_data_regions_count; i++ ) {
    pb_bytes_array_t * array = input->vm_ctx.input_data_regions[i].content;
    if( !input->vm_ctx.input_data_regions[i].content ) {
      continue;
    }
    fd_memcpy( input_data_ptr, array->bytes, array->size );
    input_data_ptr += array->size;
  }

  if( input_data_ptr != (input_data + input_data_sz) ) {
    break;
  }

  /* Turn input into a single memory region */
  fd_vm_input_region_t input_region = {
    .vaddr_offset = 0UL,
    .haddr        = (ulong)input_data,
    .region_sz    = (uint)input_data_sz,
    .is_writable  = 1U,
    .pubkey       = NULL
  };


  if (input->vm_ctx.heap_max > FD_VM_HEAP_DEFAULT) {
    break;
  }

  /* Setup calldests from call_whitelist */
  ulong * calldests = (ulong *) input->vm_ctx.call_whitelist->bytes;

  /* Setup syscalls. Have them all be no-ops */
  fd_sbpf_syscalls_t * syscalls = fd_sbpf_syscalls_new( fd_valloc_malloc( valloc, fd_sbpf_syscalls_align(), fd_sbpf_syscalls_footprint() ) );
  fd_vm_syscall_register_all( syscalls, 0 );

  for( ulong i=0; i< fd_sbpf_syscalls_slot_cnt(); i++ ){
    fd_sbpf_syscalls_t * syscall = fd_sbpf_syscalls_query( syscalls, syscalls[i].key, NULL ); // TODO: can just use syscalls[i].func directly?
    if ( !syscall ) {
      continue;
    }
    syscall->func = fd_vm_syscall_noop;
  }

  /* Setup vm */
  fd_vm_t * vm = fd_vm_join( fd_vm_new( fd_valloc_malloc( valloc, fd_vm_align(), fd_vm_footprint() ) ) );
  FD_TEST( vm );

  fd_exec_instr_ctx_t * instr_ctx = test_vm_minimal_exec_instr_ctx( valloc, false /* flag not required here */);

  fd_vm_init(
    vm,
    instr_ctx,
    FD_VM_HEAP_MAX,
    input->has_instr_ctx ? input->instr_ctx.cu_avail : 0,
    rodata,
    rodata_sz,
    (ulong *) rodata, /* text*, same as rodata */
    rodata_sz / 8, /* text_cnt */
    0, /* text_off */
    rodata_sz, /* text_sz */
    input->vm_ctx.entry_pc,
    calldests,
    syscalls,
    NULL, /* trace */
    NULL, /* sha */
    &input_region,
    1UL,
    NULL, /* vm_acc_region_meta*/
    0 /* is deprecated */
  );

  // Validate the vm
  if ( !fd_vm_validate( vm ) ) {
    effects->error = -1;
    break;
  }

  // Override some execution state values from the interp fuzzer input
  // This is so we can test if the interp mutates any of these erroneously
  vm->reg[0] = input->vm_ctx.r0;
  vm->reg[1] = input->vm_ctx.r1;
  vm->reg[2] = input->vm_ctx.r2;
  vm->reg[3] = input->vm_ctx.r3;
  vm->reg[4] = input->vm_ctx.r4;
  vm->reg[5] = input->vm_ctx.r5;
  vm->reg[6] = input->vm_ctx.r6;
  vm->reg[7] = input->vm_ctx.r7;
  vm->reg[8] = input->vm_ctx.r8;
  vm->reg[9] = input->vm_ctx.r9;
  vm->reg[10] = input->vm_ctx.r10;
  vm->reg[11] = input->vm_ctx.r11;

  vm->check_align = input->vm_ctx.check_align;
  vm->check_size = input->vm_ctx.check_size;

  if( input->syscall_invocation.stack_prefix ) {
    uchar * stack = input->syscall_invocation.stack_prefix->bytes;
    ulong stack_sz = fd_ulong_min(input->syscall_invocation.stack_prefix->size, FD_VM_STACK_MAX);
    fd_memcpy( vm->stack, stack, stack_sz );
  }

  if( input->syscall_invocation.heap_prefix ) {
    uchar * heap = input->syscall_invocation.heap_prefix->bytes;
    ulong heap_sz = fd_ulong_min(input->syscall_invocation.heap_prefix->size, FD_VM_HEAP_MAX);
    fd_memcpy( vm->heap, heap, heap_sz );
  }

  /* Run vm */
  effects->error = -fd_vm_exec_notrace( vm );

  /* Capture outputs */
  effects->cu_avail = vm->cu;
  effects->frame_count = vm->frame_cnt;
  effects->r0 = effects->error ? 0 : vm->reg[0]; /* Only capture r0 if no error */
  effects->pc = vm->pc;

  effects->heap = FD_SCRATCH_ALLOC_APPEND(
    l, alignof(uchar), PB_BYTES_ARRAY_T_ALLOCSIZE( vm->heap_max ) );
  effects->heap->size = (uint)vm->heap_max;
  fd_memcpy( effects->heap->bytes, vm->heap, vm->heap_max );

  effects->stack = FD_SCRATCH_ALLOC_APPEND(
    l, alignof(uchar), PB_BYTES_ARRAY_T_ALLOCSIZE( FD_VM_STACK_MAX ) );
  effects->stack->size = (uint)FD_VM_STACK_MAX;
  fd_memcpy( effects->stack->bytes, vm->stack, FD_VM_STACK_MAX );

  /* TODO: capture input region */
  effects->inputdata = NULL;
  /* skip logs since syscalls are stubbed */
  effects->log = NULL;
} while(0);

  ulong actual_end = FD_SCRATCH_ALLOC_FINI( l, 1UL );
  *output = effects;
  return actual_end - (ulong)output_buf;


}


uint
setup_vm_input_regions( fd_vm_input_region_t *                   input,
                        fd_exec_test_input_data_region_t const * test_input,
                        ulong                                    test_input_count ) {
  ulong offset = 0UL;
  uint input_idx = 0UL;
  for( ulong i=0; i<test_input_count; i++ ) {
    fd_exec_test_input_data_region_t const * region = &test_input[i];
    pb_bytes_array_t * array = region->content;
    if( !array ) {
      continue; /* skip empty regions https://github.com/anza-xyz/agave/blob/3072c1a72b2edbfa470ca869f1ea891dfb6517f2/programs/bpf_loader/src/serialization.rs#L136 */
    }

    input[input_idx].vaddr_offset     = offset;
    input[input_idx].haddr            = (ulong)array->bytes;
    input[input_idx].region_sz        = array->size;
    input[input_idx].is_writable      = region->is_writable;

    input_idx++;
    offset += array->size;
  }
  return input_idx; /* return the number of populated regions */
}


ulong
load_from_vm_input_regions( fd_vm_input_region_t const *        input,
                            uint                                input_count,
                            fd_exec_test_input_data_region_t ** output,
                            pb_size_t *                         output_count,
                            void *                              output_buf,
                            ulong                               output_bufsz ) {
  /* pre-flight checks on output buffer size*/
  ulong input_regions_total_sz = 0;
  for( ulong i=0; i<input_count; i++ ) {
    input_regions_total_sz += input[i].region_sz;
  }

  if( FD_UNLIKELY(   input_regions_total_sz == 0
                  || output_bufsz < input_regions_total_sz ) ) {
    *output = NULL;
    *output_count = 0;
    return 0;
  }

  FD_SCRATCH_ALLOC_INIT( l, output_buf );
  *output = FD_SCRATCH_ALLOC_APPEND( l, alignof(fd_exec_test_input_data_region_t),
                                      input_count * sizeof (fd_exec_test_input_data_region_t) );
  FD_TEST( *output );
  *output_count = input_count;

  for( ulong i=0; i<input_count; i++ ) {
    fd_vm_input_region_t const * vm_region = &input[i];
    fd_exec_test_input_data_region_t * out_region = &(*output)[i];
    out_region->is_writable = vm_region->is_writable;
    out_region->offset = vm_region->vaddr_offset;

    out_region->content = FD_SCRATCH_ALLOC_APPEND( l, alignof(pb_bytes_array_t),
                                               PB_BYTES_ARRAY_T_ALLOCSIZE(vm_region->region_sz) );
    FD_TEST( out_region->content );
    out_region->content->size = vm_region->region_sz;
    fd_memcpy( out_region->content->bytes, (void *)vm_region->haddr, vm_region->region_sz );
  }

  ulong end = FD_SCRATCH_ALLOC_FINI( l, 1UL );
  return end - (ulong)output_buf; /* return the number of bytes written */
}