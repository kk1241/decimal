#include <check.h>

#include "s21_decimal.h"

START_TEST(test_s21_from_big_decimal_to_decimal) {
  s21_big_decimal big_src = {{0, 0, 0, 1, 0, 0, 0}};
  s21_decimal dst;
  // Переполнение мантиссы
  ck_assert_int_eq(s21_from_big_decimal_to_decimal(big_src, &dst), TOOHIGH);

  s21_big_decimal big_normal = {
      {12345, 0, 0, 0, 0, 0, 0x00010000}};  // экспонента 1
  ck_assert_int_eq(s21_from_big_decimal_to_decimal(big_normal, &dst), OK);
  int res;
  s21_from_decimal_to_int(dst, &res);
  ck_assert_int_eq(res, 1234);  // 12345 / 10^1 = 1234.5 -> округление?
}
END_TEST

START_TEST(test_s21_mulMantissa10) {
  s21_big_decimal value = {{123, 0, 0, 0, 0, 0, 0}};
  s21_mulMantissa10(&value);
  ck_assert_int_eq(value.bits[0], 1230);

  s21_big_decimal max_val = {
      {__UINT32_MAX__, __UINT32_MAX__, __UINT32_MAX__, 0, 0, 0, 0}};
  s21_mulMantissa10(&max_val);  // Проверка на переполнение?
  // Здесь может потребоваться дополнительная проверка переноса битов
}
END_TEST

START_TEST(test_s21_big_decimal_norm) {
  s21_big_decimal val1 = {{123, 0, 0, 0, 0, 0, 0x00020000}};  // exp 2
  s21_big_decimal val2 = {{456, 0, 0, 0, 0, 0, 0x00030000}};  // exp 3
  s21_big_decimal_norm(&val1, &val2);
  ck_assert_int_eq(s21_getExt(val1), 3);
  ck_assert_int_eq(s21_getExt(val2), 3);
  // val1 должно быть 123 * 10^(3-2) = 1230
  ck_assert_int_eq(val1.bits[0], 1230);
}
END_TEST

START_TEST(test_s21_big_positive_zero) {
  s21_big_decimal zero_neg = {{0, 0, 0, 0, 0, 0, 0x80010000}};  // знак '-'
  s21_big_positive_zero(&zero_neg);
  ck_assert_int_eq(s21_getSign(zero_neg), 0);
}
END_TEST

START_TEST(test_s21_removeZero) {
  s21_big_decimal num = {
      {123450, 0, 0, 0, 0, 0, 0x00050000}};  // 123450 с exp 5
  s21_removeZero(&num);
  ck_assert_int_eq(s21_getExt(num), 4);  // 123450 -> 12345 (exp 5-4=1)
  ck_assert_int_eq(num.bits[0], 12345);
}
END_TEST

START_TEST(test_s21_decimal_overflow) {
  s21_big_decimal max_pos = {
      {__UINT32_MAX__, __UINT32_MAX__, __UINT32_MAX__, 0, 0, 0, 0}};
  ck_assert_int_eq(s21_decimal_overflow(max_pos), TOOHIGH);

  s21_big_decimal max_neg = {
      {__UINT32_MAX__, __UINT32_MAX__, __UINT32_MAX__, 0, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_decimal_overflow(max_neg), TOOSMALL);
}
END_TEST

START_TEST(test_s21_is_big_zero) {
  s21_big_decimal zero = {0};
  ck_assert(s21_is_big_zero(zero));

  s21_big_decimal non_zero = {{1, 0, 0, 0, 0, 0, 0}};
  ck_assert(!s21_is_big_zero(non_zero));
}
END_TEST

Suite *create_big_decimal_suite(void) {
  Suite *suite = suite_create("big_decimal");

  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_big_decimal = tcase_create("case");

  tcase_add_test(tcase_big_decimal, test_s21_from_big_decimal_to_decimal);
  tcase_add_test(tcase_big_decimal, test_s21_mulMantissa10);
  tcase_add_test(tcase_big_decimal, test_s21_big_decimal_norm);
  tcase_add_test(tcase_big_decimal, test_s21_big_positive_zero);
  tcase_add_test(tcase_big_decimal, test_s21_removeZero);
  tcase_add_test(tcase_big_decimal, test_s21_decimal_overflow);
  tcase_add_test(tcase_big_decimal, test_s21_is_big_zero);

  // Добавление TCase в сьют
  suite_add_tcase(suite, tcase_big_decimal);

  return suite;
}