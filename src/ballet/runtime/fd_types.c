#include "fd_types.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"
void fd_fee_calculator_decode(fd_fee_calculator_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->lamports_per_signature, data, dataend);
}
void fd_fee_calculator_destroy(fd_fee_calculator_t* self, fd_free_fun_t freef, void* freef_arg) {
}

void fd_fee_calculator_walk(fd_fee_calculator_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_fee_calculator", level++);
  fun(&self->lamports_per_signature, "lamports_per_signature", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_fee_calculator", --level);
}
void fd_fee_calculator_copy_to(fd_fee_calculator_t* to, fd_fee_calculator_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_fee_calculator_size(from) );
  void const *   ptr = (void const *) enc;
  fd_fee_calculator_encode( from, &ptr );
  void *input = (void *) enc;
  fd_fee_calculator_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_fee_calculator_size(fd_fee_calculator_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  return size;
}

void fd_fee_calculator_encode(fd_fee_calculator_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->lamports_per_signature, data);
}

void fd_hash_age_decode(fd_hash_age_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_fee_calculator_decode(&self->fee_calculator, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->hash_index, data, dataend);
  fd_bincode_uint64_decode(&self->timestamp, data, dataend);
}
void fd_hash_age_destroy(fd_hash_age_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_fee_calculator_destroy(&self->fee_calculator, freef, freef_arg);
}

void fd_hash_age_walk(fd_hash_age_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_hash_age", level++);
  fd_fee_calculator_walk(&self->fee_calculator, fun, "fee_calculator", level + 1);
  fun(&self->hash_index, "hash_index", 11, "ulong", level + 1);
  fun(&self->timestamp, "timestamp", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_hash_age", --level);
}
void fd_hash_age_copy_to(fd_hash_age_t* to, fd_hash_age_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_hash_age_size(from) );
  void const *   ptr = (void const *) enc;
  fd_hash_age_encode( from, &ptr );
  void *input = (void *) enc;
  fd_hash_age_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_hash_age_size(fd_hash_age_t* self) {
  ulong size = 0;
  size += fd_fee_calculator_size(&self->fee_calculator);
  size += sizeof(ulong);
  size += sizeof(ulong);
  return size;
}

void fd_hash_age_encode(fd_hash_age_t* self, void const** data) {
  fd_fee_calculator_encode(&self->fee_calculator, data);
  fd_bincode_uint64_encode(&self->hash_index, data);
  fd_bincode_uint64_encode(&self->timestamp, data);
}

void fd_hash_hash_age_pair_decode(fd_hash_hash_age_pair_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_hash_decode(&self->key, data, dataend, allocf, allocf_arg);
  fd_hash_age_decode(&self->val, data, dataend, allocf, allocf_arg);
}
void fd_hash_hash_age_pair_destroy(fd_hash_hash_age_pair_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_hash_destroy(&self->key, freef, freef_arg);
  fd_hash_age_destroy(&self->val, freef, freef_arg);
}

void fd_hash_hash_age_pair_walk(fd_hash_hash_age_pair_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_hash_hash_age_pair", level++);
  fd_hash_walk(&self->key, fun, "key", level + 1);
  fd_hash_age_walk(&self->val, fun, "val", level + 1);
  fun(self, name, 33, "fd_hash_hash_age_pair", --level);
}
void fd_hash_hash_age_pair_copy_to(fd_hash_hash_age_pair_t* to, fd_hash_hash_age_pair_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_hash_hash_age_pair_size(from) );
  void const *   ptr = (void const *) enc;
  fd_hash_hash_age_pair_encode( from, &ptr );
  void *input = (void *) enc;
  fd_hash_hash_age_pair_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_hash_hash_age_pair_size(fd_hash_hash_age_pair_t* self) {
  ulong size = 0;
  size += fd_hash_size(&self->key);
  size += fd_hash_age_size(&self->val);
  return size;
}

void fd_hash_hash_age_pair_encode(fd_hash_hash_age_pair_t* self, void const** data) {
  fd_hash_encode(&self->key, data);
  fd_hash_age_encode(&self->val, data);
}

void fd_block_hash_queue_decode(fd_block_hash_queue_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->last_hash_index, data, dataend);
  if (fd_bincode_option_decode(data, dataend)) {
    self->last_hash = (fd_hash_t*)(*allocf)(allocf_arg, FD_HASH_ALIGN, FD_HASH_FOOTPRINT);
    fd_hash_decode(self->last_hash, data, dataend, allocf, allocf_arg);
  } else
    self->last_hash = NULL;
  fd_bincode_uint64_decode(&self->ages_len, data, dataend);
  if (self->ages_len != 0) {
    self->ages = (fd_hash_hash_age_pair_t*)(*allocf)(allocf_arg, FD_HASH_HASH_AGE_PAIR_ALIGN, FD_HASH_HASH_AGE_PAIR_FOOTPRINT*self->ages_len);
    for (ulong i = 0; i < self->ages_len; ++i)
      fd_hash_hash_age_pair_decode(self->ages + i, data, dataend, allocf, allocf_arg);
  } else
    self->ages = NULL;
  fd_bincode_uint64_decode(&self->max_age, data, dataend);
}
void fd_block_hash_queue_destroy(fd_block_hash_queue_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->last_hash) {
    fd_hash_destroy(self->last_hash,  freef, freef_arg);
    freef(freef_arg, self->last_hash);
    self->last_hash = NULL;
  }
  if (NULL != self->ages) {
    for (ulong i = 0; i < self->ages_len; ++i)
      fd_hash_hash_age_pair_destroy(self->ages + i, freef, freef_arg);
    freef(freef_arg, self->ages);
    self->ages = NULL;
  }
}

void fd_block_hash_queue_walk(fd_block_hash_queue_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_block_hash_queue", level++);
  fun(&self->last_hash_index, "last_hash_index", 11, "ulong", level + 1);
  // fun(&self->last_hash, "last_hash", 16, "option", level + 1);
  if (self->ages_len != 0) {
    fun(NULL, NULL, 30, "ages", level++);
    for (ulong i = 0; i < self->ages_len; ++i)
      fd_hash_hash_age_pair_walk(self->ages + i, fun, "hash_hash_age_pair", level + 1);
    fun(NULL, NULL, 31, "ages", --level);
  }
  fun(&self->max_age, "max_age", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_block_hash_queue", --level);
}
void fd_block_hash_queue_copy_to(fd_block_hash_queue_t* to, fd_block_hash_queue_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_block_hash_queue_size(from) );
  void const *   ptr = (void const *) enc;
  fd_block_hash_queue_encode( from, &ptr );
  void *input = (void *) enc;
  fd_block_hash_queue_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_block_hash_queue_size(fd_block_hash_queue_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(char);
  if (NULL !=  self->last_hash) {
    size += fd_hash_size(self->last_hash);
  }
  size += sizeof(ulong);
  for (ulong i = 0; i < self->ages_len; ++i)
    size += fd_hash_hash_age_pair_size(self->ages + i);
  size += sizeof(ulong);
  return size;
}

void fd_block_hash_queue_encode(fd_block_hash_queue_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->last_hash_index, data);
  if (self->last_hash!= NULL) {
    fd_bincode_option_encode(1, data);
    fd_hash_encode(self->last_hash, data);
  } else
    fd_bincode_option_encode(0, data);
  fd_bincode_uint64_encode(&self->ages_len, data);
  if (self->ages_len != 0) {
    for (ulong i = 0; i < self->ages_len; ++i)
      fd_hash_hash_age_pair_encode(self->ages + i, data);
  }
  fd_bincode_uint64_encode(&self->max_age, data);
}

void fd_epoch_schedule_decode(fd_epoch_schedule_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->slots_per_epoch, data, dataend);
  fd_bincode_uint64_decode(&self->leader_schedule_slot_offset, data, dataend);
  fd_bincode_uint8_decode(&self->warmup, data, dataend);
  fd_bincode_uint64_decode(&self->first_normal_epoch, data, dataend);
  fd_bincode_uint64_decode(&self->first_normal_slot, data, dataend);
}
void fd_epoch_schedule_destroy(fd_epoch_schedule_t* self, fd_free_fun_t freef, void* freef_arg) {
}

void fd_epoch_schedule_walk(fd_epoch_schedule_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_epoch_schedule", level++);
  fun(&self->slots_per_epoch, "slots_per_epoch", 11, "ulong", level + 1);
  fun(&self->leader_schedule_slot_offset, "leader_schedule_slot_offset", 11, "ulong", level + 1);
  fun(&self->warmup, "warmup", 9, "uchar", level + 1);
  fun(&self->first_normal_epoch, "first_normal_epoch", 11, "ulong", level + 1);
  fun(&self->first_normal_slot, "first_normal_slot", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_epoch_schedule", --level);
}
void fd_epoch_schedule_copy_to(fd_epoch_schedule_t* to, fd_epoch_schedule_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_epoch_schedule_size(from) );
  void const *   ptr = (void const *) enc;
  fd_epoch_schedule_encode( from, &ptr );
  void *input = (void *) enc;
  fd_epoch_schedule_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_epoch_schedule_size(fd_epoch_schedule_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(char);
  size += sizeof(ulong);
  size += sizeof(ulong);
  return size;
}

void fd_epoch_schedule_encode(fd_epoch_schedule_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->slots_per_epoch, data);
  fd_bincode_uint64_encode(&self->leader_schedule_slot_offset, data);
  fd_bincode_uint8_encode(&self->warmup, data);
  fd_bincode_uint64_encode(&self->first_normal_epoch, data);
  fd_bincode_uint64_encode(&self->first_normal_slot, data);
}

void fd_fee_rate_governor_decode(fd_fee_rate_governor_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->target_lamports_per_signature, data, dataend);
  fd_bincode_uint64_decode(&self->target_signatures_per_slot, data, dataend);
  fd_bincode_uint64_decode(&self->min_lamports_per_signature, data, dataend);
  fd_bincode_uint64_decode(&self->max_lamports_per_signature, data, dataend);
  fd_bincode_uint8_decode(&self->burn_percent, data, dataend);
}
void fd_fee_rate_governor_destroy(fd_fee_rate_governor_t* self, fd_free_fun_t freef, void* freef_arg) {
}

void fd_fee_rate_governor_walk(fd_fee_rate_governor_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_fee_rate_governor", level++);
  fun(&self->target_lamports_per_signature, "target_lamports_per_signature", 11, "ulong", level + 1);
  fun(&self->target_signatures_per_slot, "target_signatures_per_slot", 11, "ulong", level + 1);
  fun(&self->min_lamports_per_signature, "min_lamports_per_signature", 11, "ulong", level + 1);
  fun(&self->max_lamports_per_signature, "max_lamports_per_signature", 11, "ulong", level + 1);
  fun(&self->burn_percent, "burn_percent", 9, "uchar", level + 1);
  fun(self, name, 33, "fd_fee_rate_governor", --level);
}
void fd_fee_rate_governor_copy_to(fd_fee_rate_governor_t* to, fd_fee_rate_governor_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_fee_rate_governor_size(from) );
  void const *   ptr = (void const *) enc;
  fd_fee_rate_governor_encode( from, &ptr );
  void *input = (void *) enc;
  fd_fee_rate_governor_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_fee_rate_governor_size(fd_fee_rate_governor_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(char);
  return size;
}

void fd_fee_rate_governor_encode(fd_fee_rate_governor_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->target_lamports_per_signature, data);
  fd_bincode_uint64_encode(&self->target_signatures_per_slot, data);
  fd_bincode_uint64_encode(&self->min_lamports_per_signature, data);
  fd_bincode_uint64_encode(&self->max_lamports_per_signature, data);
  fd_bincode_uint8_encode(&self->burn_percent, data);
}

void fd_slot_pair_decode(fd_slot_pair_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->slot, data, dataend);
  fd_bincode_uint64_decode(&self->val, data, dataend);
}
void fd_slot_pair_destroy(fd_slot_pair_t* self, fd_free_fun_t freef, void* freef_arg) {
}

void fd_slot_pair_walk(fd_slot_pair_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_slot_pair", level++);
  fun(&self->slot, "slot", 11, "ulong", level + 1);
  fun(&self->val, "val", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_slot_pair", --level);
}
void fd_slot_pair_copy_to(fd_slot_pair_t* to, fd_slot_pair_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_slot_pair_size(from) );
  void const *   ptr = (void const *) enc;
  fd_slot_pair_encode( from, &ptr );
  void *input = (void *) enc;
  fd_slot_pair_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_slot_pair_size(fd_slot_pair_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(ulong);
  return size;
}

void fd_slot_pair_encode(fd_slot_pair_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->slot, data);
  fd_bincode_uint64_encode(&self->val, data);
}

void fd_hard_forks_decode(fd_hard_forks_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->hard_forks_len, data, dataend);
  if (self->hard_forks_len != 0) {
    self->hard_forks = (fd_slot_pair_t*)(*allocf)(allocf_arg, FD_SLOT_PAIR_ALIGN, FD_SLOT_PAIR_FOOTPRINT*self->hard_forks_len);
    for (ulong i = 0; i < self->hard_forks_len; ++i)
      fd_slot_pair_decode(self->hard_forks + i, data, dataend, allocf, allocf_arg);
  } else
    self->hard_forks = NULL;
}
void fd_hard_forks_destroy(fd_hard_forks_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->hard_forks) {
    for (ulong i = 0; i < self->hard_forks_len; ++i)
      fd_slot_pair_destroy(self->hard_forks + i, freef, freef_arg);
    freef(freef_arg, self->hard_forks);
    self->hard_forks = NULL;
  }
}

void fd_hard_forks_walk(fd_hard_forks_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_hard_forks", level++);
  if (self->hard_forks_len != 0) {
    fun(NULL, NULL, 30, "hard_forks", level++);
    for (ulong i = 0; i < self->hard_forks_len; ++i)
      fd_slot_pair_walk(self->hard_forks + i, fun, "slot_pair", level + 1);
    fun(NULL, NULL, 31, "hard_forks", --level);
  }
  fun(self, name, 33, "fd_hard_forks", --level);
}
void fd_hard_forks_copy_to(fd_hard_forks_t* to, fd_hard_forks_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_hard_forks_size(from) );
  void const *   ptr = (void const *) enc;
  fd_hard_forks_encode( from, &ptr );
  void *input = (void *) enc;
  fd_hard_forks_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_hard_forks_size(fd_hard_forks_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  for (ulong i = 0; i < self->hard_forks_len; ++i)
    size += fd_slot_pair_size(self->hard_forks + i);
  return size;
}

void fd_hard_forks_encode(fd_hard_forks_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->hard_forks_len, data);
  if (self->hard_forks_len != 0) {
    for (ulong i = 0; i < self->hard_forks_len; ++i)
      fd_slot_pair_encode(self->hard_forks + i, data);
  }
}

void fd_inflation_decode(fd_inflation_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_double_decode(&self->initial, data, dataend);
  fd_bincode_double_decode(&self->terminal, data, dataend);
  fd_bincode_double_decode(&self->taper, data, dataend);
  fd_bincode_double_decode(&self->foundation, data, dataend);
  fd_bincode_double_decode(&self->foundation_term, data, dataend);
  fd_bincode_double_decode(&self->__unused, data, dataend);
}
void fd_inflation_destroy(fd_inflation_t* self, fd_free_fun_t freef, void* freef_arg) {
}

void fd_inflation_walk(fd_inflation_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_inflation", level++);
  fun(&self->initial, "initial", 5, "double", level + 1);
  fun(&self->terminal, "terminal", 5, "double", level + 1);
  fun(&self->taper, "taper", 5, "double", level + 1);
  fun(&self->foundation, "foundation", 5, "double", level + 1);
  fun(&self->foundation_term, "foundation_term", 5, "double", level + 1);
  fun(&self->__unused, "__unused", 5, "double", level + 1);
  fun(self, name, 33, "fd_inflation", --level);
}
void fd_inflation_copy_to(fd_inflation_t* to, fd_inflation_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_inflation_size(from) );
  void const *   ptr = (void const *) enc;
  fd_inflation_encode( from, &ptr );
  void *input = (void *) enc;
  fd_inflation_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_inflation_size(fd_inflation_t* self) {
  ulong size = 0;
  size += sizeof(double);
  size += sizeof(double);
  size += sizeof(double);
  size += sizeof(double);
  size += sizeof(double);
  size += sizeof(double);
  return size;
}

void fd_inflation_encode(fd_inflation_t* self, void const** data) {
  fd_bincode_double_encode(&self->initial, data);
  fd_bincode_double_encode(&self->terminal, data);
  fd_bincode_double_encode(&self->taper, data);
  fd_bincode_double_encode(&self->foundation, data);
  fd_bincode_double_encode(&self->foundation_term, data);
  fd_bincode_double_encode(&self->__unused, data);
}

void fd_rent_decode(fd_rent_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->lamports_per_uint8_year, data, dataend);
  fd_bincode_double_decode(&self->exemption_threshold, data, dataend);
  fd_bincode_uint8_decode(&self->burn_percent, data, dataend);
}
void fd_rent_destroy(fd_rent_t* self, fd_free_fun_t freef, void* freef_arg) {
}

void fd_rent_walk(fd_rent_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_rent", level++);
  fun(&self->lamports_per_uint8_year, "lamports_per_uint8_year", 11, "ulong", level + 1);
  fun(&self->exemption_threshold, "exemption_threshold", 5, "double", level + 1);
  fun(&self->burn_percent, "burn_percent", 9, "uchar", level + 1);
  fun(self, name, 33, "fd_rent", --level);
}
void fd_rent_copy_to(fd_rent_t* to, fd_rent_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_rent_size(from) );
  void const *   ptr = (void const *) enc;
  fd_rent_encode( from, &ptr );
  void *input = (void *) enc;
  fd_rent_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_rent_size(fd_rent_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(double);
  size += sizeof(char);
  return size;
}

void fd_rent_encode(fd_rent_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->lamports_per_uint8_year, data);
  fd_bincode_double_encode(&self->exemption_threshold, data);
  fd_bincode_uint8_encode(&self->burn_percent, data);
}

void fd_rent_collector_decode(fd_rent_collector_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->epoch, data, dataend);
  fd_epoch_schedule_decode(&self->epoch_schedule, data, dataend, allocf, allocf_arg);
  fd_bincode_double_decode(&self->slots_per_year, data, dataend);
  fd_rent_decode(&self->rent, data, dataend, allocf, allocf_arg);
}
void fd_rent_collector_destroy(fd_rent_collector_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_epoch_schedule_destroy(&self->epoch_schedule, freef, freef_arg);
  fd_rent_destroy(&self->rent, freef, freef_arg);
}

void fd_rent_collector_walk(fd_rent_collector_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_rent_collector", level++);
  fun(&self->epoch, "epoch", 11, "ulong", level + 1);
  fd_epoch_schedule_walk(&self->epoch_schedule, fun, "epoch_schedule", level + 1);
  fun(&self->slots_per_year, "slots_per_year", 5, "double", level + 1);
  fd_rent_walk(&self->rent, fun, "rent", level + 1);
  fun(self, name, 33, "fd_rent_collector", --level);
}
void fd_rent_collector_copy_to(fd_rent_collector_t* to, fd_rent_collector_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_rent_collector_size(from) );
  void const *   ptr = (void const *) enc;
  fd_rent_collector_encode( from, &ptr );
  void *input = (void *) enc;
  fd_rent_collector_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_rent_collector_size(fd_rent_collector_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += fd_epoch_schedule_size(&self->epoch_schedule);
  size += sizeof(double);
  size += fd_rent_size(&self->rent);
  return size;
}

void fd_rent_collector_encode(fd_rent_collector_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->epoch, data);
  fd_epoch_schedule_encode(&self->epoch_schedule, data);
  fd_bincode_double_encode(&self->slots_per_year, data);
  fd_rent_encode(&self->rent, data);
}

void fd_stake_history_entry_decode(fd_stake_history_entry_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->effective, data, dataend);
  fd_bincode_uint64_decode(&self->activating, data, dataend);
  fd_bincode_uint64_decode(&self->deactivating, data, dataend);
}
void fd_stake_history_entry_destroy(fd_stake_history_entry_t* self, fd_free_fun_t freef, void* freef_arg) {
}

void fd_stake_history_entry_walk(fd_stake_history_entry_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_stake_history_entry", level++);
  fun(&self->effective, "effective", 11, "ulong", level + 1);
  fun(&self->activating, "activating", 11, "ulong", level + 1);
  fun(&self->deactivating, "deactivating", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_stake_history_entry", --level);
}
void fd_stake_history_entry_copy_to(fd_stake_history_entry_t* to, fd_stake_history_entry_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_stake_history_entry_size(from) );
  void const *   ptr = (void const *) enc;
  fd_stake_history_entry_encode( from, &ptr );
  void *input = (void *) enc;
  fd_stake_history_entry_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_stake_history_entry_size(fd_stake_history_entry_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  return size;
}

void fd_stake_history_entry_encode(fd_stake_history_entry_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->effective, data);
  fd_bincode_uint64_encode(&self->activating, data);
  fd_bincode_uint64_encode(&self->deactivating, data);
}

void fd_stake_history_epochentry_pair_decode(fd_stake_history_epochentry_pair_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->epoch, data, dataend);
  fd_stake_history_entry_decode(&self->entry, data, dataend, allocf, allocf_arg);
}
void fd_stake_history_epochentry_pair_destroy(fd_stake_history_epochentry_pair_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_stake_history_entry_destroy(&self->entry, freef, freef_arg);
}

void fd_stake_history_epochentry_pair_walk(fd_stake_history_epochentry_pair_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_stake_history_epochentry_pair", level++);
  fun(&self->epoch, "epoch", 11, "ulong", level + 1);
  fd_stake_history_entry_walk(&self->entry, fun, "entry", level + 1);
  fun(self, name, 33, "fd_stake_history_epochentry_pair", --level);
}
void fd_stake_history_epochentry_pair_copy_to(fd_stake_history_epochentry_pair_t* to, fd_stake_history_epochentry_pair_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_stake_history_epochentry_pair_size(from) );
  void const *   ptr = (void const *) enc;
  fd_stake_history_epochentry_pair_encode( from, &ptr );
  void *input = (void *) enc;
  fd_stake_history_epochentry_pair_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_stake_history_epochentry_pair_size(fd_stake_history_epochentry_pair_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += fd_stake_history_entry_size(&self->entry);
  return size;
}

void fd_stake_history_epochentry_pair_encode(fd_stake_history_epochentry_pair_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->epoch, data);
  fd_stake_history_entry_encode(&self->entry, data);
}

void fd_stake_history_decode(fd_stake_history_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->entries_len, data, dataend);
  if (self->entries_len != 0) {
    self->entries = (fd_stake_history_epochentry_pair_t*)(*allocf)(allocf_arg, FD_STAKE_HISTORY_EPOCHENTRY_PAIR_ALIGN, FD_STAKE_HISTORY_EPOCHENTRY_PAIR_FOOTPRINT*self->entries_len);
    for (ulong i = 0; i < self->entries_len; ++i)
      fd_stake_history_epochentry_pair_decode(self->entries + i, data, dataend, allocf, allocf_arg);
  } else
    self->entries = NULL;
}
void fd_stake_history_destroy(fd_stake_history_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->entries) {
    for (ulong i = 0; i < self->entries_len; ++i)
      fd_stake_history_epochentry_pair_destroy(self->entries + i, freef, freef_arg);
    freef(freef_arg, self->entries);
    self->entries = NULL;
  }
}

void fd_stake_history_walk(fd_stake_history_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_stake_history", level++);
  if (self->entries_len != 0) {
    fun(NULL, NULL, 30, "entries", level++);
    for (ulong i = 0; i < self->entries_len; ++i)
      fd_stake_history_epochentry_pair_walk(self->entries + i, fun, "stake_history_epochentry_pair", level + 1);
    fun(NULL, NULL, 31, "entries", --level);
  }
  fun(self, name, 33, "fd_stake_history", --level);
}
void fd_stake_history_copy_to(fd_stake_history_t* to, fd_stake_history_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_stake_history_size(from) );
  void const *   ptr = (void const *) enc;
  fd_stake_history_encode( from, &ptr );
  void *input = (void *) enc;
  fd_stake_history_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_stake_history_size(fd_stake_history_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  for (ulong i = 0; i < self->entries_len; ++i)
    size += fd_stake_history_epochentry_pair_size(self->entries + i);
  return size;
}

void fd_stake_history_encode(fd_stake_history_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->entries_len, data);
  if (self->entries_len != 0) {
    for (ulong i = 0; i < self->entries_len; ++i)
      fd_stake_history_epochentry_pair_encode(self->entries + i, data);
  }
}

void fd_solana_account_decode(fd_solana_account_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->lamports, data, dataend);
  fd_bincode_uint64_decode(&self->data_len, data, dataend);
  if (self->data_len != 0) {
    self->data = (unsigned char*)(*allocf)(allocf_arg, 8, self->data_len);
    fd_bincode_bytes_decode(self->data, self->data_len, data, dataend);
  } else
    self->data = NULL;
  fd_pubkey_decode(&self->owner, data, dataend, allocf, allocf_arg);
  fd_bincode_uint8_decode(&self->executable, data, dataend);
  fd_bincode_uint64_decode(&self->rent_epoch, data, dataend);
}
void fd_solana_account_destroy(fd_solana_account_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->data) {
    freef(freef_arg, self->data);
    self->data = NULL;
  }
  fd_pubkey_destroy(&self->owner, freef, freef_arg);
}

void fd_solana_account_walk(fd_solana_account_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_solana_account", level++);
  fun(&self->lamports, "lamports", 11, "ulong", level + 1);
  fun(self->data, "data", 2, "unsigned char", level + 1);
  fd_pubkey_walk(&self->owner, fun, "owner", level + 1);
  fun(&self->executable, "executable", 9, "uchar", level + 1);
  fun(&self->rent_epoch, "rent_epoch", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_solana_account", --level);
}
void fd_solana_account_copy_to(fd_solana_account_t* to, fd_solana_account_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_solana_account_size(from) );
  void const *   ptr = (void const *) enc;
  fd_solana_account_encode( from, &ptr );
  void *input = (void *) enc;
  fd_solana_account_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_solana_account_size(fd_solana_account_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += self->data_len;
  size += fd_pubkey_size(&self->owner);
  size += sizeof(char);
  size += sizeof(ulong);
  return size;
}

void fd_solana_account_encode(fd_solana_account_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->lamports, data);
  fd_bincode_uint64_encode(&self->data_len, data);
  if (self->data_len != 0) {
    fd_bincode_bytes_encode(self->data, self->data_len, data);
  }
  fd_pubkey_encode(&self->owner, data);
  fd_bincode_uint8_encode(&self->executable, data);
  fd_bincode_uint64_encode(&self->rent_epoch, data);
}

void fd_vote_accounts_pair_decode(fd_vote_accounts_pair_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->key, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->stake, data, dataend);
  fd_solana_account_decode(&self->value, data, dataend, allocf, allocf_arg);
}
void fd_vote_accounts_pair_destroy(fd_vote_accounts_pair_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->key, freef, freef_arg);
  fd_solana_account_destroy(&self->value, freef, freef_arg);
}

void fd_vote_accounts_pair_walk(fd_vote_accounts_pair_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_accounts_pair", level++);
  fd_pubkey_walk(&self->key, fun, "key", level + 1);
  fun(&self->stake, "stake", 11, "ulong", level + 1);
  fd_solana_account_walk(&self->value, fun, "value", level + 1);
  fun(self, name, 33, "fd_vote_accounts_pair", --level);
}
void fd_vote_accounts_pair_copy_to(fd_vote_accounts_pair_t* to, fd_vote_accounts_pair_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_accounts_pair_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_accounts_pair_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_accounts_pair_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_accounts_pair_size(fd_vote_accounts_pair_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->key);
  size += sizeof(ulong);
  size += fd_solana_account_size(&self->value);
  return size;
}

void fd_vote_accounts_pair_encode(fd_vote_accounts_pair_t* self, void const** data) {
  fd_pubkey_encode(&self->key, data);
  fd_bincode_uint64_encode(&self->stake, data);
  fd_solana_account_encode(&self->value, data);
}

void fd_vote_accounts_decode(fd_vote_accounts_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->vote_accounts_len, data, dataend);
  if (self->vote_accounts_len != 0) {
    self->vote_accounts = (fd_vote_accounts_pair_t*)(*allocf)(allocf_arg, FD_VOTE_ACCOUNTS_PAIR_ALIGN, FD_VOTE_ACCOUNTS_PAIR_FOOTPRINT*self->vote_accounts_len);
    for (ulong i = 0; i < self->vote_accounts_len; ++i)
      fd_vote_accounts_pair_decode(self->vote_accounts + i, data, dataend, allocf, allocf_arg);
  } else
    self->vote_accounts = NULL;
}
void fd_vote_accounts_destroy(fd_vote_accounts_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->vote_accounts) {
    for (ulong i = 0; i < self->vote_accounts_len; ++i)
      fd_vote_accounts_pair_destroy(self->vote_accounts + i, freef, freef_arg);
    freef(freef_arg, self->vote_accounts);
    self->vote_accounts = NULL;
  }
}

void fd_vote_accounts_walk(fd_vote_accounts_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_accounts", level++);
  if (self->vote_accounts_len != 0) {
    fun(NULL, NULL, 30, "vote_accounts", level++);
    for (ulong i = 0; i < self->vote_accounts_len; ++i)
      fd_vote_accounts_pair_walk(self->vote_accounts + i, fun, "vote_accounts_pair", level + 1);
    fun(NULL, NULL, 31, "vote_accounts", --level);
  }
  fun(self, name, 33, "fd_vote_accounts", --level);
}
void fd_vote_accounts_copy_to(fd_vote_accounts_t* to, fd_vote_accounts_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_accounts_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_accounts_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_accounts_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_accounts_size(fd_vote_accounts_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  for (ulong i = 0; i < self->vote_accounts_len; ++i)
    size += fd_vote_accounts_pair_size(self->vote_accounts + i);
  return size;
}

void fd_vote_accounts_encode(fd_vote_accounts_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->vote_accounts_len, data);
  if (self->vote_accounts_len != 0) {
    for (ulong i = 0; i < self->vote_accounts_len; ++i)
      fd_vote_accounts_pair_encode(self->vote_accounts + i, data);
  }
}

void fd_delegation_decode(fd_delegation_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->voter_pubkey, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->stake, data, dataend);
  fd_bincode_uint64_decode(&self->activation_epoch, data, dataend);
  fd_bincode_uint64_decode(&self->deactivation_epoch, data, dataend);
  fd_bincode_double_decode(&self->warmup_cooldown_rate, data, dataend);
}
void fd_delegation_destroy(fd_delegation_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->voter_pubkey, freef, freef_arg);
}

void fd_delegation_walk(fd_delegation_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_delegation", level++);
  fd_pubkey_walk(&self->voter_pubkey, fun, "voter_pubkey", level + 1);
  fun(&self->stake, "stake", 11, "ulong", level + 1);
  fun(&self->activation_epoch, "activation_epoch", 11, "ulong", level + 1);
  fun(&self->deactivation_epoch, "deactivation_epoch", 11, "ulong", level + 1);
  fun(&self->warmup_cooldown_rate, "warmup_cooldown_rate", 5, "double", level + 1);
  fun(self, name, 33, "fd_delegation", --level);
}
void fd_delegation_copy_to(fd_delegation_t* to, fd_delegation_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_delegation_size(from) );
  void const *   ptr = (void const *) enc;
  fd_delegation_encode( from, &ptr );
  void *input = (void *) enc;
  fd_delegation_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_delegation_size(fd_delegation_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->voter_pubkey);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(double);
  return size;
}

void fd_delegation_encode(fd_delegation_t* self, void const** data) {
  fd_pubkey_encode(&self->voter_pubkey, data);
  fd_bincode_uint64_encode(&self->stake, data);
  fd_bincode_uint64_encode(&self->activation_epoch, data);
  fd_bincode_uint64_encode(&self->deactivation_epoch, data);
  fd_bincode_double_encode(&self->warmup_cooldown_rate, data);
}

void fd_delegation_pair_decode(fd_delegation_pair_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->key, data, dataend, allocf, allocf_arg);
  fd_delegation_decode(&self->value, data, dataend, allocf, allocf_arg);
}
void fd_delegation_pair_destroy(fd_delegation_pair_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->key, freef, freef_arg);
  fd_delegation_destroy(&self->value, freef, freef_arg);
}

void fd_delegation_pair_walk(fd_delegation_pair_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_delegation_pair", level++);
  fd_pubkey_walk(&self->key, fun, "key", level + 1);
  fd_delegation_walk(&self->value, fun, "value", level + 1);
  fun(self, name, 33, "fd_delegation_pair", --level);
}
void fd_delegation_pair_copy_to(fd_delegation_pair_t* to, fd_delegation_pair_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_delegation_pair_size(from) );
  void const *   ptr = (void const *) enc;
  fd_delegation_pair_encode( from, &ptr );
  void *input = (void *) enc;
  fd_delegation_pair_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_delegation_pair_size(fd_delegation_pair_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->key);
  size += fd_delegation_size(&self->value);
  return size;
}

void fd_delegation_pair_encode(fd_delegation_pair_t* self, void const** data) {
  fd_pubkey_encode(&self->key, data);
  fd_delegation_encode(&self->value, data);
}

void fd_stakes_decode(fd_stakes_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_vote_accounts_decode(&self->vote_accounts, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->stake_delegations_len, data, dataend);
  if (self->stake_delegations_len != 0) {
    self->stake_delegations = (fd_delegation_pair_t*)(*allocf)(allocf_arg, FD_DELEGATION_PAIR_ALIGN, FD_DELEGATION_PAIR_FOOTPRINT*self->stake_delegations_len);
    for (ulong i = 0; i < self->stake_delegations_len; ++i)
      fd_delegation_pair_decode(self->stake_delegations + i, data, dataend, allocf, allocf_arg);
  } else
    self->stake_delegations = NULL;
  fd_bincode_uint64_decode(&self->unused, data, dataend);
  fd_bincode_uint64_decode(&self->epoch, data, dataend);
  fd_stake_history_decode(&self->stake_history, data, dataend, allocf, allocf_arg);
}
void fd_stakes_destroy(fd_stakes_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_vote_accounts_destroy(&self->vote_accounts, freef, freef_arg);
  if (NULL != self->stake_delegations) {
    for (ulong i = 0; i < self->stake_delegations_len; ++i)
      fd_delegation_pair_destroy(self->stake_delegations + i, freef, freef_arg);
    freef(freef_arg, self->stake_delegations);
    self->stake_delegations = NULL;
  }
  fd_stake_history_destroy(&self->stake_history, freef, freef_arg);
}

void fd_stakes_walk(fd_stakes_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_stakes", level++);
  fd_vote_accounts_walk(&self->vote_accounts, fun, "vote_accounts", level + 1);
  if (self->stake_delegations_len != 0) {
    fun(NULL, NULL, 30, "stake_delegations", level++);
    for (ulong i = 0; i < self->stake_delegations_len; ++i)
      fd_delegation_pair_walk(self->stake_delegations + i, fun, "delegation_pair", level + 1);
    fun(NULL, NULL, 31, "stake_delegations", --level);
  }
  fun(&self->unused, "unused", 11, "ulong", level + 1);
  fun(&self->epoch, "epoch", 11, "ulong", level + 1);
  fd_stake_history_walk(&self->stake_history, fun, "stake_history", level + 1);
  fun(self, name, 33, "fd_stakes", --level);
}
void fd_stakes_copy_to(fd_stakes_t* to, fd_stakes_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_stakes_size(from) );
  void const *   ptr = (void const *) enc;
  fd_stakes_encode( from, &ptr );
  void *input = (void *) enc;
  fd_stakes_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_stakes_size(fd_stakes_t* self) {
  ulong size = 0;
  size += fd_vote_accounts_size(&self->vote_accounts);
  size += sizeof(ulong);
  for (ulong i = 0; i < self->stake_delegations_len; ++i)
    size += fd_delegation_pair_size(self->stake_delegations + i);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += fd_stake_history_size(&self->stake_history);
  return size;
}

void fd_stakes_encode(fd_stakes_t* self, void const** data) {
  fd_vote_accounts_encode(&self->vote_accounts, data);
  fd_bincode_uint64_encode(&self->stake_delegations_len, data);
  if (self->stake_delegations_len != 0) {
    for (ulong i = 0; i < self->stake_delegations_len; ++i)
      fd_delegation_pair_encode(self->stake_delegations + i, data);
  }
  fd_bincode_uint64_encode(&self->unused, data);
  fd_bincode_uint64_encode(&self->epoch, data);
  fd_stake_history_encode(&self->stake_history, data);
}

void fd_bank_incremental_snapshot_persistence_decode(fd_bank_incremental_snapshot_persistence_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->full_slot, data, dataend);
  fd_hash_decode(&self->full_hash, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->full_capitalization, data, dataend);
  fd_hash_decode(&self->incremental_hash, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->incremental_capitalization, data, dataend);
}
void fd_bank_incremental_snapshot_persistence_destroy(fd_bank_incremental_snapshot_persistence_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_hash_destroy(&self->full_hash, freef, freef_arg);
  fd_hash_destroy(&self->incremental_hash, freef, freef_arg);
}

void fd_bank_incremental_snapshot_persistence_walk(fd_bank_incremental_snapshot_persistence_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_bank_incremental_snapshot_persistence", level++);
  fun(&self->full_slot, "full_slot", 11, "ulong", level + 1);
  fd_hash_walk(&self->full_hash, fun, "full_hash", level + 1);
  fun(&self->full_capitalization, "full_capitalization", 11, "ulong", level + 1);
  fd_hash_walk(&self->incremental_hash, fun, "incremental_hash", level + 1);
  fun(&self->incremental_capitalization, "incremental_capitalization", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_bank_incremental_snapshot_persistence", --level);
}
void fd_bank_incremental_snapshot_persistence_copy_to(fd_bank_incremental_snapshot_persistence_t* to, fd_bank_incremental_snapshot_persistence_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_bank_incremental_snapshot_persistence_size(from) );
  void const *   ptr = (void const *) enc;
  fd_bank_incremental_snapshot_persistence_encode( from, &ptr );
  void *input = (void *) enc;
  fd_bank_incremental_snapshot_persistence_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_bank_incremental_snapshot_persistence_size(fd_bank_incremental_snapshot_persistence_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += fd_hash_size(&self->full_hash);
  size += sizeof(ulong);
  size += fd_hash_size(&self->incremental_hash);
  size += sizeof(ulong);
  return size;
}

void fd_bank_incremental_snapshot_persistence_encode(fd_bank_incremental_snapshot_persistence_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->full_slot, data);
  fd_hash_encode(&self->full_hash, data);
  fd_bincode_uint64_encode(&self->full_capitalization, data);
  fd_hash_encode(&self->incremental_hash, data);
  fd_bincode_uint64_encode(&self->incremental_capitalization, data);
}

void fd_node_vote_accounts_decode(fd_node_vote_accounts_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->vote_accounts_len, data, dataend);
  if (self->vote_accounts_len != 0) {
    self->vote_accounts = (fd_pubkey_t*)(*allocf)(allocf_arg, FD_PUBKEY_ALIGN, FD_PUBKEY_FOOTPRINT*self->vote_accounts_len);
    for (ulong i = 0; i < self->vote_accounts_len; ++i)
      fd_pubkey_decode(self->vote_accounts + i, data, dataend, allocf, allocf_arg);
  } else
    self->vote_accounts = NULL;
  fd_bincode_uint64_decode(&self->total_stake, data, dataend);
}
void fd_node_vote_accounts_destroy(fd_node_vote_accounts_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->vote_accounts) {
    for (ulong i = 0; i < self->vote_accounts_len; ++i)
      fd_pubkey_destroy(self->vote_accounts + i, freef, freef_arg);
    freef(freef_arg, self->vote_accounts);
    self->vote_accounts = NULL;
  }
}

void fd_node_vote_accounts_walk(fd_node_vote_accounts_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_node_vote_accounts", level++);
  if (self->vote_accounts_len != 0) {
    fun(NULL, NULL, 30, "vote_accounts", level++);
    for (ulong i = 0; i < self->vote_accounts_len; ++i)
      fd_pubkey_walk(self->vote_accounts + i, fun, "pubkey", level + 1);
    fun(NULL, NULL, 31, "vote_accounts", --level);
  }
  fun(&self->total_stake, "total_stake", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_node_vote_accounts", --level);
}
void fd_node_vote_accounts_copy_to(fd_node_vote_accounts_t* to, fd_node_vote_accounts_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_node_vote_accounts_size(from) );
  void const *   ptr = (void const *) enc;
  fd_node_vote_accounts_encode( from, &ptr );
  void *input = (void *) enc;
  fd_node_vote_accounts_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_node_vote_accounts_size(fd_node_vote_accounts_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  for (ulong i = 0; i < self->vote_accounts_len; ++i)
    size += fd_pubkey_size(self->vote_accounts + i);
  size += sizeof(ulong);
  return size;
}

void fd_node_vote_accounts_encode(fd_node_vote_accounts_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->vote_accounts_len, data);
  if (self->vote_accounts_len != 0) {
    for (ulong i = 0; i < self->vote_accounts_len; ++i)
      fd_pubkey_encode(self->vote_accounts + i, data);
  }
  fd_bincode_uint64_encode(&self->total_stake, data);
}

void fd_pubkey_node_vote_accounts_pair_decode(fd_pubkey_node_vote_accounts_pair_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->key, data, dataend, allocf, allocf_arg);
  fd_node_vote_accounts_decode(&self->value, data, dataend, allocf, allocf_arg);
}
void fd_pubkey_node_vote_accounts_pair_destroy(fd_pubkey_node_vote_accounts_pair_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->key, freef, freef_arg);
  fd_node_vote_accounts_destroy(&self->value, freef, freef_arg);
}

void fd_pubkey_node_vote_accounts_pair_walk(fd_pubkey_node_vote_accounts_pair_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_pubkey_node_vote_accounts_pair", level++);
  fd_pubkey_walk(&self->key, fun, "key", level + 1);
  fd_node_vote_accounts_walk(&self->value, fun, "value", level + 1);
  fun(self, name, 33, "fd_pubkey_node_vote_accounts_pair", --level);
}
void fd_pubkey_node_vote_accounts_pair_copy_to(fd_pubkey_node_vote_accounts_pair_t* to, fd_pubkey_node_vote_accounts_pair_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_pubkey_node_vote_accounts_pair_size(from) );
  void const *   ptr = (void const *) enc;
  fd_pubkey_node_vote_accounts_pair_encode( from, &ptr );
  void *input = (void *) enc;
  fd_pubkey_node_vote_accounts_pair_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_pubkey_node_vote_accounts_pair_size(fd_pubkey_node_vote_accounts_pair_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->key);
  size += fd_node_vote_accounts_size(&self->value);
  return size;
}

void fd_pubkey_node_vote_accounts_pair_encode(fd_pubkey_node_vote_accounts_pair_t* self, void const** data) {
  fd_pubkey_encode(&self->key, data);
  fd_node_vote_accounts_encode(&self->value, data);
}

void fd_pubkey_pubkey_pair_decode(fd_pubkey_pubkey_pair_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->key, data, dataend, allocf, allocf_arg);
  fd_pubkey_decode(&self->value, data, dataend, allocf, allocf_arg);
}
void fd_pubkey_pubkey_pair_destroy(fd_pubkey_pubkey_pair_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->key, freef, freef_arg);
  fd_pubkey_destroy(&self->value, freef, freef_arg);
}

void fd_pubkey_pubkey_pair_walk(fd_pubkey_pubkey_pair_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_pubkey_pubkey_pair", level++);
  fd_pubkey_walk(&self->key, fun, "key", level + 1);
  fd_pubkey_walk(&self->value, fun, "value", level + 1);
  fun(self, name, 33, "fd_pubkey_pubkey_pair", --level);
}
void fd_pubkey_pubkey_pair_copy_to(fd_pubkey_pubkey_pair_t* to, fd_pubkey_pubkey_pair_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_pubkey_pubkey_pair_size(from) );
  void const *   ptr = (void const *) enc;
  fd_pubkey_pubkey_pair_encode( from, &ptr );
  void *input = (void *) enc;
  fd_pubkey_pubkey_pair_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_pubkey_pubkey_pair_size(fd_pubkey_pubkey_pair_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->key);
  size += fd_pubkey_size(&self->value);
  return size;
}

void fd_pubkey_pubkey_pair_encode(fd_pubkey_pubkey_pair_t* self, void const** data) {
  fd_pubkey_encode(&self->key, data);
  fd_pubkey_encode(&self->value, data);
}

void fd_epoch_stakes_decode(fd_epoch_stakes_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_stakes_decode(&self->stakes, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->total_stake, data, dataend);
  fd_bincode_uint64_decode(&self->node_id_to_vote_accounts_len, data, dataend);
  if (self->node_id_to_vote_accounts_len != 0) {
    self->node_id_to_vote_accounts = (fd_pubkey_node_vote_accounts_pair_t*)(*allocf)(allocf_arg, FD_PUBKEY_NODE_VOTE_ACCOUNTS_PAIR_ALIGN, FD_PUBKEY_NODE_VOTE_ACCOUNTS_PAIR_FOOTPRINT*self->node_id_to_vote_accounts_len);
    for (ulong i = 0; i < self->node_id_to_vote_accounts_len; ++i)
      fd_pubkey_node_vote_accounts_pair_decode(self->node_id_to_vote_accounts + i, data, dataend, allocf, allocf_arg);
  } else
    self->node_id_to_vote_accounts = NULL;
  fd_bincode_uint64_decode(&self->epoch_authorized_voters_len, data, dataend);
  if (self->epoch_authorized_voters_len != 0) {
    self->epoch_authorized_voters = (fd_pubkey_pubkey_pair_t*)(*allocf)(allocf_arg, FD_PUBKEY_PUBKEY_PAIR_ALIGN, FD_PUBKEY_PUBKEY_PAIR_FOOTPRINT*self->epoch_authorized_voters_len);
    for (ulong i = 0; i < self->epoch_authorized_voters_len; ++i)
      fd_pubkey_pubkey_pair_decode(self->epoch_authorized_voters + i, data, dataend, allocf, allocf_arg);
  } else
    self->epoch_authorized_voters = NULL;
}
void fd_epoch_stakes_destroy(fd_epoch_stakes_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_stakes_destroy(&self->stakes, freef, freef_arg);
  if (NULL != self->node_id_to_vote_accounts) {
    for (ulong i = 0; i < self->node_id_to_vote_accounts_len; ++i)
      fd_pubkey_node_vote_accounts_pair_destroy(self->node_id_to_vote_accounts + i, freef, freef_arg);
    freef(freef_arg, self->node_id_to_vote_accounts);
    self->node_id_to_vote_accounts = NULL;
  }
  if (NULL != self->epoch_authorized_voters) {
    for (ulong i = 0; i < self->epoch_authorized_voters_len; ++i)
      fd_pubkey_pubkey_pair_destroy(self->epoch_authorized_voters + i, freef, freef_arg);
    freef(freef_arg, self->epoch_authorized_voters);
    self->epoch_authorized_voters = NULL;
  }
}

void fd_epoch_stakes_walk(fd_epoch_stakes_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_epoch_stakes", level++);
  fd_stakes_walk(&self->stakes, fun, "stakes", level + 1);
  fun(&self->total_stake, "total_stake", 11, "ulong", level + 1);
  if (self->node_id_to_vote_accounts_len != 0) {
    fun(NULL, NULL, 30, "node_id_to_vote_accounts", level++);
    for (ulong i = 0; i < self->node_id_to_vote_accounts_len; ++i)
      fd_pubkey_node_vote_accounts_pair_walk(self->node_id_to_vote_accounts + i, fun, "pubkey_node_vote_accounts_pair", level + 1);
    fun(NULL, NULL, 31, "node_id_to_vote_accounts", --level);
  }
  if (self->epoch_authorized_voters_len != 0) {
    fun(NULL, NULL, 30, "epoch_authorized_voters", level++);
    for (ulong i = 0; i < self->epoch_authorized_voters_len; ++i)
      fd_pubkey_pubkey_pair_walk(self->epoch_authorized_voters + i, fun, "pubkey_pubkey_pair", level + 1);
    fun(NULL, NULL, 31, "epoch_authorized_voters", --level);
  }
  fun(self, name, 33, "fd_epoch_stakes", --level);
}
void fd_epoch_stakes_copy_to(fd_epoch_stakes_t* to, fd_epoch_stakes_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_epoch_stakes_size(from) );
  void const *   ptr = (void const *) enc;
  fd_epoch_stakes_encode( from, &ptr );
  void *input = (void *) enc;
  fd_epoch_stakes_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_epoch_stakes_size(fd_epoch_stakes_t* self) {
  ulong size = 0;
  size += fd_stakes_size(&self->stakes);
  size += sizeof(ulong);
  size += sizeof(ulong);
  for (ulong i = 0; i < self->node_id_to_vote_accounts_len; ++i)
    size += fd_pubkey_node_vote_accounts_pair_size(self->node_id_to_vote_accounts + i);
  size += sizeof(ulong);
  for (ulong i = 0; i < self->epoch_authorized_voters_len; ++i)
    size += fd_pubkey_pubkey_pair_size(self->epoch_authorized_voters + i);
  return size;
}

void fd_epoch_stakes_encode(fd_epoch_stakes_t* self, void const** data) {
  fd_stakes_encode(&self->stakes, data);
  fd_bincode_uint64_encode(&self->total_stake, data);
  fd_bincode_uint64_encode(&self->node_id_to_vote_accounts_len, data);
  if (self->node_id_to_vote_accounts_len != 0) {
    for (ulong i = 0; i < self->node_id_to_vote_accounts_len; ++i)
      fd_pubkey_node_vote_accounts_pair_encode(self->node_id_to_vote_accounts + i, data);
  }
  fd_bincode_uint64_encode(&self->epoch_authorized_voters_len, data);
  if (self->epoch_authorized_voters_len != 0) {
    for (ulong i = 0; i < self->epoch_authorized_voters_len; ++i)
      fd_pubkey_pubkey_pair_encode(self->epoch_authorized_voters + i, data);
  }
}

void fd_epoch_epoch_stakes_pair_decode(fd_epoch_epoch_stakes_pair_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->key, data, dataend);
  fd_epoch_stakes_decode(&self->value, data, dataend, allocf, allocf_arg);
}
void fd_epoch_epoch_stakes_pair_destroy(fd_epoch_epoch_stakes_pair_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_epoch_stakes_destroy(&self->value, freef, freef_arg);
}

void fd_epoch_epoch_stakes_pair_walk(fd_epoch_epoch_stakes_pair_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_epoch_epoch_stakes_pair", level++);
  fun(&self->key, "key", 11, "ulong", level + 1);
  fd_epoch_stakes_walk(&self->value, fun, "value", level + 1);
  fun(self, name, 33, "fd_epoch_epoch_stakes_pair", --level);
}
void fd_epoch_epoch_stakes_pair_copy_to(fd_epoch_epoch_stakes_pair_t* to, fd_epoch_epoch_stakes_pair_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_epoch_epoch_stakes_pair_size(from) );
  void const *   ptr = (void const *) enc;
  fd_epoch_epoch_stakes_pair_encode( from, &ptr );
  void *input = (void *) enc;
  fd_epoch_epoch_stakes_pair_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_epoch_epoch_stakes_pair_size(fd_epoch_epoch_stakes_pair_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += fd_epoch_stakes_size(&self->value);
  return size;
}

void fd_epoch_epoch_stakes_pair_encode(fd_epoch_epoch_stakes_pair_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->key, data);
  fd_epoch_stakes_encode(&self->value, data);
}

void fd_pubkey_u64_pair_decode(fd_pubkey_u64_pair_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->_0, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->_1, data, dataend);
}
void fd_pubkey_u64_pair_destroy(fd_pubkey_u64_pair_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->_0, freef, freef_arg);
}

void fd_pubkey_u64_pair_walk(fd_pubkey_u64_pair_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_pubkey_u64_pair", level++);
  fd_pubkey_walk(&self->_0, fun, "_0", level + 1);
  fun(&self->_1, "_1", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_pubkey_u64_pair", --level);
}
void fd_pubkey_u64_pair_copy_to(fd_pubkey_u64_pair_t* to, fd_pubkey_u64_pair_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_pubkey_u64_pair_size(from) );
  void const *   ptr = (void const *) enc;
  fd_pubkey_u64_pair_encode( from, &ptr );
  void *input = (void *) enc;
  fd_pubkey_u64_pair_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_pubkey_u64_pair_size(fd_pubkey_u64_pair_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->_0);
  size += sizeof(ulong);
  return size;
}

void fd_pubkey_u64_pair_encode(fd_pubkey_u64_pair_t* self, void const** data) {
  fd_pubkey_encode(&self->_0, data);
  fd_bincode_uint64_encode(&self->_1, data);
}

void fd_unused_accounts_decode(fd_unused_accounts_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->unused1_len, data, dataend);
  if (self->unused1_len != 0) {
    self->unused1 = (fd_pubkey_t*)(*allocf)(allocf_arg, FD_PUBKEY_ALIGN, FD_PUBKEY_FOOTPRINT*self->unused1_len);
    for (ulong i = 0; i < self->unused1_len; ++i)
      fd_pubkey_decode(self->unused1 + i, data, dataend, allocf, allocf_arg);
  } else
    self->unused1 = NULL;
  fd_bincode_uint64_decode(&self->unused2_len, data, dataend);
  if (self->unused2_len != 0) {
    self->unused2 = (fd_pubkey_t*)(*allocf)(allocf_arg, FD_PUBKEY_ALIGN, FD_PUBKEY_FOOTPRINT*self->unused2_len);
    for (ulong i = 0; i < self->unused2_len; ++i)
      fd_pubkey_decode(self->unused2 + i, data, dataend, allocf, allocf_arg);
  } else
    self->unused2 = NULL;
  fd_bincode_uint64_decode(&self->unused3_len, data, dataend);
  if (self->unused3_len != 0) {
    self->unused3 = (fd_pubkey_u64_pair_t*)(*allocf)(allocf_arg, FD_PUBKEY_U64_PAIR_ALIGN, FD_PUBKEY_U64_PAIR_FOOTPRINT*self->unused3_len);
    for (ulong i = 0; i < self->unused3_len; ++i)
      fd_pubkey_u64_pair_decode(self->unused3 + i, data, dataend, allocf, allocf_arg);
  } else
    self->unused3 = NULL;
}
void fd_unused_accounts_destroy(fd_unused_accounts_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->unused1) {
    for (ulong i = 0; i < self->unused1_len; ++i)
      fd_pubkey_destroy(self->unused1 + i, freef, freef_arg);
    freef(freef_arg, self->unused1);
    self->unused1 = NULL;
  }
  if (NULL != self->unused2) {
    for (ulong i = 0; i < self->unused2_len; ++i)
      fd_pubkey_destroy(self->unused2 + i, freef, freef_arg);
    freef(freef_arg, self->unused2);
    self->unused2 = NULL;
  }
  if (NULL != self->unused3) {
    for (ulong i = 0; i < self->unused3_len; ++i)
      fd_pubkey_u64_pair_destroy(self->unused3 + i, freef, freef_arg);
    freef(freef_arg, self->unused3);
    self->unused3 = NULL;
  }
}

void fd_unused_accounts_walk(fd_unused_accounts_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_unused_accounts", level++);
  if (self->unused1_len != 0) {
    fun(NULL, NULL, 30, "unused1", level++);
    for (ulong i = 0; i < self->unused1_len; ++i)
      fd_pubkey_walk(self->unused1 + i, fun, "pubkey", level + 1);
    fun(NULL, NULL, 31, "unused1", --level);
  }
  if (self->unused2_len != 0) {
    fun(NULL, NULL, 30, "unused2", level++);
    for (ulong i = 0; i < self->unused2_len; ++i)
      fd_pubkey_walk(self->unused2 + i, fun, "pubkey", level + 1);
    fun(NULL, NULL, 31, "unused2", --level);
  }
  if (self->unused3_len != 0) {
    fun(NULL, NULL, 30, "unused3", level++);
    for (ulong i = 0; i < self->unused3_len; ++i)
      fd_pubkey_u64_pair_walk(self->unused3 + i, fun, "pubkey_u64_pair", level + 1);
    fun(NULL, NULL, 31, "unused3", --level);
  }
  fun(self, name, 33, "fd_unused_accounts", --level);
}
void fd_unused_accounts_copy_to(fd_unused_accounts_t* to, fd_unused_accounts_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_unused_accounts_size(from) );
  void const *   ptr = (void const *) enc;
  fd_unused_accounts_encode( from, &ptr );
  void *input = (void *) enc;
  fd_unused_accounts_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_unused_accounts_size(fd_unused_accounts_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  for (ulong i = 0; i < self->unused1_len; ++i)
    size += fd_pubkey_size(self->unused1 + i);
  size += sizeof(ulong);
  for (ulong i = 0; i < self->unused2_len; ++i)
    size += fd_pubkey_size(self->unused2 + i);
  size += sizeof(ulong);
  for (ulong i = 0; i < self->unused3_len; ++i)
    size += fd_pubkey_u64_pair_size(self->unused3 + i);
  return size;
}

void fd_unused_accounts_encode(fd_unused_accounts_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->unused1_len, data);
  if (self->unused1_len != 0) {
    for (ulong i = 0; i < self->unused1_len; ++i)
      fd_pubkey_encode(self->unused1 + i, data);
  }
  fd_bincode_uint64_encode(&self->unused2_len, data);
  if (self->unused2_len != 0) {
    for (ulong i = 0; i < self->unused2_len; ++i)
      fd_pubkey_encode(self->unused2 + i, data);
  }
  fd_bincode_uint64_encode(&self->unused3_len, data);
  if (self->unused3_len != 0) {
    for (ulong i = 0; i < self->unused3_len; ++i)
      fd_pubkey_u64_pair_encode(self->unused3 + i, data);
  }
}

void fd_deserializable_versioned_bank_decode(fd_deserializable_versioned_bank_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_block_hash_queue_decode(&self->blockhash_queue, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->ancestors_len, data, dataend);
  if (self->ancestors_len != 0) {
    self->ancestors = (fd_slot_pair_t*)(*allocf)(allocf_arg, FD_SLOT_PAIR_ALIGN, FD_SLOT_PAIR_FOOTPRINT*self->ancestors_len);
    for (ulong i = 0; i < self->ancestors_len; ++i)
      fd_slot_pair_decode(self->ancestors + i, data, dataend, allocf, allocf_arg);
  } else
    self->ancestors = NULL;
  fd_hash_decode(&self->hash, data, dataend, allocf, allocf_arg);
  fd_hash_decode(&self->parent_hash, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->parent_slot, data, dataend);
  fd_hard_forks_decode(&self->hard_forks, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->transaction_count, data, dataend);
  fd_bincode_uint64_decode(&self->tick_height, data, dataend);
  fd_bincode_uint64_decode(&self->signature_count, data, dataend);
  fd_bincode_uint64_decode(&self->capitalization, data, dataend);
  fd_bincode_uint64_decode(&self->max_tick_height, data, dataend);
  if (fd_bincode_option_decode(data, dataend)) {
    self->hashes_per_tick = (ulong*)(*allocf)(allocf_arg, 8, sizeof(ulong));
    fd_bincode_uint64_decode(self->hashes_per_tick, data, dataend);
  } else
    self->hashes_per_tick = NULL;
  fd_bincode_uint64_decode(&self->ticks_per_slot, data, dataend);
  fd_bincode_uint128_decode(&self->ns_per_slot, data, dataend);
  fd_bincode_uint64_decode(&self->genesis_creation_time, data, dataend);
  fd_bincode_double_decode(&self->slots_per_year, data, dataend);
  fd_bincode_uint64_decode(&self->accounts_data_len, data, dataend);
  fd_bincode_uint64_decode(&self->slot, data, dataend);
  fd_bincode_uint64_decode(&self->epoch, data, dataend);
  fd_bincode_uint64_decode(&self->block_height, data, dataend);
  fd_pubkey_decode(&self->collector_id, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->collector_fees, data, dataend);
  fd_fee_calculator_decode(&self->fee_calculator, data, dataend, allocf, allocf_arg);
  fd_fee_rate_governor_decode(&self->fee_rate_governor, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->collected_rent, data, dataend);
  fd_rent_collector_decode(&self->rent_collector, data, dataend, allocf, allocf_arg);
  fd_epoch_schedule_decode(&self->epoch_schedule, data, dataend, allocf, allocf_arg);
  fd_inflation_decode(&self->inflation, data, dataend, allocf, allocf_arg);
  fd_stakes_decode(&self->stakes, data, dataend, allocf, allocf_arg);
  fd_unused_accounts_decode(&self->unused_accounts, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->epoch_stakes_len, data, dataend);
  if (self->epoch_stakes_len != 0) {
    self->epoch_stakes = (fd_epoch_epoch_stakes_pair_t*)(*allocf)(allocf_arg, FD_EPOCH_EPOCH_STAKES_PAIR_ALIGN, FD_EPOCH_EPOCH_STAKES_PAIR_FOOTPRINT*self->epoch_stakes_len);
    for (ulong i = 0; i < self->epoch_stakes_len; ++i)
      fd_epoch_epoch_stakes_pair_decode(self->epoch_stakes + i, data, dataend, allocf, allocf_arg);
  } else
    self->epoch_stakes = NULL;
  fd_bincode_uint8_decode((unsigned char *) &self->is_delta, data, dataend);
}
void fd_deserializable_versioned_bank_destroy(fd_deserializable_versioned_bank_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_block_hash_queue_destroy(&self->blockhash_queue, freef, freef_arg);
  if (NULL != self->ancestors) {
    for (ulong i = 0; i < self->ancestors_len; ++i)
      fd_slot_pair_destroy(self->ancestors + i, freef, freef_arg);
    freef(freef_arg, self->ancestors);
    self->ancestors = NULL;
  }
  fd_hash_destroy(&self->hash, freef, freef_arg);
  fd_hash_destroy(&self->parent_hash, freef, freef_arg);
  fd_hard_forks_destroy(&self->hard_forks, freef, freef_arg);
  if (NULL != self->hashes_per_tick) {
    freef(freef_arg, self->hashes_per_tick);
    self->hashes_per_tick = NULL;
  }
  fd_pubkey_destroy(&self->collector_id, freef, freef_arg);
  fd_fee_calculator_destroy(&self->fee_calculator, freef, freef_arg);
  fd_fee_rate_governor_destroy(&self->fee_rate_governor, freef, freef_arg);
  fd_rent_collector_destroy(&self->rent_collector, freef, freef_arg);
  fd_epoch_schedule_destroy(&self->epoch_schedule, freef, freef_arg);
  fd_inflation_destroy(&self->inflation, freef, freef_arg);
  fd_stakes_destroy(&self->stakes, freef, freef_arg);
  fd_unused_accounts_destroy(&self->unused_accounts, freef, freef_arg);
  if (NULL != self->epoch_stakes) {
    for (ulong i = 0; i < self->epoch_stakes_len; ++i)
      fd_epoch_epoch_stakes_pair_destroy(self->epoch_stakes + i, freef, freef_arg);
    freef(freef_arg, self->epoch_stakes);
    self->epoch_stakes = NULL;
  }
}

void fd_deserializable_versioned_bank_walk(fd_deserializable_versioned_bank_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_deserializable_versioned_bank", level++);
  fd_block_hash_queue_walk(&self->blockhash_queue, fun, "blockhash_queue", level + 1);
  if (self->ancestors_len != 0) {
    fun(NULL, NULL, 30, "ancestors", level++);
    for (ulong i = 0; i < self->ancestors_len; ++i)
      fd_slot_pair_walk(self->ancestors + i, fun, "slot_pair", level + 1);
    fun(NULL, NULL, 31, "ancestors", --level);
  }
  fd_hash_walk(&self->hash, fun, "hash", level + 1);
  fd_hash_walk(&self->parent_hash, fun, "parent_hash", level + 1);
  fun(&self->parent_slot, "parent_slot", 11, "ulong", level + 1);
  fd_hard_forks_walk(&self->hard_forks, fun, "hard_forks", level + 1);
  fun(&self->transaction_count, "transaction_count", 11, "ulong", level + 1);
  fun(&self->tick_height, "tick_height", 11, "ulong", level + 1);
  fun(&self->signature_count, "signature_count", 11, "ulong", level + 1);
  fun(&self->capitalization, "capitalization", 11, "ulong", level + 1);
  fun(&self->max_tick_height, "max_tick_height", 11, "ulong", level + 1);
  fun(self->hashes_per_tick, "hashes_per_tick", 11, "ulong", level + 1);
  fun(&self->ticks_per_slot, "ticks_per_slot", 11, "ulong", level + 1);
  fun(&self->ns_per_slot, "ns_per_slot", 8, "uint128", level + 1);
  fun(&self->genesis_creation_time, "genesis_creation_time", 11, "ulong", level + 1);
  fun(&self->slots_per_year, "slots_per_year", 5, "double", level + 1);
  fun(&self->accounts_data_len, "accounts_data_len", 11, "ulong", level + 1);
  fun(&self->slot, "slot", 11, "ulong", level + 1);
  fun(&self->epoch, "epoch", 11, "ulong", level + 1);
  fun(&self->block_height, "block_height", 11, "ulong", level + 1);
  fd_pubkey_walk(&self->collector_id, fun, "collector_id", level + 1);
  fun(&self->collector_fees, "collector_fees", 11, "ulong", level + 1);
  fd_fee_calculator_walk(&self->fee_calculator, fun, "fee_calculator", level + 1);
  fd_fee_rate_governor_walk(&self->fee_rate_governor, fun, "fee_rate_governor", level + 1);
  fun(&self->collected_rent, "collected_rent", 11, "ulong", level + 1);
  fd_rent_collector_walk(&self->rent_collector, fun, "rent_collector", level + 1);
  fd_epoch_schedule_walk(&self->epoch_schedule, fun, "epoch_schedule", level + 1);
  fd_inflation_walk(&self->inflation, fun, "inflation", level + 1);
  fd_stakes_walk(&self->stakes, fun, "stakes", level + 1);
  fd_unused_accounts_walk(&self->unused_accounts, fun, "unused_accounts", level + 1);
  if (self->epoch_stakes_len != 0) {
    fun(NULL, NULL, 30, "epoch_stakes", level++);
    for (ulong i = 0; i < self->epoch_stakes_len; ++i)
      fd_epoch_epoch_stakes_pair_walk(self->epoch_stakes + i, fun, "epoch_epoch_stakes_pair", level + 1);
    fun(NULL, NULL, 31, "epoch_stakes", --level);
  }
  fun(&self->is_delta, "is_delta", 1, "char", level + 1);
  fun(self, name, 33, "fd_deserializable_versioned_bank", --level);
}
void fd_deserializable_versioned_bank_copy_to(fd_deserializable_versioned_bank_t* to, fd_deserializable_versioned_bank_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_deserializable_versioned_bank_size(from) );
  void const *   ptr = (void const *) enc;
  fd_deserializable_versioned_bank_encode( from, &ptr );
  void *input = (void *) enc;
  fd_deserializable_versioned_bank_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_deserializable_versioned_bank_size(fd_deserializable_versioned_bank_t* self) {
  ulong size = 0;
  size += fd_block_hash_queue_size(&self->blockhash_queue);
  size += sizeof(ulong);
  for (ulong i = 0; i < self->ancestors_len; ++i)
    size += fd_slot_pair_size(self->ancestors + i);
  size += fd_hash_size(&self->hash);
  size += fd_hash_size(&self->parent_hash);
  size += sizeof(ulong);
  size += fd_hard_forks_size(&self->hard_forks);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(char);
  if (NULL !=  self->hashes_per_tick) {
    size += sizeof(ulong);
  }
  size += sizeof(ulong);
  size += sizeof(uint128);
  size += sizeof(ulong);
  size += sizeof(double);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += fd_pubkey_size(&self->collector_id);
  size += sizeof(ulong);
  size += fd_fee_calculator_size(&self->fee_calculator);
  size += fd_fee_rate_governor_size(&self->fee_rate_governor);
  size += sizeof(ulong);
  size += fd_rent_collector_size(&self->rent_collector);
  size += fd_epoch_schedule_size(&self->epoch_schedule);
  size += fd_inflation_size(&self->inflation);
  size += fd_stakes_size(&self->stakes);
  size += fd_unused_accounts_size(&self->unused_accounts);
  size += sizeof(ulong);
  for (ulong i = 0; i < self->epoch_stakes_len; ++i)
    size += fd_epoch_epoch_stakes_pair_size(self->epoch_stakes + i);
  size += sizeof(char);
  return size;
}

void fd_deserializable_versioned_bank_encode(fd_deserializable_versioned_bank_t* self, void const** data) {
  fd_block_hash_queue_encode(&self->blockhash_queue, data);
  fd_bincode_uint64_encode(&self->ancestors_len, data);
  if (self->ancestors_len != 0) {
    for (ulong i = 0; i < self->ancestors_len; ++i)
      fd_slot_pair_encode(self->ancestors + i, data);
  }
  fd_hash_encode(&self->hash, data);
  fd_hash_encode(&self->parent_hash, data);
  fd_bincode_uint64_encode(&self->parent_slot, data);
  fd_hard_forks_encode(&self->hard_forks, data);
  fd_bincode_uint64_encode(&self->transaction_count, data);
  fd_bincode_uint64_encode(&self->tick_height, data);
  fd_bincode_uint64_encode(&self->signature_count, data);
  fd_bincode_uint64_encode(&self->capitalization, data);
  fd_bincode_uint64_encode(&self->max_tick_height, data);
  if (self->hashes_per_tick!= NULL) {
    fd_bincode_option_encode(1, data);
    fd_bincode_uint64_encode(self->hashes_per_tick, data);
  } else
    fd_bincode_option_encode(0, data);
  fd_bincode_uint64_encode(&self->ticks_per_slot, data);
  fd_bincode_uint128_encode(&self->ns_per_slot, data);
  fd_bincode_uint64_encode(&self->genesis_creation_time, data);
  fd_bincode_double_encode(&self->slots_per_year, data);
  fd_bincode_uint64_encode(&self->accounts_data_len, data);
  fd_bincode_uint64_encode(&self->slot, data);
  fd_bincode_uint64_encode(&self->epoch, data);
  fd_bincode_uint64_encode(&self->block_height, data);
  fd_pubkey_encode(&self->collector_id, data);
  fd_bincode_uint64_encode(&self->collector_fees, data);
  fd_fee_calculator_encode(&self->fee_calculator, data);
  fd_fee_rate_governor_encode(&self->fee_rate_governor, data);
  fd_bincode_uint64_encode(&self->collected_rent, data);
  fd_rent_collector_encode(&self->rent_collector, data);
  fd_epoch_schedule_encode(&self->epoch_schedule, data);
  fd_inflation_encode(&self->inflation, data);
  fd_stakes_encode(&self->stakes, data);
  fd_unused_accounts_encode(&self->unused_accounts, data);
  fd_bincode_uint64_encode(&self->epoch_stakes_len, data);
  if (self->epoch_stakes_len != 0) {
    for (ulong i = 0; i < self->epoch_stakes_len; ++i)
      fd_epoch_epoch_stakes_pair_encode(self->epoch_stakes + i, data);
  }
  fd_bincode_uint8_encode((unsigned char *) &self->is_delta, data);
}

void fd_serializable_account_storage_entry_decode(fd_serializable_account_storage_entry_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->id, data, dataend);
  fd_bincode_uint64_decode(&self->accounts_current_len, data, dataend);
}
void fd_serializable_account_storage_entry_destroy(fd_serializable_account_storage_entry_t* self, fd_free_fun_t freef, void* freef_arg) {
}

void fd_serializable_account_storage_entry_walk(fd_serializable_account_storage_entry_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_serializable_account_storage_entry", level++);
  fun(&self->id, "id", 11, "ulong", level + 1);
  fun(&self->accounts_current_len, "accounts_current_len", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_serializable_account_storage_entry", --level);
}
void fd_serializable_account_storage_entry_copy_to(fd_serializable_account_storage_entry_t* to, fd_serializable_account_storage_entry_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_serializable_account_storage_entry_size(from) );
  void const *   ptr = (void const *) enc;
  fd_serializable_account_storage_entry_encode( from, &ptr );
  void *input = (void *) enc;
  fd_serializable_account_storage_entry_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_serializable_account_storage_entry_size(fd_serializable_account_storage_entry_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(ulong);
  return size;
}

void fd_serializable_account_storage_entry_encode(fd_serializable_account_storage_entry_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->id, data);
  fd_bincode_uint64_encode(&self->accounts_current_len, data);
}

void fd_bank_hash_stats_decode(fd_bank_hash_stats_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->num_updated_accounts, data, dataend);
  fd_bincode_uint64_decode(&self->num_removed_accounts, data, dataend);
  fd_bincode_uint64_decode(&self->num_lamports_stored, data, dataend);
  fd_bincode_uint64_decode(&self->total_data_len, data, dataend);
  fd_bincode_uint64_decode(&self->num_executable_accounts, data, dataend);
}
void fd_bank_hash_stats_destroy(fd_bank_hash_stats_t* self, fd_free_fun_t freef, void* freef_arg) {
}

void fd_bank_hash_stats_walk(fd_bank_hash_stats_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_bank_hash_stats", level++);
  fun(&self->num_updated_accounts, "num_updated_accounts", 11, "ulong", level + 1);
  fun(&self->num_removed_accounts, "num_removed_accounts", 11, "ulong", level + 1);
  fun(&self->num_lamports_stored, "num_lamports_stored", 11, "ulong", level + 1);
  fun(&self->total_data_len, "total_data_len", 11, "ulong", level + 1);
  fun(&self->num_executable_accounts, "num_executable_accounts", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_bank_hash_stats", --level);
}
void fd_bank_hash_stats_copy_to(fd_bank_hash_stats_t* to, fd_bank_hash_stats_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_bank_hash_stats_size(from) );
  void const *   ptr = (void const *) enc;
  fd_bank_hash_stats_encode( from, &ptr );
  void *input = (void *) enc;
  fd_bank_hash_stats_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_bank_hash_stats_size(fd_bank_hash_stats_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  return size;
}

void fd_bank_hash_stats_encode(fd_bank_hash_stats_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->num_updated_accounts, data);
  fd_bincode_uint64_encode(&self->num_removed_accounts, data);
  fd_bincode_uint64_encode(&self->num_lamports_stored, data);
  fd_bincode_uint64_encode(&self->total_data_len, data);
  fd_bincode_uint64_encode(&self->num_executable_accounts, data);
}

void fd_bank_hash_info_decode(fd_bank_hash_info_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_hash_decode(&self->hash, data, dataend, allocf, allocf_arg);
  fd_hash_decode(&self->snapshot_hash, data, dataend, allocf, allocf_arg);
  fd_bank_hash_stats_decode(&self->stats, data, dataend, allocf, allocf_arg);
}
void fd_bank_hash_info_destroy(fd_bank_hash_info_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_hash_destroy(&self->hash, freef, freef_arg);
  fd_hash_destroy(&self->snapshot_hash, freef, freef_arg);
  fd_bank_hash_stats_destroy(&self->stats, freef, freef_arg);
}

void fd_bank_hash_info_walk(fd_bank_hash_info_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_bank_hash_info", level++);
  fd_hash_walk(&self->hash, fun, "hash", level + 1);
  fd_hash_walk(&self->snapshot_hash, fun, "snapshot_hash", level + 1);
  fd_bank_hash_stats_walk(&self->stats, fun, "stats", level + 1);
  fun(self, name, 33, "fd_bank_hash_info", --level);
}
void fd_bank_hash_info_copy_to(fd_bank_hash_info_t* to, fd_bank_hash_info_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_bank_hash_info_size(from) );
  void const *   ptr = (void const *) enc;
  fd_bank_hash_info_encode( from, &ptr );
  void *input = (void *) enc;
  fd_bank_hash_info_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_bank_hash_info_size(fd_bank_hash_info_t* self) {
  ulong size = 0;
  size += fd_hash_size(&self->hash);
  size += fd_hash_size(&self->snapshot_hash);
  size += fd_bank_hash_stats_size(&self->stats);
  return size;
}

void fd_bank_hash_info_encode(fd_bank_hash_info_t* self, void const** data) {
  fd_hash_encode(&self->hash, data);
  fd_hash_encode(&self->snapshot_hash, data);
  fd_bank_hash_stats_encode(&self->stats, data);
}

void fd_slot_account_pair_decode(fd_slot_account_pair_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->slot, data, dataend);
  ulong accounts_len;
  fd_bincode_uint64_decode(&accounts_len, data, dataend);
  void* accounts_mem = (*allocf)(allocf_arg, fd_serializable_account_storage_entry_t_map_align(), fd_serializable_account_storage_entry_t_map_footprint(accounts_len));
  self->accounts_pool = fd_serializable_account_storage_entry_t_map_join(fd_serializable_account_storage_entry_t_map_new(accounts_mem, accounts_len));
  self->accounts_root = NULL;
  for (ulong i = 0; i < accounts_len; ++i) {
    fd_serializable_account_storage_entry_t_mapnode_t* node = fd_serializable_account_storage_entry_t_map_acquire(self->accounts_pool);
    fd_serializable_account_storage_entry_decode(&node->elem, data, dataend, allocf, allocf_arg);
    fd_serializable_account_storage_entry_t_map_insert(self->accounts_pool, &self->accounts_root, node);
  }
}
void fd_slot_account_pair_destroy(fd_slot_account_pair_t* self, fd_free_fun_t freef, void* freef_arg) {
  for ( fd_serializable_account_storage_entry_t_mapnode_t* n = fd_serializable_account_storage_entry_t_map_minimum(self->accounts_pool, self->accounts_root); n; n = fd_serializable_account_storage_entry_t_map_successor(self->accounts_pool, n) ) {
    fd_serializable_account_storage_entry_destroy(&n->elem, freef, freef_arg);
  }
  freef(freef_arg, fd_serializable_account_storage_entry_t_map_delete(fd_serializable_account_storage_entry_t_map_leave(self->accounts_pool)));
  self->accounts_pool = NULL;
  self->accounts_root = NULL;
}

void fd_slot_account_pair_walk(fd_slot_account_pair_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_slot_account_pair", level++);
  fun(&self->slot, "slot", 11, "ulong", level + 1);
  //fun(&self->accounts, "accounts", 17, "map");
  fun(self, name, 33, "fd_slot_account_pair", --level);
}
void fd_slot_account_pair_copy_to(fd_slot_account_pair_t* to, fd_slot_account_pair_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_slot_account_pair_size(from) );
  void const *   ptr = (void const *) enc;
  fd_slot_account_pair_encode( from, &ptr );
  void *input = (void *) enc;
  fd_slot_account_pair_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_slot_account_pair_size(fd_slot_account_pair_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(ulong);
  for ( fd_serializable_account_storage_entry_t_mapnode_t* n = fd_serializable_account_storage_entry_t_map_minimum(self->accounts_pool, self->accounts_root); n; n = fd_serializable_account_storage_entry_t_map_successor(self->accounts_pool, n) ) {
    size += fd_serializable_account_storage_entry_size(&n->elem);
  }
  return size;
}

void fd_slot_account_pair_encode(fd_slot_account_pair_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->slot, data);
  ulong accounts_len = fd_serializable_account_storage_entry_t_map_size(self->accounts_pool, self->accounts_root);
  fd_bincode_uint64_encode(&accounts_len, data);
  for ( fd_serializable_account_storage_entry_t_mapnode_t* n = fd_serializable_account_storage_entry_t_map_minimum(self->accounts_pool, self->accounts_root); n; n = fd_serializable_account_storage_entry_t_map_successor(self->accounts_pool, n) ) {
    fd_serializable_account_storage_entry_encode(&n->elem, data);
  }
}

void fd_slot_map_pair_decode(fd_slot_map_pair_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->slot, data, dataend);
  fd_hash_decode(&self->hash, data, dataend, allocf, allocf_arg);
}
void fd_slot_map_pair_destroy(fd_slot_map_pair_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_hash_destroy(&self->hash, freef, freef_arg);
}

void fd_slot_map_pair_walk(fd_slot_map_pair_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_slot_map_pair", level++);
  fun(&self->slot, "slot", 11, "ulong", level + 1);
  fd_hash_walk(&self->hash, fun, "hash", level + 1);
  fun(self, name, 33, "fd_slot_map_pair", --level);
}
void fd_slot_map_pair_copy_to(fd_slot_map_pair_t* to, fd_slot_map_pair_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_slot_map_pair_size(from) );
  void const *   ptr = (void const *) enc;
  fd_slot_map_pair_encode( from, &ptr );
  void *input = (void *) enc;
  fd_slot_map_pair_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_slot_map_pair_size(fd_slot_map_pair_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += fd_hash_size(&self->hash);
  return size;
}

void fd_slot_map_pair_encode(fd_slot_map_pair_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->slot, data);
  fd_hash_encode(&self->hash, data);
}

void fd_solana_accounts_db_fields_decode(fd_solana_accounts_db_fields_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  ulong storages_len;
  fd_bincode_uint64_decode(&storages_len, data, dataend);
  void* storages_mem = (*allocf)(allocf_arg, fd_slot_account_pair_t_map_align(), fd_slot_account_pair_t_map_footprint(storages_len));
  self->storages_pool = fd_slot_account_pair_t_map_join(fd_slot_account_pair_t_map_new(storages_mem, storages_len));
  self->storages_root = NULL;
  for (ulong i = 0; i < storages_len; ++i) {
    fd_slot_account_pair_t_mapnode_t* node = fd_slot_account_pair_t_map_acquire(self->storages_pool);
    fd_slot_account_pair_decode(&node->elem, data, dataend, allocf, allocf_arg);
    fd_slot_account_pair_t_map_insert(self->storages_pool, &self->storages_root, node);
  }
  fd_bincode_uint64_decode(&self->version, data, dataend);
  fd_bincode_uint64_decode(&self->slot, data, dataend);
  fd_bank_hash_info_decode(&self->bank_hash_info, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->historical_roots_len, data, dataend);
  if (self->historical_roots_len != 0) {
    self->historical_roots = (ulong*)(*allocf)(allocf_arg, 8UL, sizeof(ulong)*self->historical_roots_len);
    for (ulong i = 0; i < self->historical_roots_len; ++i)
      fd_bincode_uint64_decode(self->historical_roots + i, data, dataend);
  } else
    self->historical_roots = NULL;
  fd_bincode_uint64_decode(&self->historical_roots_with_hash_len, data, dataend);
  if (self->historical_roots_with_hash_len != 0) {
    self->historical_roots_with_hash = (fd_slot_map_pair_t*)(*allocf)(allocf_arg, FD_SLOT_MAP_PAIR_ALIGN, FD_SLOT_MAP_PAIR_FOOTPRINT*self->historical_roots_with_hash_len);
    for (ulong i = 0; i < self->historical_roots_with_hash_len; ++i)
      fd_slot_map_pair_decode(self->historical_roots_with_hash + i, data, dataend, allocf, allocf_arg);
  } else
    self->historical_roots_with_hash = NULL;
}
void fd_solana_accounts_db_fields_destroy(fd_solana_accounts_db_fields_t* self, fd_free_fun_t freef, void* freef_arg) {
  for ( fd_slot_account_pair_t_mapnode_t* n = fd_slot_account_pair_t_map_minimum(self->storages_pool, self->storages_root); n; n = fd_slot_account_pair_t_map_successor(self->storages_pool, n) ) {
    fd_slot_account_pair_destroy(&n->elem, freef, freef_arg);
  }
  freef(freef_arg, fd_slot_account_pair_t_map_delete(fd_slot_account_pair_t_map_leave(self->storages_pool)));
  self->storages_pool = NULL;
  self->storages_root = NULL;
  fd_bank_hash_info_destroy(&self->bank_hash_info, freef, freef_arg);
  if (NULL != self->historical_roots) {
    freef(freef_arg, self->historical_roots);
    self->historical_roots = NULL;
  }
  if (NULL != self->historical_roots_with_hash) {
    for (ulong i = 0; i < self->historical_roots_with_hash_len; ++i)
      fd_slot_map_pair_destroy(self->historical_roots_with_hash + i, freef, freef_arg);
    freef(freef_arg, self->historical_roots_with_hash);
    self->historical_roots_with_hash = NULL;
  }
}

void fd_solana_accounts_db_fields_walk(fd_solana_accounts_db_fields_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_solana_accounts_db_fields", level++);
  //fun(&self->storages, "storages", 17, "map");
  fun(&self->version, "version", 11, "ulong", level + 1);
  fun(&self->slot, "slot", 11, "ulong", level + 1);
  fd_bank_hash_info_walk(&self->bank_hash_info, fun, "bank_hash_info", level + 1);
  if (self->historical_roots_len != 0) {
    fun(NULL, NULL, 30, "historical_roots", level++);
    for (ulong i = 0; i < self->historical_roots_len; ++i)
      fun(self->historical_roots + i, "historical_roots", 11, "ulong", level + 1);
    fun(NULL, NULL, 31, "historical_roots", --level);
  }
  if (self->historical_roots_with_hash_len != 0) {
    fun(NULL, NULL, 30, "historical_roots_with_hash", level++);
    for (ulong i = 0; i < self->historical_roots_with_hash_len; ++i)
      fd_slot_map_pair_walk(self->historical_roots_with_hash + i, fun, "slot_map_pair", level + 1);
    fun(NULL, NULL, 31, "historical_roots_with_hash", --level);
  }
  fun(self, name, 33, "fd_solana_accounts_db_fields", --level);
}
void fd_solana_accounts_db_fields_copy_to(fd_solana_accounts_db_fields_t* to, fd_solana_accounts_db_fields_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_solana_accounts_db_fields_size(from) );
  void const *   ptr = (void const *) enc;
  fd_solana_accounts_db_fields_encode( from, &ptr );
  void *input = (void *) enc;
  fd_solana_accounts_db_fields_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_solana_accounts_db_fields_size(fd_solana_accounts_db_fields_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  for ( fd_slot_account_pair_t_mapnode_t* n = fd_slot_account_pair_t_map_minimum(self->storages_pool, self->storages_root); n; n = fd_slot_account_pair_t_map_successor(self->storages_pool, n) ) {
    size += fd_slot_account_pair_size(&n->elem);
  }
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += fd_bank_hash_info_size(&self->bank_hash_info);
  size += sizeof(ulong);
  size += self->historical_roots_len * sizeof(ulong);
  size += sizeof(ulong);
  for (ulong i = 0; i < self->historical_roots_with_hash_len; ++i)
    size += fd_slot_map_pair_size(self->historical_roots_with_hash + i);
  return size;
}

void fd_solana_accounts_db_fields_encode(fd_solana_accounts_db_fields_t* self, void const** data) {
  ulong storages_len = fd_slot_account_pair_t_map_size(self->storages_pool, self->storages_root);
  fd_bincode_uint64_encode(&storages_len, data);
  for ( fd_slot_account_pair_t_mapnode_t* n = fd_slot_account_pair_t_map_minimum(self->storages_pool, self->storages_root); n; n = fd_slot_account_pair_t_map_successor(self->storages_pool, n) ) {
    fd_slot_account_pair_encode(&n->elem, data);
  }
  fd_bincode_uint64_encode(&self->version, data);
  fd_bincode_uint64_encode(&self->slot, data);
  fd_bank_hash_info_encode(&self->bank_hash_info, data);
  fd_bincode_uint64_encode(&self->historical_roots_len, data);
  if (self->historical_roots_len != 0) {
    for (ulong i = 0; i < self->historical_roots_len; ++i)
      fd_bincode_uint64_encode(self->historical_roots + i, data);
  }
  fd_bincode_uint64_encode(&self->historical_roots_with_hash_len, data);
  if (self->historical_roots_with_hash_len != 0) {
    for (ulong i = 0; i < self->historical_roots_with_hash_len; ++i)
      fd_slot_map_pair_encode(self->historical_roots_with_hash + i, data);
  }
}

void fd_solana_manifest_decode(fd_solana_manifest_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_deserializable_versioned_bank_decode(&self->bank, data, dataend, allocf, allocf_arg);
  fd_solana_accounts_db_fields_decode(&self->accounts_db, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->lamports_per_signature, data, dataend);
}
void fd_solana_manifest_destroy(fd_solana_manifest_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_deserializable_versioned_bank_destroy(&self->bank, freef, freef_arg);
  fd_solana_accounts_db_fields_destroy(&self->accounts_db, freef, freef_arg);
}

void fd_solana_manifest_walk(fd_solana_manifest_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_solana_manifest", level++);
  fd_deserializable_versioned_bank_walk(&self->bank, fun, "bank", level + 1);
  fd_solana_accounts_db_fields_walk(&self->accounts_db, fun, "accounts_db", level + 1);
  fun(&self->lamports_per_signature, "lamports_per_signature", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_solana_manifest", --level);
}
void fd_solana_manifest_copy_to(fd_solana_manifest_t* to, fd_solana_manifest_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_solana_manifest_size(from) );
  void const *   ptr = (void const *) enc;
  fd_solana_manifest_encode( from, &ptr );
  void *input = (void *) enc;
  fd_solana_manifest_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_solana_manifest_size(fd_solana_manifest_t* self) {
  ulong size = 0;
  size += fd_deserializable_versioned_bank_size(&self->bank);
  size += fd_solana_accounts_db_fields_size(&self->accounts_db);
  size += sizeof(ulong);
  return size;
}

void fd_solana_manifest_encode(fd_solana_manifest_t* self, void const** data) {
  fd_deserializable_versioned_bank_encode(&self->bank, data);
  fd_solana_accounts_db_fields_encode(&self->accounts_db, data);
  fd_bincode_uint64_encode(&self->lamports_per_signature, data);
}

void fd_rust_duration_decode(fd_rust_duration_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->seconds, data, dataend);
  fd_bincode_uint32_decode(&self->nanoseconds, data, dataend);
}
void fd_rust_duration_destroy(fd_rust_duration_t* self, fd_free_fun_t freef, void* freef_arg) {
}

void fd_rust_duration_walk(fd_rust_duration_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_rust_duration", level++);
  fun(&self->seconds, "seconds", 11, "ulong", level + 1);
  fun(&self->nanoseconds, "nanoseconds", 7, "uint", level + 1);
  fun(self, name, 33, "fd_rust_duration", --level);
}
void fd_rust_duration_copy_to(fd_rust_duration_t* to, fd_rust_duration_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_rust_duration_size(from) );
  void const *   ptr = (void const *) enc;
  fd_rust_duration_encode( from, &ptr );
  void *input = (void *) enc;
  fd_rust_duration_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_rust_duration_size(fd_rust_duration_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(uint);
  return size;
}

void fd_rust_duration_encode(fd_rust_duration_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->seconds, data);
  fd_bincode_uint32_encode(&self->nanoseconds, data);
}

void fd_poh_config_decode(fd_poh_config_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_rust_duration_decode(&self->target_tick_duration, data, dataend, allocf, allocf_arg);
  if (fd_bincode_option_decode(data, dataend)) {
    self->target_tick_count = (ulong*)(*allocf)(allocf_arg, 8, sizeof(ulong));
    fd_bincode_uint64_decode(self->target_tick_count, data, dataend);
  } else
    self->target_tick_count = NULL;
  if (fd_bincode_option_decode(data, dataend)) {
    self->hashes_per_tick = (ulong*)(*allocf)(allocf_arg, 8, sizeof(ulong));
    fd_bincode_uint64_decode(self->hashes_per_tick, data, dataend);
  } else
    self->hashes_per_tick = NULL;
}
void fd_poh_config_destroy(fd_poh_config_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_rust_duration_destroy(&self->target_tick_duration, freef, freef_arg);
  if (NULL != self->target_tick_count) {
    freef(freef_arg, self->target_tick_count);
    self->target_tick_count = NULL;
  }
  if (NULL != self->hashes_per_tick) {
    freef(freef_arg, self->hashes_per_tick);
    self->hashes_per_tick = NULL;
  }
}

void fd_poh_config_walk(fd_poh_config_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_poh_config", level++);
  fd_rust_duration_walk(&self->target_tick_duration, fun, "target_tick_duration", level + 1);
  fun(self->target_tick_count, "target_tick_count", 11, "ulong", level + 1);
  fun(self->hashes_per_tick, "hashes_per_tick", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_poh_config", --level);
}
void fd_poh_config_copy_to(fd_poh_config_t* to, fd_poh_config_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_poh_config_size(from) );
  void const *   ptr = (void const *) enc;
  fd_poh_config_encode( from, &ptr );
  void *input = (void *) enc;
  fd_poh_config_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_poh_config_size(fd_poh_config_t* self) {
  ulong size = 0;
  size += fd_rust_duration_size(&self->target_tick_duration);
  size += sizeof(char);
  if (NULL !=  self->target_tick_count) {
    size += sizeof(ulong);
  }
  size += sizeof(char);
  if (NULL !=  self->hashes_per_tick) {
    size += sizeof(ulong);
  }
  return size;
}

void fd_poh_config_encode(fd_poh_config_t* self, void const** data) {
  fd_rust_duration_encode(&self->target_tick_duration, data);
  if (self->target_tick_count!= NULL) {
    fd_bincode_option_encode(1, data);
    fd_bincode_uint64_encode(self->target_tick_count, data);
  } else
    fd_bincode_option_encode(0, data);
  if (self->hashes_per_tick!= NULL) {
    fd_bincode_option_encode(1, data);
    fd_bincode_uint64_encode(self->hashes_per_tick, data);
  } else
    fd_bincode_option_encode(0, data);
}

void fd_string_pubkey_pair_decode(fd_string_pubkey_pair_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  ulong slen;
  fd_bincode_uint64_decode(&slen, data, dataend);
  self->string = (char*)(*allocf)(allocf_arg, 1, slen + 1);
  fd_bincode_bytes_decode((uchar *) self->string, slen, data, dataend);
  self->string[slen] = '\0';
  fd_pubkey_decode(&self->pubkey, data, dataend, allocf, allocf_arg);
}
void fd_string_pubkey_pair_destroy(fd_string_pubkey_pair_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->string) {
    freef(freef_arg, self->string);
    self->string = NULL;
  }
  fd_pubkey_destroy(&self->pubkey, freef, freef_arg);
}

void fd_string_pubkey_pair_walk(fd_string_pubkey_pair_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_string_pubkey_pair", level++);
  fun(self->string, "string", 2, "char*", level + 1);
  fd_pubkey_walk(&self->pubkey, fun, "pubkey", level + 1);
  fun(self, name, 33, "fd_string_pubkey_pair", --level);
}
void fd_string_pubkey_pair_copy_to(fd_string_pubkey_pair_t* to, fd_string_pubkey_pair_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_string_pubkey_pair_size(from) );
  void const *   ptr = (void const *) enc;
  fd_string_pubkey_pair_encode( from, &ptr );
  void *input = (void *) enc;
  fd_string_pubkey_pair_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_string_pubkey_pair_size(fd_string_pubkey_pair_t* self) {
  ulong size = 0;
  size += sizeof(ulong) + strlen(self->string);
  size += fd_pubkey_size(&self->pubkey);
  return size;
}

void fd_string_pubkey_pair_encode(fd_string_pubkey_pair_t* self, void const** data) {
  ulong slen = strlen((char *) self->string);
  fd_bincode_uint64_encode(&slen, data);
  fd_bincode_bytes_encode((uchar *) self->string, slen, data);
  fd_pubkey_encode(&self->pubkey, data);
}

void fd_pubkey_account_pair_decode(fd_pubkey_account_pair_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->key, data, dataend, allocf, allocf_arg);
  fd_solana_account_decode(&self->account, data, dataend, allocf, allocf_arg);
}
void fd_pubkey_account_pair_destroy(fd_pubkey_account_pair_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->key, freef, freef_arg);
  fd_solana_account_destroy(&self->account, freef, freef_arg);
}

void fd_pubkey_account_pair_walk(fd_pubkey_account_pair_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_pubkey_account_pair", level++);
  fd_pubkey_walk(&self->key, fun, "key", level + 1);
  fd_solana_account_walk(&self->account, fun, "account", level + 1);
  fun(self, name, 33, "fd_pubkey_account_pair", --level);
}
void fd_pubkey_account_pair_copy_to(fd_pubkey_account_pair_t* to, fd_pubkey_account_pair_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_pubkey_account_pair_size(from) );
  void const *   ptr = (void const *) enc;
  fd_pubkey_account_pair_encode( from, &ptr );
  void *input = (void *) enc;
  fd_pubkey_account_pair_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_pubkey_account_pair_size(fd_pubkey_account_pair_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->key);
  size += fd_solana_account_size(&self->account);
  return size;
}

void fd_pubkey_account_pair_encode(fd_pubkey_account_pair_t* self, void const** data) {
  fd_pubkey_encode(&self->key, data);
  fd_solana_account_encode(&self->account, data);
}

void fd_genesis_solana_decode(fd_genesis_solana_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->creation_time, data, dataend);
  fd_bincode_uint64_decode(&self->accounts_len, data, dataend);
  if (self->accounts_len != 0) {
    self->accounts = (fd_pubkey_account_pair_t*)(*allocf)(allocf_arg, FD_PUBKEY_ACCOUNT_PAIR_ALIGN, FD_PUBKEY_ACCOUNT_PAIR_FOOTPRINT*self->accounts_len);
    for (ulong i = 0; i < self->accounts_len; ++i)
      fd_pubkey_account_pair_decode(self->accounts + i, data, dataend, allocf, allocf_arg);
  } else
    self->accounts = NULL;
  fd_bincode_uint64_decode(&self->native_instruction_processors_len, data, dataend);
  if (self->native_instruction_processors_len != 0) {
    self->native_instruction_processors = (fd_string_pubkey_pair_t*)(*allocf)(allocf_arg, FD_STRING_PUBKEY_PAIR_ALIGN, FD_STRING_PUBKEY_PAIR_FOOTPRINT*self->native_instruction_processors_len);
    for (ulong i = 0; i < self->native_instruction_processors_len; ++i)
      fd_string_pubkey_pair_decode(self->native_instruction_processors + i, data, dataend, allocf, allocf_arg);
  } else
    self->native_instruction_processors = NULL;
  fd_bincode_uint64_decode(&self->rewards_pools_len, data, dataend);
  if (self->rewards_pools_len != 0) {
    self->rewards_pools = (fd_pubkey_account_pair_t*)(*allocf)(allocf_arg, FD_PUBKEY_ACCOUNT_PAIR_ALIGN, FD_PUBKEY_ACCOUNT_PAIR_FOOTPRINT*self->rewards_pools_len);
    for (ulong i = 0; i < self->rewards_pools_len; ++i)
      fd_pubkey_account_pair_decode(self->rewards_pools + i, data, dataend, allocf, allocf_arg);
  } else
    self->rewards_pools = NULL;
  fd_bincode_uint64_decode(&self->ticks_per_slot, data, dataend);
  fd_bincode_uint64_decode(&self->unused, data, dataend);
  fd_poh_config_decode(&self->poh_config, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->__backwards_compat_with_v0_23, data, dataend);
  fd_fee_rate_governor_decode(&self->fee_rate_governor, data, dataend, allocf, allocf_arg);
  fd_rent_decode(&self->rent, data, dataend, allocf, allocf_arg);
  fd_inflation_decode(&self->inflation, data, dataend, allocf, allocf_arg);
  fd_epoch_schedule_decode(&self->epoch_schedule, data, dataend, allocf, allocf_arg);
  fd_bincode_uint32_decode(&self->cluster_type, data, dataend);
}
void fd_genesis_solana_destroy(fd_genesis_solana_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->accounts) {
    for (ulong i = 0; i < self->accounts_len; ++i)
      fd_pubkey_account_pair_destroy(self->accounts + i, freef, freef_arg);
    freef(freef_arg, self->accounts);
    self->accounts = NULL;
  }
  if (NULL != self->native_instruction_processors) {
    for (ulong i = 0; i < self->native_instruction_processors_len; ++i)
      fd_string_pubkey_pair_destroy(self->native_instruction_processors + i, freef, freef_arg);
    freef(freef_arg, self->native_instruction_processors);
    self->native_instruction_processors = NULL;
  }
  if (NULL != self->rewards_pools) {
    for (ulong i = 0; i < self->rewards_pools_len; ++i)
      fd_pubkey_account_pair_destroy(self->rewards_pools + i, freef, freef_arg);
    freef(freef_arg, self->rewards_pools);
    self->rewards_pools = NULL;
  }
  fd_poh_config_destroy(&self->poh_config, freef, freef_arg);
  fd_fee_rate_governor_destroy(&self->fee_rate_governor, freef, freef_arg);
  fd_rent_destroy(&self->rent, freef, freef_arg);
  fd_inflation_destroy(&self->inflation, freef, freef_arg);
  fd_epoch_schedule_destroy(&self->epoch_schedule, freef, freef_arg);
}

void fd_genesis_solana_walk(fd_genesis_solana_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_genesis_solana", level++);
  fun(&self->creation_time, "creation_time", 11, "ulong", level + 1);
  if (self->accounts_len != 0) {
    fun(NULL, NULL, 30, "accounts", level++);
    for (ulong i = 0; i < self->accounts_len; ++i)
      fd_pubkey_account_pair_walk(self->accounts + i, fun, "pubkey_account_pair", level + 1);
    fun(NULL, NULL, 31, "accounts", --level);
  }
  if (self->native_instruction_processors_len != 0) {
    fun(NULL, NULL, 30, "native_instruction_processors", level++);
    for (ulong i = 0; i < self->native_instruction_processors_len; ++i)
      fd_string_pubkey_pair_walk(self->native_instruction_processors + i, fun, "string_pubkey_pair", level + 1);
    fun(NULL, NULL, 31, "native_instruction_processors", --level);
  }
  if (self->rewards_pools_len != 0) {
    fun(NULL, NULL, 30, "rewards_pools", level++);
    for (ulong i = 0; i < self->rewards_pools_len; ++i)
      fd_pubkey_account_pair_walk(self->rewards_pools + i, fun, "pubkey_account_pair", level + 1);
    fun(NULL, NULL, 31, "rewards_pools", --level);
  }
  fun(&self->ticks_per_slot, "ticks_per_slot", 11, "ulong", level + 1);
  fun(&self->unused, "unused", 11, "ulong", level + 1);
  fd_poh_config_walk(&self->poh_config, fun, "poh_config", level + 1);
  fun(&self->__backwards_compat_with_v0_23, "__backwards_compat_with_v0_23", 11, "ulong", level + 1);
  fd_fee_rate_governor_walk(&self->fee_rate_governor, fun, "fee_rate_governor", level + 1);
  fd_rent_walk(&self->rent, fun, "rent", level + 1);
  fd_inflation_walk(&self->inflation, fun, "inflation", level + 1);
  fd_epoch_schedule_walk(&self->epoch_schedule, fun, "epoch_schedule", level + 1);
  fun(&self->cluster_type, "cluster_type", 7, "uint", level + 1);
  fun(self, name, 33, "fd_genesis_solana", --level);
}
void fd_genesis_solana_copy_to(fd_genesis_solana_t* to, fd_genesis_solana_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_genesis_solana_size(from) );
  void const *   ptr = (void const *) enc;
  fd_genesis_solana_encode( from, &ptr );
  void *input = (void *) enc;
  fd_genesis_solana_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_genesis_solana_size(fd_genesis_solana_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(ulong);
  for (ulong i = 0; i < self->accounts_len; ++i)
    size += fd_pubkey_account_pair_size(self->accounts + i);
  size += sizeof(ulong);
  for (ulong i = 0; i < self->native_instruction_processors_len; ++i)
    size += fd_string_pubkey_pair_size(self->native_instruction_processors + i);
  size += sizeof(ulong);
  for (ulong i = 0; i < self->rewards_pools_len; ++i)
    size += fd_pubkey_account_pair_size(self->rewards_pools + i);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += fd_poh_config_size(&self->poh_config);
  size += sizeof(ulong);
  size += fd_fee_rate_governor_size(&self->fee_rate_governor);
  size += fd_rent_size(&self->rent);
  size += fd_inflation_size(&self->inflation);
  size += fd_epoch_schedule_size(&self->epoch_schedule);
  size += sizeof(uint);
  return size;
}

void fd_genesis_solana_encode(fd_genesis_solana_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->creation_time, data);
  fd_bincode_uint64_encode(&self->accounts_len, data);
  if (self->accounts_len != 0) {
    for (ulong i = 0; i < self->accounts_len; ++i)
      fd_pubkey_account_pair_encode(self->accounts + i, data);
  }
  fd_bincode_uint64_encode(&self->native_instruction_processors_len, data);
  if (self->native_instruction_processors_len != 0) {
    for (ulong i = 0; i < self->native_instruction_processors_len; ++i)
      fd_string_pubkey_pair_encode(self->native_instruction_processors + i, data);
  }
  fd_bincode_uint64_encode(&self->rewards_pools_len, data);
  if (self->rewards_pools_len != 0) {
    for (ulong i = 0; i < self->rewards_pools_len; ++i)
      fd_pubkey_account_pair_encode(self->rewards_pools + i, data);
  }
  fd_bincode_uint64_encode(&self->ticks_per_slot, data);
  fd_bincode_uint64_encode(&self->unused, data);
  fd_poh_config_encode(&self->poh_config, data);
  fd_bincode_uint64_encode(&self->__backwards_compat_with_v0_23, data);
  fd_fee_rate_governor_encode(&self->fee_rate_governor, data);
  fd_rent_encode(&self->rent, data);
  fd_inflation_encode(&self->inflation, data);
  fd_epoch_schedule_encode(&self->epoch_schedule, data);
  fd_bincode_uint32_encode(&self->cluster_type, data);
}

void fd_secp256k1_signature_offsets_decode(fd_secp256k1_signature_offsets_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint16_decode(&self->signature_offset, data, dataend);
  fd_bincode_uint8_decode(&self->signature_instruction_index, data, dataend);
  fd_bincode_uint16_decode(&self->eth_address_offset, data, dataend);
  fd_bincode_uint8_decode(&self->eth_address_instruction_index, data, dataend);
  fd_bincode_uint16_decode(&self->message_data_offset, data, dataend);
  fd_bincode_uint16_decode(&self->message_data_size, data, dataend);
  fd_bincode_uint8_decode(&self->message_instruction_index, data, dataend);
}
void fd_secp256k1_signature_offsets_destroy(fd_secp256k1_signature_offsets_t* self, fd_free_fun_t freef, void* freef_arg) {
}

void fd_secp256k1_signature_offsets_walk(fd_secp256k1_signature_offsets_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_secp256k1_signature_offsets", level++);
  fun(&self->signature_offset, "signature_offset", 12, "ushort", level + 1);
  fun(&self->signature_instruction_index, "signature_instruction_index", 9, "uchar", level + 1);
  fun(&self->eth_address_offset, "eth_address_offset", 12, "ushort", level + 1);
  fun(&self->eth_address_instruction_index, "eth_address_instruction_index", 9, "uchar", level + 1);
  fun(&self->message_data_offset, "message_data_offset", 12, "ushort", level + 1);
  fun(&self->message_data_size, "message_data_size", 12, "ushort", level + 1);
  fun(&self->message_instruction_index, "message_instruction_index", 9, "uchar", level + 1);
  fun(self, name, 33, "fd_secp256k1_signature_offsets", --level);
}
void fd_secp256k1_signature_offsets_copy_to(fd_secp256k1_signature_offsets_t* to, fd_secp256k1_signature_offsets_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_secp256k1_signature_offsets_size(from) );
  void const *   ptr = (void const *) enc;
  fd_secp256k1_signature_offsets_encode( from, &ptr );
  void *input = (void *) enc;
  fd_secp256k1_signature_offsets_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_secp256k1_signature_offsets_size(fd_secp256k1_signature_offsets_t* self) {
  ulong size = 0;
  size += sizeof(ushort);
  size += sizeof(char);
  size += sizeof(ushort);
  size += sizeof(char);
  size += sizeof(ushort);
  size += sizeof(ushort);
  size += sizeof(char);
  return size;
}

void fd_secp256k1_signature_offsets_encode(fd_secp256k1_signature_offsets_t* self, void const** data) {
  fd_bincode_uint16_encode(&self->signature_offset, data);
  fd_bincode_uint8_encode(&self->signature_instruction_index, data);
  fd_bincode_uint16_encode(&self->eth_address_offset, data);
  fd_bincode_uint8_encode(&self->eth_address_instruction_index, data);
  fd_bincode_uint16_encode(&self->message_data_offset, data);
  fd_bincode_uint16_encode(&self->message_data_size, data);
  fd_bincode_uint8_encode(&self->message_instruction_index, data);
}

void fd_sol_sysvar_clock_decode(fd_sol_sysvar_clock_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->slot, data, dataend);
  fd_bincode_uint64_decode((unsigned long *) &self->epoch_start_timestamp, data, dataend);
  fd_bincode_uint64_decode(&self->epoch, data, dataend);
  fd_bincode_uint64_decode(&self->leader_schedule_epoch, data, dataend);
  fd_bincode_uint64_decode((unsigned long *) &self->unix_timestamp, data, dataend);
}
void fd_sol_sysvar_clock_destroy(fd_sol_sysvar_clock_t* self, fd_free_fun_t freef, void* freef_arg) {
}

void fd_sol_sysvar_clock_walk(fd_sol_sysvar_clock_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_sol_sysvar_clock", level++);
  fun(&self->slot, "slot", 11, "ulong", level + 1);
  fun(&self->epoch_start_timestamp, "epoch_start_timestamp", 6, "long", level + 1);
  fun(&self->epoch, "epoch", 11, "ulong", level + 1);
  fun(&self->leader_schedule_epoch, "leader_schedule_epoch", 11, "ulong", level + 1);
  fun(&self->unix_timestamp, "unix_timestamp", 6, "long", level + 1);
  fun(self, name, 33, "fd_sol_sysvar_clock", --level);
}
void fd_sol_sysvar_clock_copy_to(fd_sol_sysvar_clock_t* to, fd_sol_sysvar_clock_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_sol_sysvar_clock_size(from) );
  void const *   ptr = (void const *) enc;
  fd_sol_sysvar_clock_encode( from, &ptr );
  void *input = (void *) enc;
  fd_sol_sysvar_clock_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_sol_sysvar_clock_size(fd_sol_sysvar_clock_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(long);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(long);
  return size;
}

void fd_sol_sysvar_clock_encode(fd_sol_sysvar_clock_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->slot, data);
  fd_bincode_uint64_encode((unsigned long *) &self->epoch_start_timestamp, data);
  fd_bincode_uint64_encode(&self->epoch, data);
  fd_bincode_uint64_encode(&self->leader_schedule_epoch, data);
  fd_bincode_uint64_encode((unsigned long *) &self->unix_timestamp, data);
}

void fd_vote_lockout_decode(fd_vote_lockout_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->slot, data, dataend);
  fd_bincode_uint32_decode(&self->confirmation_count, data, dataend);
}
void fd_vote_lockout_destroy(fd_vote_lockout_t* self, fd_free_fun_t freef, void* freef_arg) {
}

void fd_vote_lockout_walk(fd_vote_lockout_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_lockout", level++);
  fun(&self->slot, "slot", 11, "ulong", level + 1);
  fun(&self->confirmation_count, "confirmation_count", 7, "uint", level + 1);
  fun(self, name, 33, "fd_vote_lockout", --level);
}
void fd_vote_lockout_copy_to(fd_vote_lockout_t* to, fd_vote_lockout_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_lockout_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_lockout_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_lockout_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_lockout_size(fd_vote_lockout_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(uint);
  return size;
}

void fd_vote_lockout_encode(fd_vote_lockout_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->slot, data);
  fd_bincode_uint32_encode(&self->confirmation_count, data);
}

void fd_compact_vote_lockout_decode(fd_compact_vote_lockout_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_decode_varint(&self->slot, data, dataend);
  fd_bincode_uint8_decode(&self->confirmation_count, data, dataend);
}
void fd_compact_vote_lockout_destroy(fd_compact_vote_lockout_t* self, fd_free_fun_t freef, void* freef_arg) {
}

void fd_compact_vote_lockout_walk(fd_compact_vote_lockout_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_compact_vote_lockout", level++);
  fun(&self->slot, "slot", 11, "ulong", level + 1);
  fun(&self->confirmation_count, "confirmation_count", 9, "uchar", level + 1);
  fun(self, name, 33, "fd_compact_vote_lockout", --level);
}
void fd_compact_vote_lockout_copy_to(fd_compact_vote_lockout_t* to, fd_compact_vote_lockout_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_compact_vote_lockout_size(from) );
  void const *   ptr = (void const *) enc;
  fd_compact_vote_lockout_encode( from, &ptr );
  void *input = (void *) enc;
  fd_compact_vote_lockout_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_compact_vote_lockout_size(fd_compact_vote_lockout_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(char);
  return size;
}

void fd_compact_vote_lockout_encode(fd_compact_vote_lockout_t* self, void const** data) {
  fd_encode_varint(self->slot, (uchar **) data);
  fd_bincode_uint8_encode(&self->confirmation_count, data);
}

void fd_vote_authorized_voter_decode(fd_vote_authorized_voter_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->epoch, data, dataend);
  fd_pubkey_decode(&self->pubkey, data, dataend, allocf, allocf_arg);
}
void fd_vote_authorized_voter_destroy(fd_vote_authorized_voter_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->pubkey, freef, freef_arg);
}

void fd_vote_authorized_voter_walk(fd_vote_authorized_voter_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_authorized_voter", level++);
  fun(&self->epoch, "epoch", 11, "ulong", level + 1);
  fd_pubkey_walk(&self->pubkey, fun, "pubkey", level + 1);
  fun(self, name, 33, "fd_vote_authorized_voter", --level);
}
void fd_vote_authorized_voter_copy_to(fd_vote_authorized_voter_t* to, fd_vote_authorized_voter_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_authorized_voter_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_authorized_voter_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_authorized_voter_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_authorized_voter_size(fd_vote_authorized_voter_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += fd_pubkey_size(&self->pubkey);
  return size;
}

void fd_vote_authorized_voter_encode(fd_vote_authorized_voter_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->epoch, data);
  fd_pubkey_encode(&self->pubkey, data);
}

void fd_vote_prior_voter_decode(fd_vote_prior_voter_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->pubkey, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->epoch_start, data, dataend);
  fd_bincode_uint64_decode(&self->epoch_end, data, dataend);
}
void fd_vote_prior_voter_destroy(fd_vote_prior_voter_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->pubkey, freef, freef_arg);
}

void fd_vote_prior_voter_walk(fd_vote_prior_voter_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_prior_voter", level++);
  fd_pubkey_walk(&self->pubkey, fun, "pubkey", level + 1);
  fun(&self->epoch_start, "epoch_start", 11, "ulong", level + 1);
  fun(&self->epoch_end, "epoch_end", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_vote_prior_voter", --level);
}
void fd_vote_prior_voter_copy_to(fd_vote_prior_voter_t* to, fd_vote_prior_voter_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_prior_voter_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_prior_voter_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_prior_voter_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_prior_voter_size(fd_vote_prior_voter_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->pubkey);
  size += sizeof(ulong);
  size += sizeof(ulong);
  return size;
}

void fd_vote_prior_voter_encode(fd_vote_prior_voter_t* self, void const** data) {
  fd_pubkey_encode(&self->pubkey, data);
  fd_bincode_uint64_encode(&self->epoch_start, data);
  fd_bincode_uint64_encode(&self->epoch_end, data);
}

void fd_vote_prior_voter_0_23_5_decode(fd_vote_prior_voter_0_23_5_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->pubkey, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->epoch_start, data, dataend);
  fd_bincode_uint64_decode(&self->epoch_end, data, dataend);
  fd_bincode_uint64_decode(&self->slot, data, dataend);
}
void fd_vote_prior_voter_0_23_5_destroy(fd_vote_prior_voter_0_23_5_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->pubkey, freef, freef_arg);
}

void fd_vote_prior_voter_0_23_5_walk(fd_vote_prior_voter_0_23_5_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_prior_voter_0_23_5", level++);
  fd_pubkey_walk(&self->pubkey, fun, "pubkey", level + 1);
  fun(&self->epoch_start, "epoch_start", 11, "ulong", level + 1);
  fun(&self->epoch_end, "epoch_end", 11, "ulong", level + 1);
  fun(&self->slot, "slot", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_vote_prior_voter_0_23_5", --level);
}
void fd_vote_prior_voter_0_23_5_copy_to(fd_vote_prior_voter_0_23_5_t* to, fd_vote_prior_voter_0_23_5_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_prior_voter_0_23_5_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_prior_voter_0_23_5_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_prior_voter_0_23_5_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_prior_voter_0_23_5_size(fd_vote_prior_voter_0_23_5_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->pubkey);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  return size;
}

void fd_vote_prior_voter_0_23_5_encode(fd_vote_prior_voter_0_23_5_t* self, void const** data) {
  fd_pubkey_encode(&self->pubkey, data);
  fd_bincode_uint64_encode(&self->epoch_start, data);
  fd_bincode_uint64_encode(&self->epoch_end, data);
  fd_bincode_uint64_encode(&self->slot, data);
}

void fd_vote_epoch_credits_decode(fd_vote_epoch_credits_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->epoch, data, dataend);
  fd_bincode_uint64_decode(&self->credits, data, dataend);
  fd_bincode_uint64_decode(&self->prev_credits, data, dataend);
}
void fd_vote_epoch_credits_destroy(fd_vote_epoch_credits_t* self, fd_free_fun_t freef, void* freef_arg) {
}

void fd_vote_epoch_credits_walk(fd_vote_epoch_credits_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_epoch_credits", level++);
  fun(&self->epoch, "epoch", 11, "ulong", level + 1);
  fun(&self->credits, "credits", 11, "ulong", level + 1);
  fun(&self->prev_credits, "prev_credits", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_vote_epoch_credits", --level);
}
void fd_vote_epoch_credits_copy_to(fd_vote_epoch_credits_t* to, fd_vote_epoch_credits_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_epoch_credits_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_epoch_credits_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_epoch_credits_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_epoch_credits_size(fd_vote_epoch_credits_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  return size;
}

void fd_vote_epoch_credits_encode(fd_vote_epoch_credits_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->epoch, data);
  fd_bincode_uint64_encode(&self->credits, data);
  fd_bincode_uint64_encode(&self->prev_credits, data);
}

void fd_vote_historical_authorized_voter_decode(fd_vote_historical_authorized_voter_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->epoch, data, dataend);
  fd_pubkey_decode(&self->pubkey, data, dataend, allocf, allocf_arg);
}
void fd_vote_historical_authorized_voter_destroy(fd_vote_historical_authorized_voter_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->pubkey, freef, freef_arg);
}

void fd_vote_historical_authorized_voter_walk(fd_vote_historical_authorized_voter_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_historical_authorized_voter", level++);
  fun(&self->epoch, "epoch", 11, "ulong", level + 1);
  fd_pubkey_walk(&self->pubkey, fun, "pubkey", level + 1);
  fun(self, name, 33, "fd_vote_historical_authorized_voter", --level);
}
void fd_vote_historical_authorized_voter_copy_to(fd_vote_historical_authorized_voter_t* to, fd_vote_historical_authorized_voter_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_historical_authorized_voter_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_historical_authorized_voter_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_historical_authorized_voter_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_historical_authorized_voter_size(fd_vote_historical_authorized_voter_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += fd_pubkey_size(&self->pubkey);
  return size;
}

void fd_vote_historical_authorized_voter_encode(fd_vote_historical_authorized_voter_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->epoch, data);
  fd_pubkey_encode(&self->pubkey, data);
}

void fd_vote_block_timestamp_decode(fd_vote_block_timestamp_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->slot, data, dataend);
  fd_bincode_uint64_decode(&self->timestamp, data, dataend);
}
void fd_vote_block_timestamp_destroy(fd_vote_block_timestamp_t* self, fd_free_fun_t freef, void* freef_arg) {
}

void fd_vote_block_timestamp_walk(fd_vote_block_timestamp_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_block_timestamp", level++);
  fun(&self->slot, "slot", 11, "ulong", level + 1);
  fun(&self->timestamp, "timestamp", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_vote_block_timestamp", --level);
}
void fd_vote_block_timestamp_copy_to(fd_vote_block_timestamp_t* to, fd_vote_block_timestamp_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_block_timestamp_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_block_timestamp_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_block_timestamp_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_block_timestamp_size(fd_vote_block_timestamp_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(ulong);
  return size;
}

void fd_vote_block_timestamp_encode(fd_vote_block_timestamp_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->slot, data);
  fd_bincode_uint64_encode(&self->timestamp, data);
}

void fd_vote_prior_voters_decode(fd_vote_prior_voters_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  self->buf = (fd_vote_prior_voter_t*)(*allocf)(allocf_arg, FD_VOTE_PRIOR_VOTER_ALIGN, FD_VOTE_PRIOR_VOTER_FOOTPRINT*32);
  for (ulong i = 0; i < 32; ++i)
    fd_vote_prior_voter_decode(self->buf + i, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->idx, data, dataend);
  fd_bincode_uint8_decode(&self->is_empty, data, dataend);
}
void fd_vote_prior_voters_destroy(fd_vote_prior_voters_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->buf) {
    for (ulong i = 0; i < 32; ++i)
      fd_vote_prior_voter_destroy(self->buf + i,  freef, freef_arg);
    freef(freef_arg, self->buf);
    self->buf = NULL;
  }
}

void fd_vote_prior_voters_walk(fd_vote_prior_voters_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_prior_voters", level++);
  //  fun(&self->buf, "buf", 15, "array");
  fun(&self->idx, "idx", 11, "ulong", level + 1);
  fun(&self->is_empty, "is_empty", 9, "uchar", level + 1);
  fun(self, name, 33, "fd_vote_prior_voters", --level);
}
void fd_vote_prior_voters_copy_to(fd_vote_prior_voters_t* to, fd_vote_prior_voters_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_prior_voters_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_prior_voters_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_prior_voters_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_prior_voters_size(fd_vote_prior_voters_t* self) {
  ulong size = 0;
  for (ulong i = 0; i < 32; ++i)
    size += fd_vote_prior_voter_size(self->buf + i);
  size += sizeof(ulong);
  size += sizeof(char);
  return size;
}

void fd_vote_prior_voters_encode(fd_vote_prior_voters_t* self, void const** data) {
  for (ulong i = 0; i < 32; ++i)
    fd_vote_prior_voter_encode(self->buf + i, data);
  fd_bincode_uint64_encode(&self->idx, data);
  fd_bincode_uint8_encode(&self->is_empty, data);
}

void fd_vote_prior_voters_0_23_5_decode(fd_vote_prior_voters_0_23_5_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  self->buf = (fd_vote_prior_voter_0_23_5_t*)(*allocf)(allocf_arg, FD_VOTE_PRIOR_VOTER_0_23_5_ALIGN, FD_VOTE_PRIOR_VOTER_0_23_5_FOOTPRINT*32);
  for (ulong i = 0; i < 32; ++i)
    fd_vote_prior_voter_0_23_5_decode(self->buf + i, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->idx, data, dataend);
  fd_bincode_uint8_decode(&self->is_empty, data, dataend);
}
void fd_vote_prior_voters_0_23_5_destroy(fd_vote_prior_voters_0_23_5_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->buf) {
    for (ulong i = 0; i < 32; ++i)
      fd_vote_prior_voter_0_23_5_destroy(self->buf + i,  freef, freef_arg);
    freef(freef_arg, self->buf);
    self->buf = NULL;
  }
}

void fd_vote_prior_voters_0_23_5_walk(fd_vote_prior_voters_0_23_5_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_prior_voters_0_23_5", level++);
  //  fun(&self->buf, "buf", 15, "array");
  fun(&self->idx, "idx", 11, "ulong", level + 1);
  fun(&self->is_empty, "is_empty", 9, "uchar", level + 1);
  fun(self, name, 33, "fd_vote_prior_voters_0_23_5", --level);
}
void fd_vote_prior_voters_0_23_5_copy_to(fd_vote_prior_voters_0_23_5_t* to, fd_vote_prior_voters_0_23_5_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_prior_voters_0_23_5_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_prior_voters_0_23_5_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_prior_voters_0_23_5_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_prior_voters_0_23_5_size(fd_vote_prior_voters_0_23_5_t* self) {
  ulong size = 0;
  for (ulong i = 0; i < 32; ++i)
    size += fd_vote_prior_voter_0_23_5_size(self->buf + i);
  size += sizeof(ulong);
  size += sizeof(char);
  return size;
}

void fd_vote_prior_voters_0_23_5_encode(fd_vote_prior_voters_0_23_5_t* self, void const** data) {
  for (ulong i = 0; i < 32; ++i)
    fd_vote_prior_voter_0_23_5_encode(self->buf + i, data);
  fd_bincode_uint64_encode(&self->idx, data);
  fd_bincode_uint8_encode(&self->is_empty, data);
}

void fd_vote_state_0_23_5_decode(fd_vote_state_0_23_5_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->voting_node, data, dataend, allocf, allocf_arg);
  fd_pubkey_decode(&self->authorized_voter, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->authorized_voter_epoch, data, dataend);
  fd_vote_prior_voters_0_23_5_decode(&self->prior_voters, data, dataend, allocf, allocf_arg);
  fd_pubkey_decode(&self->authorized_withdrawer, data, dataend, allocf, allocf_arg);
  fd_bincode_uint8_decode(&self->commission, data, dataend);
  fd_vec_fd_vote_lockout_t_new(&self->votes);
  ulong votes_len;
  fd_bincode_uint64_decode(&votes_len, data, dataend);
  for (ulong i = 0; i < votes_len; ++i) {
    fd_vote_lockout_t elem;
    fd_vote_lockout_decode(&elem, data, dataend, allocf, allocf_arg);
    fd_vec_fd_vote_lockout_t_push(&self->votes, elem);
  }
  if (fd_bincode_option_decode(data, dataend)) {
    self->saved_root_slot = (ulong*)(*allocf)(allocf_arg, 8, sizeof(ulong));
    fd_bincode_uint64_decode(self->saved_root_slot, data, dataend);
  } else
    self->saved_root_slot = NULL;
  fd_vec_fd_vote_epoch_credits_t_new(&self->epoch_credits);
  ulong epoch_credits_len;
  fd_bincode_uint64_decode(&epoch_credits_len, data, dataend);
  for (ulong i = 0; i < epoch_credits_len; ++i) {
    fd_vote_epoch_credits_t elem;
    fd_vote_epoch_credits_decode(&elem, data, dataend, allocf, allocf_arg);
    fd_vec_fd_vote_epoch_credits_t_push(&self->epoch_credits, elem);
  }
  fd_vote_block_timestamp_decode(&self->latest_timestamp, data, dataend, allocf, allocf_arg);
}
void fd_vote_state_0_23_5_destroy(fd_vote_state_0_23_5_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->voting_node, freef, freef_arg);
  fd_pubkey_destroy(&self->authorized_voter, freef, freef_arg);
  fd_vote_prior_voters_0_23_5_destroy(&self->prior_voters, freef, freef_arg);
  fd_pubkey_destroy(&self->authorized_withdrawer, freef, freef_arg);
  fd_vec_fd_vote_lockout_t_destroy(&self->votes);
  if (NULL != self->saved_root_slot) {
    freef(freef_arg, self->saved_root_slot);
    self->saved_root_slot = NULL;
  }
  fd_vec_fd_vote_epoch_credits_t_destroy(&self->epoch_credits);
  fd_vote_block_timestamp_destroy(&self->latest_timestamp, freef, freef_arg);
}

void fd_vote_state_0_23_5_walk(fd_vote_state_0_23_5_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_state_0_23_5", level++);
  fd_pubkey_walk(&self->voting_node, fun, "voting_node", level + 1);
  fd_pubkey_walk(&self->authorized_voter, fun, "authorized_voter", level + 1);
  fun(&self->authorized_voter_epoch, "authorized_voter_epoch", 11, "ulong", level + 1);
  fd_vote_prior_voters_0_23_5_walk(&self->prior_voters, fun, "prior_voters", level + 1);
  fd_pubkey_walk(&self->authorized_withdrawer, fun, "authorized_withdrawer", level + 1);
  fun(&self->commission, "commission", 9, "uchar", level + 1);
  fun(NULL, NULL, 30, "votes", level++);
  for (ulong i = 0; i < self->votes.cnt; ++i)
    fd_vote_lockout_walk(&self->votes.elems[i], fun, "votes", level + 1);
  fun(NULL, NULL, 31, "votes", --level);
  fun(self->saved_root_slot, "saved_root_slot", 11, "ulong", level + 1);
  fun(NULL, NULL, 30, "epoch_credits", level++);
  for (ulong i = 0; i < self->epoch_credits.cnt; ++i)
    fd_vote_epoch_credits_walk(&self->epoch_credits.elems[i], fun, "epoch_credits", level + 1);
  fun(NULL, NULL, 31, "epoch_credits", --level);
  fd_vote_block_timestamp_walk(&self->latest_timestamp, fun, "latest_timestamp", level + 1);
  fun(self, name, 33, "fd_vote_state_0_23_5", --level);
}
void fd_vote_state_0_23_5_copy_to(fd_vote_state_0_23_5_t* to, fd_vote_state_0_23_5_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_state_0_23_5_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_state_0_23_5_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_state_0_23_5_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_state_0_23_5_size(fd_vote_state_0_23_5_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->voting_node);
  size += fd_pubkey_size(&self->authorized_voter);
  size += sizeof(ulong);
  size += fd_vote_prior_voters_0_23_5_size(&self->prior_voters);
  size += fd_pubkey_size(&self->authorized_withdrawer);
  size += sizeof(char);
  size += sizeof(ulong);
  for (ulong i = 0; i < self->votes.cnt; ++i)
    size += fd_vote_lockout_size(&self->votes.elems[i]);
  size += sizeof(char);
  if (NULL !=  self->saved_root_slot) {
    size += sizeof(ulong);
  }
  size += sizeof(ulong);
  for (ulong i = 0; i < self->epoch_credits.cnt; ++i)
    size += fd_vote_epoch_credits_size(&self->epoch_credits.elems[i]);
  size += fd_vote_block_timestamp_size(&self->latest_timestamp);
  return size;
}

void fd_vote_state_0_23_5_encode(fd_vote_state_0_23_5_t* self, void const** data) {
  fd_pubkey_encode(&self->voting_node, data);
  fd_pubkey_encode(&self->authorized_voter, data);
  fd_bincode_uint64_encode(&self->authorized_voter_epoch, data);
  fd_vote_prior_voters_0_23_5_encode(&self->prior_voters, data);
  fd_pubkey_encode(&self->authorized_withdrawer, data);
  fd_bincode_uint8_encode(&self->commission, data);
  fd_bincode_uint64_encode(&self->votes.cnt, data);
  for (ulong i = 0; i < self->votes.cnt; ++i)
    fd_vote_lockout_encode(&self->votes.elems[i], data);
  if (self->saved_root_slot!= NULL) {
    fd_bincode_option_encode(1, data);
    fd_bincode_uint64_encode(self->saved_root_slot, data);
  } else
    fd_bincode_option_encode(0, data);
  fd_bincode_uint64_encode(&self->epoch_credits.cnt, data);
  for (ulong i = 0; i < self->epoch_credits.cnt; ++i)
    fd_vote_epoch_credits_encode(&self->epoch_credits.elems[i], data);
  fd_vote_block_timestamp_encode(&self->latest_timestamp, data);
}

void fd_vote_state_decode(fd_vote_state_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->voting_node, data, dataend, allocf, allocf_arg);
  fd_pubkey_decode(&self->authorized_withdrawer, data, dataend, allocf, allocf_arg);
  fd_bincode_uint8_decode(&self->commission, data, dataend);
  fd_vec_fd_vote_lockout_t_new(&self->votes);
  ulong votes_len;
  fd_bincode_uint64_decode(&votes_len, data, dataend);
  for (ulong i = 0; i < votes_len; ++i) {
    fd_vote_lockout_t elem;
    fd_vote_lockout_decode(&elem, data, dataend, allocf, allocf_arg);
    fd_vec_fd_vote_lockout_t_push(&self->votes, elem);
  }
  if (fd_bincode_option_decode(data, dataend)) {
    self->saved_root_slot = (ulong*)(*allocf)(allocf_arg, 8, sizeof(ulong));
    fd_bincode_uint64_decode(self->saved_root_slot, data, dataend);
  } else
    self->saved_root_slot = NULL;
  fd_vec_fd_vote_historical_authorized_voter_t_new(&self->authorized_voters);
  ulong authorized_voters_len;
  fd_bincode_uint64_decode(&authorized_voters_len, data, dataend);
  for (ulong i = 0; i < authorized_voters_len; ++i) {
    fd_vote_historical_authorized_voter_t elem;
    fd_vote_historical_authorized_voter_decode(&elem, data, dataend, allocf, allocf_arg);
    fd_vec_fd_vote_historical_authorized_voter_t_push(&self->authorized_voters, elem);
  }
  fd_vote_prior_voters_decode(&self->prior_voters, data, dataend, allocf, allocf_arg);
  fd_vec_fd_vote_epoch_credits_t_new(&self->epoch_credits);
  ulong epoch_credits_len;
  fd_bincode_uint64_decode(&epoch_credits_len, data, dataend);
  for (ulong i = 0; i < epoch_credits_len; ++i) {
    fd_vote_epoch_credits_t elem;
    fd_vote_epoch_credits_decode(&elem, data, dataend, allocf, allocf_arg);
    fd_vec_fd_vote_epoch_credits_t_push(&self->epoch_credits, elem);
  }
  fd_vote_block_timestamp_decode(&self->latest_timestamp, data, dataend, allocf, allocf_arg);
}
void fd_vote_state_destroy(fd_vote_state_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->voting_node, freef, freef_arg);
  fd_pubkey_destroy(&self->authorized_withdrawer, freef, freef_arg);
  fd_vec_fd_vote_lockout_t_destroy(&self->votes);
  if (NULL != self->saved_root_slot) {
    freef(freef_arg, self->saved_root_slot);
    self->saved_root_slot = NULL;
  }
  fd_vec_fd_vote_historical_authorized_voter_t_destroy(&self->authorized_voters);
  fd_vote_prior_voters_destroy(&self->prior_voters, freef, freef_arg);
  fd_vec_fd_vote_epoch_credits_t_destroy(&self->epoch_credits);
  fd_vote_block_timestamp_destroy(&self->latest_timestamp, freef, freef_arg);
}

void fd_vote_state_walk(fd_vote_state_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_state", level++);
  fd_pubkey_walk(&self->voting_node, fun, "voting_node", level + 1);
  fd_pubkey_walk(&self->authorized_withdrawer, fun, "authorized_withdrawer", level + 1);
  fun(&self->commission, "commission", 9, "uchar", level + 1);
  fun(NULL, NULL, 30, "votes", level++);
  for (ulong i = 0; i < self->votes.cnt; ++i)
    fd_vote_lockout_walk(&self->votes.elems[i], fun, "votes", level + 1);
  fun(NULL, NULL, 31, "votes", --level);
  fun(self->saved_root_slot, "saved_root_slot", 11, "ulong", level + 1);
  fun(NULL, NULL, 30, "authorized_voters", level++);
  for (ulong i = 0; i < self->authorized_voters.cnt; ++i)
    fd_vote_historical_authorized_voter_walk(&self->authorized_voters.elems[i], fun, "authorized_voters", level + 1);
  fun(NULL, NULL, 31, "authorized_voters", --level);
  fd_vote_prior_voters_walk(&self->prior_voters, fun, "prior_voters", level + 1);
  fun(NULL, NULL, 30, "epoch_credits", level++);
  for (ulong i = 0; i < self->epoch_credits.cnt; ++i)
    fd_vote_epoch_credits_walk(&self->epoch_credits.elems[i], fun, "epoch_credits", level + 1);
  fun(NULL, NULL, 31, "epoch_credits", --level);
  fd_vote_block_timestamp_walk(&self->latest_timestamp, fun, "latest_timestamp", level + 1);
  fun(self, name, 33, "fd_vote_state", --level);
}
void fd_vote_state_copy_to(fd_vote_state_t* to, fd_vote_state_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_state_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_state_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_state_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_state_size(fd_vote_state_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->voting_node);
  size += fd_pubkey_size(&self->authorized_withdrawer);
  size += sizeof(char);
  size += sizeof(ulong);
  for (ulong i = 0; i < self->votes.cnt; ++i)
    size += fd_vote_lockout_size(&self->votes.elems[i]);
  size += sizeof(char);
  if (NULL !=  self->saved_root_slot) {
    size += sizeof(ulong);
  }
  size += sizeof(ulong);
  for (ulong i = 0; i < self->authorized_voters.cnt; ++i)
    size += fd_vote_historical_authorized_voter_size(&self->authorized_voters.elems[i]);
  size += fd_vote_prior_voters_size(&self->prior_voters);
  size += sizeof(ulong);
  for (ulong i = 0; i < self->epoch_credits.cnt; ++i)
    size += fd_vote_epoch_credits_size(&self->epoch_credits.elems[i]);
  size += fd_vote_block_timestamp_size(&self->latest_timestamp);
  return size;
}

void fd_vote_state_encode(fd_vote_state_t* self, void const** data) {
  fd_pubkey_encode(&self->voting_node, data);
  fd_pubkey_encode(&self->authorized_withdrawer, data);
  fd_bincode_uint8_encode(&self->commission, data);
  fd_bincode_uint64_encode(&self->votes.cnt, data);
  for (ulong i = 0; i < self->votes.cnt; ++i)
    fd_vote_lockout_encode(&self->votes.elems[i], data);
  if (self->saved_root_slot!= NULL) {
    fd_bincode_option_encode(1, data);
    fd_bincode_uint64_encode(self->saved_root_slot, data);
  } else
    fd_bincode_option_encode(0, data);
  fd_bincode_uint64_encode(&self->authorized_voters.cnt, data);
  for (ulong i = 0; i < self->authorized_voters.cnt; ++i)
    fd_vote_historical_authorized_voter_encode(&self->authorized_voters.elems[i], data);
  fd_vote_prior_voters_encode(&self->prior_voters, data);
  fd_bincode_uint64_encode(&self->epoch_credits.cnt, data);
  for (ulong i = 0; i < self->epoch_credits.cnt; ++i)
    fd_vote_epoch_credits_encode(&self->epoch_credits.elems[i], data);
  fd_vote_block_timestamp_encode(&self->latest_timestamp, data);
}

uchar fd_vote_state_versioned_is_v0_23_5(fd_vote_state_versioned_t* self) {
  return self->discriminant == 0;
}
uchar fd_vote_state_versioned_is_current(fd_vote_state_versioned_t* self) {
  return self->discriminant == 1;
}
void fd_vote_state_versioned_inner_decode(fd_vote_state_versioned_inner_t* self, uint discriminant, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  switch (discriminant) {
  case 0: {
    fd_vote_state_0_23_5_decode(&self->v0_23_5, data, dataend, allocf, allocf_arg);
    break;
  }
  case 1: {
    fd_vote_state_decode(&self->current, data, dataend, allocf, allocf_arg);
    break;
  }
  default: FD_LOG_ERR(( "unhandled type"));
  }
}
void fd_vote_state_versioned_decode(fd_vote_state_versioned_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint32_decode(&self->discriminant, data, dataend);
  fd_vote_state_versioned_inner_decode(&self->inner, self->discriminant, data, dataend, allocf, allocf_arg);
}
void fd_vote_state_versioned_inner_destroy(fd_vote_state_versioned_inner_t* self, uint discriminant, fd_free_fun_t freef, void* freef_arg) {
  switch (discriminant) {
  case 0: {
    fd_vote_state_0_23_5_destroy(&self->v0_23_5, freef, freef_arg);
    break;
  }
  case 1: {
    fd_vote_state_destroy(&self->current, freef, freef_arg);
    break;
  }
  default: break; // FD_LOG_ERR(( "unhandled type"));
  }
}
void fd_vote_state_versioned_destroy(fd_vote_state_versioned_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_vote_state_versioned_inner_destroy(&self->inner, self->discriminant, freef, freef_arg);
}

void fd_vote_state_versioned_walk(fd_vote_state_versioned_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_state_versioned", level++);
  // enum fd_vote_block_timestamp_walk(&self->latest_timestamp, fun, "latest_timestamp", level + 1);
  fun(self, name, 33, "fd_vote_state_versioned", --level);
}
void fd_vote_state_versioned_copy_to(fd_vote_state_versioned_t* to, fd_vote_state_versioned_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_state_versioned_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_state_versioned_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_state_versioned_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_state_versioned_size(fd_vote_state_versioned_t* self) {
  ulong size = 0;
  size += sizeof(uint);
  switch (self->discriminant) {
  case 0: {
    size += fd_vote_state_0_23_5_size(&self->inner.v0_23_5);
    break;
  }
  case 1: {
    size += fd_vote_state_size(&self->inner.current);
    break;
  }
  }
  return size;
}

void fd_vote_state_versioned_inner_encode(fd_vote_state_versioned_inner_t* self, uint discriminant, void const** data) {
  switch (discriminant) {
  case 0: {
    fd_vote_state_0_23_5_encode(&self->v0_23_5, data);
    break;
  }
  case 1: {
    fd_vote_state_encode(&self->current, data);
    break;
  }
  }
}
void fd_vote_state_versioned_encode(fd_vote_state_versioned_t* self, void const** data) {
  fd_bincode_uint32_encode(&self->discriminant, data);
  fd_vote_state_versioned_inner_encode(&self->inner, self->discriminant, data);
}

void fd_vote_state_update_decode(fd_vote_state_update_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->lockouts_len, data, dataend);
  if (self->lockouts_len != 0) {
    self->lockouts = (fd_vote_lockout_t*)(*allocf)(allocf_arg, FD_VOTE_LOCKOUT_ALIGN, FD_VOTE_LOCKOUT_FOOTPRINT*self->lockouts_len);
    for (ulong i = 0; i < self->lockouts_len; ++i)
      fd_vote_lockout_decode(self->lockouts + i, data, dataend, allocf, allocf_arg);
  } else
    self->lockouts = NULL;
  if (fd_bincode_option_decode(data, dataend)) {
    self->proposed_root = (ulong*)(*allocf)(allocf_arg, 8, sizeof(ulong));
    fd_bincode_uint64_decode(self->proposed_root, data, dataend);
  } else
    self->proposed_root = NULL;
  fd_hash_decode(&self->hash, data, dataend, allocf, allocf_arg);
  if (fd_bincode_option_decode(data, dataend)) {
    self->timestamp = (ulong*)(*allocf)(allocf_arg, 8, sizeof(ulong));
    fd_bincode_uint64_decode(self->timestamp, data, dataend);
  } else
    self->timestamp = NULL;
}
void fd_vote_state_update_destroy(fd_vote_state_update_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->lockouts) {
    for (ulong i = 0; i < self->lockouts_len; ++i)
      fd_vote_lockout_destroy(self->lockouts + i, freef, freef_arg);
    freef(freef_arg, self->lockouts);
    self->lockouts = NULL;
  }
  if (NULL != self->proposed_root) {
    freef(freef_arg, self->proposed_root);
    self->proposed_root = NULL;
  }
  fd_hash_destroy(&self->hash, freef, freef_arg);
  if (NULL != self->timestamp) {
    freef(freef_arg, self->timestamp);
    self->timestamp = NULL;
  }
}

void fd_vote_state_update_walk(fd_vote_state_update_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_state_update", level++);
  if (self->lockouts_len != 0) {
    fun(NULL, NULL, 30, "lockouts", level++);
    for (ulong i = 0; i < self->lockouts_len; ++i)
      fd_vote_lockout_walk(self->lockouts + i, fun, "vote_lockout", level + 1);
    fun(NULL, NULL, 31, "lockouts", --level);
  }
  fun(self->proposed_root, "proposed_root", 11, "ulong", level + 1);
  fd_hash_walk(&self->hash, fun, "hash", level + 1);
  fun(self->timestamp, "timestamp", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_vote_state_update", --level);
}
void fd_vote_state_update_copy_to(fd_vote_state_update_t* to, fd_vote_state_update_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_state_update_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_state_update_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_state_update_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_state_update_size(fd_vote_state_update_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  for (ulong i = 0; i < self->lockouts_len; ++i)
    size += fd_vote_lockout_size(self->lockouts + i);
  size += sizeof(char);
  if (NULL !=  self->proposed_root) {
    size += sizeof(ulong);
  }
  size += fd_hash_size(&self->hash);
  size += sizeof(char);
  if (NULL !=  self->timestamp) {
    size += sizeof(ulong);
  }
  return size;
}

void fd_vote_state_update_encode(fd_vote_state_update_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->lockouts_len, data);
  if (self->lockouts_len != 0) {
    for (ulong i = 0; i < self->lockouts_len; ++i)
      fd_vote_lockout_encode(self->lockouts + i, data);
  }
  if (self->proposed_root!= NULL) {
    fd_bincode_option_encode(1, data);
    fd_bincode_uint64_encode(self->proposed_root, data);
  } else
    fd_bincode_option_encode(0, data);
  fd_hash_encode(&self->hash, data);
  if (self->timestamp!= NULL) {
    fd_bincode_option_encode(1, data);
    fd_bincode_uint64_encode(self->timestamp, data);
  } else
    fd_bincode_option_encode(0, data);
}

void fd_compact_vote_state_update_decode(fd_compact_vote_state_update_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->proposed_root, data, dataend);
  fd_decode_short_u16(&self->lockouts_len, data, dataend);
  if (self->lockouts_len != 0) {
    self->lockouts = (fd_compact_vote_lockout_t*)(*allocf)(allocf_arg, FD_COMPACT_VOTE_LOCKOUT_ALIGN, FD_COMPACT_VOTE_LOCKOUT_FOOTPRINT*self->lockouts_len);
    for (ulong i = 0; i < self->lockouts_len; ++i)
      fd_compact_vote_lockout_decode(self->lockouts + i, data, dataend, allocf, allocf_arg);
  } else
    self->lockouts = NULL;
  fd_hash_decode(&self->hash, data, dataend, allocf, allocf_arg);
  if (fd_bincode_option_decode(data, dataend)) {
    self->timestamp = (ulong*)(*allocf)(allocf_arg, 8, sizeof(ulong));
    fd_bincode_uint64_decode(self->timestamp, data, dataend);
  } else
    self->timestamp = NULL;
}
void fd_compact_vote_state_update_destroy(fd_compact_vote_state_update_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->lockouts) {
    for (ulong i = 0; i < self->lockouts_len; ++i)
      fd_compact_vote_lockout_destroy(self->lockouts + i, freef, freef_arg);
    freef(freef_arg, self->lockouts);
    self->lockouts = NULL;
  }
  fd_hash_destroy(&self->hash, freef, freef_arg);
  if (NULL != self->timestamp) {
    freef(freef_arg, self->timestamp);
    self->timestamp = NULL;
  }
}

void fd_compact_vote_state_update_walk(fd_compact_vote_state_update_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_compact_vote_state_update", level++);
  fun(&self->proposed_root, "proposed_root", 11, "ulong", level + 1);
  if (self->lockouts_len != 0) {
    fun(NULL, NULL, 30, "lockouts", level++);
    for (ulong i = 0; i < self->lockouts_len; ++i)
      fd_compact_vote_lockout_walk(self->lockouts + i, fun, "compact_vote_lockout", level + 1);
    fun(NULL, NULL, 31, "lockouts", --level);
  }
  fd_hash_walk(&self->hash, fun, "hash", level + 1);
  fun(self->timestamp, "timestamp", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_compact_vote_state_update", --level);
}
void fd_compact_vote_state_update_copy_to(fd_compact_vote_state_update_t* to, fd_compact_vote_state_update_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_compact_vote_state_update_size(from) );
  void const *   ptr = (void const *) enc;
  fd_compact_vote_state_update_encode( from, &ptr );
  void *input = (void *) enc;
  fd_compact_vote_state_update_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_compact_vote_state_update_size(fd_compact_vote_state_update_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(ulong);
  for (ulong i = 0; i < self->lockouts_len; ++i)
    size += fd_compact_vote_lockout_size(self->lockouts + i);
  size += fd_hash_size(&self->hash);
  size += sizeof(char);
  if (NULL !=  self->timestamp) {
    size += sizeof(ulong);
  }
  return size;
}

void fd_compact_vote_state_update_encode(fd_compact_vote_state_update_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->proposed_root, data);
  fd_encode_short_u16(&self->lockouts_len, (void **) data);
  if (self->lockouts_len != 0) {
    for (ulong i = 0; i < self->lockouts_len; ++i)
      fd_compact_vote_lockout_encode(self->lockouts + i, data);
  }
  fd_hash_encode(&self->hash, data);
  if (self->timestamp!= NULL) {
    fd_bincode_option_encode(1, data);
    fd_bincode_uint64_encode(self->timestamp, data);
  } else
    fd_bincode_option_encode(0, data);
}

void fd_slot_history_inner_decode(fd_slot_history_inner_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->blocks_len, data, dataend);
  if (self->blocks_len != 0) {
    self->blocks = (ulong*)(*allocf)(allocf_arg, 8UL, sizeof(ulong)*self->blocks_len);
    for (ulong i = 0; i < self->blocks_len; ++i)
      fd_bincode_uint64_decode(self->blocks + i, data, dataend);
  } else
    self->blocks = NULL;
}
void fd_slot_history_inner_destroy(fd_slot_history_inner_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->blocks) {
    freef(freef_arg, self->blocks);
    self->blocks = NULL;
  }
}

void fd_slot_history_inner_walk(fd_slot_history_inner_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_slot_history_inner", level++);
  if (self->blocks_len != 0) {
    fun(NULL, NULL, 30, "blocks", level++);
    for (ulong i = 0; i < self->blocks_len; ++i)
      fun(self->blocks + i, "blocks", 11, "ulong", level + 1);
    fun(NULL, NULL, 31, "blocks", --level);
  }
  fun(self, name, 33, "fd_slot_history_inner", --level);
}
void fd_slot_history_inner_copy_to(fd_slot_history_inner_t* to, fd_slot_history_inner_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_slot_history_inner_size(from) );
  void const *   ptr = (void const *) enc;
  fd_slot_history_inner_encode( from, &ptr );
  void *input = (void *) enc;
  fd_slot_history_inner_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_slot_history_inner_size(fd_slot_history_inner_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += self->blocks_len * sizeof(ulong);
  return size;
}

void fd_slot_history_inner_encode(fd_slot_history_inner_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->blocks_len, data);
  if (self->blocks_len != 0) {
    for (ulong i = 0; i < self->blocks_len; ++i)
      fd_bincode_uint64_encode(self->blocks + i, data);
  }
}

void fd_slot_history_bitvec_decode(fd_slot_history_bitvec_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  if (fd_bincode_option_decode(data, dataend)) {
    self->bits = (fd_slot_history_inner_t*)(*allocf)(allocf_arg, FD_SLOT_HISTORY_INNER_ALIGN, FD_SLOT_HISTORY_INNER_FOOTPRINT);
    fd_slot_history_inner_decode(self->bits, data, dataend, allocf, allocf_arg);
  } else
    self->bits = NULL;
  fd_bincode_uint64_decode(&self->len, data, dataend);
}
void fd_slot_history_bitvec_destroy(fd_slot_history_bitvec_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->bits) {
    fd_slot_history_inner_destroy(self->bits,  freef, freef_arg);
    freef(freef_arg, self->bits);
    self->bits = NULL;
  }
}

void fd_slot_history_bitvec_walk(fd_slot_history_bitvec_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_slot_history_bitvec", level++);
  // fun(&self->bits, "bits", 16, "option", level + 1);
  fun(&self->len, "len", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_slot_history_bitvec", --level);
}
void fd_slot_history_bitvec_copy_to(fd_slot_history_bitvec_t* to, fd_slot_history_bitvec_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_slot_history_bitvec_size(from) );
  void const *   ptr = (void const *) enc;
  fd_slot_history_bitvec_encode( from, &ptr );
  void *input = (void *) enc;
  fd_slot_history_bitvec_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_slot_history_bitvec_size(fd_slot_history_bitvec_t* self) {
  ulong size = 0;
  size += sizeof(char);
  if (NULL !=  self->bits) {
    size += fd_slot_history_inner_size(self->bits);
  }
  size += sizeof(ulong);
  return size;
}

void fd_slot_history_bitvec_encode(fd_slot_history_bitvec_t* self, void const** data) {
  if (self->bits!= NULL) {
    fd_bincode_option_encode(1, data);
    fd_slot_history_inner_encode(self->bits, data);
  } else
    fd_bincode_option_encode(0, data);
  fd_bincode_uint64_encode(&self->len, data);
}

void fd_slot_history_decode(fd_slot_history_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_slot_history_bitvec_decode(&self->bits, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->next_slot, data, dataend);
}
void fd_slot_history_destroy(fd_slot_history_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_slot_history_bitvec_destroy(&self->bits, freef, freef_arg);
}

void fd_slot_history_walk(fd_slot_history_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_slot_history", level++);
  fd_slot_history_bitvec_walk(&self->bits, fun, "bits", level + 1);
  fun(&self->next_slot, "next_slot", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_slot_history", --level);
}
void fd_slot_history_copy_to(fd_slot_history_t* to, fd_slot_history_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_slot_history_size(from) );
  void const *   ptr = (void const *) enc;
  fd_slot_history_encode( from, &ptr );
  void *input = (void *) enc;
  fd_slot_history_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_slot_history_size(fd_slot_history_t* self) {
  ulong size = 0;
  size += fd_slot_history_bitvec_size(&self->bits);
  size += sizeof(ulong);
  return size;
}

void fd_slot_history_encode(fd_slot_history_t* self, void const** data) {
  fd_slot_history_bitvec_encode(&self->bits, data);
  fd_bincode_uint64_encode(&self->next_slot, data);
}

void fd_slot_hash_decode(fd_slot_hash_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->slot, data, dataend);
  fd_hash_decode(&self->hash, data, dataend, allocf, allocf_arg);
}
void fd_slot_hash_destroy(fd_slot_hash_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_hash_destroy(&self->hash, freef, freef_arg);
}

void fd_slot_hash_walk(fd_slot_hash_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_slot_hash", level++);
  fun(&self->slot, "slot", 11, "ulong", level + 1);
  fd_hash_walk(&self->hash, fun, "hash", level + 1);
  fun(self, name, 33, "fd_slot_hash", --level);
}
void fd_slot_hash_copy_to(fd_slot_hash_t* to, fd_slot_hash_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_slot_hash_size(from) );
  void const *   ptr = (void const *) enc;
  fd_slot_hash_encode( from, &ptr );
  void *input = (void *) enc;
  fd_slot_hash_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_slot_hash_size(fd_slot_hash_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += fd_hash_size(&self->hash);
  return size;
}

void fd_slot_hash_encode(fd_slot_hash_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->slot, data);
  fd_hash_encode(&self->hash, data);
}

void fd_slot_hashes_decode(fd_slot_hashes_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_vec_fd_slot_hash_t_new(&self->hashes);
  ulong hashes_len;
  fd_bincode_uint64_decode(&hashes_len, data, dataend);
  for (ulong i = 0; i < hashes_len; ++i) {
    fd_slot_hash_t elem;
    fd_slot_hash_decode(&elem, data, dataend, allocf, allocf_arg);
    fd_vec_fd_slot_hash_t_push(&self->hashes, elem);
  }
}
void fd_slot_hashes_destroy(fd_slot_hashes_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_vec_fd_slot_hash_t_destroy(&self->hashes);
}

void fd_slot_hashes_walk(fd_slot_hashes_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_slot_hashes", level++);
  fun(NULL, NULL, 30, "hashes", level++);
  for (ulong i = 0; i < self->hashes.cnt; ++i)
    fd_slot_hash_walk(&self->hashes.elems[i], fun, "hashes", level + 1);
  fun(NULL, NULL, 31, "hashes", --level);
  fun(self, name, 33, "fd_slot_hashes", --level);
}
void fd_slot_hashes_copy_to(fd_slot_hashes_t* to, fd_slot_hashes_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_slot_hashes_size(from) );
  void const *   ptr = (void const *) enc;
  fd_slot_hashes_encode( from, &ptr );
  void *input = (void *) enc;
  fd_slot_hashes_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_slot_hashes_size(fd_slot_hashes_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  for (ulong i = 0; i < self->hashes.cnt; ++i)
    size += fd_slot_hash_size(&self->hashes.elems[i]);
  return size;
}

void fd_slot_hashes_encode(fd_slot_hashes_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->hashes.cnt, data);
  for (ulong i = 0; i < self->hashes.cnt; ++i)
    fd_slot_hash_encode(&self->hashes.elems[i], data);
}

void fd_block_block_hash_entry_decode(fd_block_block_hash_entry_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_hash_decode(&self->blockhash, data, dataend, allocf, allocf_arg);
  fd_fee_calculator_decode(&self->fee_calculator, data, dataend, allocf, allocf_arg);
}
void fd_block_block_hash_entry_destroy(fd_block_block_hash_entry_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_hash_destroy(&self->blockhash, freef, freef_arg);
  fd_fee_calculator_destroy(&self->fee_calculator, freef, freef_arg);
}

void fd_block_block_hash_entry_walk(fd_block_block_hash_entry_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_block_block_hash_entry", level++);
  fd_hash_walk(&self->blockhash, fun, "blockhash", level + 1);
  fd_fee_calculator_walk(&self->fee_calculator, fun, "fee_calculator", level + 1);
  fun(self, name, 33, "fd_block_block_hash_entry", --level);
}
void fd_block_block_hash_entry_copy_to(fd_block_block_hash_entry_t* to, fd_block_block_hash_entry_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_block_block_hash_entry_size(from) );
  void const *   ptr = (void const *) enc;
  fd_block_block_hash_entry_encode( from, &ptr );
  void *input = (void *) enc;
  fd_block_block_hash_entry_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_block_block_hash_entry_size(fd_block_block_hash_entry_t* self) {
  ulong size = 0;
  size += fd_hash_size(&self->blockhash);
  size += fd_fee_calculator_size(&self->fee_calculator);
  return size;
}

void fd_block_block_hash_entry_encode(fd_block_block_hash_entry_t* self, void const** data) {
  fd_hash_encode(&self->blockhash, data);
  fd_fee_calculator_encode(&self->fee_calculator, data);
}

void fd_recent_block_hashes_decode(fd_recent_block_hashes_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_vec_fd_block_block_hash_entry_t_new(&self->hashes);
  ulong hashes_len;
  fd_bincode_uint64_decode(&hashes_len, data, dataend);
  for (ulong i = 0; i < hashes_len; ++i) {
    fd_block_block_hash_entry_t elem;
    fd_block_block_hash_entry_decode(&elem, data, dataend, allocf, allocf_arg);
    fd_vec_fd_block_block_hash_entry_t_push(&self->hashes, elem);
  }
}
void fd_recent_block_hashes_destroy(fd_recent_block_hashes_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_vec_fd_block_block_hash_entry_t_destroy(&self->hashes);
}

void fd_recent_block_hashes_walk(fd_recent_block_hashes_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_recent_block_hashes", level++);
  fun(NULL, NULL, 30, "hashes", level++);
  for (ulong i = 0; i < self->hashes.cnt; ++i)
    fd_block_block_hash_entry_walk(&self->hashes.elems[i], fun, "hashes", level + 1);
  fun(NULL, NULL, 31, "hashes", --level);
  fun(self, name, 33, "fd_recent_block_hashes", --level);
}
void fd_recent_block_hashes_copy_to(fd_recent_block_hashes_t* to, fd_recent_block_hashes_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_recent_block_hashes_size(from) );
  void const *   ptr = (void const *) enc;
  fd_recent_block_hashes_encode( from, &ptr );
  void *input = (void *) enc;
  fd_recent_block_hashes_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_recent_block_hashes_size(fd_recent_block_hashes_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  for (ulong i = 0; i < self->hashes.cnt; ++i)
    size += fd_block_block_hash_entry_size(&self->hashes.elems[i]);
  return size;
}

void fd_recent_block_hashes_encode(fd_recent_block_hashes_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->hashes.cnt, data);
  for (ulong i = 0; i < self->hashes.cnt; ++i)
    fd_block_block_hash_entry_encode(&self->hashes.elems[i], data);
}

void fd_slot_meta_decode(fd_slot_meta_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->slot, data, dataend);
  fd_bincode_uint64_decode(&self->consumed, data, dataend);
  fd_bincode_uint64_decode(&self->received, data, dataend);
  fd_bincode_uint64_decode(&self->first_shred_timestamp, data, dataend);
  fd_bincode_uint64_decode(&self->last_index, data, dataend);
  fd_bincode_uint64_decode(&self->parent_slot, data, dataend);
  fd_bincode_uint64_decode(&self->next_slot_len, data, dataend);
  if (self->next_slot_len != 0) {
    self->next_slot = (ulong*)(*allocf)(allocf_arg, 8UL, sizeof(ulong)*self->next_slot_len);
    for (ulong i = 0; i < self->next_slot_len; ++i)
      fd_bincode_uint64_decode(self->next_slot + i, data, dataend);
  } else
    self->next_slot = NULL;
  fd_bincode_uint8_decode(&self->is_connected, data, dataend);
  fd_bincode_uint64_decode(&self->entry_end_indexes_len, data, dataend);
  if (self->entry_end_indexes_len != 0) {
    self->entry_end_indexes = (uint*)(*allocf)(allocf_arg, 8UL, sizeof(ulong)*self->entry_end_indexes_len);
    for (ulong i = 0; i < self->entry_end_indexes_len; ++i)
      fd_bincode_uint32_decode(self->entry_end_indexes + i, data, dataend);
  } else
    self->entry_end_indexes = NULL;
}
void fd_slot_meta_destroy(fd_slot_meta_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->next_slot) {
    freef(freef_arg, self->next_slot);
    self->next_slot = NULL;
  }
  if (NULL != self->entry_end_indexes) {
    freef(freef_arg, self->entry_end_indexes);
    self->entry_end_indexes = NULL;
  }
}

void fd_slot_meta_walk(fd_slot_meta_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_slot_meta", level++);
  fun(&self->slot, "slot", 11, "ulong", level + 1);
  fun(&self->consumed, "consumed", 11, "ulong", level + 1);
  fun(&self->received, "received", 11, "ulong", level + 1);
  fun(&self->first_shred_timestamp, "first_shred_timestamp", 11, "ulong", level + 1);
  fun(&self->last_index, "last_index", 11, "ulong", level + 1);
  fun(&self->parent_slot, "parent_slot", 11, "ulong", level + 1);
  if (self->next_slot_len != 0) {
    fun(NULL, NULL, 30, "next_slot", level++);
    for (ulong i = 0; i < self->next_slot_len; ++i)
      fun(self->next_slot + i, "next_slot", 11, "ulong", level + 1);
    fun(NULL, NULL, 31, "next_slot", --level);
  }
  fun(&self->is_connected, "is_connected", 9, "uchar", level + 1);
  if (self->entry_end_indexes_len != 0) {
    fun(NULL, NULL, 30, "entry_end_indexes", level++);
    for (ulong i = 0; i < self->entry_end_indexes_len; ++i)
      fun(self->entry_end_indexes + i, "entry_end_indexes", 7, "uint", level + 1);
    fun(NULL, NULL, 31, "entry_end_indexes", --level);
  }
  fun(self, name, 33, "fd_slot_meta", --level);
}
void fd_slot_meta_copy_to(fd_slot_meta_t* to, fd_slot_meta_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_slot_meta_size(from) );
  void const *   ptr = (void const *) enc;
  fd_slot_meta_encode( from, &ptr );
  void *input = (void *) enc;
  fd_slot_meta_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_slot_meta_size(fd_slot_meta_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += self->next_slot_len * sizeof(ulong);
  size += sizeof(char);
  size += sizeof(ulong);
  size += self->entry_end_indexes_len * sizeof(uint);
  return size;
}

void fd_slot_meta_encode(fd_slot_meta_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->slot, data);
  fd_bincode_uint64_encode(&self->consumed, data);
  fd_bincode_uint64_encode(&self->received, data);
  fd_bincode_uint64_encode(&self->first_shred_timestamp, data);
  fd_bincode_uint64_encode(&self->last_index, data);
  fd_bincode_uint64_encode(&self->parent_slot, data);
  fd_bincode_uint64_encode(&self->next_slot_len, data);
  if (self->next_slot_len != 0) {
    for (ulong i = 0; i < self->next_slot_len; ++i)
      fd_bincode_uint64_encode(self->next_slot + i, data);
  }
  fd_bincode_uint8_encode(&self->is_connected, data);
  fd_bincode_uint64_encode(&self->entry_end_indexes_len, data);
  if (self->entry_end_indexes_len != 0) {
    for (ulong i = 0; i < self->entry_end_indexes_len; ++i)
      fd_bincode_uint32_encode(self->entry_end_indexes + i, data);
  }
}

void fd_clock_timestamp_vote_decode(fd_clock_timestamp_vote_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->pubkey, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode((unsigned long *) &self->timestamp, data, dataend);
  fd_bincode_uint64_decode(&self->slot, data, dataend);
}
void fd_clock_timestamp_vote_destroy(fd_clock_timestamp_vote_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->pubkey, freef, freef_arg);
}

void fd_clock_timestamp_vote_walk(fd_clock_timestamp_vote_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_clock_timestamp_vote", level++);
  fd_pubkey_walk(&self->pubkey, fun, "pubkey", level + 1);
  fun(&self->timestamp, "timestamp", 6, "long", level + 1);
  fun(&self->slot, "slot", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_clock_timestamp_vote", --level);
}
void fd_clock_timestamp_vote_copy_to(fd_clock_timestamp_vote_t* to, fd_clock_timestamp_vote_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_clock_timestamp_vote_size(from) );
  void const *   ptr = (void const *) enc;
  fd_clock_timestamp_vote_encode( from, &ptr );
  void *input = (void *) enc;
  fd_clock_timestamp_vote_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_clock_timestamp_vote_size(fd_clock_timestamp_vote_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->pubkey);
  size += sizeof(long);
  size += sizeof(ulong);
  return size;
}

void fd_clock_timestamp_vote_encode(fd_clock_timestamp_vote_t* self, void const** data) {
  fd_pubkey_encode(&self->pubkey, data);
  fd_bincode_uint64_encode((unsigned long *) &self->timestamp, data);
  fd_bincode_uint64_encode(&self->slot, data);
}

void fd_clock_timestamp_votes_decode(fd_clock_timestamp_votes_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_vec_fd_clock_timestamp_vote_t_new(&self->votes);
  ulong votes_len;
  fd_bincode_uint64_decode(&votes_len, data, dataend);
  for (ulong i = 0; i < votes_len; ++i) {
    fd_clock_timestamp_vote_t elem;
    fd_clock_timestamp_vote_decode(&elem, data, dataend, allocf, allocf_arg);
    fd_vec_fd_clock_timestamp_vote_t_push(&self->votes, elem);
  }
}
void fd_clock_timestamp_votes_destroy(fd_clock_timestamp_votes_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_vec_fd_clock_timestamp_vote_t_destroy(&self->votes);
}

void fd_clock_timestamp_votes_walk(fd_clock_timestamp_votes_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_clock_timestamp_votes", level++);
  fun(NULL, NULL, 30, "votes", level++);
  for (ulong i = 0; i < self->votes.cnt; ++i)
    fd_clock_timestamp_vote_walk(&self->votes.elems[i], fun, "votes", level + 1);
  fun(NULL, NULL, 31, "votes", --level);
  fun(self, name, 33, "fd_clock_timestamp_votes", --level);
}
void fd_clock_timestamp_votes_copy_to(fd_clock_timestamp_votes_t* to, fd_clock_timestamp_votes_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_clock_timestamp_votes_size(from) );
  void const *   ptr = (void const *) enc;
  fd_clock_timestamp_votes_encode( from, &ptr );
  void *input = (void *) enc;
  fd_clock_timestamp_votes_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_clock_timestamp_votes_size(fd_clock_timestamp_votes_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  for (ulong i = 0; i < self->votes.cnt; ++i)
    size += fd_clock_timestamp_vote_size(&self->votes.elems[i]);
  return size;
}

void fd_clock_timestamp_votes_encode(fd_clock_timestamp_votes_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->votes.cnt, data);
  for (ulong i = 0; i < self->votes.cnt; ++i)
    fd_clock_timestamp_vote_encode(&self->votes.elems[i], data);
}

void fd_sysvar_fees_decode(fd_sysvar_fees_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_fee_calculator_decode(&self->fee_calculator, data, dataend, allocf, allocf_arg);
}
void fd_sysvar_fees_destroy(fd_sysvar_fees_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_fee_calculator_destroy(&self->fee_calculator, freef, freef_arg);
}

void fd_sysvar_fees_walk(fd_sysvar_fees_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_sysvar_fees", level++);
  fd_fee_calculator_walk(&self->fee_calculator, fun, "fee_calculator", level + 1);
  fun(self, name, 33, "fd_sysvar_fees", --level);
}
void fd_sysvar_fees_copy_to(fd_sysvar_fees_t* to, fd_sysvar_fees_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_sysvar_fees_size(from) );
  void const *   ptr = (void const *) enc;
  fd_sysvar_fees_encode( from, &ptr );
  void *input = (void *) enc;
  fd_sysvar_fees_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_sysvar_fees_size(fd_sysvar_fees_t* self) {
  ulong size = 0;
  size += fd_fee_calculator_size(&self->fee_calculator);
  return size;
}

void fd_sysvar_fees_encode(fd_sysvar_fees_t* self, void const** data) {
  fd_fee_calculator_encode(&self->fee_calculator, data);
}

void fd_config_keys_pair_decode(fd_config_keys_pair_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->key, data, dataend, allocf, allocf_arg);
  fd_bincode_uint8_decode(&self->value, data, dataend);
}
void fd_config_keys_pair_destroy(fd_config_keys_pair_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->key, freef, freef_arg);
}

void fd_config_keys_pair_walk(fd_config_keys_pair_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_config_keys_pair", level++);
  fd_pubkey_walk(&self->key, fun, "key", level + 1);
  fun(&self->value, "value", 9, "uchar", level + 1);
  fun(self, name, 33, "fd_config_keys_pair", --level);
}
void fd_config_keys_pair_copy_to(fd_config_keys_pair_t* to, fd_config_keys_pair_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_config_keys_pair_size(from) );
  void const *   ptr = (void const *) enc;
  fd_config_keys_pair_encode( from, &ptr );
  void *input = (void *) enc;
  fd_config_keys_pair_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_config_keys_pair_size(fd_config_keys_pair_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->key);
  size += sizeof(char);
  return size;
}

void fd_config_keys_pair_encode(fd_config_keys_pair_t* self, void const** data) {
  fd_pubkey_encode(&self->key, data);
  fd_bincode_uint8_encode(&self->value, data);
}

void fd_stake_config_decode(fd_stake_config_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_decode_short_u16(&self->config_keys_len, data, dataend);
  if (self->config_keys_len != 0) {
    self->config_keys = (fd_config_keys_pair_t*)(*allocf)(allocf_arg, FD_CONFIG_KEYS_PAIR_ALIGN, FD_CONFIG_KEYS_PAIR_FOOTPRINT*self->config_keys_len);
    for (ulong i = 0; i < self->config_keys_len; ++i)
      fd_config_keys_pair_decode(self->config_keys + i, data, dataend, allocf, allocf_arg);
  } else
    self->config_keys = NULL;
  fd_bincode_double_decode(&self->warmup_cooldown_rate, data, dataend);
  fd_bincode_uint8_decode(&self->slash_penalty, data, dataend);
}
void fd_stake_config_destroy(fd_stake_config_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->config_keys) {
    for (ulong i = 0; i < self->config_keys_len; ++i)
      fd_config_keys_pair_destroy(self->config_keys + i, freef, freef_arg);
    freef(freef_arg, self->config_keys);
    self->config_keys = NULL;
  }
}

void fd_stake_config_walk(fd_stake_config_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_stake_config", level++);
  if (self->config_keys_len != 0) {
    fun(NULL, NULL, 30, "config_keys", level++);
    for (ulong i = 0; i < self->config_keys_len; ++i)
      fd_config_keys_pair_walk(self->config_keys + i, fun, "config_keys_pair", level + 1);
    fun(NULL, NULL, 31, "config_keys", --level);
  }
  fun(&self->warmup_cooldown_rate, "warmup_cooldown_rate", 5, "double", level + 1);
  fun(&self->slash_penalty, "slash_penalty", 9, "uchar", level + 1);
  fun(self, name, 33, "fd_stake_config", --level);
}
void fd_stake_config_copy_to(fd_stake_config_t* to, fd_stake_config_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_stake_config_size(from) );
  void const *   ptr = (void const *) enc;
  fd_stake_config_encode( from, &ptr );
  void *input = (void *) enc;
  fd_stake_config_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_stake_config_size(fd_stake_config_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  for (ulong i = 0; i < self->config_keys_len; ++i)
    size += fd_config_keys_pair_size(self->config_keys + i);
  size += sizeof(double);
  size += sizeof(char);
  return size;
}

void fd_stake_config_encode(fd_stake_config_t* self, void const** data) {
  fd_encode_short_u16(&self->config_keys_len, (void **) data);
  if (self->config_keys_len != 0) {
    for (ulong i = 0; i < self->config_keys_len; ++i)
      fd_config_keys_pair_encode(self->config_keys + i, data);
  }
  fd_bincode_double_encode(&self->warmup_cooldown_rate, data);
  fd_bincode_uint8_encode(&self->slash_penalty, data);
}

void fd_firedancer_banks_decode(fd_firedancer_banks_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_deserializable_versioned_bank_decode(&self->solana_bank, data, dataend, allocf, allocf_arg);
  fd_recent_block_hashes_decode(&self->recent_block_hashes, data, dataend, allocf, allocf_arg);
  fd_clock_timestamp_votes_decode(&self->timestamp_votes, data, dataend, allocf, allocf_arg);
}
void fd_firedancer_banks_destroy(fd_firedancer_banks_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_deserializable_versioned_bank_destroy(&self->solana_bank, freef, freef_arg);
  fd_recent_block_hashes_destroy(&self->recent_block_hashes, freef, freef_arg);
  fd_clock_timestamp_votes_destroy(&self->timestamp_votes, freef, freef_arg);
}

void fd_firedancer_banks_walk(fd_firedancer_banks_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_firedancer_banks", level++);
  fd_deserializable_versioned_bank_walk(&self->solana_bank, fun, "solana_bank", level + 1);
  fd_recent_block_hashes_walk(&self->recent_block_hashes, fun, "recent_block_hashes", level + 1);
  fd_clock_timestamp_votes_walk(&self->timestamp_votes, fun, "timestamp_votes", level + 1);
  fun(self, name, 33, "fd_firedancer_banks", --level);
}
void fd_firedancer_banks_copy_to(fd_firedancer_banks_t* to, fd_firedancer_banks_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_firedancer_banks_size(from) );
  void const *   ptr = (void const *) enc;
  fd_firedancer_banks_encode( from, &ptr );
  void *input = (void *) enc;
  fd_firedancer_banks_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_firedancer_banks_size(fd_firedancer_banks_t* self) {
  ulong size = 0;
  size += fd_deserializable_versioned_bank_size(&self->solana_bank);
  size += fd_recent_block_hashes_size(&self->recent_block_hashes);
  size += fd_clock_timestamp_votes_size(&self->timestamp_votes);
  return size;
}

void fd_firedancer_banks_encode(fd_firedancer_banks_t* self, void const** data) {
  fd_deserializable_versioned_bank_encode(&self->solana_bank, data);
  fd_recent_block_hashes_encode(&self->recent_block_hashes, data);
  fd_clock_timestamp_votes_encode(&self->timestamp_votes, data);
}

void fd_vote_decode(fd_vote_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_vec_ulong_new(&self->slots);
  ulong slots_len;
  fd_bincode_uint64_decode(&slots_len, data, dataend);
  for (ulong i = 0; i < slots_len; ++i) {
    ulong elem;
    fd_bincode_uint64_decode(&elem, data, dataend);
    fd_vec_ulong_push(&self->slots, elem);
  }
  fd_hash_decode(&self->hash, data, dataend, allocf, allocf_arg);
  if (fd_bincode_option_decode(data, dataend)) {
    self->timestamp = (ulong*)(*allocf)(allocf_arg, 8, sizeof(ulong));
    fd_bincode_uint64_decode(self->timestamp, data, dataend);
  } else
    self->timestamp = NULL;
}
void fd_vote_destroy(fd_vote_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_vec_ulong_destroy(&self->slots);
  fd_hash_destroy(&self->hash, freef, freef_arg);
  if (NULL != self->timestamp) {
    freef(freef_arg, self->timestamp);
    self->timestamp = NULL;
  }
}

void fd_vote_walk(fd_vote_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote", level++);
  fun(NULL, NULL, 30, "slots", level++);
  for (ulong i = 0; i < self->slots.cnt; ++i)
    ; //fd_bincode_uint64_walk(&self->slots.elems[i], data);
  fun(NULL, NULL, 31, "slots", --level);
  fd_hash_walk(&self->hash, fun, "hash", level + 1);
  fun(self->timestamp, "timestamp", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_vote", --level);
}
void fd_vote_copy_to(fd_vote_t* to, fd_vote_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_size(fd_vote_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += self->slots.cnt * sizeof(ulong);
  size += fd_hash_size(&self->hash);
  size += sizeof(char);
  if (NULL !=  self->timestamp) {
    size += sizeof(ulong);
  }
  return size;
}

void fd_vote_encode(fd_vote_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->slots.cnt, data);
  for (ulong i = 0; i < self->slots.cnt; ++i)
    fd_bincode_uint64_encode(&self->slots.elems[i], data);
  fd_hash_encode(&self->hash, data);
  if (self->timestamp!= NULL) {
    fd_bincode_option_encode(1, data);
    fd_bincode_uint64_encode(self->timestamp, data);
  } else
    fd_bincode_option_encode(0, data);
}

void fd_vote_init_decode(fd_vote_init_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->node_pubkey, data, dataend, allocf, allocf_arg);
  fd_pubkey_decode(&self->authorized_voter, data, dataend, allocf, allocf_arg);
  fd_pubkey_decode(&self->authorized_withdrawer, data, dataend, allocf, allocf_arg);
  fd_bincode_uint8_decode(&self->commission, data, dataend);
}
void fd_vote_init_destroy(fd_vote_init_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->node_pubkey, freef, freef_arg);
  fd_pubkey_destroy(&self->authorized_voter, freef, freef_arg);
  fd_pubkey_destroy(&self->authorized_withdrawer, freef, freef_arg);
}

void fd_vote_init_walk(fd_vote_init_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_init", level++);
  fd_pubkey_walk(&self->node_pubkey, fun, "node_pubkey", level + 1);
  fd_pubkey_walk(&self->authorized_voter, fun, "authorized_voter", level + 1);
  fd_pubkey_walk(&self->authorized_withdrawer, fun, "authorized_withdrawer", level + 1);
  fun(&self->commission, "commission", 9, "uchar", level + 1);
  fun(self, name, 33, "fd_vote_init", --level);
}
void fd_vote_init_copy_to(fd_vote_init_t* to, fd_vote_init_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_init_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_init_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_init_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_init_size(fd_vote_init_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->node_pubkey);
  size += fd_pubkey_size(&self->authorized_voter);
  size += fd_pubkey_size(&self->authorized_withdrawer);
  size += sizeof(char);
  return size;
}

void fd_vote_init_encode(fd_vote_init_t* self, void const** data) {
  fd_pubkey_encode(&self->node_pubkey, data);
  fd_pubkey_encode(&self->authorized_voter, data);
  fd_pubkey_encode(&self->authorized_withdrawer, data);
  fd_bincode_uint8_encode(&self->commission, data);
}

uchar fd_vote_authorize_is_voter(fd_vote_authorize_t* self) {
  return self->discriminant == 0;
}
uchar fd_vote_authorize_is_withdrawer(fd_vote_authorize_t* self) {
  return self->discriminant == 1;
}
void fd_vote_authorize_inner_decode(fd_vote_authorize_inner_t* self, uint discriminant, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  switch (discriminant) {
  case 0: {
    break;
  }
  case 1: {
    break;
  }
  default: FD_LOG_ERR(( "unhandled type"));
  }
}
void fd_vote_authorize_decode(fd_vote_authorize_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint32_decode(&self->discriminant, data, dataend);
  fd_vote_authorize_inner_decode(&self->inner, self->discriminant, data, dataend, allocf, allocf_arg);
}
void fd_vote_authorize_inner_destroy(fd_vote_authorize_inner_t* self, uint discriminant, fd_free_fun_t freef, void* freef_arg) {
  switch (discriminant) {
  case 0: {
    break;
  }
  case 1: {
    break;
  }
  default: break; // FD_LOG_ERR(( "unhandled type"));
  }
}
void fd_vote_authorize_destroy(fd_vote_authorize_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_vote_authorize_inner_destroy(&self->inner, self->discriminant, freef, freef_arg);
}

void fd_vote_authorize_walk(fd_vote_authorize_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_authorize", level++);
  // enum fd_unsigned char_walk(&self->commission, fun, "commission", level + 1);
  fun(self, name, 33, "fd_vote_authorize", --level);
}
void fd_vote_authorize_copy_to(fd_vote_authorize_t* to, fd_vote_authorize_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_authorize_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_authorize_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_authorize_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_authorize_size(fd_vote_authorize_t* self) {
  ulong size = 0;
  size += sizeof(uint);
  switch (self->discriminant) {
  }
  return size;
}

void fd_vote_authorize_inner_encode(fd_vote_authorize_inner_t* self, uint discriminant, void const** data) {
  switch (discriminant) {
  }
}
void fd_vote_authorize_encode(fd_vote_authorize_t* self, void const** data) {
  fd_bincode_uint32_encode(&self->discriminant, data);
  fd_vote_authorize_inner_encode(&self->inner, self->discriminant, data);
}

void fd_vote_authorize_pubkey_decode(fd_vote_authorize_pubkey_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->pubkey, data, dataend, allocf, allocf_arg);
  fd_vote_authorize_decode(&self->vote_authorize, data, dataend, allocf, allocf_arg);
}
void fd_vote_authorize_pubkey_destroy(fd_vote_authorize_pubkey_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->pubkey, freef, freef_arg);
  fd_vote_authorize_destroy(&self->vote_authorize, freef, freef_arg);
}

void fd_vote_authorize_pubkey_walk(fd_vote_authorize_pubkey_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_authorize_pubkey", level++);
  fd_pubkey_walk(&self->pubkey, fun, "pubkey", level + 1);
  fd_vote_authorize_walk(&self->vote_authorize, fun, "vote_authorize", level + 1);
  fun(self, name, 33, "fd_vote_authorize_pubkey", --level);
}
void fd_vote_authorize_pubkey_copy_to(fd_vote_authorize_pubkey_t* to, fd_vote_authorize_pubkey_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_authorize_pubkey_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_authorize_pubkey_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_authorize_pubkey_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_authorize_pubkey_size(fd_vote_authorize_pubkey_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->pubkey);
  size += fd_vote_authorize_size(&self->vote_authorize);
  return size;
}

void fd_vote_authorize_pubkey_encode(fd_vote_authorize_pubkey_t* self, void const** data) {
  fd_pubkey_encode(&self->pubkey, data);
  fd_vote_authorize_encode(&self->vote_authorize, data);
}

void fd_vote_switch_decode(fd_vote_switch_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_vote_decode(&self->vote, data, dataend, allocf, allocf_arg);
  fd_hash_decode(&self->hash, data, dataend, allocf, allocf_arg);
}
void fd_vote_switch_destroy(fd_vote_switch_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_vote_destroy(&self->vote, freef, freef_arg);
  fd_hash_destroy(&self->hash, freef, freef_arg);
}

void fd_vote_switch_walk(fd_vote_switch_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_switch", level++);
  fd_vote_walk(&self->vote, fun, "vote", level + 1);
  fd_hash_walk(&self->hash, fun, "hash", level + 1);
  fun(self, name, 33, "fd_vote_switch", --level);
}
void fd_vote_switch_copy_to(fd_vote_switch_t* to, fd_vote_switch_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_switch_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_switch_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_switch_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_switch_size(fd_vote_switch_t* self) {
  ulong size = 0;
  size += fd_vote_size(&self->vote);
  size += fd_hash_size(&self->hash);
  return size;
}

void fd_vote_switch_encode(fd_vote_switch_t* self, void const** data) {
  fd_vote_encode(&self->vote, data);
  fd_hash_encode(&self->hash, data);
}

void fd_update_vote_state_switch_decode(fd_update_vote_state_switch_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_vote_state_update_decode(&self->vote_state_update, data, dataend, allocf, allocf_arg);
  fd_hash_decode(&self->hash, data, dataend, allocf, allocf_arg);
}
void fd_update_vote_state_switch_destroy(fd_update_vote_state_switch_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_vote_state_update_destroy(&self->vote_state_update, freef, freef_arg);
  fd_hash_destroy(&self->hash, freef, freef_arg);
}

void fd_update_vote_state_switch_walk(fd_update_vote_state_switch_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_update_vote_state_switch", level++);
  fd_vote_state_update_walk(&self->vote_state_update, fun, "vote_state_update", level + 1);
  fd_hash_walk(&self->hash, fun, "hash", level + 1);
  fun(self, name, 33, "fd_update_vote_state_switch", --level);
}
void fd_update_vote_state_switch_copy_to(fd_update_vote_state_switch_t* to, fd_update_vote_state_switch_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_update_vote_state_switch_size(from) );
  void const *   ptr = (void const *) enc;
  fd_update_vote_state_switch_encode( from, &ptr );
  void *input = (void *) enc;
  fd_update_vote_state_switch_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_update_vote_state_switch_size(fd_update_vote_state_switch_t* self) {
  ulong size = 0;
  size += fd_vote_state_update_size(&self->vote_state_update);
  size += fd_hash_size(&self->hash);
  return size;
}

void fd_update_vote_state_switch_encode(fd_update_vote_state_switch_t* self, void const** data) {
  fd_vote_state_update_encode(&self->vote_state_update, data);
  fd_hash_encode(&self->hash, data);
}

void fd_vote_authorize_with_seed_args_decode(fd_vote_authorize_with_seed_args_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_vote_authorize_decode(&self->authorization_type, data, dataend, allocf, allocf_arg);
  fd_pubkey_decode(&self->current_authority_derived_key_owner, data, dataend, allocf, allocf_arg);
  ulong slen;
  fd_bincode_uint64_decode(&slen, data, dataend);
  self->current_authority_derived_key_seed = (char*)(*allocf)(allocf_arg, 1, slen + 1);
  fd_bincode_bytes_decode((uchar *) self->current_authority_derived_key_seed, slen, data, dataend);
  self->current_authority_derived_key_seed[slen] = '\0';
  fd_pubkey_decode(&self->new_authority, data, dataend, allocf, allocf_arg);
}
void fd_vote_authorize_with_seed_args_destroy(fd_vote_authorize_with_seed_args_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_vote_authorize_destroy(&self->authorization_type, freef, freef_arg);
  fd_pubkey_destroy(&self->current_authority_derived_key_owner, freef, freef_arg);
  if (NULL != self->current_authority_derived_key_seed) {
    freef(freef_arg, self->current_authority_derived_key_seed);
    self->current_authority_derived_key_seed = NULL;
  }
  fd_pubkey_destroy(&self->new_authority, freef, freef_arg);
}

void fd_vote_authorize_with_seed_args_walk(fd_vote_authorize_with_seed_args_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_authorize_with_seed_args", level++);
  fd_vote_authorize_walk(&self->authorization_type, fun, "authorization_type", level + 1);
  fd_pubkey_walk(&self->current_authority_derived_key_owner, fun, "current_authority_derived_key_owner", level + 1);
  fun(self->current_authority_derived_key_seed, "current_authority_derived_key_seed", 2, "char*", level + 1);
  fd_pubkey_walk(&self->new_authority, fun, "new_authority", level + 1);
  fun(self, name, 33, "fd_vote_authorize_with_seed_args", --level);
}
void fd_vote_authorize_with_seed_args_copy_to(fd_vote_authorize_with_seed_args_t* to, fd_vote_authorize_with_seed_args_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_authorize_with_seed_args_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_authorize_with_seed_args_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_authorize_with_seed_args_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_authorize_with_seed_args_size(fd_vote_authorize_with_seed_args_t* self) {
  ulong size = 0;
  size += fd_vote_authorize_size(&self->authorization_type);
  size += fd_pubkey_size(&self->current_authority_derived_key_owner);
  size += sizeof(ulong) + strlen(self->current_authority_derived_key_seed);
  size += fd_pubkey_size(&self->new_authority);
  return size;
}

void fd_vote_authorize_with_seed_args_encode(fd_vote_authorize_with_seed_args_t* self, void const** data) {
  fd_vote_authorize_encode(&self->authorization_type, data);
  fd_pubkey_encode(&self->current_authority_derived_key_owner, data);
  ulong slen = strlen((char *) self->current_authority_derived_key_seed);
  fd_bincode_uint64_encode(&slen, data);
  fd_bincode_bytes_encode((uchar *) self->current_authority_derived_key_seed, slen, data);
  fd_pubkey_encode(&self->new_authority, data);
}

void fd_vote_authorize_checked_with_seed_args_decode(fd_vote_authorize_checked_with_seed_args_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_vote_authorize_decode(&self->authorization_type, data, dataend, allocf, allocf_arg);
  fd_pubkey_decode(&self->current_authority_derived_key_owner, data, dataend, allocf, allocf_arg);
  ulong slen;
  fd_bincode_uint64_decode(&slen, data, dataend);
  self->current_authority_derived_key_seed = (char*)(*allocf)(allocf_arg, 1, slen + 1);
  fd_bincode_bytes_decode((uchar *) self->current_authority_derived_key_seed, slen, data, dataend);
  self->current_authority_derived_key_seed[slen] = '\0';
}
void fd_vote_authorize_checked_with_seed_args_destroy(fd_vote_authorize_checked_with_seed_args_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_vote_authorize_destroy(&self->authorization_type, freef, freef_arg);
  fd_pubkey_destroy(&self->current_authority_derived_key_owner, freef, freef_arg);
  if (NULL != self->current_authority_derived_key_seed) {
    freef(freef_arg, self->current_authority_derived_key_seed);
    self->current_authority_derived_key_seed = NULL;
  }
}

void fd_vote_authorize_checked_with_seed_args_walk(fd_vote_authorize_checked_with_seed_args_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_authorize_checked_with_seed_args", level++);
  fd_vote_authorize_walk(&self->authorization_type, fun, "authorization_type", level + 1);
  fd_pubkey_walk(&self->current_authority_derived_key_owner, fun, "current_authority_derived_key_owner", level + 1);
  fun(self->current_authority_derived_key_seed, "current_authority_derived_key_seed", 2, "char*", level + 1);
  fun(self, name, 33, "fd_vote_authorize_checked_with_seed_args", --level);
}
void fd_vote_authorize_checked_with_seed_args_copy_to(fd_vote_authorize_checked_with_seed_args_t* to, fd_vote_authorize_checked_with_seed_args_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_authorize_checked_with_seed_args_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_authorize_checked_with_seed_args_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_authorize_checked_with_seed_args_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_authorize_checked_with_seed_args_size(fd_vote_authorize_checked_with_seed_args_t* self) {
  ulong size = 0;
  size += fd_vote_authorize_size(&self->authorization_type);
  size += fd_pubkey_size(&self->current_authority_derived_key_owner);
  size += sizeof(ulong) + strlen(self->current_authority_derived_key_seed);
  return size;
}

void fd_vote_authorize_checked_with_seed_args_encode(fd_vote_authorize_checked_with_seed_args_t* self, void const** data) {
  fd_vote_authorize_encode(&self->authorization_type, data);
  fd_pubkey_encode(&self->current_authority_derived_key_owner, data);
  ulong slen = strlen((char *) self->current_authority_derived_key_seed);
  fd_bincode_uint64_encode(&slen, data);
  fd_bincode_bytes_encode((uchar *) self->current_authority_derived_key_seed, slen, data);
}

uchar fd_vote_instruction_is_initialize_account(fd_vote_instruction_t* self) {
  return self->discriminant == 0;
}
uchar fd_vote_instruction_is_authorize(fd_vote_instruction_t* self) {
  return self->discriminant == 1;
}
uchar fd_vote_instruction_is_vote(fd_vote_instruction_t* self) {
  return self->discriminant == 2;
}
uchar fd_vote_instruction_is_withdraw(fd_vote_instruction_t* self) {
  return self->discriminant == 3;
}
uchar fd_vote_instruction_is_update_validator_identity(fd_vote_instruction_t* self) {
  return self->discriminant == 4;
}
uchar fd_vote_instruction_is_update_commission(fd_vote_instruction_t* self) {
  return self->discriminant == 5;
}
uchar fd_vote_instruction_is_vote_switch(fd_vote_instruction_t* self) {
  return self->discriminant == 6;
}
uchar fd_vote_instruction_is_authorize_checked(fd_vote_instruction_t* self) {
  return self->discriminant == 7;
}
uchar fd_vote_instruction_is_update_vote_state(fd_vote_instruction_t* self) {
  return self->discriminant == 8;
}
uchar fd_vote_instruction_is_update_vote_state_switch(fd_vote_instruction_t* self) {
  return self->discriminant == 9;
}
uchar fd_vote_instruction_is_authorize_with_seed(fd_vote_instruction_t* self) {
  return self->discriminant == 10;
}
uchar fd_vote_instruction_is_authorize_checked_with_seed(fd_vote_instruction_t* self) {
  return self->discriminant == 11;
}
void fd_vote_instruction_inner_decode(fd_vote_instruction_inner_t* self, uint discriminant, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  switch (discriminant) {
  case 0: {
    fd_vote_init_decode(&self->initialize_account, data, dataend, allocf, allocf_arg);
    break;
  }
  case 1: {
    fd_vote_authorize_pubkey_decode(&self->authorize, data, dataend, allocf, allocf_arg);
    break;
  }
  case 2: {
    fd_vote_decode(&self->vote, data, dataend, allocf, allocf_arg);
    break;
  }
  case 3: {
    fd_bincode_uint64_decode(&self->withdraw, data, dataend);
    break;
  }
  case 4: {
    break;
  }
  case 5: {
    fd_bincode_uint8_decode(&self->update_commission, data, dataend);
    break;
  }
  case 6: {
    fd_vote_switch_decode(&self->vote_switch, data, dataend, allocf, allocf_arg);
    break;
  }
  case 7: {
    fd_vote_authorize_decode(&self->authorize_checked, data, dataend, allocf, allocf_arg);
    break;
  }
  case 8: {
    fd_vote_state_update_decode(&self->update_vote_state, data, dataend, allocf, allocf_arg);
    break;
  }
  case 9: {
    fd_update_vote_state_switch_decode(&self->update_vote_state_switch, data, dataend, allocf, allocf_arg);
    break;
  }
  case 10: {
    fd_vote_authorize_with_seed_args_decode(&self->authorize_with_seed, data, dataend, allocf, allocf_arg);
    break;
  }
  case 11: {
    fd_vote_authorize_checked_with_seed_args_decode(&self->authorize_checked_with_seed, data, dataend, allocf, allocf_arg);
    break;
  }
  default: FD_LOG_ERR(( "unhandled type"));
  }
}
void fd_vote_instruction_decode(fd_vote_instruction_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint32_decode(&self->discriminant, data, dataend);
  fd_vote_instruction_inner_decode(&self->inner, self->discriminant, data, dataend, allocf, allocf_arg);
}
void fd_vote_instruction_inner_destroy(fd_vote_instruction_inner_t* self, uint discriminant, fd_free_fun_t freef, void* freef_arg) {
  switch (discriminant) {
  case 0: {
    fd_vote_init_destroy(&self->initialize_account, freef, freef_arg);
    break;
  }
  case 1: {
    fd_vote_authorize_pubkey_destroy(&self->authorize, freef, freef_arg);
    break;
  }
  case 2: {
    fd_vote_destroy(&self->vote, freef, freef_arg);
    break;
  }
  case 3: {
    break;
  }
  case 4: {
    break;
  }
  case 5: {
    break;
  }
  case 6: {
    fd_vote_switch_destroy(&self->vote_switch, freef, freef_arg);
    break;
  }
  case 7: {
    fd_vote_authorize_destroy(&self->authorize_checked, freef, freef_arg);
    break;
  }
  case 8: {
    fd_vote_state_update_destroy(&self->update_vote_state, freef, freef_arg);
    break;
  }
  case 9: {
    fd_update_vote_state_switch_destroy(&self->update_vote_state_switch, freef, freef_arg);
    break;
  }
  case 10: {
    fd_vote_authorize_with_seed_args_destroy(&self->authorize_with_seed, freef, freef_arg);
    break;
  }
  case 11: {
    fd_vote_authorize_checked_with_seed_args_destroy(&self->authorize_checked_with_seed, freef, freef_arg);
    break;
  }
  default: break; // FD_LOG_ERR(( "unhandled type"));
  }
}
void fd_vote_instruction_destroy(fd_vote_instruction_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_vote_instruction_inner_destroy(&self->inner, self->discriminant, freef, freef_arg);
}

void fd_vote_instruction_walk(fd_vote_instruction_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_vote_instruction", level++);
  // enum fd_char*_walk(&self->current_authority_derived_key_seed, fun, "current_authority_derived_key_seed", level + 1);
  fun(self, name, 33, "fd_vote_instruction", --level);
}
void fd_vote_instruction_copy_to(fd_vote_instruction_t* to, fd_vote_instruction_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_vote_instruction_size(from) );
  void const *   ptr = (void const *) enc;
  fd_vote_instruction_encode( from, &ptr );
  void *input = (void *) enc;
  fd_vote_instruction_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_vote_instruction_size(fd_vote_instruction_t* self) {
  ulong size = 0;
  size += sizeof(uint);
  switch (self->discriminant) {
  case 0: {
    size += fd_vote_init_size(&self->inner.initialize_account);
    break;
  }
  case 1: {
    size += fd_vote_authorize_pubkey_size(&self->inner.authorize);
    break;
  }
  case 2: {
    size += fd_vote_size(&self->inner.vote);
    break;
  }
  case 3: {
    size += sizeof(ulong);
    break;
  }
  case 5: {
    size += sizeof(char);
    break;
  }
  case 6: {
    size += fd_vote_switch_size(&self->inner.vote_switch);
    break;
  }
  case 7: {
    size += fd_vote_authorize_size(&self->inner.authorize_checked);
    break;
  }
  case 8: {
    size += fd_vote_state_update_size(&self->inner.update_vote_state);
    break;
  }
  case 9: {
    size += fd_update_vote_state_switch_size(&self->inner.update_vote_state_switch);
    break;
  }
  case 10: {
    size += fd_vote_authorize_with_seed_args_size(&self->inner.authorize_with_seed);
    break;
  }
  case 11: {
    size += fd_vote_authorize_checked_with_seed_args_size(&self->inner.authorize_checked_with_seed);
    break;
  }
  }
  return size;
}

void fd_vote_instruction_inner_encode(fd_vote_instruction_inner_t* self, uint discriminant, void const** data) {
  switch (discriminant) {
  case 0: {
    fd_vote_init_encode(&self->initialize_account, data);
    break;
  }
  case 1: {
    fd_vote_authorize_pubkey_encode(&self->authorize, data);
    break;
  }
  case 2: {
    fd_vote_encode(&self->vote, data);
    break;
  }
  case 3: {
    fd_bincode_uint64_encode(&self->withdraw, data);
    break;
  }
  case 5: {
    fd_bincode_uint8_encode(&self->update_commission, data);
    break;
  }
  case 6: {
    fd_vote_switch_encode(&self->vote_switch, data);
    break;
  }
  case 7: {
    fd_vote_authorize_encode(&self->authorize_checked, data);
    break;
  }
  case 8: {
    fd_vote_state_update_encode(&self->update_vote_state, data);
    break;
  }
  case 9: {
    fd_update_vote_state_switch_encode(&self->update_vote_state_switch, data);
    break;
  }
  case 10: {
    fd_vote_authorize_with_seed_args_encode(&self->authorize_with_seed, data);
    break;
  }
  case 11: {
    fd_vote_authorize_checked_with_seed_args_encode(&self->authorize_checked_with_seed, data);
    break;
  }
  }
}
void fd_vote_instruction_encode(fd_vote_instruction_t* self, void const** data) {
  fd_bincode_uint32_encode(&self->discriminant, data);
  fd_vote_instruction_inner_encode(&self->inner, self->discriminant, data);
}

void fd_system_program_instruction_create_account_decode(fd_system_program_instruction_create_account_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->lamports, data, dataend);
  fd_bincode_uint64_decode(&self->space, data, dataend);
  fd_pubkey_decode(&self->owner, data, dataend, allocf, allocf_arg);
}
void fd_system_program_instruction_create_account_destroy(fd_system_program_instruction_create_account_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->owner, freef, freef_arg);
}

void fd_system_program_instruction_create_account_walk(fd_system_program_instruction_create_account_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_system_program_instruction_create_account", level++);
  fun(&self->lamports, "lamports", 11, "ulong", level + 1);
  fun(&self->space, "space", 11, "ulong", level + 1);
  fd_pubkey_walk(&self->owner, fun, "owner", level + 1);
  fun(self, name, 33, "fd_system_program_instruction_create_account", --level);
}
void fd_system_program_instruction_create_account_copy_to(fd_system_program_instruction_create_account_t* to, fd_system_program_instruction_create_account_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_system_program_instruction_create_account_size(from) );
  void const *   ptr = (void const *) enc;
  fd_system_program_instruction_create_account_encode( from, &ptr );
  void *input = (void *) enc;
  fd_system_program_instruction_create_account_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_system_program_instruction_create_account_size(fd_system_program_instruction_create_account_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += fd_pubkey_size(&self->owner);
  return size;
}

void fd_system_program_instruction_create_account_encode(fd_system_program_instruction_create_account_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->lamports, data);
  fd_bincode_uint64_encode(&self->space, data);
  fd_pubkey_encode(&self->owner, data);
}

void fd_system_program_instruction_create_account_with_seed_decode(fd_system_program_instruction_create_account_with_seed_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->base, data, dataend, allocf, allocf_arg);
  ulong slen;
  fd_bincode_uint64_decode(&slen, data, dataend);
  self->seed = (char*)(*allocf)(allocf_arg, 1, slen + 1);
  fd_bincode_bytes_decode((uchar *) self->seed, slen, data, dataend);
  self->seed[slen] = '\0';
  fd_bincode_uint64_decode(&self->lamports, data, dataend);
  fd_bincode_uint64_decode(&self->space, data, dataend);
  fd_pubkey_decode(&self->owner, data, dataend, allocf, allocf_arg);
}
void fd_system_program_instruction_create_account_with_seed_destroy(fd_system_program_instruction_create_account_with_seed_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->base, freef, freef_arg);
  if (NULL != self->seed) {
    freef(freef_arg, self->seed);
    self->seed = NULL;
  }
  fd_pubkey_destroy(&self->owner, freef, freef_arg);
}

void fd_system_program_instruction_create_account_with_seed_walk(fd_system_program_instruction_create_account_with_seed_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_system_program_instruction_create_account_with_seed", level++);
  fd_pubkey_walk(&self->base, fun, "base", level + 1);
  fun(self->seed, "seed", 2, "char*", level + 1);
  fun(&self->lamports, "lamports", 11, "ulong", level + 1);
  fun(&self->space, "space", 11, "ulong", level + 1);
  fd_pubkey_walk(&self->owner, fun, "owner", level + 1);
  fun(self, name, 33, "fd_system_program_instruction_create_account_with_seed", --level);
}
void fd_system_program_instruction_create_account_with_seed_copy_to(fd_system_program_instruction_create_account_with_seed_t* to, fd_system_program_instruction_create_account_with_seed_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_system_program_instruction_create_account_with_seed_size(from) );
  void const *   ptr = (void const *) enc;
  fd_system_program_instruction_create_account_with_seed_encode( from, &ptr );
  void *input = (void *) enc;
  fd_system_program_instruction_create_account_with_seed_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_system_program_instruction_create_account_with_seed_size(fd_system_program_instruction_create_account_with_seed_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->base);
  size += sizeof(ulong) + strlen(self->seed);
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += fd_pubkey_size(&self->owner);
  return size;
}

void fd_system_program_instruction_create_account_with_seed_encode(fd_system_program_instruction_create_account_with_seed_t* self, void const** data) {
  fd_pubkey_encode(&self->base, data);
  ulong slen = strlen((char *) self->seed);
  fd_bincode_uint64_encode(&slen, data);
  fd_bincode_bytes_encode((uchar *) self->seed, slen, data);
  fd_bincode_uint64_encode(&self->lamports, data);
  fd_bincode_uint64_encode(&self->space, data);
  fd_pubkey_encode(&self->owner, data);
}

void fd_system_program_instruction_allocate_with_seed_decode(fd_system_program_instruction_allocate_with_seed_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->base, data, dataend, allocf, allocf_arg);
  ulong slen;
  fd_bincode_uint64_decode(&slen, data, dataend);
  self->seed = (char*)(*allocf)(allocf_arg, 1, slen + 1);
  fd_bincode_bytes_decode((uchar *) self->seed, slen, data, dataend);
  self->seed[slen] = '\0';
  fd_bincode_uint64_decode(&self->space, data, dataend);
  fd_pubkey_decode(&self->owner, data, dataend, allocf, allocf_arg);
}
void fd_system_program_instruction_allocate_with_seed_destroy(fd_system_program_instruction_allocate_with_seed_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->base, freef, freef_arg);
  if (NULL != self->seed) {
    freef(freef_arg, self->seed);
    self->seed = NULL;
  }
  fd_pubkey_destroy(&self->owner, freef, freef_arg);
}

void fd_system_program_instruction_allocate_with_seed_walk(fd_system_program_instruction_allocate_with_seed_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_system_program_instruction_allocate_with_seed", level++);
  fd_pubkey_walk(&self->base, fun, "base", level + 1);
  fun(self->seed, "seed", 2, "char*", level + 1);
  fun(&self->space, "space", 11, "ulong", level + 1);
  fd_pubkey_walk(&self->owner, fun, "owner", level + 1);
  fun(self, name, 33, "fd_system_program_instruction_allocate_with_seed", --level);
}
void fd_system_program_instruction_allocate_with_seed_copy_to(fd_system_program_instruction_allocate_with_seed_t* to, fd_system_program_instruction_allocate_with_seed_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_system_program_instruction_allocate_with_seed_size(from) );
  void const *   ptr = (void const *) enc;
  fd_system_program_instruction_allocate_with_seed_encode( from, &ptr );
  void *input = (void *) enc;
  fd_system_program_instruction_allocate_with_seed_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_system_program_instruction_allocate_with_seed_size(fd_system_program_instruction_allocate_with_seed_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->base);
  size += sizeof(ulong) + strlen(self->seed);
  size += sizeof(ulong);
  size += fd_pubkey_size(&self->owner);
  return size;
}

void fd_system_program_instruction_allocate_with_seed_encode(fd_system_program_instruction_allocate_with_seed_t* self, void const** data) {
  fd_pubkey_encode(&self->base, data);
  ulong slen = strlen((char *) self->seed);
  fd_bincode_uint64_encode(&slen, data);
  fd_bincode_bytes_encode((uchar *) self->seed, slen, data);
  fd_bincode_uint64_encode(&self->space, data);
  fd_pubkey_encode(&self->owner, data);
}

void fd_system_program_instruction_assign_with_seed_decode(fd_system_program_instruction_assign_with_seed_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->base, data, dataend, allocf, allocf_arg);
  ulong slen;
  fd_bincode_uint64_decode(&slen, data, dataend);
  self->seed = (char*)(*allocf)(allocf_arg, 1, slen + 1);
  fd_bincode_bytes_decode((uchar *) self->seed, slen, data, dataend);
  self->seed[slen] = '\0';
  fd_pubkey_decode(&self->owner, data, dataend, allocf, allocf_arg);
}
void fd_system_program_instruction_assign_with_seed_destroy(fd_system_program_instruction_assign_with_seed_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->base, freef, freef_arg);
  if (NULL != self->seed) {
    freef(freef_arg, self->seed);
    self->seed = NULL;
  }
  fd_pubkey_destroy(&self->owner, freef, freef_arg);
}

void fd_system_program_instruction_assign_with_seed_walk(fd_system_program_instruction_assign_with_seed_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_system_program_instruction_assign_with_seed", level++);
  fd_pubkey_walk(&self->base, fun, "base", level + 1);
  fun(self->seed, "seed", 2, "char*", level + 1);
  fd_pubkey_walk(&self->owner, fun, "owner", level + 1);
  fun(self, name, 33, "fd_system_program_instruction_assign_with_seed", --level);
}
void fd_system_program_instruction_assign_with_seed_copy_to(fd_system_program_instruction_assign_with_seed_t* to, fd_system_program_instruction_assign_with_seed_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_system_program_instruction_assign_with_seed_size(from) );
  void const *   ptr = (void const *) enc;
  fd_system_program_instruction_assign_with_seed_encode( from, &ptr );
  void *input = (void *) enc;
  fd_system_program_instruction_assign_with_seed_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_system_program_instruction_assign_with_seed_size(fd_system_program_instruction_assign_with_seed_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->base);
  size += sizeof(ulong) + strlen(self->seed);
  size += fd_pubkey_size(&self->owner);
  return size;
}

void fd_system_program_instruction_assign_with_seed_encode(fd_system_program_instruction_assign_with_seed_t* self, void const** data) {
  fd_pubkey_encode(&self->base, data);
  ulong slen = strlen((char *) self->seed);
  fd_bincode_uint64_encode(&slen, data);
  fd_bincode_bytes_encode((uchar *) self->seed, slen, data);
  fd_pubkey_encode(&self->owner, data);
}

void fd_system_program_instruction_transfer_with_seed_decode(fd_system_program_instruction_transfer_with_seed_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->lamports, data, dataend);
  ulong slen;
  fd_bincode_uint64_decode(&slen, data, dataend);
  self->from_seed = (char*)(*allocf)(allocf_arg, 1, slen + 1);
  fd_bincode_bytes_decode((uchar *) self->from_seed, slen, data, dataend);
  self->from_seed[slen] = '\0';
  fd_pubkey_decode(&self->from_owner, data, dataend, allocf, allocf_arg);
}
void fd_system_program_instruction_transfer_with_seed_destroy(fd_system_program_instruction_transfer_with_seed_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->from_seed) {
    freef(freef_arg, self->from_seed);
    self->from_seed = NULL;
  }
  fd_pubkey_destroy(&self->from_owner, freef, freef_arg);
}

void fd_system_program_instruction_transfer_with_seed_walk(fd_system_program_instruction_transfer_with_seed_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_system_program_instruction_transfer_with_seed", level++);
  fun(&self->lamports, "lamports", 11, "ulong", level + 1);
  fun(self->from_seed, "from_seed", 2, "char*", level + 1);
  fd_pubkey_walk(&self->from_owner, fun, "from_owner", level + 1);
  fun(self, name, 33, "fd_system_program_instruction_transfer_with_seed", --level);
}
void fd_system_program_instruction_transfer_with_seed_copy_to(fd_system_program_instruction_transfer_with_seed_t* to, fd_system_program_instruction_transfer_with_seed_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_system_program_instruction_transfer_with_seed_size(from) );
  void const *   ptr = (void const *) enc;
  fd_system_program_instruction_transfer_with_seed_encode( from, &ptr );
  void *input = (void *) enc;
  fd_system_program_instruction_transfer_with_seed_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_system_program_instruction_transfer_with_seed_size(fd_system_program_instruction_transfer_with_seed_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(ulong) + strlen(self->from_seed);
  size += fd_pubkey_size(&self->from_owner);
  return size;
}

void fd_system_program_instruction_transfer_with_seed_encode(fd_system_program_instruction_transfer_with_seed_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->lamports, data);
  ulong slen = strlen((char *) self->from_seed);
  fd_bincode_uint64_encode(&slen, data);
  fd_bincode_bytes_encode((uchar *) self->from_seed, slen, data);
  fd_pubkey_encode(&self->from_owner, data);
}

uchar fd_system_program_instruction_is_create_account(fd_system_program_instruction_t* self) {
  return self->discriminant == 0;
}
uchar fd_system_program_instruction_is_assign(fd_system_program_instruction_t* self) {
  return self->discriminant == 1;
}
uchar fd_system_program_instruction_is_transfer(fd_system_program_instruction_t* self) {
  return self->discriminant == 2;
}
uchar fd_system_program_instruction_is_create_account_with_seed(fd_system_program_instruction_t* self) {
  return self->discriminant == 3;
}
uchar fd_system_program_instruction_is_advance_nonce_account(fd_system_program_instruction_t* self) {
  return self->discriminant == 4;
}
uchar fd_system_program_instruction_is_withdraw_nonce_account(fd_system_program_instruction_t* self) {
  return self->discriminant == 5;
}
uchar fd_system_program_instruction_is_initialize_nonce_account(fd_system_program_instruction_t* self) {
  return self->discriminant == 6;
}
uchar fd_system_program_instruction_is_authorize_nonce_account(fd_system_program_instruction_t* self) {
  return self->discriminant == 7;
}
uchar fd_system_program_instruction_is_allocate(fd_system_program_instruction_t* self) {
  return self->discriminant == 8;
}
uchar fd_system_program_instruction_is_allocate_with_seed(fd_system_program_instruction_t* self) {
  return self->discriminant == 9;
}
uchar fd_system_program_instruction_is_assign_with_seed(fd_system_program_instruction_t* self) {
  return self->discriminant == 10;
}
uchar fd_system_program_instruction_is_transfer_with_seed(fd_system_program_instruction_t* self) {
  return self->discriminant == 11;
}
uchar fd_system_program_instruction_is_upgrade_nonce_account(fd_system_program_instruction_t* self) {
  return self->discriminant == 12;
}
void fd_system_program_instruction_inner_decode(fd_system_program_instruction_inner_t* self, uint discriminant, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  switch (discriminant) {
  case 0: {
    fd_system_program_instruction_create_account_decode(&self->create_account, data, dataend, allocf, allocf_arg);
    break;
  }
  case 1: {
    fd_pubkey_decode(&self->assign, data, dataend, allocf, allocf_arg);
    break;
  }
  case 2: {
    fd_bincode_uint64_decode(&self->transfer, data, dataend);
    break;
  }
  case 3: {
    fd_system_program_instruction_create_account_with_seed_decode(&self->create_account_with_seed, data, dataend, allocf, allocf_arg);
    break;
  }
  case 4: {
    break;
  }
  case 5: {
    fd_bincode_uint64_decode(&self->withdraw_nonce_account, data, dataend);
    break;
  }
  case 6: {
    fd_pubkey_decode(&self->initialize_nonce_account, data, dataend, allocf, allocf_arg);
    break;
  }
  case 7: {
    fd_pubkey_decode(&self->authorize_nonce_account, data, dataend, allocf, allocf_arg);
    break;
  }
  case 8: {
    fd_bincode_uint64_decode(&self->allocate, data, dataend);
    break;
  }
  case 9: {
    fd_system_program_instruction_allocate_with_seed_decode(&self->allocate_with_seed, data, dataend, allocf, allocf_arg);
    break;
  }
  case 10: {
    fd_system_program_instruction_assign_with_seed_decode(&self->assign_with_seed, data, dataend, allocf, allocf_arg);
    break;
  }
  case 11: {
    fd_system_program_instruction_transfer_with_seed_decode(&self->transfer_with_seed, data, dataend, allocf, allocf_arg);
    break;
  }
  case 12: {
    break;
  }
  default: FD_LOG_ERR(( "unhandled type"));
  }
}
void fd_system_program_instruction_decode(fd_system_program_instruction_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint32_decode(&self->discriminant, data, dataend);
  fd_system_program_instruction_inner_decode(&self->inner, self->discriminant, data, dataend, allocf, allocf_arg);
}
void fd_system_program_instruction_inner_destroy(fd_system_program_instruction_inner_t* self, uint discriminant, fd_free_fun_t freef, void* freef_arg) {
  switch (discriminant) {
  case 0: {
    fd_system_program_instruction_create_account_destroy(&self->create_account, freef, freef_arg);
    break;
  }
  case 1: {
    fd_pubkey_destroy(&self->assign, freef, freef_arg);
    break;
  }
  case 2: {
    break;
  }
  case 3: {
    fd_system_program_instruction_create_account_with_seed_destroy(&self->create_account_with_seed, freef, freef_arg);
    break;
  }
  case 4: {
    break;
  }
  case 5: {
    break;
  }
  case 6: {
    fd_pubkey_destroy(&self->initialize_nonce_account, freef, freef_arg);
    break;
  }
  case 7: {
    fd_pubkey_destroy(&self->authorize_nonce_account, freef, freef_arg);
    break;
  }
  case 8: {
    break;
  }
  case 9: {
    fd_system_program_instruction_allocate_with_seed_destroy(&self->allocate_with_seed, freef, freef_arg);
    break;
  }
  case 10: {
    fd_system_program_instruction_assign_with_seed_destroy(&self->assign_with_seed, freef, freef_arg);
    break;
  }
  case 11: {
    fd_system_program_instruction_transfer_with_seed_destroy(&self->transfer_with_seed, freef, freef_arg);
    break;
  }
  case 12: {
    break;
  }
  default: break; // FD_LOG_ERR(( "unhandled type"));
  }
}
void fd_system_program_instruction_destroy(fd_system_program_instruction_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_system_program_instruction_inner_destroy(&self->inner, self->discriminant, freef, freef_arg);
}

void fd_system_program_instruction_walk(fd_system_program_instruction_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_system_program_instruction", level++);
  // enum fd_pubkey_walk(&self->from_owner, fun, "from_owner", level + 1);
  fun(self, name, 33, "fd_system_program_instruction", --level);
}
void fd_system_program_instruction_copy_to(fd_system_program_instruction_t* to, fd_system_program_instruction_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_system_program_instruction_size(from) );
  void const *   ptr = (void const *) enc;
  fd_system_program_instruction_encode( from, &ptr );
  void *input = (void *) enc;
  fd_system_program_instruction_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_system_program_instruction_size(fd_system_program_instruction_t* self) {
  ulong size = 0;
  size += sizeof(uint);
  switch (self->discriminant) {
  case 0: {
    size += fd_system_program_instruction_create_account_size(&self->inner.create_account);
    break;
  }
  case 1: {
    size += fd_pubkey_size(&self->inner.assign);
    break;
  }
  case 2: {
    size += sizeof(ulong);
    break;
  }
  case 3: {
    size += fd_system_program_instruction_create_account_with_seed_size(&self->inner.create_account_with_seed);
    break;
  }
  case 5: {
    size += sizeof(ulong);
    break;
  }
  case 6: {
    size += fd_pubkey_size(&self->inner.initialize_nonce_account);
    break;
  }
  case 7: {
    size += fd_pubkey_size(&self->inner.authorize_nonce_account);
    break;
  }
  case 8: {
    size += sizeof(ulong);
    break;
  }
  case 9: {
    size += fd_system_program_instruction_allocate_with_seed_size(&self->inner.allocate_with_seed);
    break;
  }
  case 10: {
    size += fd_system_program_instruction_assign_with_seed_size(&self->inner.assign_with_seed);
    break;
  }
  case 11: {
    size += fd_system_program_instruction_transfer_with_seed_size(&self->inner.transfer_with_seed);
    break;
  }
  }
  return size;
}

void fd_system_program_instruction_inner_encode(fd_system_program_instruction_inner_t* self, uint discriminant, void const** data) {
  switch (discriminant) {
  case 0: {
    fd_system_program_instruction_create_account_encode(&self->create_account, data);
    break;
  }
  case 1: {
    fd_pubkey_encode(&self->assign, data);
    break;
  }
  case 2: {
    fd_bincode_uint64_encode(&self->transfer, data);
    break;
  }
  case 3: {
    fd_system_program_instruction_create_account_with_seed_encode(&self->create_account_with_seed, data);
    break;
  }
  case 5: {
    fd_bincode_uint64_encode(&self->withdraw_nonce_account, data);
    break;
  }
  case 6: {
    fd_pubkey_encode(&self->initialize_nonce_account, data);
    break;
  }
  case 7: {
    fd_pubkey_encode(&self->authorize_nonce_account, data);
    break;
  }
  case 8: {
    fd_bincode_uint64_encode(&self->allocate, data);
    break;
  }
  case 9: {
    fd_system_program_instruction_allocate_with_seed_encode(&self->allocate_with_seed, data);
    break;
  }
  case 10: {
    fd_system_program_instruction_assign_with_seed_encode(&self->assign_with_seed, data);
    break;
  }
  case 11: {
    fd_system_program_instruction_transfer_with_seed_encode(&self->transfer_with_seed, data);
    break;
  }
  }
}
void fd_system_program_instruction_encode(fd_system_program_instruction_t* self, void const** data) {
  fd_bincode_uint32_encode(&self->discriminant, data);
  fd_system_program_instruction_inner_encode(&self->inner, self->discriminant, data);
}

uchar fd_system_error_is_account_already_in_use(fd_system_error_t* self) {
  return self->discriminant == 0;
}
uchar fd_system_error_is_result_with_negative_lamports(fd_system_error_t* self) {
  return self->discriminant == 1;
}
uchar fd_system_error_is_invalid_program_id(fd_system_error_t* self) {
  return self->discriminant == 2;
}
uchar fd_system_error_is_invalid_account_data_length(fd_system_error_t* self) {
  return self->discriminant == 3;
}
uchar fd_system_error_is_max_seed_length_exceeded(fd_system_error_t* self) {
  return self->discriminant == 4;
}
uchar fd_system_error_is_address_with_seed_mismatch(fd_system_error_t* self) {
  return self->discriminant == 5;
}
uchar fd_system_error_is_nonce_no_recent_blockhashes(fd_system_error_t* self) {
  return self->discriminant == 6;
}
uchar fd_system_error_is_nonce_blockhash_not_expired(fd_system_error_t* self) {
  return self->discriminant == 7;
}
uchar fd_system_error_is_nonce_unexpected_blockhash_value(fd_system_error_t* self) {
  return self->discriminant == 8;
}
void fd_system_error_inner_decode(fd_system_error_inner_t* self, uint discriminant, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  switch (discriminant) {
  case 0: {
    break;
  }
  case 1: {
    break;
  }
  case 2: {
    break;
  }
  case 3: {
    break;
  }
  case 4: {
    break;
  }
  case 5: {
    break;
  }
  case 6: {
    break;
  }
  case 7: {
    break;
  }
  case 8: {
    break;
  }
  default: FD_LOG_ERR(( "unhandled type"));
  }
}
void fd_system_error_decode(fd_system_error_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint32_decode(&self->discriminant, data, dataend);
  fd_system_error_inner_decode(&self->inner, self->discriminant, data, dataend, allocf, allocf_arg);
}
void fd_system_error_inner_destroy(fd_system_error_inner_t* self, uint discriminant, fd_free_fun_t freef, void* freef_arg) {
  switch (discriminant) {
  case 0: {
    break;
  }
  case 1: {
    break;
  }
  case 2: {
    break;
  }
  case 3: {
    break;
  }
  case 4: {
    break;
  }
  case 5: {
    break;
  }
  case 6: {
    break;
  }
  case 7: {
    break;
  }
  case 8: {
    break;
  }
  default: break; // FD_LOG_ERR(( "unhandled type"));
  }
}
void fd_system_error_destroy(fd_system_error_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_system_error_inner_destroy(&self->inner, self->discriminant, freef, freef_arg);
}

void fd_system_error_walk(fd_system_error_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_system_error", level++);
  // enum fd_pubkey_walk(&self->from_owner, fun, "from_owner", level + 1);
  fun(self, name, 33, "fd_system_error", --level);
}
void fd_system_error_copy_to(fd_system_error_t* to, fd_system_error_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_system_error_size(from) );
  void const *   ptr = (void const *) enc;
  fd_system_error_encode( from, &ptr );
  void *input = (void *) enc;
  fd_system_error_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_system_error_size(fd_system_error_t* self) {
  ulong size = 0;
  size += sizeof(uint);
  switch (self->discriminant) {
  }
  return size;
}

void fd_system_error_inner_encode(fd_system_error_inner_t* self, uint discriminant, void const** data) {
  switch (discriminant) {
  }
}
void fd_system_error_encode(fd_system_error_t* self, void const** data) {
  fd_bincode_uint32_encode(&self->discriminant, data);
  fd_system_error_inner_encode(&self->inner, self->discriminant, data);
}

void fd_stake_authorized_decode(fd_stake_authorized_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->staker, data, dataend, allocf, allocf_arg);
  fd_pubkey_decode(&self->withdrawer, data, dataend, allocf, allocf_arg);
}
void fd_stake_authorized_destroy(fd_stake_authorized_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->staker, freef, freef_arg);
  fd_pubkey_destroy(&self->withdrawer, freef, freef_arg);
}

void fd_stake_authorized_walk(fd_stake_authorized_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_stake_authorized", level++);
  fd_pubkey_walk(&self->staker, fun, "staker", level + 1);
  fd_pubkey_walk(&self->withdrawer, fun, "withdrawer", level + 1);
  fun(self, name, 33, "fd_stake_authorized", --level);
}
void fd_stake_authorized_copy_to(fd_stake_authorized_t* to, fd_stake_authorized_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_stake_authorized_size(from) );
  void const *   ptr = (void const *) enc;
  fd_stake_authorized_encode( from, &ptr );
  void *input = (void *) enc;
  fd_stake_authorized_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_stake_authorized_size(fd_stake_authorized_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->staker);
  size += fd_pubkey_size(&self->withdrawer);
  return size;
}

void fd_stake_authorized_encode(fd_stake_authorized_t* self, void const** data) {
  fd_pubkey_encode(&self->staker, data);
  fd_pubkey_encode(&self->withdrawer, data);
}

void fd_stake_lockup_decode(fd_stake_lockup_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->unix_timestamp, data, dataend);
  fd_bincode_uint64_decode(&self->epoch, data, dataend);
  fd_pubkey_decode(&self->custodian, data, dataend, allocf, allocf_arg);
}
void fd_stake_lockup_destroy(fd_stake_lockup_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->custodian, freef, freef_arg);
}

void fd_stake_lockup_walk(fd_stake_lockup_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_stake_lockup", level++);
  fun(&self->unix_timestamp, "unix_timestamp", 11, "ulong", level + 1);
  fun(&self->epoch, "epoch", 11, "ulong", level + 1);
  fd_pubkey_walk(&self->custodian, fun, "custodian", level + 1);
  fun(self, name, 33, "fd_stake_lockup", --level);
}
void fd_stake_lockup_copy_to(fd_stake_lockup_t* to, fd_stake_lockup_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_stake_lockup_size(from) );
  void const *   ptr = (void const *) enc;
  fd_stake_lockup_encode( from, &ptr );
  void *input = (void *) enc;
  fd_stake_lockup_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_stake_lockup_size(fd_stake_lockup_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += sizeof(ulong);
  size += fd_pubkey_size(&self->custodian);
  return size;
}

void fd_stake_lockup_encode(fd_stake_lockup_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->unix_timestamp, data);
  fd_bincode_uint64_encode(&self->epoch, data);
  fd_pubkey_encode(&self->custodian, data);
}

void fd_stake_instruction_initialize_decode(fd_stake_instruction_initialize_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_stake_authorized_decode(&self->authorized, data, dataend, allocf, allocf_arg);
  fd_pubkey_decode(&self->lockup, data, dataend, allocf, allocf_arg);
}
void fd_stake_instruction_initialize_destroy(fd_stake_instruction_initialize_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_stake_authorized_destroy(&self->authorized, freef, freef_arg);
  fd_pubkey_destroy(&self->lockup, freef, freef_arg);
}

void fd_stake_instruction_initialize_walk(fd_stake_instruction_initialize_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_stake_instruction_initialize", level++);
  fd_stake_authorized_walk(&self->authorized, fun, "authorized", level + 1);
  fd_pubkey_walk(&self->lockup, fun, "lockup", level + 1);
  fun(self, name, 33, "fd_stake_instruction_initialize", --level);
}
void fd_stake_instruction_initialize_copy_to(fd_stake_instruction_initialize_t* to, fd_stake_instruction_initialize_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_stake_instruction_initialize_size(from) );
  void const *   ptr = (void const *) enc;
  fd_stake_instruction_initialize_encode( from, &ptr );
  void *input = (void *) enc;
  fd_stake_instruction_initialize_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_stake_instruction_initialize_size(fd_stake_instruction_initialize_t* self) {
  ulong size = 0;
  size += fd_stake_authorized_size(&self->authorized);
  size += fd_pubkey_size(&self->lockup);
  return size;
}

void fd_stake_instruction_initialize_encode(fd_stake_instruction_initialize_t* self, void const** data) {
  fd_stake_authorized_encode(&self->authorized, data);
  fd_pubkey_encode(&self->lockup, data);
}

uchar fd_stake_authorize_is_staker(fd_stake_authorize_t* self) {
  return self->discriminant == 0;
}
uchar fd_stake_authorize_is_withdrawer(fd_stake_authorize_t* self) {
  return self->discriminant == 1;
}
void fd_stake_authorize_inner_decode(fd_stake_authorize_inner_t* self, uint discriminant, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  switch (discriminant) {
  case 0: {
    break;
  }
  case 1: {
    break;
  }
  default: FD_LOG_ERR(( "unhandled type"));
  }
}
void fd_stake_authorize_decode(fd_stake_authorize_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint32_decode(&self->discriminant, data, dataend);
  fd_stake_authorize_inner_decode(&self->inner, self->discriminant, data, dataend, allocf, allocf_arg);
}
void fd_stake_authorize_inner_destroy(fd_stake_authorize_inner_t* self, uint discriminant, fd_free_fun_t freef, void* freef_arg) {
  switch (discriminant) {
  case 0: {
    break;
  }
  case 1: {
    break;
  }
  default: break; // FD_LOG_ERR(( "unhandled type"));
  }
}
void fd_stake_authorize_destroy(fd_stake_authorize_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_stake_authorize_inner_destroy(&self->inner, self->discriminant, freef, freef_arg);
}

void fd_stake_authorize_walk(fd_stake_authorize_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_stake_authorize", level++);
  // enum fd_pubkey_walk(&self->lockup, fun, "lockup", level + 1);
  fun(self, name, 33, "fd_stake_authorize", --level);
}
void fd_stake_authorize_copy_to(fd_stake_authorize_t* to, fd_stake_authorize_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_stake_authorize_size(from) );
  void const *   ptr = (void const *) enc;
  fd_stake_authorize_encode( from, &ptr );
  void *input = (void *) enc;
  fd_stake_authorize_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_stake_authorize_size(fd_stake_authorize_t* self) {
  ulong size = 0;
  size += sizeof(uint);
  switch (self->discriminant) {
  }
  return size;
}

void fd_stake_authorize_inner_encode(fd_stake_authorize_inner_t* self, uint discriminant, void const** data) {
  switch (discriminant) {
  }
}
void fd_stake_authorize_encode(fd_stake_authorize_t* self, void const** data) {
  fd_bincode_uint32_encode(&self->discriminant, data);
  fd_stake_authorize_inner_encode(&self->inner, self->discriminant, data);
}

void fd_stake_instruction_authorize_decode(fd_stake_instruction_authorize_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->pubkey, data, dataend, allocf, allocf_arg);
  fd_stake_authorize_decode(&self->stake_authorize, data, dataend, allocf, allocf_arg);
}
void fd_stake_instruction_authorize_destroy(fd_stake_instruction_authorize_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->pubkey, freef, freef_arg);
  fd_stake_authorize_destroy(&self->stake_authorize, freef, freef_arg);
}

void fd_stake_instruction_authorize_walk(fd_stake_instruction_authorize_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_stake_instruction_authorize", level++);
  fd_pubkey_walk(&self->pubkey, fun, "pubkey", level + 1);
  fd_stake_authorize_walk(&self->stake_authorize, fun, "stake_authorize", level + 1);
  fun(self, name, 33, "fd_stake_instruction_authorize", --level);
}
void fd_stake_instruction_authorize_copy_to(fd_stake_instruction_authorize_t* to, fd_stake_instruction_authorize_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_stake_instruction_authorize_size(from) );
  void const *   ptr = (void const *) enc;
  fd_stake_instruction_authorize_encode( from, &ptr );
  void *input = (void *) enc;
  fd_stake_instruction_authorize_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_stake_instruction_authorize_size(fd_stake_instruction_authorize_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->pubkey);
  size += fd_stake_authorize_size(&self->stake_authorize);
  return size;
}

void fd_stake_instruction_authorize_encode(fd_stake_instruction_authorize_t* self, void const** data) {
  fd_pubkey_encode(&self->pubkey, data);
  fd_stake_authorize_encode(&self->stake_authorize, data);
}

void fd_lockup_args_decode(fd_lockup_args_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  if (fd_bincode_option_decode(data, dataend)) {
    self->unix_timestamp = (ulong*)(*allocf)(allocf_arg, 8, sizeof(ulong));
    fd_bincode_uint64_decode(self->unix_timestamp, data, dataend);
  } else
    self->unix_timestamp = NULL;
  if (fd_bincode_option_decode(data, dataend)) {
    self->epoch = (ulong*)(*allocf)(allocf_arg, 8, sizeof(ulong));
    fd_bincode_uint64_decode(self->epoch, data, dataend);
  } else
    self->epoch = NULL;
  if (fd_bincode_option_decode(data, dataend)) {
    self->custodian = (fd_pubkey_t*)(*allocf)(allocf_arg, FD_PUBKEY_ALIGN, FD_PUBKEY_FOOTPRINT);
    fd_pubkey_decode(self->custodian, data, dataend, allocf, allocf_arg);
  } else
    self->custodian = NULL;
}
void fd_lockup_args_destroy(fd_lockup_args_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->unix_timestamp) {
    freef(freef_arg, self->unix_timestamp);
    self->unix_timestamp = NULL;
  }
  if (NULL != self->epoch) {
    freef(freef_arg, self->epoch);
    self->epoch = NULL;
  }
  if (NULL != self->custodian) {
    fd_pubkey_destroy(self->custodian,  freef, freef_arg);
    freef(freef_arg, self->custodian);
    self->custodian = NULL;
  }
}

void fd_lockup_args_walk(fd_lockup_args_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_lockup_args", level++);
  fun(self->unix_timestamp, "unix_timestamp", 11, "ulong", level + 1);
  fun(self->epoch, "epoch", 11, "ulong", level + 1);
  // fun(&self->custodian, "custodian", 16, "option", level + 1);
  fun(self, name, 33, "fd_lockup_args", --level);
}
void fd_lockup_args_copy_to(fd_lockup_args_t* to, fd_lockup_args_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_lockup_args_size(from) );
  void const *   ptr = (void const *) enc;
  fd_lockup_args_encode( from, &ptr );
  void *input = (void *) enc;
  fd_lockup_args_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_lockup_args_size(fd_lockup_args_t* self) {
  ulong size = 0;
  size += sizeof(char);
  if (NULL !=  self->unix_timestamp) {
    size += sizeof(ulong);
  }
  size += sizeof(char);
  if (NULL !=  self->epoch) {
    size += sizeof(ulong);
  }
  size += sizeof(char);
  if (NULL !=  self->custodian) {
    size += fd_pubkey_size(self->custodian);
  }
  return size;
}

void fd_lockup_args_encode(fd_lockup_args_t* self, void const** data) {
  if (self->unix_timestamp!= NULL) {
    fd_bincode_option_encode(1, data);
    fd_bincode_uint64_encode(self->unix_timestamp, data);
  } else
    fd_bincode_option_encode(0, data);
  if (self->epoch!= NULL) {
    fd_bincode_option_encode(1, data);
    fd_bincode_uint64_encode(self->epoch, data);
  } else
    fd_bincode_option_encode(0, data);
  if (self->custodian!= NULL) {
    fd_bincode_option_encode(1, data);
    fd_pubkey_encode(self->custodian, data);
  } else
    fd_bincode_option_encode(0, data);
}

void fd_authorize_with_seed_args_decode(fd_authorize_with_seed_args_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_pubkey_decode(&self->new_authorized_pubkey, data, dataend, allocf, allocf_arg);
  fd_stake_authorize_decode(&self->stake_authorize, data, dataend, allocf, allocf_arg);
  ulong slen;
  fd_bincode_uint64_decode(&slen, data, dataend);
  self->authority_seed = (char*)(*allocf)(allocf_arg, 1, slen + 1);
  fd_bincode_bytes_decode((uchar *) self->authority_seed, slen, data, dataend);
  self->authority_seed[slen] = '\0';
  fd_pubkey_decode(&self->authority_owner, data, dataend, allocf, allocf_arg);
}
void fd_authorize_with_seed_args_destroy(fd_authorize_with_seed_args_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_pubkey_destroy(&self->new_authorized_pubkey, freef, freef_arg);
  fd_stake_authorize_destroy(&self->stake_authorize, freef, freef_arg);
  if (NULL != self->authority_seed) {
    freef(freef_arg, self->authority_seed);
    self->authority_seed = NULL;
  }
  fd_pubkey_destroy(&self->authority_owner, freef, freef_arg);
}

void fd_authorize_with_seed_args_walk(fd_authorize_with_seed_args_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_authorize_with_seed_args", level++);
  fd_pubkey_walk(&self->new_authorized_pubkey, fun, "new_authorized_pubkey", level + 1);
  fd_stake_authorize_walk(&self->stake_authorize, fun, "stake_authorize", level + 1);
  fun(self->authority_seed, "authority_seed", 2, "char*", level + 1);
  fd_pubkey_walk(&self->authority_owner, fun, "authority_owner", level + 1);
  fun(self, name, 33, "fd_authorize_with_seed_args", --level);
}
void fd_authorize_with_seed_args_copy_to(fd_authorize_with_seed_args_t* to, fd_authorize_with_seed_args_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_authorize_with_seed_args_size(from) );
  void const *   ptr = (void const *) enc;
  fd_authorize_with_seed_args_encode( from, &ptr );
  void *input = (void *) enc;
  fd_authorize_with_seed_args_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_authorize_with_seed_args_size(fd_authorize_with_seed_args_t* self) {
  ulong size = 0;
  size += fd_pubkey_size(&self->new_authorized_pubkey);
  size += fd_stake_authorize_size(&self->stake_authorize);
  size += sizeof(ulong) + strlen(self->authority_seed);
  size += fd_pubkey_size(&self->authority_owner);
  return size;
}

void fd_authorize_with_seed_args_encode(fd_authorize_with_seed_args_t* self, void const** data) {
  fd_pubkey_encode(&self->new_authorized_pubkey, data);
  fd_stake_authorize_encode(&self->stake_authorize, data);
  ulong slen = strlen((char *) self->authority_seed);
  fd_bincode_uint64_encode(&slen, data);
  fd_bincode_bytes_encode((uchar *) self->authority_seed, slen, data);
  fd_pubkey_encode(&self->authority_owner, data);
}

void fd_authorize_checked_with_seed_args_decode(fd_authorize_checked_with_seed_args_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_stake_authorize_decode(&self->stake_authorize, data, dataend, allocf, allocf_arg);
  ulong slen;
  fd_bincode_uint64_decode(&slen, data, dataend);
  self->authority_seed = (char*)(*allocf)(allocf_arg, 1, slen + 1);
  fd_bincode_bytes_decode((uchar *) self->authority_seed, slen, data, dataend);
  self->authority_seed[slen] = '\0';
  fd_pubkey_decode(&self->authority_owner, data, dataend, allocf, allocf_arg);
}
void fd_authorize_checked_with_seed_args_destroy(fd_authorize_checked_with_seed_args_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_stake_authorize_destroy(&self->stake_authorize, freef, freef_arg);
  if (NULL != self->authority_seed) {
    freef(freef_arg, self->authority_seed);
    self->authority_seed = NULL;
  }
  fd_pubkey_destroy(&self->authority_owner, freef, freef_arg);
}

void fd_authorize_checked_with_seed_args_walk(fd_authorize_checked_with_seed_args_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_authorize_checked_with_seed_args", level++);
  fd_stake_authorize_walk(&self->stake_authorize, fun, "stake_authorize", level + 1);
  fun(self->authority_seed, "authority_seed", 2, "char*", level + 1);
  fd_pubkey_walk(&self->authority_owner, fun, "authority_owner", level + 1);
  fun(self, name, 33, "fd_authorize_checked_with_seed_args", --level);
}
void fd_authorize_checked_with_seed_args_copy_to(fd_authorize_checked_with_seed_args_t* to, fd_authorize_checked_with_seed_args_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_authorize_checked_with_seed_args_size(from) );
  void const *   ptr = (void const *) enc;
  fd_authorize_checked_with_seed_args_encode( from, &ptr );
  void *input = (void *) enc;
  fd_authorize_checked_with_seed_args_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_authorize_checked_with_seed_args_size(fd_authorize_checked_with_seed_args_t* self) {
  ulong size = 0;
  size += fd_stake_authorize_size(&self->stake_authorize);
  size += sizeof(ulong) + strlen(self->authority_seed);
  size += fd_pubkey_size(&self->authority_owner);
  return size;
}

void fd_authorize_checked_with_seed_args_encode(fd_authorize_checked_with_seed_args_t* self, void const** data) {
  fd_stake_authorize_encode(&self->stake_authorize, data);
  ulong slen = strlen((char *) self->authority_seed);
  fd_bincode_uint64_encode(&slen, data);
  fd_bincode_bytes_encode((uchar *) self->authority_seed, slen, data);
  fd_pubkey_encode(&self->authority_owner, data);
}

void fd_lockup_checked_args_decode(fd_lockup_checked_args_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  if (fd_bincode_option_decode(data, dataend)) {
    self->unix_timestamp = (ulong*)(*allocf)(allocf_arg, 8, sizeof(ulong));
    fd_bincode_uint64_decode(self->unix_timestamp, data, dataend);
  } else
    self->unix_timestamp = NULL;
  if (fd_bincode_option_decode(data, dataend)) {
    self->epoch = (ulong*)(*allocf)(allocf_arg, 8, sizeof(ulong));
    fd_bincode_uint64_decode(self->epoch, data, dataend);
  } else
    self->epoch = NULL;
}
void fd_lockup_checked_args_destroy(fd_lockup_checked_args_t* self, fd_free_fun_t freef, void* freef_arg) {
  if (NULL != self->unix_timestamp) {
    freef(freef_arg, self->unix_timestamp);
    self->unix_timestamp = NULL;
  }
  if (NULL != self->epoch) {
    freef(freef_arg, self->epoch);
    self->epoch = NULL;
  }
}

void fd_lockup_checked_args_walk(fd_lockup_checked_args_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_lockup_checked_args", level++);
  fun(self->unix_timestamp, "unix_timestamp", 11, "ulong", level + 1);
  fun(self->epoch, "epoch", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_lockup_checked_args", --level);
}
void fd_lockup_checked_args_copy_to(fd_lockup_checked_args_t* to, fd_lockup_checked_args_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_lockup_checked_args_size(from) );
  void const *   ptr = (void const *) enc;
  fd_lockup_checked_args_encode( from, &ptr );
  void *input = (void *) enc;
  fd_lockup_checked_args_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_lockup_checked_args_size(fd_lockup_checked_args_t* self) {
  ulong size = 0;
  size += sizeof(char);
  if (NULL !=  self->unix_timestamp) {
    size += sizeof(ulong);
  }
  size += sizeof(char);
  if (NULL !=  self->epoch) {
    size += sizeof(ulong);
  }
  return size;
}

void fd_lockup_checked_args_encode(fd_lockup_checked_args_t* self, void const** data) {
  if (self->unix_timestamp!= NULL) {
    fd_bincode_option_encode(1, data);
    fd_bincode_uint64_encode(self->unix_timestamp, data);
  } else
    fd_bincode_option_encode(0, data);
  if (self->epoch!= NULL) {
    fd_bincode_option_encode(1, data);
    fd_bincode_uint64_encode(self->epoch, data);
  } else
    fd_bincode_option_encode(0, data);
}

uchar fd_stake_instruction_is_initialize(fd_stake_instruction_t* self) {
  return self->discriminant == 0;
}
uchar fd_stake_instruction_is_authorize(fd_stake_instruction_t* self) {
  return self->discriminant == 1;
}
uchar fd_stake_instruction_is_delegate_stake(fd_stake_instruction_t* self) {
  return self->discriminant == 2;
}
uchar fd_stake_instruction_is_split(fd_stake_instruction_t* self) {
  return self->discriminant == 3;
}
uchar fd_stake_instruction_is_withdraw(fd_stake_instruction_t* self) {
  return self->discriminant == 4;
}
uchar fd_stake_instruction_is_deactivate(fd_stake_instruction_t* self) {
  return self->discriminant == 5;
}
uchar fd_stake_instruction_is_set_lockup(fd_stake_instruction_t* self) {
  return self->discriminant == 6;
}
uchar fd_stake_instruction_is_merge(fd_stake_instruction_t* self) {
  return self->discriminant == 7;
}
uchar fd_stake_instruction_is_authorize_with_seed(fd_stake_instruction_t* self) {
  return self->discriminant == 8;
}
uchar fd_stake_instruction_is_initialize_checked(fd_stake_instruction_t* self) {
  return self->discriminant == 9;
}
uchar fd_stake_instruction_is_authorize_checked(fd_stake_instruction_t* self) {
  return self->discriminant == 10;
}
uchar fd_stake_instruction_is_authorize_checked_with_seed(fd_stake_instruction_t* self) {
  return self->discriminant == 11;
}
uchar fd_stake_instruction_is_set_lockup_checked(fd_stake_instruction_t* self) {
  return self->discriminant == 12;
}
void fd_stake_instruction_inner_decode(fd_stake_instruction_inner_t* self, uint discriminant, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  switch (discriminant) {
  case 0: {
    fd_stake_instruction_initialize_decode(&self->initialize, data, dataend, allocf, allocf_arg);
    break;
  }
  case 1: {
    fd_stake_instruction_authorize_decode(&self->authorize, data, dataend, allocf, allocf_arg);
    break;
  }
  case 2: {
    break;
  }
  case 3: {
    fd_bincode_uint64_decode(&self->split, data, dataend);
    break;
  }
  case 4: {
    fd_bincode_uint64_decode(&self->withdraw, data, dataend);
    break;
  }
  case 5: {
    break;
  }
  case 6: {
    break;
  }
  case 7: {
    break;
  }
  case 8: {
    fd_authorize_with_seed_args_decode(&self->authorize_with_seed, data, dataend, allocf, allocf_arg);
    break;
  }
  case 9: {
    break;
  }
  case 10: {
    fd_stake_authorize_decode(&self->authorize_checked, data, dataend, allocf, allocf_arg);
    break;
  }
  case 11: {
    fd_authorize_checked_with_seed_args_decode(&self->authorize_checked_with_seed, data, dataend, allocf, allocf_arg);
    break;
  }
  case 12: {
    fd_lockup_checked_args_decode(&self->set_lockup_checked, data, dataend, allocf, allocf_arg);
    break;
  }
  default: FD_LOG_ERR(( "unhandled type"));
  }
}
void fd_stake_instruction_decode(fd_stake_instruction_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint32_decode(&self->discriminant, data, dataend);
  fd_stake_instruction_inner_decode(&self->inner, self->discriminant, data, dataend, allocf, allocf_arg);
}
void fd_stake_instruction_inner_destroy(fd_stake_instruction_inner_t* self, uint discriminant, fd_free_fun_t freef, void* freef_arg) {
  switch (discriminant) {
  case 0: {
    fd_stake_instruction_initialize_destroy(&self->initialize, freef, freef_arg);
    break;
  }
  case 1: {
    fd_stake_instruction_authorize_destroy(&self->authorize, freef, freef_arg);
    break;
  }
  case 2: {
    break;
  }
  case 3: {
    break;
  }
  case 4: {
    break;
  }
  case 5: {
    break;
  }
  case 6: {
    break;
  }
  case 7: {
    break;
  }
  case 8: {
    fd_authorize_with_seed_args_destroy(&self->authorize_with_seed, freef, freef_arg);
    break;
  }
  case 9: {
    break;
  }
  case 10: {
    fd_stake_authorize_destroy(&self->authorize_checked, freef, freef_arg);
    break;
  }
  case 11: {
    fd_authorize_checked_with_seed_args_destroy(&self->authorize_checked_with_seed, freef, freef_arg);
    break;
  }
  case 12: {
    fd_lockup_checked_args_destroy(&self->set_lockup_checked, freef, freef_arg);
    break;
  }
  default: break; // FD_LOG_ERR(( "unhandled type"));
  }
}
void fd_stake_instruction_destroy(fd_stake_instruction_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_stake_instruction_inner_destroy(&self->inner, self->discriminant, freef, freef_arg);
}

void fd_stake_instruction_walk(fd_stake_instruction_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_stake_instruction", level++);
  // enum fd_option_walk(&self->epoch, fun, "epoch", level + 1);
  fun(self, name, 33, "fd_stake_instruction", --level);
}
void fd_stake_instruction_copy_to(fd_stake_instruction_t* to, fd_stake_instruction_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_stake_instruction_size(from) );
  void const *   ptr = (void const *) enc;
  fd_stake_instruction_encode( from, &ptr );
  void *input = (void *) enc;
  fd_stake_instruction_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_stake_instruction_size(fd_stake_instruction_t* self) {
  ulong size = 0;
  size += sizeof(uint);
  switch (self->discriminant) {
  case 0: {
    size += fd_stake_instruction_initialize_size(&self->inner.initialize);
    break;
  }
  case 1: {
    size += fd_stake_instruction_authorize_size(&self->inner.authorize);
    break;
  }
  case 3: {
    size += sizeof(ulong);
    break;
  }
  case 4: {
    size += sizeof(ulong);
    break;
  }
  case 8: {
    size += fd_authorize_with_seed_args_size(&self->inner.authorize_with_seed);
    break;
  }
  case 10: {
    size += fd_stake_authorize_size(&self->inner.authorize_checked);
    break;
  }
  case 11: {
    size += fd_authorize_checked_with_seed_args_size(&self->inner.authorize_checked_with_seed);
    break;
  }
  case 12: {
    size += fd_lockup_checked_args_size(&self->inner.set_lockup_checked);
    break;
  }
  }
  return size;
}

void fd_stake_instruction_inner_encode(fd_stake_instruction_inner_t* self, uint discriminant, void const** data) {
  switch (discriminant) {
  case 0: {
    fd_stake_instruction_initialize_encode(&self->initialize, data);
    break;
  }
  case 1: {
    fd_stake_instruction_authorize_encode(&self->authorize, data);
    break;
  }
  case 3: {
    fd_bincode_uint64_encode(&self->split, data);
    break;
  }
  case 4: {
    fd_bincode_uint64_encode(&self->withdraw, data);
    break;
  }
  case 8: {
    fd_authorize_with_seed_args_encode(&self->authorize_with_seed, data);
    break;
  }
  case 10: {
    fd_stake_authorize_encode(&self->authorize_checked, data);
    break;
  }
  case 11: {
    fd_authorize_checked_with_seed_args_encode(&self->authorize_checked_with_seed, data);
    break;
  }
  case 12: {
    fd_lockup_checked_args_encode(&self->set_lockup_checked, data);
    break;
  }
  }
}
void fd_stake_instruction_encode(fd_stake_instruction_t* self, void const** data) {
  fd_bincode_uint32_encode(&self->discriminant, data);
  fd_stake_instruction_inner_encode(&self->inner, self->discriminant, data);
}

void fd_stake_state_meta_decode(fd_stake_state_meta_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint64_decode(&self->rent_exempt_reserve, data, dataend);
  fd_stake_authorized_decode(&self->authorized, data, dataend, allocf, allocf_arg);
  fd_stake_lockup_decode(&self->lockup, data, dataend, allocf, allocf_arg);
}
void fd_stake_state_meta_destroy(fd_stake_state_meta_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_stake_authorized_destroy(&self->authorized, freef, freef_arg);
  fd_stake_lockup_destroy(&self->lockup, freef, freef_arg);
}

void fd_stake_state_meta_walk(fd_stake_state_meta_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_stake_state_meta", level++);
  fun(&self->rent_exempt_reserve, "rent_exempt_reserve", 11, "ulong", level + 1);
  fd_stake_authorized_walk(&self->authorized, fun, "authorized", level + 1);
  fd_stake_lockup_walk(&self->lockup, fun, "lockup", level + 1);
  fun(self, name, 33, "fd_stake_state_meta", --level);
}
void fd_stake_state_meta_copy_to(fd_stake_state_meta_t* to, fd_stake_state_meta_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_stake_state_meta_size(from) );
  void const *   ptr = (void const *) enc;
  fd_stake_state_meta_encode( from, &ptr );
  void *input = (void *) enc;
  fd_stake_state_meta_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_stake_state_meta_size(fd_stake_state_meta_t* self) {
  ulong size = 0;
  size += sizeof(ulong);
  size += fd_stake_authorized_size(&self->authorized);
  size += fd_stake_lockup_size(&self->lockup);
  return size;
}

void fd_stake_state_meta_encode(fd_stake_state_meta_t* self, void const** data) {
  fd_bincode_uint64_encode(&self->rent_exempt_reserve, data);
  fd_stake_authorized_encode(&self->authorized, data);
  fd_stake_lockup_encode(&self->lockup, data);
}

void fd_stake_decode(fd_stake_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_delegation_decode(&self->delegation, data, dataend, allocf, allocf_arg);
  fd_bincode_uint64_decode(&self->credits_observed, data, dataend);
}
void fd_stake_destroy(fd_stake_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_delegation_destroy(&self->delegation, freef, freef_arg);
}

void fd_stake_walk(fd_stake_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_stake", level++);
  fd_delegation_walk(&self->delegation, fun, "delegation", level + 1);
  fun(&self->credits_observed, "credits_observed", 11, "ulong", level + 1);
  fun(self, name, 33, "fd_stake", --level);
}
void fd_stake_copy_to(fd_stake_t* to, fd_stake_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_stake_size(from) );
  void const *   ptr = (void const *) enc;
  fd_stake_encode( from, &ptr );
  void *input = (void *) enc;
  fd_stake_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_stake_size(fd_stake_t* self) {
  ulong size = 0;
  size += fd_delegation_size(&self->delegation);
  size += sizeof(ulong);
  return size;
}

void fd_stake_encode(fd_stake_t* self, void const** data) {
  fd_delegation_encode(&self->delegation, data);
  fd_bincode_uint64_encode(&self->credits_observed, data);
}

void fd_stake_state_stake_decode(fd_stake_state_stake_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_stake_state_meta_decode(&self->meta, data, dataend, allocf, allocf_arg);
  fd_stake_decode(&self->stake, data, dataend, allocf, allocf_arg);
}
void fd_stake_state_stake_destroy(fd_stake_state_stake_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_stake_state_meta_destroy(&self->meta, freef, freef_arg);
  fd_stake_destroy(&self->stake, freef, freef_arg);
}

void fd_stake_state_stake_walk(fd_stake_state_stake_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_stake_state_stake", level++);
  fd_stake_state_meta_walk(&self->meta, fun, "meta", level + 1);
  fd_stake_walk(&self->stake, fun, "stake", level + 1);
  fun(self, name, 33, "fd_stake_state_stake", --level);
}
void fd_stake_state_stake_copy_to(fd_stake_state_stake_t* to, fd_stake_state_stake_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_stake_state_stake_size(from) );
  void const *   ptr = (void const *) enc;
  fd_stake_state_stake_encode( from, &ptr );
  void *input = (void *) enc;
  fd_stake_state_stake_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_stake_state_stake_size(fd_stake_state_stake_t* self) {
  ulong size = 0;
  size += fd_stake_state_meta_size(&self->meta);
  size += fd_stake_size(&self->stake);
  return size;
}

void fd_stake_state_stake_encode(fd_stake_state_stake_t* self, void const** data) {
  fd_stake_state_meta_encode(&self->meta, data);
  fd_stake_encode(&self->stake, data);
}

uchar fd_stake_state_is_uninitialized(fd_stake_state_t* self) {
  return self->discriminant == 0;
}
uchar fd_stake_state_is_initialized(fd_stake_state_t* self) {
  return self->discriminant == 1;
}
uchar fd_stake_state_is_stake(fd_stake_state_t* self) {
  return self->discriminant == 2;
}
uchar fd_stake_state_is_rewards_pool(fd_stake_state_t* self) {
  return self->discriminant == 3;
}
void fd_stake_state_inner_decode(fd_stake_state_inner_t* self, uint discriminant, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  switch (discriminant) {
  case 0: {
    break;
  }
  case 1: {
    fd_stake_state_meta_decode(&self->initialized, data, dataend, allocf, allocf_arg);
    break;
  }
  case 2: {
    fd_stake_state_stake_decode(&self->stake, data, dataend, allocf, allocf_arg);
    break;
  }
  case 3: {
    break;
  }
  default: FD_LOG_ERR(( "unhandled type"));
  }
}
void fd_stake_state_decode(fd_stake_state_t* self, void const** data, void const* dataend, fd_alloc_fun_t allocf, void* allocf_arg) {
  fd_bincode_uint32_decode(&self->discriminant, data, dataend);
  fd_stake_state_inner_decode(&self->inner, self->discriminant, data, dataend, allocf, allocf_arg);
}
void fd_stake_state_inner_destroy(fd_stake_state_inner_t* self, uint discriminant, fd_free_fun_t freef, void* freef_arg) {
  switch (discriminant) {
  case 0: {
    break;
  }
  case 1: {
    fd_stake_state_meta_destroy(&self->initialized, freef, freef_arg);
    break;
  }
  case 2: {
    fd_stake_state_stake_destroy(&self->stake, freef, freef_arg);
    break;
  }
  case 3: {
    break;
  }
  default: break; // FD_LOG_ERR(( "unhandled type"));
  }
}
void fd_stake_state_destroy(fd_stake_state_t* self, fd_free_fun_t freef, void* freef_arg) {
  fd_stake_state_inner_destroy(&self->inner, self->discriminant, freef, freef_arg);
}

void fd_stake_state_walk(fd_stake_state_t* self, fd_walk_fun_t fun, const char *name, int level) {
  fun(self, name, 32, "fd_stake_state", level++);
  // enum fd_stake_walk(&self->stake, fun, "stake", level + 1);
  fun(self, name, 33, "fd_stake_state", --level);
}
void fd_stake_state_copy_to(fd_stake_state_t* to, fd_stake_state_t* from, fd_alloc_fun_t allocf, void* allocf_arg) {
  unsigned char *enc = fd_alloca( 1, fd_stake_state_size(from) );
  void const *   ptr = (void const *) enc;
  fd_stake_state_encode( from, &ptr );
  void *input = (void *) enc;
  fd_stake_state_decode( to, (const void **) &input, ptr, allocf, allocf_arg );
}
ulong fd_stake_state_size(fd_stake_state_t* self) {
  ulong size = 0;
  size += sizeof(uint);
  switch (self->discriminant) {
  case 1: {
    size += fd_stake_state_meta_size(&self->inner.initialized);
    break;
  }
  case 2: {
    size += fd_stake_state_stake_size(&self->inner.stake);
    break;
  }
  }
  return size;
}

void fd_stake_state_inner_encode(fd_stake_state_inner_t* self, uint discriminant, void const** data) {
  switch (discriminant) {
  case 1: {
    fd_stake_state_meta_encode(&self->initialized, data);
    break;
  }
  case 2: {
    fd_stake_state_stake_encode(&self->stake, data);
    break;
  }
  }
}
void fd_stake_state_encode(fd_stake_state_t* self, void const** data) {
  fd_bincode_uint32_encode(&self->discriminant, data);
  fd_stake_state_inner_encode(&self->inner, self->discriminant, data);
}

#define REDBLK_T fd_serializable_account_storage_entry_t_mapnode_t
#define REDBLK_NAME fd_serializable_account_storage_entry_t_map
#define REDBLK_IMPL_STYLE 2
#include "../../util/tmpl/fd_redblack.c"
#undef REDBLK_T
#undef REDBLK_NAME
long fd_serializable_account_storage_entry_t_map_compare(fd_serializable_account_storage_entry_t_mapnode_t * left, fd_serializable_account_storage_entry_t_mapnode_t * right) {
  return (long)(left->elem.id - right->elem.id);
}
#define REDBLK_T fd_slot_account_pair_t_mapnode_t
#define REDBLK_NAME fd_slot_account_pair_t_map
#define REDBLK_IMPL_STYLE 2
#include "../../util/tmpl/fd_redblack.c"
#undef REDBLK_T
#undef REDBLK_NAME
long fd_slot_account_pair_t_map_compare(fd_slot_account_pair_t_mapnode_t * left, fd_slot_account_pair_t_mapnode_t * right) {
  return (long)(left->elem.slot - right->elem.slot);
}
