$(call make-lib,fd_funk)
$(call add-hdrs,fd_funk_base.h fd_funk_txn.h fd_funk_rec.h fd_funk_val.h fd_funk_part.h fd_funk_archive.h fd_funk_filemap.h fd_funk.h)
$(call add-objs,fd_funk_base fd_funk_txn fd_funk_rec fd_funk_val fd_funk_part fd_funk_archive fd_funk_filemap fd_funk,fd_funk)
$(call make-unit-test,test_funk_txn,test_funk_txn,fd_funk fd_util)
$(call run-unit-test,test_funk_txn)
ifdef FD_HAS_HOSTED
$(call make-unit-test,test_funk_base,test_funk_base,fd_funk fd_util)
$(call run-unit-test,test_funk_base)
$(call make-unit-test,test_funk_txn2,test_funk_txn2,fd_funk fd_util)
$(call run-unit-test,test_funk_txn2)
$(call make-unit-test,test_funk_file,test_funk_file,fd_funk fd_util)
$(call make-unit-test,test_funk_archive,test_funk_archive,fd_funk fd_util)
$(call run-unit-test,test_funk_archive)
endif
$(call make-unit-test,test_funk_rec,test_funk_rec test_funk_common,fd_funk fd_util)
$(call run-unit-test,test_funk_rec)
$(call make-unit-test,test_funk_val,test_funk_val test_funk_common,fd_funk fd_util)
$(call run-unit-test,test_funk_val)
$(call make-unit-test,test_funk_part,test_funk_part test_funk_common,fd_funk fd_util)
$(call run-unit-test,test_funk_part)
$(call make-unit-test,test_funk,test_funk,fd_funk fd_util)
$(call run-unit-test,test_funk)
ifdef FD_HAS_HOSTED
$(call make-unit-test,test_funk_concur,test_funk_concur,fd_funk fd_util)
endif
