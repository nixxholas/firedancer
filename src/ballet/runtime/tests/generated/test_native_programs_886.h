#include "../fd_tests.h"
int test_886(fd_executor_test_suite_t *suite) {
  fd_executor_test_t test;
  fd_memset( &test, 0, FD_EXECUTOR_TEST_FOOTPRINT );
  test.disable_cnt = 47;
  uchar disabled_features[] = { 111,98,29,82,113,90,33,116,77,125,89,78,120,92,112,110,124,105,114,126,122,117,26,62,80,87,75,83,79,27,106,109,30,118,108,128,76,24,56,121,2,15,61,127,103,55,123 };
  test.disable_feature = disabled_features;
  test.bt = "   2: solana_stake_program::stake_instruction::tests::process_instruction             at ./src/stake_instruction.rs:578:9   3: solana_stake_program::stake_instruction::tests::test_split_to_account_with_rent_exempt_reserve             at ./src/stake_instruction.rs:5150:28   4: solana_stake_program::stake_instruction::tests::test_split_to_account_with_rent_exempt_reserve::old_behavior             at ./src/stake_instruction.rs:5078:5   5: solana_stake_program::stake_instruction::tests::test_split_to_account_with_rent_exempt_reserve::old_behavior::{{closure}}             at ./src/stake_instruction.rs:5078:5";
  test.test_name = "stake_instruction::tests::test_split_to_account_with_rent_exempt_reserve::old_behavior";
  test.test_nonce  = 407;
  test.test_number = 886;
  if (fd_executor_test_suite_check_filter(suite, &test)) return -9999;
  ulong test_accs_len = 3;
  fd_executor_test_acc_t* test_accs = fd_alloca( 1UL, FD_EXECUTOR_TEST_ACC_FOOTPRINT * test_accs_len );
  fd_memset( test_accs, 0, FD_EXECUTOR_TEST_ACC_FOOTPRINT * test_accs_len );

  fd_executor_test_acc_t* test_acc = test_accs;
  fd_base58_decode_32( "7W2zXWRPWuECRvPHeM3aocPfLVGdh7WxsejHPNwex7wj",  (uchar *) &test_acc->pubkey);
  fd_base58_decode_32( "Stake11111111111111111111111111111111111111",  (uchar *) &test_acc->owner);
  test_acc->lamports        = 4565762UL;
  test_acc->result_lamports = 2282881UL;
  test_acc->executable      = 0;
  test_acc->rent_epoch      = 0;
  static uchar const fd_flamenco_native_prog_test_886_acc_0_data[] = { 0x02,0x00,0x00,0x00,0x80,0xd5,0x22,0x00,0x00,0x00,0x00,0x00,0x60,0x96,0x37,0x99,0x9c,0x73,0xd8,0x31,0x7f,0xe4,0xdd,0xf9,0x06,0x64,0x23,0x31,0x72,0x71,0x1f,0x4f,0x48,0x5a,0xb9,0xa5,0xc1,0xc7,0xa1,0xef,0xba,0x63,0xdf,0x26,0x60,0x96,0x37,0x99,0x9c,0x73,0xd8,0x31,0x7f,0xe4,0xdd,0xf9,0x06,0x64,0x23,0x31,0x72,0x71,0x1f,0x4f,0x48,0x5a,0xb9,0xa5,0xc1,0xc7,0xa1,0xef,0xba,0x63,0xdf,0x26,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x82,0xd5,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xd0,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
  test_acc->data            = fd_flamenco_native_prog_test_886_acc_0_data;
  test_acc->data_len        = 200UL;
  static uchar const fd_flamenco_native_prog_test_886_acc_0_post_data[] = { 0x02,0x00,0x00,0x00,0x80,0xd5,0x22,0x00,0x00,0x00,0x00,0x00,0x60,0x96,0x37,0x99,0x9c,0x73,0xd8,0x31,0x7f,0xe4,0xdd,0xf9,0x06,0x64,0x23,0x31,0x72,0x71,0x1f,0x4f,0x48,0x5a,0xb9,0xa5,0xc1,0xc7,0xa1,0xef,0xba,0x63,0xdf,0x26,0x60,0x96,0x37,0x99,0x9c,0x73,0xd8,0x31,0x7f,0xe4,0xdd,0xf9,0x06,0x64,0x23,0x31,0x72,0x71,0x1f,0x4f,0x48,0x5a,0xb9,0xa5,0xc1,0xc7,0xa1,0xef,0xba,0x63,0xdf,0x26,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xd0,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
  test_acc->result_data     = fd_flamenco_native_prog_test_886_acc_0_post_data;
  test_acc->result_data_len = 200UL;
  test_acc++;
  fd_base58_decode_32( "5LdSRvZQgi6iktkgNhQ1nbyuNcBKjyJrVUfKoHu3bh7b",  (uchar *) &test_acc->pubkey);
  fd_base58_decode_32( "Stake11111111111111111111111111111111111111",  (uchar *) &test_acc->owner);
  test_acc->lamports        = 2282881UL;
  test_acc->result_lamports = 4565762UL;
  test_acc->executable      = 0;
  test_acc->rent_epoch      = 0;
  static uchar const fd_flamenco_native_prog_test_886_acc_1_data[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
  test_acc->data            = fd_flamenco_native_prog_test_886_acc_1_data;
  test_acc->data_len        = 200UL;
  static uchar const fd_flamenco_native_prog_test_886_acc_1_post_data[] = { 0x02,0x00,0x00,0x00,0x80,0xd5,0x22,0x00,0x00,0x00,0x00,0x00,0x60,0x96,0x37,0x99,0x9c,0x73,0xd8,0x31,0x7f,0xe4,0xdd,0xf9,0x06,0x64,0x23,0x31,0x72,0x71,0x1f,0x4f,0x48,0x5a,0xb9,0xa5,0xc1,0xc7,0xa1,0xef,0xba,0x63,0xdf,0x26,0x60,0x96,0x37,0x99,0x9c,0x73,0xd8,0x31,0x7f,0xe4,0xdd,0xf9,0x06,0x64,0x23,0x31,0x72,0x71,0x1f,0x4f,0x48,0x5a,0xb9,0xa5,0xc1,0xc7,0xa1,0xef,0xba,0x63,0xdf,0x26,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x81,0xd5,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xd0,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
  test_acc->result_data     = fd_flamenco_native_prog_test_886_acc_1_post_data;
  test_acc->result_data_len = 200UL;
  test_acc++;
  fd_base58_decode_32( "SysvarRent111111111111111111111111111111111",  (uchar *) &test_acc->pubkey);
  fd_base58_decode_32( "Sysvar1111111111111111111111111111111111111",  (uchar *) &test_acc->owner);
  test_acc->lamports        = 1UL;
  test_acc->result_lamports = 1UL;
  test_acc->executable      = 0;
  test_acc->rent_epoch      = 0;
  static uchar const fd_flamenco_native_prog_test_886_acc_2_data[] = { 0x98,0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x32 };
  test_acc->data            = fd_flamenco_native_prog_test_886_acc_2_data;
  test_acc->data_len        = 17UL;
  static uchar const fd_flamenco_native_prog_test_886_acc_2_post_data[] = { 0x98,0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x32 };
  test_acc->result_data     = fd_flamenco_native_prog_test_886_acc_2_post_data;
  test_acc->result_data_len = 17UL;
  test_acc++;
  fd_base58_decode_32( "Stake11111111111111111111111111111111111111",  (unsigned char *) &test.program_id);
  static uchar const fd_flamenco_native_prog_test_886_raw[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x03,0x60,0x96,0x37,0x99,0x9c,0x73,0xd8,0x31,0x7f,0xe4,0xdd,0xf9,0x06,0x64,0x23,0x31,0x72,0x71,0x1f,0x4f,0x48,0x5a,0xb9,0xa5,0xc1,0xc7,0xa1,0xef,0xba,0x63,0xdf,0x26,0x40,0x75,0xfb,0xf1,0xb7,0xef,0x2f,0x1f,0x69,0xb0,0xef,0x67,0xe5,0x3b,0xb6,0x04,0x72,0x73,0x93,0xfe,0xf3,0x74,0xaa,0xf4,0x1e,0x63,0x98,0x83,0x89,0x7b,0x58,0x0e,0x06,0xa1,0xd8,0x17,0x91,0x37,0x54,0x2a,0x98,0x34,0x37,0xbd,0xfe,0x2a,0x7a,0xb2,0x55,0x7f,0x53,0x5c,0x8a,0x78,0x72,0x2b,0x68,0xa4,0x9d,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x02,0x00,0x01,0x0c,0x03,0x00,0x00,0x00,0x81,0xd5,0x22,0x00,0x00,0x00,0x00,0x00 };
  test.raw_tx = fd_flamenco_native_prog_test_886_raw;
  test.raw_tx_len = 215UL;
  test.expected_result = 0;
  test.custom_err = 0;

  test.accs_len = test_accs_len;
  test.accs = test_accs;

  return fd_executor_run_test( &test, suite );
}
