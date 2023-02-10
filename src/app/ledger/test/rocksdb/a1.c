// git clone https://github.com/facebook/rocksdb.git
// cd rocksdb
// make static_lib -j10
//
// back to this directory
// make

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../../util/bits/fd_bits.h"
#include "../../../../util/fd_util.h"
#include "../../../../ballet/bank/fd_banks.h"

#include <rocksdb/c.h>

struct fd_slot_meta {
  ulong slot;
  ulong consumed;
  ulong received;
  ulong first_shred_timestamp;
  ulong last_index;
  ulong parent_slot;
  ulong num_next_slots;
  ulong *next_slots;
  uchar is_connected;
  ulong num_entry_end_indexes;
  uint entry_end_indexes[64];
};
typedef struct fd_slot_meta fd_slot_meta_t;
#define FD_SLOT_META_FOOTPRINT sizeof(fd_slot_meta_t)
#define FD_SLOT_META_ALIGN (8UL)

void fd_slot_meta_decode(fd_slot_meta_t* self, void const** data, void const* dataend, FD_FN_UNUSED alloc_fun allocf, FD_FN_UNUSED void* allocf_arg) {
  fd_bincode_uint64_decode(&self->slot, data, dataend);
  fd_bincode_uint64_decode(&self->consumed, data, dataend);
  fd_bincode_uint64_decode(&self->received, data, dataend);
  fd_bincode_uint64_decode(&self->first_shred_timestamp, data, dataend);
  fd_bincode_uint64_decode(&self->last_index, data, dataend);
  fd_bincode_uint64_decode(&self->parent_slot, data, dataend);
  fd_bincode_uint64_decode(&self->num_next_slots, data, dataend);
  if (self->num_next_slots > 0) {
    self->next_slots = (ulong*)(*allocf)(sizeof(ulong)*self->num_next_slots, (8UL), allocf_arg);
    for (ulong i = 0; i < self->num_next_slots; ++i)
      fd_bincode_uint64_decode(self->next_slots + i, data, dataend);
  } else
    self->next_slots = NULL;
  fd_bincode_uint8_decode(&self->is_connected, data, dataend);
  fd_bincode_uint64_decode(&self->num_entry_end_indexes, data, dataend);
  for (ulong i = 0; i < self->num_entry_end_indexes; ++i)
    fd_bincode_uint32_decode(self->entry_end_indexes + i, data, dataend);
}

char* allocf(unsigned long len, FD_FN_UNUSED unsigned long align, FD_FN_UNUSED void* arg) {
  return malloc(len);
}

int main()
{
    const char *db_name = "/home/jsiegel/repos/solana/test-ledger/rocksdb";
    rocksdb_options_t *opts = rocksdb_options_create();
    char *err = NULL;

//    size_t lencf = 0;
//    char **cf = rocksdb_list_column_families(opts, db_name, &lencf, &err);
//    for (int i = 0; i < lencf; i++) {
//      printf("%s\n", cf[i]);
//    }

    const char *cfs[] = {"default", "meta", "root", "data_shred", "code_shred"};
    const rocksdb_options_t *cf_options[] = {opts, opts, opts, opts, opts}; // One per cfs

    rocksdb_column_family_handle_t* column_family_handles[5] = {NULL, NULL, NULL, NULL, NULL};

    rocksdb_t *db = rocksdb_open_for_read_only_column_families(
      opts, db_name, 5,
        (const char * const *) &cfs, 
        (const rocksdb_options_t * const*) cf_options,
        column_family_handles, 
        false, &err);

    if (err != NULL) {
        fprintf(stderr, "database open %s\n", err);
        free(err);
        return -1;
    }

    rocksdb_readoptions_t *ro = rocksdb_readoptions_create();

    rocksdb_iterator_t* iter = rocksdb_create_iterator_cf(db, ro, column_family_handles[2]);
    rocksdb_iter_seek_to_last(iter);    
    if (!rocksdb_iter_valid(iter)) {
      fprintf(stderr, "Odd, no slots?");
      rocksdb_close(db);
      return -1;
    }

    size_t klen = 0;
    const char *key = rocksdb_iter_key(iter, &klen); // There is no need to free kee
    unsigned long slot = fd_ulong_bswap(*((unsigned long *) key));
    printf("Last slot in the db: %ld\n", slot);
    rocksdb_iter_destroy(iter);


    ulong ks = fd_ulong_bswap(1);
    size_t vallen = 0;

    char *meta = rocksdb_get_cf(
      db, ro, column_family_handles[1], (const char *) &ks, sizeof(ks), &vallen, &err);

    unsigned char *outend = (unsigned char *) &meta[vallen];
    const void * o = meta;

    fd_slot_meta_t m;
    fd_slot_meta_decode(&m, &o, outend, allocf, NULL);

    rocksdb_readoptions_destroy(ro);

// ~/repos/radiance/pkg/blockstore/
// func (d *DB) GetEntries(meta *SlotMeta, shredRevision int) ([]Entries, error) {
// 	shreds, err := d.GetDataShreds(meta.Slot, 0, uint32(meta.Received), shredRevision)
// 	if err != nil {
// 		return nil, err
// 	}
// 	return DataShredsToEntries(meta, shreds)
// }

    rocksdb_close(db);
    rocksdb_options_destroy(opts);

    return 0;
}
