#include "../fd_tests.h"
int test_1404(fd_executor_test_suite_t *suite) {
  fd_executor_test_t test;
  fd_memset( &test, 0, FD_EXECUTOR_TEST_FOOTPRINT );
  test.disable_cnt = 47;
  uchar disabled_features[] = { 77,33,117,87,98,78,24,82,56,121,26,80,83,75,113,90,110,123,62,30,105,126,118,108,111,92,29,89,122,120,61,79,112,128,2,125,116,55,114,15,124,103,76,27,109,106,127 };
  test.disable_feature = disabled_features;
  test.bt = "   2: solana_runtime::system_instruction_processor::tests::test_nonce_account_upgrade             at ./src/system_instruction_processor.rs:2354:24   3: solana_runtime::system_instruction_processor::tests::test_nonce_account_upgrade::{{closure}}             at ./src/system_instruction_processor.rs:2273:5   4: core::ops::function::FnOnce::call_once             at /rustc/0677edc86e342f333d4828b0ee1ef395a4e70fe5/library/core/src/ops/function.rs:227:5   5: core::ops::function::FnOnce::call_once             at /rustc/0677edc86e342f333d4828b0ee1ef395a4e70fe5/library/core/src/ops/function.rs:227:5";
  test.test_name = "system_instruction_processor::tests::test_nonce_account_upgrade";
  test.test_nonce  = 27;
  test.test_number = 1404;
  if (fd_executor_test_suite_check_filter(suite, &test)) return -9999;
  ulong test_accs_len = 1;
  fd_executor_test_acc_t* test_accs = fd_alloca( 1UL, FD_EXECUTOR_TEST_ACC_FOOTPRINT * test_accs_len );
  fd_memset( test_accs, 0, FD_EXECUTOR_TEST_ACC_FOOTPRINT * test_accs_len );

  fd_executor_test_acc_t* test_acc = test_accs;
  fd_base58_decode_32( "1111113ZZwyAsQBjoLLAa5nA8Mw5a4qUKdRbfHyYMV",  (uchar *) &test_acc->pubkey);
  fd_base58_decode_32( "11111111111111111111111111111111",  (uchar *) &test_acc->owner);
  test_acc->lamports        = 1000000UL;
  test_acc->result_lamports = 1000000UL;
  test_acc->executable      = 0;
  test_acc->rent_epoch      = 0;
  static uchar const fd_flamenco_native_prog_test_1404_acc_0_data[] = { 0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x53,0xa8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xb0,0x7e,0x8f,0x4b,0xc7,0x9b,0xc5,0x94,0x60,0x0b,0x84,0xa0,0x93,0x85,0xbc,0xfd,0x09,0xcf,0x9b,0x66,0x12,0xfc,0xe3,0x05,0xec,0x2e,0x8c,0x54,0x19,0xb6,0xf2,0x3a,0x9e,0x0a,0x00,0x00,0x00,0x00,0x00,0x00 };
  test_acc->data            = fd_flamenco_native_prog_test_1404_acc_0_data;
  test_acc->data_len        = 80UL;
  static uchar const fd_flamenco_native_prog_test_1404_acc_0_post_data[] = { 0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x53,0xa8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xb0,0x7e,0x8f,0x4b,0xc7,0x9b,0xc5,0x94,0x60,0x0b,0x84,0xa0,0x93,0x85,0xbc,0xfd,0x09,0xcf,0x9b,0x66,0x12,0xfc,0xe3,0x05,0xec,0x2e,0x8c,0x54,0x19,0xb6,0xf2,0x3a,0x9e,0x0a,0x00,0x00,0x00,0x00,0x00,0x00 };
  test_acc->result_data     = fd_flamenco_native_prog_test_1404_acc_0_post_data;
  test_acc->result_data_len = 80UL;
  test_acc++;
  fd_base58_decode_32( "11111111111111111111111111111111",  (unsigned char *) &test.program_id);
  static uchar const fd_flamenco_native_prog_test_1404_raw[] = { 0x00,0x00,0x00,0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x53,0xa7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x04,0x0c,0x00,0x00,0x00 };
  test.raw_tx = fd_flamenco_native_prog_test_1404_raw;
  test.raw_tx_len = 110UL;
  test.expected_result = -2;
  test.custom_err = 0;

  test.accs_len = test_accs_len;
  test.accs = test_accs;

  return fd_executor_run_test( &test, suite );
}
