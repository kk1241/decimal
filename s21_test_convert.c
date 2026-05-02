#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"
#include "s21_output.h"

START_TEST(int_to_dec_null) {
  ck_assert_msg(((s21_from_int_to_decimal(50, NULL) == CONVERT_ERROR)),
                "\n\n\033[91mFAIL\033[39m\n exp: CONVERT_ERROR\n");
}
END_TEST

START_TEST(int_to_dec_plus) {
  s21_decimal res = {0};
  int num = 1655654;
  s21_from_int_to_decimal(num, &res);
  printf("\n");
  printf("int_to_dec_plus: \n");
  printf("num: %d\n", num);
  s21_printDecimalBin(res);

  printf("\n");
}
END_TEST

START_TEST(int_to_dec_minus) {
  s21_decimal res = {0};
  int num = -999999;
  s21_from_int_to_decimal(num, &res);
  printf("\n");
  printf("int_to_dec_minus: \n");
  printf("num: %d\n", num);
  s21_printDecimalBin(res);

  printf("\n");
}
END_TEST

// --------------------------------------------------------------------------------

START_TEST(float_to_dec_max) {
  s21_decimal res = {0};
  ck_assert_msg((s21_from_float_to_decimal(pow(2, 96), &res) == CONVERT_ERROR),
                "\n\n\033[91mFAIL\033[39m\nexp: CONVERT_ERROR\n");
}
END_TEST

START_TEST(float_to_dec_min) {
  s21_decimal res = {0};
  ck_assert_msg((s21_from_float_to_decimal(-pow(2, 96), &res) == CONVERT_ERROR),
                "\n\n\033[91mFAIL\033[39m\nexp: CONVERT_ERROR\n");
}
END_TEST

START_TEST(float_to_dec_toosmall) {
  s21_decimal res = {0};
  ck_assert_msg(
      ((s21_from_float_to_decimal(pow(10, -29), &res) == CONVERT_ERROR)),
      "\n\n\033[91mFAIL\033[39m\nexp: CONVERT_ERROR\n");
}
END_TEST

START_TEST(float_to_dec_inf) {
  float a = INFINITY;
  s21_decimal res = {0};
  int r = s21_from_float_to_decimal(a, &res);

  ck_assert_msg(((r == CONVERT_ERROR)),
                "\n\n\033[91mFAIL\033[39m\nexp: CONVERT_ERROR\n");
}
END_TEST

START_TEST(float_to_dec_nan) {
  float a = NAN;
  s21_decimal res = {0};
  printf("float_to_dec_nan: \n");
  int r = s21_from_float_to_decimal(a, &res);
  printf("test\n");
  ck_assert_msg(((r == CONVERT_ERROR)),
                "\n\n\033[91mFAIL\033[39m\nexp: CONVERT_ERROR\n");
}
END_TEST

// 79228162514264337593543950335 - max
// 79228162514264337593543950336

// true = 1
START_TEST(float_to_dec_32) {
  printf("\n");
  printf("float_to_dec_32: \n");
  s21_decimal res = {0};

  double num = pow(2, 32);
  printf("num: %lf\n", num);

  s21_from_float_to_decimal(num, &res);
  printf("test\n");

  s21_printDecimalBin(res);

  printf("\n");
}
END_TEST

START_TEST(float_to_dec_64) {
  s21_decimal res = {0};
  s21_initialDecimal(&res);
  double num = pow(2, 64);
  printf("\n");
  printf("float_to_dec_64: \n");

  s21_from_float_to_decimal(num, &res);

  printf("num: %lf\n", num);
  s21_printDecimalBin(res);
  // s21_printDecimalDec(res);
  printf("\n");
}
END_TEST

START_TEST(float_to_dec_norm) {
  // -12.18000
  float num = -121.8;
  s21_decimal res = {0};
  printf("\n");
  printf("float_to_dec_norm: \n");
  s21_from_float_to_decimal(num, &res);

  printf("num: %lf\n", num);
  s21_printDecimalBin(res);
  s21_printDecimalDec(res, 0);
  printf("\n");
}
END_TEST

START_TEST(float_to_dec_less1m) {
  // -12.18000
  float num = -0.5;
  s21_decimal res = {0};
  printf("\n");
  printf("float_to_dec_less1m: \n");
  s21_from_float_to_decimal(num, &res);

  printf("num: %f\n", num);
  s21_printDecimalBin(res);
  s21_printDecimalDec(res, 0);
  printf("\n");
}
END_TEST

START_TEST(float_to_dec_less1) {
  // -12.18000
  // 0.00265 +
  //
  float num = 0.5;
  s21_decimal res = {0};
  printf("\n");
  printf("float_to_dec_less1: \n");
  s21_from_float_to_decimal(num, &res);

  printf("num: %f\n", num);
  s21_printDecimalBin(res);
  s21_printDecimalDec(res, 0);
  printf("\n");
}
END_TEST

/*-------CONVERT TEST-------*/
START_TEST(test_s21_from_decimal_to_int) {
  s21_decimal src;
  int result;

  // Тест 1: положительное число
  s21_from_int_to_decimal(123456, &src);
  ck_assert_int_eq(s21_from_decimal_to_int(src, &result), OK);
  ck_assert_int_eq(result, 123456);

  // Тест 2: отрицательное число
  s21_from_int_to_decimal(-654321, &src);
  ck_assert_int_eq(s21_from_decimal_to_int(src, &result), OK);
  ck_assert_int_eq(result, -654321);

  // Тест 3: ноль
  s21_from_int_to_decimal(0, &src);
  ck_assert_int_eq(s21_from_decimal_to_int(src, &result), OK);
  ck_assert_int_eq(result, 0);

  // Остальные тесты где check не нужен
  s21_from_string_to_decimal("2147483648", &src);
  ck_assert_int_eq(s21_from_decimal_to_int(src, &result), CONVERT_ERROR);

  s21_from_string_to_decimal("-2147483649", &src);
  ck_assert_int_eq(s21_from_decimal_to_int(src, &result), CONVERT_ERROR);

  s21_from_float_to_decimal(123.999, &src);
  ck_assert_int_eq(s21_from_decimal_to_int(src, &result), OK);
  ck_assert_int_eq(result, 123);

  ck_assert_int_eq(s21_from_decimal_to_int(src, NULL), CONVERT_ERROR);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal) {
  s21_decimal result;
  int src = 12345;
  s21_from_int_to_decimal(src, &result);

  int check;
  s21_from_decimal_to_int(result, &check);
  ck_assert_int_eq(src, check);

  src = -67890;
  s21_from_int_to_decimal(src, &result);
  s21_from_decimal_to_int(result, &check);
  ck_assert_int_eq(src, check);

  src = 0;
  s21_from_int_to_decimal(src, &result);
  s21_from_decimal_to_int(result, &check);
  ck_assert_int_eq(src, check);

  ck_assert_int_eq(s21_from_int_to_decimal(42, NULL), CONVERT_ERROR);
}
END_TEST

// test_s21_from_decimal_to_float
START_TEST(test_s21_from_decimal_to_float) {
  s21_decimal src = {{0}};
  float result;

  // Проверка отрицательного значения
  s21_from_string_to_decimal("-789.123", &src);
  s21_from_decimal_to_float(src, &result);
  ck_assert_float_eq_tol(result, -789.123f, 1e-3);

  // Проверка точности
  s21_from_string_to_decimal("123.456789", &src);
  s21_from_decimal_to_float(src, &result);
  ck_assert_float_eq_tol(result, 123.456789f, 1e-6);
}
END_TEST

// test_s21_from_float_to_decimal new
START_TEST(test_s21_from_float_to_decimal) {
  s21_decimal dec = {{0}};
  int res;

  // Тест 1: Положительное целое число
  res = s21_from_float_to_decimal(12345.0f, &dec);
  ck_assert_int_eq(res, OK);

  // Тест 2: Отрицательное число
  res = s21_from_float_to_decimal(-123.456f, &dec);
  ck_assert_int_eq(res, OK);

  // Тест 3: Число с дробной частью (0.1)
  res = s21_from_float_to_decimal(0.1f, &dec);
  ck_assert_int_eq(res, OK);

  // Тест 4: Число в пределах диапазона (1e-28)
  res = s21_from_float_to_decimal(1e-28f, &dec);
  ck_assert_int_eq(res, OK);

  // Тест 5: Число с экспонентой (1.23e5)
  res = s21_from_float_to_decimal(1.23e5f, &dec);
  ck_assert_int_eq(res, OK);

  // Тест 6: Число с экспонентой (1.23e-5)
  res = s21_from_float_to_decimal(1.23e-5f, &dec);
  ck_assert_int_eq(res, OK);

  // Тест 7: Слишком маленькое число (должно вызвать ошибку)
  res = s21_from_float_to_decimal(1e-30f, &dec);
  ck_assert_int_eq(res, CONVERT_ERROR);

  // Тест 8: Слишком большое число (должно вызвать ошибку)
  res = s21_from_float_to_decimal(1e30f, &dec);
  ck_assert_int_eq(res, CONVERT_ERROR);
}
END_TEST

START_TEST(test_s21_from_string_to_decimal) {
  s21_decimal result = {{0}};
  int int_val;

  s21_from_string_to_decimal("12345", &result);
  s21_from_decimal_to_int(result, &int_val);
  ck_assert_int_eq(int_val, 12345);

  float float_val;
  s21_from_string_to_decimal("-123.456", &result);
  s21_from_decimal_to_float(result, &float_val);
  ck_assert_float_eq_tol(float_val, -123.456f, 1e-6);
}
END_TEST

START_TEST(test_s21_from_string_to_big_decimal) {
  s21_big_decimal result;
  s21_from_string_to_big_decimal("123456789.12345", &result);

  ck_assert_int_eq(s21_getExt(result), 5);
  ck_assert_int_eq(s21_getSign(result), 0);
  ck_assert(result.bits[0] != 0);
}
END_TEST

// -------------------------------------------

Suite *create_convert_suite(void) {
  Suite *suite = suite_create("convert");

  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_int_to_dec = tcase_create("int to dec");
  TCase *tcase_float_to_dec = tcase_create("float to dec");
  TCase *tcase_dec_to_int = tcase_create("dec to int");
  TCase *tcase_dec_to_float = tcase_create("dec to float");
  TCase *tcase_skytemal = tcase_create("convert test by skytemal");

  tcase_add_test(tcase_int_to_dec, int_to_dec_null);
  tcase_add_test(tcase_int_to_dec, int_to_dec_plus);
  tcase_add_test(tcase_int_to_dec, int_to_dec_minus);

  tcase_add_test(tcase_float_to_dec, float_to_dec_max);
  tcase_add_test(tcase_float_to_dec, float_to_dec_min);
  tcase_add_test(tcase_float_to_dec, float_to_dec_toosmall);
  tcase_add_test(tcase_float_to_dec, float_to_dec_inf);
  tcase_add_test(tcase_float_to_dec, float_to_dec_nan);

  tcase_add_test(tcase_float_to_dec, float_to_dec_norm);
  tcase_add_test(tcase_float_to_dec, float_to_dec_32);
  tcase_add_test(tcase_float_to_dec, float_to_dec_64);
  tcase_add_test(tcase_float_to_dec, float_to_dec_less1m);
  tcase_add_test(tcase_float_to_dec, float_to_dec_less1);
  tcase_add_test(tcase_skytemal, test_s21_from_decimal_to_int);
  tcase_add_test(tcase_skytemal, test_s21_from_int_to_decimal);
  tcase_add_test(tcase_skytemal, test_s21_from_decimal_to_float);
  tcase_add_test(tcase_skytemal, test_s21_from_float_to_decimal);
  tcase_add_test(tcase_skytemal, test_s21_from_string_to_decimal);
  tcase_add_test(tcase_skytemal, test_s21_from_string_to_big_decimal);

  /*Добавление групп в тестовый набор.*/
  suite_add_tcase(suite, tcase_int_to_dec);
  suite_add_tcase(suite, tcase_float_to_dec);
  suite_add_tcase(suite, tcase_dec_to_int);
  suite_add_tcase(suite, tcase_dec_to_float);
  suite_add_tcase(suite, tcase_skytemal);

  return suite;
}