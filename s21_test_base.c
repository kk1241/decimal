#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"
#include "s21_extra.h"
#include "s21_output.h"

START_TEST(init_dec) {
  s21_decimal res = {0};
  s21_decimal exp = {0};

  s21_initialDecimal(&res);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

// 79228162514264337593543950335
START_TEST(is_m_full) {
  s21_big_decimal a = {0};
  s21_from_string_to_big_decimal("792281625142643375935439503350", &a);

  int r = s21_isMantissaFull(a);

  ck_assert_msg(((r != 0)), "\n\n\033[91mFAIL\033[39m\nexp: not 0\n");
}
END_TEST

START_TEST(get_ext) {
  s21_big_decimal a = {0};
  s21_from_string_to_big_decimal("0.05", &a);
  //   printf("%c\n", )

  ck_assert_msg((s21_getExt(a) == 2),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(set_ext) {
  s21_big_decimal a = {0};
  s21_from_string_to_big_decimal("0.05", &a);
  //   printf("%c\n", )

  s21_setExt(&a, 5);

  ck_assert_msg((s21_getExt(a) == 5),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

// ---------------------------------------------------------------------------------------------------------------------------------

START_TEST(get_sign_1) {
  s21_big_decimal res = {0};

  s21_from_string_to_big_decimal("-15800", &res);

  ck_assert_msg((s21_getSign(res) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(get_sign_0) {
  s21_big_decimal res = {0};

  s21_from_string_to_big_decimal("862", &res);

  ck_assert_msg((s21_getSign(res) == 0),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(set_sign) {
  s21_big_decimal res = {0};
  s21_big_decimal exp = {0};

  s21_from_string_to_big_decimal("79228162514264337593543950334", &res);
  s21_from_string_to_big_decimal("-79228162514264337593543950334", &exp);

  s21_setSign(&res);

  ck_assert_msg((s21_is_big_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(reset_sign) {
  s21_big_decimal res = {0};
  s21_big_decimal exp = {0};

  s21_from_string_to_big_decimal("-7922816251450334", &res);
  s21_from_string_to_big_decimal("7922816251450334", &exp);

  s21_resetSign(&res);

  ck_assert_msg((s21_is_big_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

START_TEST(not_0) {
  printf("\033[33mnot_0:\033[39m\n%c\n", s21_NOT('0'));
  ck_assert_msg((s21_NOT(0) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}

START_TEST(not_1) {
  printf("\n\033[33mnot_1:\033[39m\n%c\n", s21_NOT('1'));
  ck_assert_msg((s21_NOT(1) == 0),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}

// ---------------------------------------------------------------------------------------------------------------------------------

START_TEST(write_bit_0) {
  s21_big_decimal res = {0};
  s21_big_decimal exp = {0};

  s21_from_string_to_big_decimal("17", &res);
  s21_from_string_to_big_decimal("16", &exp);

  s21_writeBit(&res, 0, 0);

  ck_assert_msg((s21_is_big_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(write_bit_1) {
  s21_big_decimal res = {0};
  s21_big_decimal exp = {0};

  s21_from_string_to_big_decimal("8", &exp);

  s21_writeBit(&res, 3, 1);

  ck_assert_msg((s21_is_big_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(get_bit_1) {
  s21_big_decimal res = {0};

  s21_from_string_to_big_decimal("-15800", &res);

  ck_assert_msg((s21_getBit(res, 8) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(get_bit_0) {
  s21_big_decimal res = {0};

  s21_from_string_to_big_decimal("862", &res);

  ck_assert_msg((s21_getBit(res, 20) == 0),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(reset_bit) {
  s21_big_decimal res = {0};
  s21_big_decimal exp = {0};

  s21_from_string_to_big_decimal("7922816251450335", &res);
  s21_from_string_to_big_decimal("7922816251450334", &exp);

  s21_resetBit(&res, 0);

  ck_assert_msg((s21_is_big_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(set_bit) {
  s21_big_decimal res = {0};
  s21_big_decimal exp = {0};

  s21_from_string_to_big_decimal("8", &exp);

  s21_setBit(&res, 3);

  ck_assert_msg((s21_is_big_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

// ---------------------------------------------------------------------------------------------------------------------------------

START_TEST(add_m_plus_plus_num1) {
  s21_big_decimal num1 = {0};
  s21_big_decimal num2 = {0};
  s21_big_decimal res = {0};
  s21_big_decimal exp = {0};

  s21_from_string_to_big_decimal("5", &num1);
  s21_from_string_to_big_decimal("2", &num2);
  s21_from_string_to_big_decimal("7", &exp);

  s21_addMantissa(num1, num2, &res);

  ck_assert_msg((s21_is_big_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}

START_TEST(add_m_plus_plus_num2) {
  s21_big_decimal num1 = {0};
  s21_big_decimal num2 = {0};
  s21_big_decimal res = {0};
  s21_big_decimal exp = {0};

  s21_from_string_to_big_decimal("50206", &num1);
  s21_from_string_to_big_decimal("1231502", &num2);
  s21_from_string_to_big_decimal("1281708", &exp);

  s21_addMantissa(num1, num2, &res);

  ck_assert_msg((s21_is_big_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(add_m_plus_plus_eq) {
  s21_big_decimal num1 = {0};
  s21_big_decimal num2 = {0};
  s21_big_decimal res = {0};
  s21_big_decimal exp = {0};

  s21_from_string_to_big_decimal("105", &num1);
  s21_from_string_to_big_decimal("105", &num2);
  s21_from_string_to_big_decimal("210", &exp);

  s21_addMantissa(num1, num2, &res);

  ck_assert_msg((s21_is_big_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

// ---------------------------------------------------------------------------------------------------------------------------------

START_TEST(sub_m_plus_plus_num1) {
  s21_big_decimal num1 = {0};
  s21_big_decimal num2 = {0};
  s21_big_decimal res = {0};
  s21_big_decimal exp = {0};

  s21_from_string_to_big_decimal("5", &num1);
  s21_from_string_to_big_decimal("2", &num2);
  s21_from_string_to_big_decimal("3", &exp);

  s21_subMantissa(num1, num2, &res);

  ck_assert_msg((s21_is_big_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(sub_m_plus_plus_num2) {
  s21_big_decimal num1 = {0};
  s21_big_decimal num2 = {0};
  s21_big_decimal res = {0};
  s21_big_decimal exp = {0};

  s21_from_string_to_big_decimal("500", &num1);
  s21_from_string_to_big_decimal("200", &num2);
  s21_from_string_to_big_decimal("300", &exp);

  s21_subMantissa(num1, num2, &res);

  ck_assert_msg((s21_is_big_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(sub_m_plus_plus_eq) {
  s21_big_decimal num1 = {0};
  s21_big_decimal num2 = {0};
  s21_big_decimal res = {0};
  s21_big_decimal exp = {0};

  s21_from_string_to_big_decimal("2525914985", &num1);
  s21_from_string_to_big_decimal("2525914985", &num2);
  s21_from_string_to_big_decimal("0", &exp);

  s21_subMantissa(num1, num2, &res);

  ck_assert_msg((s21_is_big_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

// ---------------------------------------------------------------------------------------------------------------------------------

START_TEST(mul_m_zero) {
  s21_big_decimal num1 = {0};
  s21_big_decimal num2 = {0};
  s21_big_decimal res = {0};
  s21_big_decimal exp = {0};

  s21_from_string_to_big_decimal("5", &num1);

  s21_mulMantissa(num1, num2, &res);

  ck_assert_msg((s21_is_big_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(mul_m_plus_plus) {
  s21_big_decimal num1 = {0};
  s21_big_decimal num2 = {0};
  s21_big_decimal res = {0};
  s21_big_decimal exp = {0};

  s21_from_string_to_big_decimal("5", &num1);
  s21_from_string_to_big_decimal("8", &num1);
  s21_from_string_to_big_decimal("40", &num1);

  s21_mulMantissa(num1, num2, &res);

  ck_assert_msg((s21_is_big_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

// ---------------------------------------------------------------------------------------------------------------------------------

START_TEST(div_m_plus_plus) {
  s21_big_decimal num1 = {0};
  s21_big_decimal num2 = {0};
  s21_big_decimal res_q = {0};
  s21_big_decimal exp_q = {0};
  s21_big_decimal res_r = {0};
  s21_big_decimal exp_r = {0};

  s21_from_string_to_big_decimal("50", &num1);
  s21_from_string_to_big_decimal("8", &num2);
  s21_from_string_to_big_decimal("6", &exp_r);
  s21_from_string_to_big_decimal("2", &exp_q);

  s21_divMantissa(num1, num2, &res_r, &res_q);

  ck_assert_msg((s21_is_big_equal(res_r, exp_r) == 1 &&
                 s21_is_big_equal(res_q, exp_q) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

Suite *create_base_suite(void) {
  Suite *suite = suite_create("base");

  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_base = tcase_create("base");

  tcase_add_test(tcase_base, init_dec);
  tcase_add_test(tcase_base, is_m_full);
  tcase_add_test(tcase_base, get_ext);
  tcase_add_test(tcase_base, set_ext);
  tcase_add_test(tcase_base, not_0);
  tcase_add_test(tcase_base, not_1);

  tcase_add_test(tcase_base, get_sign_0);
  tcase_add_test(tcase_base, get_sign_1);
  tcase_add_test(tcase_base, set_sign);
  tcase_add_test(tcase_base, reset_sign);

  tcase_add_test(tcase_base, reset_bit);
  tcase_add_test(tcase_base, set_bit);
  tcase_add_test(tcase_base, get_bit_0);
  tcase_add_test(tcase_base, get_bit_1);
  tcase_add_test(tcase_base, write_bit_0);
  tcase_add_test(tcase_base, write_bit_1);

  TCase *tcase_add_m = tcase_create("add");
  TCase *tcase_sub_m = tcase_create("sub");
  TCase *tcase_mul_m = tcase_create("mul");
  TCase *tcase_div_m = tcase_create("div");

  /*добавляем тесты в группу, некоторые тесты вызываются в цикле от -10 до 10 -
  зацикленный тест нужен, чтобы выводилась не только первая ошибка */

  tcase_add_test(tcase_add_m, add_m_plus_plus_num1);
  tcase_add_test(tcase_add_m, add_m_plus_plus_num2);
  tcase_add_test(tcase_add_m, add_m_plus_plus_eq);
  tcase_add_test(tcase_sub_m, sub_m_plus_plus_num1);
  tcase_add_test(tcase_sub_m, sub_m_plus_plus_num2);
  tcase_add_test(tcase_sub_m, sub_m_plus_plus_eq);

  tcase_add_test(tcase_mul_m, mul_m_zero);
  tcase_add_test(tcase_mul_m, mul_m_plus_plus);

  tcase_add_test(tcase_div_m, div_m_plus_plus);

  /*Добавление групп в тестовый набор.*/
  suite_add_tcase(suite, tcase_base);
  suite_add_tcase(suite, tcase_mul_m);
  suite_add_tcase(suite, tcase_add_m);
  suite_add_tcase(suite, tcase_sub_m);
  suite_add_tcase(suite, tcase_div_m);

  return suite;
}