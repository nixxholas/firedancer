#include "../fd_tests.h"
int test_779(fd_executor_test_suite_t *suite) {
  fd_executor_test_t test;
  fd_memset( &test, 0, FD_EXECUTOR_TEST_FOOTPRINT );
  test.disable_cnt = 0;
  uchar disabled_features[] = { 103,105,106,108,109,110,111,112,113,114,116,117,118,120,121,122,123,124,125,126,127,128,15,2,24,26,27,29,30,33,55,56,61,62,75,76,77,78,79,80,82,83,87,89,90,92,98 };
  test.disable_feature = disabled_features;
  test.bt = "   2: solana_bpf_loader_program::tests::test_bpf_loader_upgradeable_close             at ./src/lib.rs:3764:24   3: solana_bpf_loader_program::tests::test_bpf_loader_upgradeable_close::{{closure}}             at ./src/lib.rs:3696:5   4: core::ops::function::FnOnce::call_once             at /rustc/0677edc86e342f333d4828b0ee1ef395a4e70fe5/library/core/src/ops/function.rs:227:5   5: core::ops::function::FnOnce::call_once             at /rustc/0677edc86e342f333d4828b0ee1ef395a4e70fe5/library/core/src/ops/function.rs:227:5";
  test.test_name = "tests::test_bpf_loader_upgradeable_close";
  test.test_nonce  = 2;
  test.test_number = 779;
  if (fd_executor_test_suite_check_filter(suite, &test)) return -9999;
  ulong test_accs_len = 3;
  fd_executor_test_acc_t* test_accs = fd_alloca( 1UL, FD_EXECUTOR_TEST_ACC_FOOTPRINT * test_accs_len );
  fd_memset( test_accs, 0, FD_EXECUTOR_TEST_ACC_FOOTPRINT * test_accs_len );

  fd_executor_test_acc_t* test_acc = test_accs;
  fd_base58_decode_32( "111111326MXXbjqcVqxz8aD85vk7VCw9nyVt9kR3M",  (uchar *) &test_acc->pubkey);
  fd_base58_decode_32( "BPFLoaderUpgradeab1e11111111111111111111111",  (uchar *) &test_acc->owner);
  test_acc->lamports        = 1UL;
  test_acc->result_lamports = 0UL;
  test_acc->executable      = 0;
  test_acc->rent_epoch      = 0;
  static uchar const fd_flamenco_native_prog_test_779_acc_0_data[] = { 0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
  test_acc->data            = fd_flamenco_native_prog_test_779_acc_0_data;
  test_acc->data_len        = 37UL;
  static uchar const fd_flamenco_native_prog_test_779_acc_0_post_data[] = { 0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
  test_acc->result_data     = fd_flamenco_native_prog_test_779_acc_0_post_data;
  test_acc->result_data_len = 37UL;
  test_acc++;
  fd_base58_decode_32( "11111131HgKZP9GC8vDMGJ35FG79EfMtnTcTgakQf",  (uchar *) &test_acc->pubkey);
  fd_base58_decode_32( "11111131h1vYVSYuKP6AhS86fbRdMw9XHiZAvAaj1",  (uchar *) &test_acc->owner);
  test_acc->lamports        = 1UL;
  test_acc->result_lamports = 2UL;
  test_acc->executable      = 0;
  test_acc->rent_epoch      = 0;
  test_acc++;
  fd_base58_decode_32( "1111112zV17bAYgmmzTiQ1s2QbUAz7ndmwj3DR5my",  (uchar *) &test_acc->pubkey);
  fd_base58_decode_32( "1111112ztLiaGqyUxTLXq9x3pvnf7PaGHCfkSzv6K",  (uchar *) &test_acc->owner);
  test_acc->lamports        = 1UL;
  test_acc->result_lamports = 1UL;
  test_acc->executable      = 0;
  test_acc->rent_epoch      = 0;
  test_acc++;
  fd_base58_decode_32( "BPFLoaderUpgradeab1e11111111111111111111111",  (unsigned char *) &test.program_id);
  static uchar const fd_flamenco_native_prog_test_779_raw[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x21,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x23,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0xa8,0xf6,0x91,0x4e,0x88,0xa1,0xb0,0xe2,0x10,0x15,0x3e,0xf7,0x63,0xae,0x2b,0x00,0xc2,0xb9,0x3d,0x16,0xc1,0x24,0xd2,0xc0,0x53,0x7a,0x10,0x04,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x02,0x01,0x00,0x04,0x05,0x00,0x00,0x00 };
  test.raw_tx = fd_flamenco_native_prog_test_779_raw;
  test.raw_tx_len = 240UL;
  test.expected_result = 0;
  test.custom_err = 0;

  test.accs_len = test_accs_len;
  test.accs = test_accs;

  return fd_executor_run_test( &test, suite );
}
