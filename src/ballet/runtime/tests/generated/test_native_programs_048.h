#include "../fd_tests.h"
int test_48(fd_executor_test_suite_t *suite) {
  fd_executor_test_t test;
  fd_memset( &test, 0, FD_EXECUTOR_TEST_FOOTPRINT );
  test.disable_cnt = 47;
  uchar disabled_features[] = { 26,105,110,61,29,75,111,114,83,62,15,118,89,117,123,90,120,122,78,126,33,128,116,106,80,103,77,56,2,82,108,55,30,27,109,79,121,76,92,112,124,87,127,125,98,24,113 };
  test.disable_feature = disabled_features;
  test.bt = "   2: solana_config_program::config_processor::tests::test_process_store_ok             at ./src/config_processor.rs:247:24   3: solana_config_program::config_processor::tests::test_process_store_ok::{{closure}}             at ./src/config_processor.rs:239:5   4: core::ops::function::FnOnce::call_once             at /rustc/0677edc86e342f333d4828b0ee1ef395a4e70fe5/library/core/src/ops/function.rs:227:5   5: core::ops::function::FnOnce::call_once             at /rustc/0677edc86e342f333d4828b0ee1ef395a4e70fe5/library/core/src/ops/function.rs:227:5";
  test.test_name = "config_processor::tests::test_process_store_ok";
  test.test_nonce  = 15;
  test.test_number = 48;
  if (fd_executor_test_suite_check_filter(suite, &test)) return -9999;
  ulong test_accs_len = 1;
  fd_executor_test_acc_t* test_accs = fd_alloca( 1UL, FD_EXECUTOR_TEST_ACC_FOOTPRINT * test_accs_len );
  fd_memset( test_accs, 0, FD_EXECUTOR_TEST_ACC_FOOTPRINT * test_accs_len );

  fd_executor_test_acc_t* test_acc = test_accs;
  fd_base58_decode_32( "8zhDq5cpWQyEZzbSP4S3Y7ccsMGA5HTP4HjgJBrmb8g5",  (uchar *) &test_acc->pubkey);
  fd_base58_decode_32( "Config1111111111111111111111111111111111111",  (uchar *) &test_acc->owner);
  test_acc->lamports        = 0UL;
  test_acc->result_lamports = 0UL;
  test_acc->executable      = 0;
  test_acc->rent_epoch      = 0;
  static uchar const fd_flamenco_native_prog_test_48_acc_0_data[] = { 0x00,0x15,0xcd,0x5b,0x07,0x00,0x00,0x00,0x00 };
  test_acc->data            = fd_flamenco_native_prog_test_48_acc_0_data;
  test_acc->data_len        = 9UL;
  static uchar const fd_flamenco_native_prog_test_48_acc_0_post_data[] = { 0x00,0x2a,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
  test_acc->result_data     = fd_flamenco_native_prog_test_48_acc_0_post_data;
  test_acc->result_data_len = 9UL;
  test_acc++;
  fd_base58_decode_32( "Config1111111111111111111111111111111111111",  (unsigned char *) &test.program_id);
  static uchar const fd_flamenco_native_prog_test_48_raw[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x02,0x76,0xc9,0x64,0x91,0x7e,0xa0,0x0e,0x23,0x4a,0x27,0xc8,0x8a,0x42,0x4c,0x15,0x86,0x85,0x24,0x2c,0x8d,0xd2,0x10,0xcb,0xda,0xa7,0x86,0x95,0x8b,0xd2,0x6e,0x54,0x86,0x03,0x06,0x4a,0xa3,0x00,0x2f,0x74,0xdc,0xc8,0x6e,0x43,0x31,0x0f,0x0c,0x05,0x2a,0xf8,0xc5,0xda,0x27,0xf6,0x10,0x40,0x19,0xa3,0x23,0xef,0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x09,0x00,0x2a,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
  test.raw_tx = fd_flamenco_native_prog_test_48_raw;
  test.raw_tx_len = 179UL;
  test.expected_result = 0;
  test.custom_err = 0;

  test.accs_len = test_accs_len;
  test.accs = test_accs;

  return fd_executor_run_test( &test, suite );
}
