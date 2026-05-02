#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

START_TEST(negate_positive) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("-1.5", &number);
  s21_from_string_to_decimal("1.5", &perfectResult);
  s21_negate(number, &result);
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(negate_negative) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("1000000000000000000", &number);
  s21_from_string_to_decimal("-1000000000000000000", &perfectResult);
  s21_negate(number, &result);
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(truncate_less_1) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("0.9999", &number);
  s21_from_string_to_decimal("0", &perfectResult);
  s21_truncate(number, &result);
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(truncate_positive) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("111.9999", &number);
  s21_from_string_to_decimal("111", &perfectResult);
  s21_truncate(number, &result);
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(truncate_negative) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("-111.0000001", &number);
  s21_from_string_to_decimal("-111", &perfectResult);
  s21_truncate(number, &result);
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(truncate_positive_int) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("65535", &number);
  s21_from_string_to_decimal("65535", &perfectResult);
  s21_truncate(number, &result);
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(truncate_negative_int) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("-32768", &number);
  s21_from_string_to_decimal("-32768", &perfectResult);
  s21_truncate(number, &result);
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(round_0_49) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("0.4999999", &number);
  s21_from_string_to_decimal("0", &perfectResult);
  s21_round(number, &result);
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(round_2_5) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("2.500000", &number);
  s21_from_string_to_decimal("3", &perfectResult);
  s21_round(number, &result);
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(round_m_2_49) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("-2.4999999999", &number);
  s21_from_string_to_decimal("-2", &perfectResult);
  s21_round(number, &result);
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(round_m_2_5) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("-2.5000000", &number);
  s21_from_string_to_decimal("-3", &perfectResult);
  s21_round(number, &result);
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(round_positive_int) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("131072", &number);
  s21_from_string_to_decimal("131072", &perfectResult);
  s21_round(number, &result);  // Исправлено с truncate на round
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(round_negative_int) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("-65536", &number);
  s21_from_string_to_decimal("-65536", &perfectResult);
  s21_round(number, &result);  // Исправлено с truncate на round
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(floor_0_49) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("0.4999999", &number);
  s21_from_string_to_decimal("0", &perfectResult);
  s21_floor(number, &result);
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(floor_2_5) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("2.500000", &number);
  s21_from_string_to_decimal("2", &perfectResult);
  s21_floor(number, &result);
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(floor_m_2_49) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("-2.4999999999", &number);
  s21_from_string_to_decimal("-3", &perfectResult);
  s21_floor(number, &result);
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(floor_m_3_1) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("-3.1000000", &number);
  s21_from_string_to_decimal("-4", &perfectResult);
  s21_floor(number, &result);
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(floor_positive_int) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("16384", &number);
  s21_from_string_to_decimal("16384", &perfectResult);
  s21_floor(number, &result);
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

START_TEST(floor_negative_int) {
  s21_decimal number = {{0}};
  s21_decimal result = {{0}};
  s21_decimal perfectResult = {{0}};

  unsigned int *presult = &result.bits[0];
  unsigned int *pperfectResult = &perfectResult.bits[0];

  s21_from_string_to_decimal("-49152", &number);
  s21_from_string_to_decimal("-49152", &perfectResult);
  s21_floor(number, &result);
  ck_assert_mem_eq(presult, pperfectResult, 16);
}
END_TEST

// ========ТЕСТЫ ДЛЯ bank_round=======

START_TEST(test_value_shot_to_decimal_basic) {
  s21_big_decimal value = {{123456789, 0}};
  value.bits[6] = 0x00010000;  // exp = 1
  s21_big_decimal remainder = {0};
  int exp = 1;

  s21_value_shot_to_decimal(&value, &remainder, &exp);

  ck_assert_int_eq(exp, 0);
  ck_assert_uint_eq(value.bits[0], 12345678);
  ck_assert_uint_eq(remainder.bits[0], 9);
}
END_TEST

START_TEST(test_bank_round_even) {
  s21_big_decimal value = {{2, 0}};
  s21_big_decimal remainder = {{5, 0}};

  s21_value_shot_bankRound(&value, &remainder, 0);

  ck_assert_uint_eq(value.bits[0], 2);
}
END_TEST

START_TEST(test_bank_round_odd) {
  s21_big_decimal value = {{3, 0}};
  s21_big_decimal remainder = {{5, 0}};

  s21_value_shot_bankRound(&value, &remainder, 0);

  ck_assert_uint_eq(value.bits[0], 4);  // Ожидаем 4 (3.5 -> 4)
}
END_TEST

START_TEST(test_round_with_carry) {
  s21_big_decimal value = {{999999999, 0}};
  value.bits[6] = 0x00010000;
  s21_big_decimal expected = {{100000000, 0}};

  s21_big_bankRound(&value);

  ck_assert_uint_eq(value.bits[0], expected.bits[0]);
  ck_assert_uint_eq(value.bits[1], expected.bits[1]);
}
END_TEST

Suite *create_another_suite(void) {
  Suite *suite = suite_create("another");

  TCase *tcase_negate = tcase_create("negate");
  TCase *tcase_truncate = tcase_create("truncate");
  TCase *tcase_round = tcase_create("round");
  TCase *tcase_floor = tcase_create("floor");

  tcase_add_test(tcase_negate, negate_positive);
  tcase_add_test(tcase_negate, negate_negative);

  tcase_add_test(tcase_truncate, truncate_less_1);
  tcase_add_test(tcase_truncate, truncate_positive);
  tcase_add_test(tcase_truncate, truncate_negative);
  tcase_add_test(tcase_truncate, truncate_positive_int);
  tcase_add_test(tcase_truncate, truncate_negative_int);

  tcase_add_test(tcase_round, round_0_49);
  tcase_add_test(tcase_round, round_2_5);
  tcase_add_test(tcase_round, round_m_2_49);
  tcase_add_test(tcase_round, round_m_2_5);
  tcase_add_test(tcase_round, round_positive_int);
  tcase_add_test(tcase_round, round_negative_int);

  tcase_add_test(tcase_floor, floor_0_49);
  tcase_add_test(tcase_floor, floor_2_5);
  tcase_add_test(tcase_floor, floor_m_2_49);
  tcase_add_test(tcase_floor, floor_m_3_1);
  tcase_add_test(tcase_floor, floor_positive_int);
  tcase_add_test(tcase_floor, floor_negative_int);

  tcase_add_test(tcase_floor, test_value_shot_to_decimal_basic);
  tcase_add_test(tcase_floor, test_bank_round_even);
  tcase_add_test(tcase_floor, test_bank_round_odd);
  tcase_add_test(tcase_floor, test_round_with_carry);

  suite_add_tcase(suite, tcase_negate);
  suite_add_tcase(suite, tcase_truncate);
  suite_add_tcase(suite, tcase_round);
  suite_add_tcase(suite, tcase_floor);

  return suite;
}
