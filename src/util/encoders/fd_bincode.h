#ifndef HEADER_fd_src_util_encoders_fd_bincode_h
#define HEADER_fd_src_util_encoders_fd_bincode_h

#include "../bits/fd_bits.h"
#include "../fd_util.h"
#include <immintrin.h>

static inline
void fd_bincode_uint128_decode(uint128* self, void const** data, void const* dataend) {
  const uint128 *ptr = (const uint128 *) *data;
  if (FD_UNLIKELY((void const *) (ptr + 1) > dataend )) {
    FD_LOG_ERR(( "buffer underflow"));
  }

  *self = (uint128) _mm_loadu_si128((void const *) ptr);
  *data = ptr + 1;
}

static inline
void fd_bincode_uint128_encode(uint128* self, void const** data) {
  uint128 *ptr = (uint128 *) *data;
  *ptr = *self;
  *data = ptr + 1;
}

static inline
void fd_bincode_uint64_decode(ulong* self, void const** data, void const* dataend) {
  const ulong *ptr = (const ulong *) *data;
  if (FD_UNLIKELY((void const *) (ptr + 1) > dataend )) {
    FD_LOG_ERR(( "buffer underflow"));
  }
  *self = *ptr;
  *data = ptr + 1;
}

static inline
void fd_bincode_uint64_encode(ulong* self, void const** data) {
  ulong *ptr = (ulong *) *data;
  *ptr = *self;
  *data = ptr + 1;
}

static inline
void fd_bincode_double_decode(double* self, void const** data, void const* dataend) {
  const double *ptr = (const double *) *data;
  if (FD_UNLIKELY((void const *) (ptr + 1) > dataend )) {
    FD_LOG_ERR(( "buffer underflow"));
  }
  *self = *ptr;
  *data = ptr + 1;
}

static inline
void fd_bincode_double_encode(double* self, void const** data) {
  double *ptr = (double *) *data;
  *ptr = *self;
  *data = ptr + 1;
}

static inline
void fd_bincode_uint32_decode(unsigned int* self, void const** data, void const* dataend) {
  const unsigned int *ptr = (const unsigned int *) *data;
  if (FD_UNLIKELY((void const *) (ptr + 1) > dataend )) {
    FD_LOG_ERR(( "buffer underflow"));
  }
  *self = *ptr;
  *data = ptr + 1;
}

static inline
void fd_bincode_uint32_encode(unsigned int* self, void const** data) {
  unsigned int *ptr = (unsigned int *) *data;
  *ptr = *self;
  *data = ptr + 1;
}

static inline
void fd_bincode_uint16_decode(ushort* self, void const** data, void const* dataend) {
  const ushort *ptr = (const ushort *) *data;
  if (FD_UNLIKELY((void const *) (ptr + 1) > dataend )) {
    FD_LOG_ERR(( "buffer underflow"));
  }
  *self = *ptr;
  *data = ptr + 1;
}

static inline
void fd_bincode_uint16_encode(ushort* self, void const** data) {
  ushort *ptr = (ushort *) *data;
  *ptr = *self;
  *data = ptr + 1;
}

static inline
void fd_bincode_uint8_decode(unsigned char* self, void const** data, void const* dataend) {
  const unsigned char *ptr = (const unsigned char *) *data;
  if (FD_UNLIKELY((void const *) (ptr + 1) > dataend )) {
    FD_LOG_ERR(( "buffer underflow"));
  }
  *self = *ptr;
  *data = ptr + 1;
}

static inline
void fd_bincode_uint8_encode(unsigned char* self, void const** data) {
  unsigned char *ptr = (unsigned char *) *data;
  *ptr = *self;
  *data = ptr + 1;
}

static inline
void fd_bincode_bytes_decode(unsigned char* self, ulong len, void const** data, void const* dataend) {
  unsigned char *ptr = (unsigned char *) *data;
  if (FD_UNLIKELY((void *) (ptr + len) > dataend )) {
    FD_LOG_ERR(( "buffer underflow"));
  }
  memcpy(self, ptr, len); // what is the FD way?
  *data = ptr + len;
}

static inline
void fd_bincode_bytes_encode(unsigned char* self, ulong len, void const** data) {
  unsigned char *ptr = (unsigned char *) *data;
  memcpy(ptr, self, len);
  *data = ptr + len;
}

static inline
unsigned char fd_bincode_option_decode(void const** data, void const* dataend) {
  unsigned char *ptr = (unsigned char *) *data;
  if (FD_UNLIKELY((void *) (ptr + 1) > dataend )) {
    FD_LOG_ERR(( "buffer underflow"));
  }
  unsigned char ret = *ptr;
  *data = ptr + 1;
  return ret;
}

static inline
void fd_bincode_option_encode(unsigned char val, void const** data) {
  unsigned char *ptr = (unsigned char *) *data;
  *ptr = val;
  *data = ptr + 1;
}

#endif /* HEADER_fd_src_util_encoders_fd_bincode_h */
