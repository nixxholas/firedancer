#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <alloca.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <zstd.h>      // presumes zstd library is installed
#include "../../util/fd_util.h"
#include "tar.h"
#include "banks.h"
#include <sys/types.h>
#include <sys/stat.h>

int hexchr2bin(const char hex, unsigned char *out)
{
  if (out == NULL)
    return 0;

  if (hex >= '0' && hex <= '9') {
    *out = (unsigned char)(hex - '0');
  } else if (hex >= 'A' && hex <= 'F') {
    *out = (unsigned char)(hex - 'A' + 10);
  } else if (hex >= 'a' && hex <= 'f') {
    *out = (unsigned char)(hex - 'a' + 10);
  } else {
    return 0;
  }

  return 1;
}

size_t hexs2bin(const char *hex, unsigned char **out)
{
  size_t len;
  unsigned char   b1;
  unsigned char   b2;
  size_t i;

  if (hex == NULL || *hex == '\0' || out == NULL)
    return 0;

  len = strlen(hex);
  if (len % 2 != 0)
    return 0;
  len /= 2;

  *out = malloc(len);
  memset(*out, 'A', len);
  for (i=0; i<len; i++) {
    if (!hexchr2bin(hex[i*2], &b1) || !hexchr2bin(hex[i*2+1], &b2)) {
      return 0;
    }
    (*out)[i] = (unsigned char) ((b1 << 4) | b2);
  }
  return len;
}

char* allocf(unsigned long len, FD_FN_UNUSED unsigned long align, FD_FN_UNUSED void* arg) {
  return malloc(len);
}

int main(FD_FN_UNUSED int argc, FD_FN_UNUSED char** argv) {

  {
    unsigned char *out = NULL;
    size_t len = hexs2bin("0100000000000000030000000000000004050646ea44f334102a779b7f5b42f8df2aef96626cb4b6bf5f192ce2b4b5a7e2b552010300000000000000", &out);
    unsigned char *outend = &out[len];
    const void * o = out;

    struct Account a;
//    memset(&a, 0, sizeof(a));
    Account_decode(&a, &o, outend, allocf, NULL);

    FD_TEST(a.lamports == 1);
    FD_TEST(a.data_len == 3);
    FD_TEST(a.data[0] == 4);
    FD_TEST(a.data[1] == 5);
    FD_TEST(a.data[2] == 6);
    FD_TEST(a.owner.key[0] == 70);
    FD_TEST(a.rent_epoch == 3);
    FD_TEST(a.executable != 0);
  }

  {
    unsigned char *out = NULL;
    size_t len = hexs2bin("0000000000000000010505050505050505050505050505050505050505050505050505050505050505010000000000000005050505050505050505050505050505050505050505050505050505050505057b00000000000000000000000000000081624f13860100000500000000000000", &out);
    unsigned char *outend = &out[len];
    const void * o = out;

    struct BlockhashQueue a;
//    memset(&a, 0, sizeof(a));
    BlockhashQueue_decode(&a, &o, outend, allocf, NULL);

    FD_TEST(memcmp(a.ages[0].key.hash, a.last_hash->hash, sizeof(a.ages[0].key.hash)) == 0);
    FD_TEST(a.max_age == 5);
    FD_TEST(a.ages_len == 1);
    FD_TEST(a.last_hash_index == 0);
    FD_TEST(a.ages[0].val.fee_calculator.lamports_per_signature == 123);
  }

  {
    unsigned char *out = NULL;
    size_t len = hexs2bin("01000000000000000500000000000000010000000000000002000000000000000300000000000000", &out);
    unsigned char *outend = &out[len];
    const void * o = out;

    struct StakeHistory a;
//    memset(&a, 0, sizeof(a));
    StakeHistory_decode(&a, &o, outend, allocf, NULL);

    FD_TEST(a.len == 1);
    FD_TEST(a.entries[0].entry.effective == 1);
    FD_TEST(a.entries[0].entry.activating == 2);
    FD_TEST(a.entries[0].entry.deactivating == 3);

// StakeHistory: [[5,{"effective":1,"activating":2,"deactivating":3}]] 01000000000000000500000000000000010000000000000002000000000000000300000000000000
  }
    

  {
    unsigned char *out = NULL;
    size_t len = hexs2bin("46ea44f334102a779b7f5b42f8df2aef96626cb4b6bf5f192ce2b4b5a7e2b5520100000000000000020000000000000003000000000000000000000000001040", &out);
    unsigned char *outend = &out[len];
    const void * o = out;

    struct Delegation a;
    memset(&a, 0, sizeof(a));
    Delegation_decode(&a, &o, outend, allocf, NULL);

    FD_TEST(a.warmup_cooldown_rate == 4.0);

    //Delegation: {"voter_pubkey":[70,234,68,243,52,16,42,119,155,127,91,66,248,223,42,239,150,98,108,180,182,191,95,25,44,226,180,181,167,226,181,82],"stake":1,"activation_epoch":2,"deactivation_epoch":3,"warmup_cooldown_rate":4.0} 
  }

  {
    unsigned char *out = NULL;
    size_t len = hexs2bin("0000000000000000010000000000000046ea44f334102a779b7f5b42f8df2aef96626cb4b6bf5f192ce2b4b5a7e2b55246ea44f334102a779b7f5b42f8df2aef96626cb4b6bf5f192ce2b4b5a7e2b5520100000000000000020000000000000003000000000000000000000000001040620000000000000029000000000000000000000000000000", &out);
    unsigned char *outend = &out[len];
    const void * o = out;


    struct StakesDeligation a;
    memset(&a, 0, sizeof(a));
    StakesDeligation_decode(&a, &o, outend, allocf, NULL);

    FD_TEST(a.epoch == 41);
    FD_TEST(a.unused == 98);
  }

  {
    unsigned char *out = NULL;
    size_t len = hexs2bin("0000000000000000010000000000000046ea44f334102a779b7f5b42f8df2aef96626cb4b6bf5f192ce2b4b5a7e2b55246ea44f334102a779b7f5b42f8df2aef96626cb4b6bf5f192ce2b4b5a7e2b5520100000000000000020000000000000003000000000000000000000000001040620000000000000029000000000000000000000000000000000000000000000000000000000000000000000000000000", &out);
    unsigned char *outend = &out[len];
    const void * o = out;

    struct EpochStakes a;
    memset(&a, 0, sizeof(a));
    EpochStakes_decode(&a, &o, outend, allocf, NULL);

    FD_TEST(a.stakes.epoch == 41);
    FD_TEST(a.stakes.unused == 98);

//EpochStakes: 0000000000000000010000000000000046ea44f334102a779b7f5b42f8df2aef96626cb4b6bf5f192ce2b4b5a7e2b55246ea44f334102a779b7f5b42f8df2aef96626cb4b6bf5f192ce2b4b5a7e2b5520100000000000000020000000000000003000000000000000000000000001040620000000000000029000000000000000000000000000000000000000000000000000000000000000000000000000000
  }


  {
    struct stat s;
    stat("/home/jsiegel/manifest",  &s);

    unsigned char *b = (unsigned char *)malloc((unsigned long) (unsigned long) s.st_size);
    int fd = open("/home/jsiegel/manifest", O_RDONLY);
    ssize_t n = read(fd, b, (unsigned long) s.st_size);

    FD_TEST(n == s.st_size);
    unsigned char *outend = &b[n];
    const void * o = b;

    struct DeserializableVersionedBank a;
    memset(&a, 0, sizeof(a));
    DeserializableVersionedBank_decode(&a, &o, outend, allocf, NULL);

    FD_TEST(a.is_delta != 0);
  }
//(gdb) print versioned_bank.transaction_count
//$2 = 138624704170
//(gdb) print versioned_bank.collector_fees
//$4 = 11329383
//versioned_bank.epoch_stakes.keys().len()) == 6

  return 0;

  
}
