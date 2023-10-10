#include "fd_exec_slot_ctx.h"

#include <time.h>

void *
fd_exec_slot_ctx_new( void * mem ) {
  if( FD_UNLIKELY( !mem ) ) {
    FD_LOG_WARNING(( "NULL mem" ));
    return NULL;
  }

  if( FD_UNLIKELY( !fd_ulong_is_aligned( (ulong)mem, FD_EXEC_SLOT_CTX_ALIGN ) ) ) {
    FD_LOG_WARNING(( "misaligned mem" ));
    return NULL;
  }

  fd_memset(mem, 0, FD_EXEC_SLOT_CTX_FOOTPRINT);

  fd_exec_slot_ctx_t * self = (fd_exec_slot_ctx_t *) mem;

  self->rng = fd_rng_join( fd_rng_new(&self->rnd_mem, (uint) time(0), 0) );;

  fd_firedancer_banks_new(&self->bank);

  FD_COMPILER_MFENCE();
  self->magic = FD_EXEC_SLOT_CTX_MAGIC;
  FD_COMPILER_MFENCE();

  return mem;
}

fd_exec_slot_ctx_t *
fd_exec_slot_ctx_join( void * mem ) {
  if( FD_UNLIKELY( !mem ) ) {
    FD_LOG_WARNING(( "NULL block" ));
    return NULL;
  }

  fd_exec_slot_ctx_t * ctx = (fd_exec_slot_ctx_t *) mem;

  if( FD_UNLIKELY( ctx->magic!=FD_EXEC_SLOT_CTX_MAGIC ) ) {
    FD_LOG_WARNING(( "bad magic" ));
    return NULL;
  }

  return ctx;
}

void *
fd_exec_slot_ctx_leave( fd_exec_slot_ctx_t * ctx) {
  if( FD_UNLIKELY( !ctx ) ) {
    FD_LOG_WARNING(( "NULL block" ));
    return NULL;
  }

  if( FD_UNLIKELY( ctx->magic!=FD_EXEC_SLOT_CTX_MAGIC ) ) {
    FD_LOG_WARNING(( "bad magic" ));
    return NULL;
  }

  return (void *) ctx;
}

void *
fd_exec_slot_ctx_delete( void * mem ) {
  if( FD_UNLIKELY( !mem ) ) {
    FD_LOG_WARNING(( "NULL mem" ));
    return NULL;
  }

  if( FD_UNLIKELY( !fd_ulong_is_aligned( (ulong)mem, FD_EXEC_SLOT_CTX_ALIGN) ) )  {
    FD_LOG_WARNING(( "misaligned mem" ));
    return NULL;
  }

  fd_exec_slot_ctx_t * hdr = (fd_exec_slot_ctx_t *)mem;
  if( FD_UNLIKELY( hdr->magic!=FD_EXEC_SLOT_CTX_MAGIC ) ) {
    FD_LOG_WARNING(( "bad magic" ));
    return NULL;
  }

  fd_bincode_destroy_ctx_t ctx = { .valloc = hdr->valloc };
  fd_firedancer_banks_destroy(&hdr->bank, &ctx);

  FD_COMPILER_MFENCE();
  FD_VOLATILE( hdr->magic ) = 0UL;
  FD_COMPILER_MFENCE();

  return mem;
}
