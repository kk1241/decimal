#include <stdio.h>

#include "s21_test_another.c"
#include "s21_test_arithmetic.c"
#include "s21_test_base.c"
#include "s21_test_big_decimal.c"
#include "s21_test_compare.c"
#include "s21_test_convert.c"

int main(void) {
  Suite *convert_suite = create_convert_suite();
  Suite *arithmetic_suite = create_arithmetic_suite();
  Suite *base_suite = create_base_suite();
  Suite *another_suite = create_another_suite();
  Suite *compare_suite = create_compare_suite();
  Suite *big_decimal_suite = create_big_decimal_suite();

  SRunner *convert_suite_runner = srunner_create(convert_suite);
  SRunner *arithmetic_suite_runner = srunner_create(arithmetic_suite);
  SRunner *base_suite_runner = srunner_create(base_suite);
  SRunner *another_suite_runner = srunner_create(another_suite);
  SRunner *compare_suite_runner = srunner_create(compare_suite);
  SRunner *big_decimal_suite_runner = srunner_create(big_decimal_suite);

  srunner_set_fork_status(convert_suite_runner, CK_NOFORK);
  srunner_set_fork_status(arithmetic_suite_runner, CK_NOFORK);
  srunner_set_fork_status(base_suite_runner, CK_NOFORK);
  srunner_set_fork_status(another_suite_runner, CK_NOFORK);
  srunner_set_fork_status(compare_suite_runner, CK_NOFORK);
  srunner_set_fork_status(big_decimal_suite_runner, CK_NOFORK);

  srunner_run_all(convert_suite_runner, CK_NORMAL);
  srunner_run_all(arithmetic_suite_runner, CK_NORMAL);
  srunner_run_all(base_suite_runner, CK_NORMAL);
  srunner_run_all(another_suite_runner, CK_NORMAL);
  srunner_run_all(compare_suite_runner, CK_NORMAL);
  srunner_run_all(big_decimal_suite_runner, CK_NORMAL);

  int failed_count = srunner_ntests_failed(convert_suite_runner) +
                     srunner_ntests_failed(arithmetic_suite_runner) +
                     srunner_ntests_failed(base_suite_runner) +
                     srunner_ntests_failed(another_suite_runner) +
                     srunner_ntests_failed(compare_suite_runner) +
                     srunner_ntests_failed(big_decimal_suite_runner);

  srunner_free(convert_suite_runner);
  srunner_free(arithmetic_suite_runner);
  srunner_free(base_suite_runner);
  srunner_free(another_suite_runner);
  srunner_free(compare_suite_runner);
  srunner_free(big_decimal_suite_runner);

  return failed_count != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}