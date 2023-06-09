#include "../fd_tests.h"
int test_1645(fd_executor_test_suite_t *suite) {
  fd_executor_test_t test;
  fd_memset( &test, 0, FD_EXECUTOR_TEST_FOOTPRINT );
  test.disable_cnt = 47;
  uchar disabled_features[] = { 103,105,106,108,109,110,111,112,113,114,116,117,118,120,121,122,123,124,125,126,127,128,15,2,24,26,27,29,30,33,55,56,61,62,75,76,77,78,79,80,82,83,87,89,90,92,98 };
  test.disable_feature = disabled_features;
  test.bt = "   2: solana_bpf_loader_program::tests::test_bpf_loader_serialize_unaligned             at ./src/lib.rs:1800:9   3: solana_bpf_loader_program::tests::test_bpf_loader_serialize_unaligned::{{closure}}             at ./src/lib.rs:1786:5   4: core::ops::function::FnOnce::call_once             at /rustc/0677edc86e342f333d4828b0ee1ef395a4e70fe5/library/core/src/ops/function.rs:227:5   5: core::ops::function::FnOnce::call_once             at /rustc/0677edc86e342f333d4828b0ee1ef395a4e70fe5/library/core/src/ops/function.rs:227:5";
  test.test_name = "tests::test_bpf_loader_serialize_unaligned";
  test.test_nonce  = 8;
  test.test_number = 1645;
  if (fd_executor_test_suite_check_filter(suite, &test)) return -9999;
  ulong test_accs_len = 2;
  fd_executor_test_acc_t* test_accs = fd_alloca( 1UL, FD_EXECUTOR_TEST_ACC_FOOTPRINT * test_accs_len );
  fd_memset( test_accs, 0, FD_EXECUTOR_TEST_ACC_FOOTPRINT * test_accs_len );

  fd_executor_test_acc_t* test_acc = test_accs;
  fd_base58_decode_32( "1111112xsehejMXw48xSfTWvjGCEV2e7kuxCH5kWb",  (uchar *) &test_acc->pubkey);
  fd_base58_decode_32( "BPFLoader1111111111111111111111111111111111",  (uchar *) &test_acc->owner);
  test_acc->lamports        = 16536960UL;
  test_acc->result_lamports = 16536960UL;
  test_acc->executable      = 1;
  test_acc->rent_epoch      = 0;
  static uchar const fd_flamenco_native_prog_test_1645_acc_0_data[] = { 0x7f,0x45,0x4c,0x46,0x02,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0xf7,0x00,0x01,0x00,0x00,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x88,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x38,0x00,0x03,0x00,0x40,0x00,0x09,0x00,0x07,0x00,0x01,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x10,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0xa0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xa0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xa0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x15,0x01,0x42,0x00,0x00,0x00,0x00,0x00,0xb7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x79,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x15,0x02,0x3f,0x00,0x00,0x00,0x00,0x00,0xb7,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xbf,0xa4,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x04,0x00,0x00,0xc2,0xff,0xff,0xff,0x07,0x01,0x00,0x00,0x08,0x00,0x00,0x00,0xb7,0x05,0x00,0x00,0x02,0x00,0x00,0x00,0x05,0x00,0x3a,0x00,0x00,0x00,0x00,0x00,0x55,0x06,0x20,0x00,0xff,0x00,0x00,0x00,0x71,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0xb7,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0xb7,0x06,0x00,0x00,0x01,0x00,0x00,0x00,0x55,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0xb7,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x73,0x64,0xfe,0xff,0x00,0x00,0x00,0x00,0x71,0x07,0x02,0x00,0x00,0x00,0x00,0x00,0xbf,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x06,0x00,0x00,0x23,0x00,0x00,0x00,0x7b,0x64,0xd6,0xff,0x00,0x00,0x00,0x00,0xbf,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x06,0x00,0x00,0x03,0x00,0x00,0x00,0x7b,0x64,0xce,0xff,0x00,0x00,0x00,0x00,0xb7,0x06,0x00,0x00,0x01,0x00,0x00,0x00,0x55,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0xb7,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x73,0x64,0xff,0xff,0x00,0x00,0x00,0x00,0x79,0x06,0x2b,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x33,0x00,0x00,0x00,0x7b,0x04,0xe6,0xff,0x00,0x00,0x00,0x00,0x7b,0x64,0xde,0xff,0x00,0x00,0x00,0x00,0x0f,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x7b,0x04,0xee,0xff,0x00,0x00,0x00,0x00,0x71,0x06,0x20,0x00,0x00,0x00,0x00,0x00,0x55,0x06,0x01,0x00,0x00,0x00,0x00,0x00,0xb7,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x73,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x79,0x01,0x21,0x00,0x00,0x00,0x00,0x00,0x7b,0x14,0xf6,0xff,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x29,0x00,0x00,0x00,0xbf,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x14,0x00,0x00,0x00,0x00,0x00,0x27,0x06,0x00,0x00,0x38,0x00,0x00,0x00,0xbf,0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x90,0xff,0xff,0xff,0x0f,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x71,0x06,0x30,0x00,0x00,0x00,0x00,0x00,0x73,0x64,0xfe,0xff,0x00,0x00,0x00,0x00,0x79,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x7b,0x64,0xce,0xff,0x00,0x00,0x00,0x00,0x79,0x06,0x08,0x00,0x00,0x00,0x00,0x00,0x7b,0x64,0xd6,0xff,0x00,0x00,0x00,0x00,0x79,0x06,0x10,0x00,0x00,0x00,0x00,0x00,0x7b,0x64,0xde,0xff,0x00,0x00,0x00,0x00,0x79,0x06,0x18,0x00,0x00,0x00,0x00,0x00,0x7b,0x64,0xe6,0xff,0x00,0x00,0x00,0x00,0x79,0x06,0x20,0x00,0x00,0x00,0x00,0x00,0x7b,0x64,0xee,0xff,0x00,0x00,0x00,0x00,0x71,0x06,0x32,0x00,0x00,0x00,0x00,0x00,0x73,0x64,0x00,0x00,0x00,0x00,0x00,0x00,0x79,0x00,0x28,0x00,0x00,0x00,0x00,0x00,0x7b,0x04,0xf6,0xff,0x00,0x00,0x00,0x00,0xb7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x04,0x00,0x00,0x38,0x00,0x00,0x00,0x07,0x03,0x00,0x00,0x01,0x00,0x00,0x00,0x2d,0x32,0x01,0x00,0x00,0x00,0x00,0x00,0x95,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xbf,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x71,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x2d,0x35,0xc2,0xff,0x00,0x00,0x00,0x00,0x55,0x06,0xf6,0xff,0xff,0x00,0x00,0x00,0x79,0x01,0x2b,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x2b,0x00,0x00,0x00,0x0f,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x01,0x00,0x00,0x31,0x00,0x00,0x00,0x05,0x00,0xf1,0xff,0x00,0x00,0x00,0x00,0x1e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x12,0x00,0x01,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x65,0x6e,0x74,0x72,0x79,0x70,0x6f,0x69,0x6e,0x74,0x00,0x4c,0x69,0x6e,0x6b,0x65,0x72,0x3a,0x20,0x4c,0x4c,0x44,0x20,0x31,0x33,0x2e,0x30,0x2e,0x30,0x20,0x28,0x68,0x74,0x74,0x70,0x73,0x3a,0x2f,0x2f,0x67,0x69,0x74,0x68,0x75,0x62,0x2e,0x63,0x6f,0x6d,0x2f,0x73,0x6f,0x6c,0x61,0x6e,0x61,0x2d,0x6c,0x61,0x62,0x73,0x2f,0x6c,0x6c,0x76,0x6d,0x2d,0x70,0x72,0x6f,0x6a,0x65,0x63,0x74,0x2e,0x67,0x69,0x74,0x20,0x31,0x65,0x38,0x30,0x38,0x31,0x64,0x37,0x32,0x35,0x62,0x62,0x30,0x63,0x32,0x61,0x65,0x65,0x66,0x30,0x62,0x35,0x62,0x36,0x61,0x66,0x30,0x32,0x30,0x34,0x31,0x31,0x63,0x30,0x62,0x38,0x33,0x34,0x62,0x62,0x29,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x04,0x00,0xf1,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x12,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x48,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1a,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x50,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x88,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0xb0,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x37,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x08,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x58,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x47,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x28,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5a,0x00,0x00,0x00,0x00,0x02,0x02,0x00,0xa0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4f,0x00,0x00,0x00,0x12,0x00,0x01,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2e,0x74,0x65,0x78,0x74,0x00,0x2e,0x64,0x79,0x6e,0x61,0x6d,0x69,0x63,0x00,0x2e,0x64,0x79,0x6e,0x73,0x79,0x6d,0x00,0x2e,0x64,0x79,0x6e,0x73,0x74,0x72,0x00,0x2e,0x63,0x6f,0x6d,0x6d,0x65,0x6e,0x74,0x00,0x2e,0x73,0x79,0x6d,0x74,0x61,0x62,0x00,0x2e,0x73,0x68,0x73,0x74,0x72,0x74,0x61,0x62,0x00,0x2e,0x73,0x74,0x72,0x74,0x61,0x62,0x00,0x00,0x6e,0x6f,0x6f,0x70,0x5f,0x75,0x6e,0x61,0x6c,0x69,0x67,0x6e,0x65,0x64,0x2e,0x63,0x00,0x4c,0x42,0x42,0x30,0x5f,0x31,0x36,0x00,0x4c,0x42,0x42,0x30,0x5f,0x33,0x00,0x4c,0x42,0x42,0x30,0x5f,0x36,0x00,0x4c,0x42,0x42,0x30,0x5f,0x31,0x34,0x00,0x4c,0x42,0x42,0x30,0x5f,0x39,0x00,0x4c,0x42,0x42,0x30,0x5f,0x31,0x31,0x00,0x4c,0x42,0x42,0x30,0x5f,0x31,0x33,0x00,0x4c,0x42,0x42,0x30,0x5f,0x31,0x35,0x00,0x65,0x6e,0x74,0x72,0x79,0x70,0x6f,0x69,0x6e,0x74,0x00,0x5f,0x44,0x59,0x4e,0x41,0x4d,0x49,0x43,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xa0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xa0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x0b,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4c,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x6e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x29,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x0b,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x43,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3b,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x23,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x63,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
  test_acc->data            = fd_flamenco_native_prog_test_1645_acc_0_data;
  test_acc->data_len        = 2248UL;
  static uchar const fd_flamenco_native_prog_test_1645_acc_0_post_data[] = { 0x7f,0x45,0x4c,0x46,0x02,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0xf7,0x00,0x01,0x00,0x00,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x88,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x38,0x00,0x03,0x00,0x40,0x00,0x09,0x00,0x07,0x00,0x01,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x10,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0xa0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xa0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xa0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x15,0x01,0x42,0x00,0x00,0x00,0x00,0x00,0xb7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x79,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x15,0x02,0x3f,0x00,0x00,0x00,0x00,0x00,0xb7,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xbf,0xa4,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x04,0x00,0x00,0xc2,0xff,0xff,0xff,0x07,0x01,0x00,0x00,0x08,0x00,0x00,0x00,0xb7,0x05,0x00,0x00,0x02,0x00,0x00,0x00,0x05,0x00,0x3a,0x00,0x00,0x00,0x00,0x00,0x55,0x06,0x20,0x00,0xff,0x00,0x00,0x00,0x71,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0xb7,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0xb7,0x06,0x00,0x00,0x01,0x00,0x00,0x00,0x55,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0xb7,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x73,0x64,0xfe,0xff,0x00,0x00,0x00,0x00,0x71,0x07,0x02,0x00,0x00,0x00,0x00,0x00,0xbf,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x06,0x00,0x00,0x23,0x00,0x00,0x00,0x7b,0x64,0xd6,0xff,0x00,0x00,0x00,0x00,0xbf,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x06,0x00,0x00,0x03,0x00,0x00,0x00,0x7b,0x64,0xce,0xff,0x00,0x00,0x00,0x00,0xb7,0x06,0x00,0x00,0x01,0x00,0x00,0x00,0x55,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0xb7,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x73,0x64,0xff,0xff,0x00,0x00,0x00,0x00,0x79,0x06,0x2b,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x33,0x00,0x00,0x00,0x7b,0x04,0xe6,0xff,0x00,0x00,0x00,0x00,0x7b,0x64,0xde,0xff,0x00,0x00,0x00,0x00,0x0f,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x7b,0x04,0xee,0xff,0x00,0x00,0x00,0x00,0x71,0x06,0x20,0x00,0x00,0x00,0x00,0x00,0x55,0x06,0x01,0x00,0x00,0x00,0x00,0x00,0xb7,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x73,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x79,0x01,0x21,0x00,0x00,0x00,0x00,0x00,0x7b,0x14,0xf6,0xff,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x29,0x00,0x00,0x00,0xbf,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x14,0x00,0x00,0x00,0x00,0x00,0x27,0x06,0x00,0x00,0x38,0x00,0x00,0x00,0xbf,0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x90,0xff,0xff,0xff,0x0f,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x71,0x06,0x30,0x00,0x00,0x00,0x00,0x00,0x73,0x64,0xfe,0xff,0x00,0x00,0x00,0x00,0x79,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x7b,0x64,0xce,0xff,0x00,0x00,0x00,0x00,0x79,0x06,0x08,0x00,0x00,0x00,0x00,0x00,0x7b,0x64,0xd6,0xff,0x00,0x00,0x00,0x00,0x79,0x06,0x10,0x00,0x00,0x00,0x00,0x00,0x7b,0x64,0xde,0xff,0x00,0x00,0x00,0x00,0x79,0x06,0x18,0x00,0x00,0x00,0x00,0x00,0x7b,0x64,0xe6,0xff,0x00,0x00,0x00,0x00,0x79,0x06,0x20,0x00,0x00,0x00,0x00,0x00,0x7b,0x64,0xee,0xff,0x00,0x00,0x00,0x00,0x71,0x06,0x32,0x00,0x00,0x00,0x00,0x00,0x73,0x64,0x00,0x00,0x00,0x00,0x00,0x00,0x79,0x00,0x28,0x00,0x00,0x00,0x00,0x00,0x7b,0x04,0xf6,0xff,0x00,0x00,0x00,0x00,0xb7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x04,0x00,0x00,0x38,0x00,0x00,0x00,0x07,0x03,0x00,0x00,0x01,0x00,0x00,0x00,0x2d,0x32,0x01,0x00,0x00,0x00,0x00,0x00,0x95,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xbf,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x71,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x2d,0x35,0xc2,0xff,0x00,0x00,0x00,0x00,0x55,0x06,0xf6,0xff,0xff,0x00,0x00,0x00,0x79,0x01,0x2b,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x2b,0x00,0x00,0x00,0x0f,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x01,0x00,0x00,0x31,0x00,0x00,0x00,0x05,0x00,0xf1,0xff,0x00,0x00,0x00,0x00,0x1e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x12,0x00,0x01,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x65,0x6e,0x74,0x72,0x79,0x70,0x6f,0x69,0x6e,0x74,0x00,0x4c,0x69,0x6e,0x6b,0x65,0x72,0x3a,0x20,0x4c,0x4c,0x44,0x20,0x31,0x33,0x2e,0x30,0x2e,0x30,0x20,0x28,0x68,0x74,0x74,0x70,0x73,0x3a,0x2f,0x2f,0x67,0x69,0x74,0x68,0x75,0x62,0x2e,0x63,0x6f,0x6d,0x2f,0x73,0x6f,0x6c,0x61,0x6e,0x61,0x2d,0x6c,0x61,0x62,0x73,0x2f,0x6c,0x6c,0x76,0x6d,0x2d,0x70,0x72,0x6f,0x6a,0x65,0x63,0x74,0x2e,0x67,0x69,0x74,0x20,0x31,0x65,0x38,0x30,0x38,0x31,0x64,0x37,0x32,0x35,0x62,0x62,0x30,0x63,0x32,0x61,0x65,0x65,0x66,0x30,0x62,0x35,0x62,0x36,0x61,0x66,0x30,0x32,0x30,0x34,0x31,0x31,0x63,0x30,0x62,0x38,0x33,0x34,0x62,0x62,0x29,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x04,0x00,0xf1,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x12,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x48,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1a,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x50,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x88,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0xb0,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x37,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x08,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x58,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x47,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x28,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5a,0x00,0x00,0x00,0x00,0x02,0x02,0x00,0xa0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4f,0x00,0x00,0x00,0x12,0x00,0x01,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2e,0x74,0x65,0x78,0x74,0x00,0x2e,0x64,0x79,0x6e,0x61,0x6d,0x69,0x63,0x00,0x2e,0x64,0x79,0x6e,0x73,0x79,0x6d,0x00,0x2e,0x64,0x79,0x6e,0x73,0x74,0x72,0x00,0x2e,0x63,0x6f,0x6d,0x6d,0x65,0x6e,0x74,0x00,0x2e,0x73,0x79,0x6d,0x74,0x61,0x62,0x00,0x2e,0x73,0x68,0x73,0x74,0x72,0x74,0x61,0x62,0x00,0x2e,0x73,0x74,0x72,0x74,0x61,0x62,0x00,0x00,0x6e,0x6f,0x6f,0x70,0x5f,0x75,0x6e,0x61,0x6c,0x69,0x67,0x6e,0x65,0x64,0x2e,0x63,0x00,0x4c,0x42,0x42,0x30,0x5f,0x31,0x36,0x00,0x4c,0x42,0x42,0x30,0x5f,0x33,0x00,0x4c,0x42,0x42,0x30,0x5f,0x36,0x00,0x4c,0x42,0x42,0x30,0x5f,0x31,0x34,0x00,0x4c,0x42,0x42,0x30,0x5f,0x39,0x00,0x4c,0x42,0x42,0x30,0x5f,0x31,0x31,0x00,0x4c,0x42,0x42,0x30,0x5f,0x31,0x33,0x00,0x4c,0x42,0x42,0x30,0x5f,0x31,0x35,0x00,0x65,0x6e,0x74,0x72,0x79,0x70,0x6f,0x69,0x6e,0x74,0x00,0x5f,0x44,0x59,0x4e,0x41,0x4d,0x49,0x43,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xa0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xa0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x0b,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4c,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x6e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x29,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x0b,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x43,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3b,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x23,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x63,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
  test_acc->result_data     = fd_flamenco_native_prog_test_1645_acc_0_post_data;
  test_acc->result_data_len = 2248UL;
  test_acc++;
  fd_base58_decode_32( "1111112ygKucwx7MR4i5XjgyZvqCjaDNmRqckFR9H",  (uchar *) &test_acc->pubkey);
  fd_base58_decode_32( "BPFLoader1111111111111111111111111111111111",  (uchar *) &test_acc->owner);
  test_acc->lamports        = 1UL;
  test_acc->result_lamports = 1UL;
  test_acc->executable      = 0;
  test_acc->rent_epoch      = 0;
  test_acc++;
  fd_base58_decode_32( "BPFLoader1111111111111111111111111111111111",  (unsigned char *) &test.program_id);
  static uchar const fd_flamenco_native_prog_test_1645_raw[] = { 0x00,0x00,0x00,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x1d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0xa8,0xf6,0x91,0x4e,0x88,0xa1,0x6b,0xbd,0x23,0x95,0x85,0x5f,0x64,0x04,0xd9,0xb4,0xf4,0x56,0xb7,0x82,0x1b,0xb0,0x14,0x57,0x49,0x42,0x8c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00 };
  test.raw_tx = fd_flamenco_native_prog_test_1645_raw;
  test.raw_tx_len = 106UL;
  test.expected_result = 0;
  test.custom_err = 0;

  test.accs_len = test_accs_len;
  test.accs = test_accs;

  return fd_executor_run_test( &test, suite );
}
