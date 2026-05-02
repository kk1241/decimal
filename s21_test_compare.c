#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

START_TEST(less_negative_true) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-65535", &number1);
  s21_from_string_to_decimal("-65534", &number2);
  ck_assert_int_eq(s21_is_less(number1, number2), TRUE);
}
END_TEST

START_TEST(less_negative_eq) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-100000", &number1);
  s21_from_string_to_decimal("-100000", &number2);
  ck_assert_int_eq(s21_is_less(number1, number2), FALSE);
}
END_TEST

START_TEST(less_negative_false) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-65535", &number1);
  s21_from_string_to_decimal("-65534", &number2);
  ck_assert_int_eq(s21_is_less(number1, number2), TRUE);
}
END_TEST

START_TEST(less_negative_positive) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-100000", &number1);
  s21_from_string_to_decimal("+100000", &number2);
  ck_assert_int_eq(s21_is_less(number1, number2), TRUE);
}
END_TEST

START_TEST(less_positive_negative) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+100000", &number1);
  s21_from_string_to_decimal("-100000", &number2);
  ck_assert_int_eq(s21_is_less(number1, number2), FALSE);
}
END_TEST

START_TEST(less_positive_true) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+100000", &number1);
  s21_from_string_to_decimal("+100001", &number2);
  ck_assert_int_eq(s21_is_less(number1, number2), TRUE);
}
END_TEST

START_TEST(less_positive_false) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+100000", &number1);
  s21_from_string_to_decimal("-100000", &number2);
  ck_assert_int_eq(s21_is_less(number1, number2), FALSE);
}
END_TEST

START_TEST(less_positive_eq) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+100002", &number1);
  s21_from_string_to_decimal("+100002", &number2);
  ck_assert_int_eq(s21_is_less(number1, number2), FALSE);
}
END_TEST

START_TEST(less_mp_zero) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-0", &number1);
  s21_from_string_to_decimal("+0", &number2);

  ck_assert_int_eq(s21_is_less(number1, number2), FALSE);
}
END_TEST

START_TEST(less_pm_zero) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+0", &number1);
  s21_from_string_to_decimal("-0", &number2);
  ck_assert_int_eq(s21_is_less(number1, number2), FALSE);
}
END_TEST

START_TEST(less_eq_negative_true) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-65535", &number1);
  s21_from_string_to_decimal("-65534", &number2);
  ck_assert_int_eq(s21_is_less_or_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(less_eq_negative_eq) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-100000", &number1);
  s21_from_string_to_decimal("-100000", &number2);
  ck_assert_int_eq(s21_is_less_or_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(less_eq_negative_false) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-100000", &number1);
  s21_from_string_to_decimal("-100001", &number2);
  ck_assert_int_eq(s21_is_less_or_equal(number1, number2), FALSE);
}
END_TEST

START_TEST(less_eq_negative_positive) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-100000", &number1);
  s21_from_string_to_decimal("+100000", &number2);
  ck_assert_int_eq(s21_is_less_or_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(less_eq_positive_negative) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+100000", &number1);
  s21_from_string_to_decimal("-100000", &number2);
  ck_assert_int_eq(s21_is_less_or_equal(number1, number2), FALSE);
}
END_TEST

START_TEST(less_eq_positive_true) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+100000", &number1);
  s21_from_string_to_decimal("+100001", &number2);
  ck_assert_int_eq(s21_is_less_or_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(less_eq_positive_false) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+100002", &number1);
  s21_from_string_to_decimal("+100001", &number2);
  ck_assert_int_eq(s21_is_less_or_equal(number1, number2), FALSE);
}
END_TEST

START_TEST(less_eq_positive_eq) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};
  s21_from_string_to_decimal("+100002", &number1);
  s21_from_string_to_decimal("+100002", &number2);
  ck_assert_int_eq(s21_is_less_or_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(less_eq_mp_zero) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-0", &number1);
  s21_from_string_to_decimal("+0", &number2);
  ck_assert_int_eq(s21_is_less_or_equal(number1, number2), TRUE);

  s21_from_string_to_decimal("+0", &number1);
  s21_from_string_to_decimal("-0", &number2);
  ck_assert_int_eq(s21_is_less_or_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(less_eq_pm_zero) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+0", &number1);
  s21_from_string_to_decimal("-0", &number2);
  ck_assert_int_eq(s21_is_less_or_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(greater_negative_false) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-65535", &number1);
  s21_from_string_to_decimal("-65534", &number2);
  ck_assert_int_eq(s21_is_greater(number1, number2), FALSE);
}
END_TEST

START_TEST(greater_negative_eq) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-100000", &number1);
  s21_from_string_to_decimal("-100000", &number2);
  ck_assert_int_eq(s21_is_greater(number1, number2), FALSE);
}
END_TEST

START_TEST(greater_negative_true) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-100000", &number1);
  s21_from_string_to_decimal("-100001", &number2);
  ck_assert_int_eq(s21_is_greater(number1, number2), TRUE);
}
END_TEST

START_TEST(greater_negative_positive) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-100000", &number1);
  s21_from_string_to_decimal("+100000", &number2);
  ck_assert_int_eq(s21_is_greater(number1, number2), FALSE);
}
END_TEST

START_TEST(greater_positive_negative) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+100000", &number1);
  s21_from_string_to_decimal("-100000", &number2);
  ck_assert_int_eq(s21_is_greater(number1, number2), TRUE);
}
END_TEST

START_TEST(greater_positive_false) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+100000", &number1);
  s21_from_string_to_decimal("+100001", &number2);
  ck_assert_int_eq(s21_is_greater(number1, number2), FALSE);
}
END_TEST

START_TEST(greater_positive_true) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+100002", &number1);
  s21_from_string_to_decimal("+100001", &number2);
  ck_assert_int_eq(s21_is_greater(number1, number2), TRUE);
}
END_TEST

START_TEST(greater_positive_eq) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+100002", &number1);
  s21_from_string_to_decimal("+100002", &number2);
  ck_assert_int_eq(s21_is_greater(number1, number2), FALSE);
}
END_TEST

START_TEST(greater_mp_zero) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-0", &number1);
  s21_from_string_to_decimal("+0", &number2);
  ck_assert_int_eq(s21_is_greater(number1, number2), FALSE);
}
END_TEST

START_TEST(greater_pm_zero) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+0", &number1);
  s21_from_string_to_decimal("-0", &number2);
  ck_assert_int_eq(s21_is_greater(number1, number2), FALSE);
}
END_TEST

START_TEST(greater_eq_negative_false) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-65535", &number1);
  s21_from_string_to_decimal("-65534", &number2);
  ck_assert_int_eq(s21_is_greater_or_equal(number1, number2), FALSE);
}
END_TEST

START_TEST(greater_eq_negative_eq) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-100000", &number1);
  s21_from_string_to_decimal("-100000", &number2);
  ck_assert_int_eq(s21_is_greater_or_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(greater_eq_negative_true) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-100000", &number1);
  s21_from_string_to_decimal("-100001", &number2);
  ck_assert_int_eq(s21_is_greater_or_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(greater_eq_negative_positive) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-100000", &number1);
  s21_from_string_to_decimal("+100000", &number2);
  ck_assert_int_eq(s21_is_greater_or_equal(number1, number2), FALSE);
}
END_TEST

START_TEST(greater_eq_positive_negative) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+100000", &number1);
  s21_from_string_to_decimal("-100000", &number2);
  ck_assert_int_eq(s21_is_greater_or_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(greater_eq_positive_false) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+100000", &number1);
  s21_from_string_to_decimal("+100001", &number2);
  ck_assert_int_eq(s21_is_greater_or_equal(number1, number2), FALSE);
}
END_TEST

START_TEST(greater_eq_positive_true) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+100002", &number1);
  s21_from_string_to_decimal("+100001", &number2);
  ck_assert_int_eq(s21_is_greater_or_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(greater_eq_positive_eq) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+100002", &number1);
  s21_from_string_to_decimal("+100002", &number2);
  ck_assert_int_eq(s21_is_greater_or_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(greater_eq_mp_zero) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-0", &number1);
  s21_from_string_to_decimal("+0", &number2);
  ck_assert_int_eq(s21_is_greater_or_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(greater_eq_pm_zero) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("+0", &number1);
  s21_from_string_to_decimal("-0", &number2);
  ck_assert_int_eq(s21_is_greater_or_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(equal_negative) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-65535", &number1);
  s21_from_string_to_decimal("-65535", &number2);
  ck_assert_int_eq(s21_is_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(equal_positive) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("65535", &number1);
  s21_from_string_to_decimal("65535", &number2);
  ck_assert_int_eq(s21_is_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(equal_negative_positive) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-65535", &number1);
  s21_from_string_to_decimal("65535", &number2);
  ck_assert_int_eq(s21_is_equal(number1, number2), FALSE);
}
END_TEST

START_TEST(equal_positive_negative) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("65535", &number1);
  s21_from_string_to_decimal("-65535", &number2);
  ck_assert_int_eq(s21_is_equal(number1, number2), FALSE);
}
END_TEST

START_TEST(equal_mp_zero) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-0", &number1);
  s21_from_string_to_decimal("0", &number2);
  ck_assert_int_eq(s21_is_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(equal_pm_zero) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("0", &number1);
  s21_from_string_to_decimal("-0", &number2);
  ck_assert_int_eq(s21_is_equal(number1, number2), TRUE);
}
END_TEST

START_TEST(not_equal_negative) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-65535", &number1);
  s21_from_string_to_decimal("-65535", &number2);
  ck_assert_int_eq(s21_is_not_equal(number1, number2), FALSE);
}
END_TEST

START_TEST(not_equal_positive) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("65535", &number1);
  s21_from_string_to_decimal("65535", &number2);
  ck_assert_int_eq(s21_is_not_equal(number1, number2), FALSE);
}

END_TEST

START_TEST(not_equal_negative_positive) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-65535", &number1);
  s21_from_string_to_decimal("65535", &number2);
  ck_assert_int_eq(s21_is_not_equal(number1, number2), TRUE);
}

END_TEST

START_TEST(not_equal_positive_negative) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("65535", &number1);
  s21_from_string_to_decimal("-65535", &number2);
  ck_assert_int_eq(s21_is_not_equal(number1, number2), TRUE);
}

END_TEST

START_TEST(not_equal_mp_zero) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("-0", &number1);
  s21_from_string_to_decimal("0", &number2);
  ck_assert_int_eq(s21_is_not_equal(number1, number2), FALSE);
}

END_TEST

START_TEST(not_equal_pm_zero) {
  s21_decimal number1 = {{0}};
  s21_decimal number2 = {{0}};

  s21_from_string_to_decimal("0", &number1);
  s21_from_string_to_decimal("-0", &number2);
  ck_assert_int_eq(s21_is_not_equal(number1, number2), FALSE);
}
END_TEST

// Функция создания набора тестов.
Suite *create_compare_suite(void) {
  Suite *suite = suite_create("compare");

  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_less = tcase_create("is_less");
  TCase *tcase_less_eq = tcase_create("is_less_or_equal");
  TCase *tcase_greater = tcase_create("is_greater");
  TCase *tcase_greater_eq = tcase_create("is_greater_or_equal");
  TCase *tcase_equal = tcase_create("is_equal");
  TCase *tcase_not_equal = tcase_create("is_not_equal");

  tcase_add_test(tcase_less, less_negative_true);
  tcase_add_test(tcase_less, less_negative_eq);
  tcase_add_test(tcase_less, less_negative_false);
  tcase_add_test(tcase_less, less_negative_positive);

  tcase_add_test(tcase_less, less_positive_true);
  tcase_add_test(tcase_less, less_positive_eq);
  tcase_add_test(tcase_less, less_positive_false);
  tcase_add_test(tcase_less, less_positive_negative);

  tcase_add_test(tcase_less, less_mp_zero);
  tcase_add_test(tcase_less, less_pm_zero);

  tcase_add_test(tcase_less_eq, less_eq_negative_true);
  tcase_add_test(tcase_less_eq, less_eq_negative_eq);
  tcase_add_test(tcase_less_eq, less_eq_negative_false);
  tcase_add_test(tcase_less_eq, less_eq_negative_positive);

  tcase_add_test(tcase_less_eq, less_eq_positive_true);
  tcase_add_test(tcase_less_eq, less_eq_positive_eq);
  tcase_add_test(tcase_less_eq, less_eq_positive_false);
  tcase_add_test(tcase_less_eq, less_eq_positive_negative);

  tcase_add_test(tcase_less_eq, less_eq_mp_zero);
  tcase_add_test(tcase_less_eq, less_eq_pm_zero);

  tcase_add_test(tcase_greater, greater_negative_true);
  tcase_add_test(tcase_greater, greater_negative_eq);
  tcase_add_test(tcase_greater, greater_negative_false);
  tcase_add_test(tcase_greater, greater_negative_positive);

  tcase_add_test(tcase_greater, greater_positive_true);
  tcase_add_test(tcase_greater, greater_positive_eq);
  tcase_add_test(tcase_greater, greater_positive_false);
  tcase_add_test(tcase_greater, greater_positive_negative);

  tcase_add_test(tcase_greater, greater_mp_zero);
  tcase_add_test(tcase_greater, greater_pm_zero);

  tcase_add_test(tcase_greater_eq, greater_eq_negative_true);
  tcase_add_test(tcase_greater_eq, greater_eq_negative_eq);
  tcase_add_test(tcase_greater_eq, greater_eq_negative_false);
  tcase_add_test(tcase_greater_eq, greater_eq_negative_positive);

  tcase_add_test(tcase_greater_eq, greater_eq_positive_true);
  tcase_add_test(tcase_greater_eq, greater_eq_positive_eq);
  tcase_add_test(tcase_greater_eq, greater_eq_positive_false);
  tcase_add_test(tcase_greater_eq, greater_eq_positive_negative);

  tcase_add_test(tcase_greater_eq, greater_eq_mp_zero);
  tcase_add_test(tcase_greater_eq, greater_eq_pm_zero);

  tcase_add_test(tcase_equal, equal_negative);
  tcase_add_test(tcase_equal, equal_positive);
  tcase_add_test(tcase_equal, equal_negative_positive);
  tcase_add_test(tcase_equal, equal_positive_negative);
  tcase_add_test(tcase_equal, equal_mp_zero);
  tcase_add_test(tcase_equal, equal_pm_zero);

  tcase_add_test(tcase_not_equal, not_equal_negative);
  tcase_add_test(tcase_not_equal, not_equal_positive);
  tcase_add_test(tcase_not_equal, not_equal_negative_positive);
  tcase_add_test(tcase_not_equal, not_equal_positive_negative);
  tcase_add_test(tcase_not_equal, not_equal_mp_zero);
  tcase_add_test(tcase_not_equal, not_equal_pm_zero);

  /*Добавление групп в тестовый набор.*/
  suite_add_tcase(suite, tcase_less);
  suite_add_tcase(suite, tcase_less_eq);
  suite_add_tcase(suite, tcase_greater);
  suite_add_tcase(suite, tcase_greater_eq);
  suite_add_tcase(suite, tcase_equal);
  suite_add_tcase(suite, tcase_not_equal);

  return suite;
}