#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"
#include "s21_extra.h"
#include "s21_output.h"

START_TEST(add_cycle) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  // s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "5";
  char *b = "2";
  char name[11] = "add_cycle";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("7", &exp);

  for (size_t i = 1; i <= 10; i++) {
    // char* num1_str = {0};
    // s21_from_decimal_to_string(num1, num1_str);

    int exp_int = 5 + (int)i * 2;
    char exp_str[96];
    sprintf(exp_str, "%d", exp_int);
    s21_from_string_to_decimal(exp_str, &exp);

    char b2[96];
    int b2_int = (int)i * 2;
    sprintf(b2, "%d", b2_int);

    s21_add(num1, num2, &num1);

    char in[20];
    char name_i[96] = {0};
    sprintf(in, ", i = %d (1-10)", (int)i);
    strcat(name_i, name);
    strcat(name_i, in);
    test_output(num1, exp, name_i, a, b2);

    ck_assert_msg((s21_is_equal(num1, exp) == 1),
                  "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
  }
}
END_TEST

START_TEST(add_inf_plus) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "79228162514264337593543950330";
  char *b = "1000000";
  char *name = "add_inf_plus";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);

  int result = s21_add(num1, num2, &res);
  if (result == 0)
    test_output(res, exp, name, a, b);
  else if (result == 1) {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOHIGH\n");
  } else {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOSMALL\n");
  }

  ck_assert_msg((result == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(add_inf_minus) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-79228162514264337593543950330";
  char *b = "-1000000";
  char *name = "add_inf_minus";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);

  int result = s21_add(num1, num2, &res);
  if (result == 0)
    test_output(res, exp, name, a, b);
  else if (result == 2) {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOSMALL\n");
  } else {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOHIGH\n");
  }

  ck_assert_msg((result == 2),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(add_plus_plus_num1) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "5";
  char *b = "2";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("7", &exp);

  s21_add(num1, num2, &res);

  test_output(res, exp, "add_plus_plus_num1", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}

START_TEST(add_plus_plus_num2) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "50206";
  char *b = "1231502";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("1281708", &exp);

  s21_add(num1, num2, &res);

  test_output(res, exp, "add_plus_plus_num2", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(add_plus_plus_eq) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "105";
  char *b = "105";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("210", &exp);

  s21_add(num1, num2, &res);

  test_output(res, exp, "add_plus_plus_eq", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

// +a + -b = -c
START_TEST(add_plus_minus_num2) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "51555615";
  char *b = "-200000000";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("-148444385", &exp);

  s21_add(num1, num2, &res);

  test_output(res, exp, "add_plus_minus_num2", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(add_plus_minus_num1) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "51555615";
  char *b = "-200";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("51555415", &exp);

  s21_add(num1, num2, &res);

  test_output(res, exp, "add_plus_minus_num1", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(add_plus_minus_eq) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "200";
  char *b = "-200";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("0", &exp);

  s21_add(num1, num2, &res);

  test_output(res, exp, "add_plus_minus_eq", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

// -a + +b = c
START_TEST(add_minus_plus_num2) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-55615";
  char *b = "1651100";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("1595485", &exp);

  s21_add(num1, num2, &res);

  test_output(res, exp, "add_minus_plus_num2", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(add_minus_plus_num1) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-5296560015";
  char *b = "165";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("-5296559850", &exp);

  s21_add(num1, num2, &res);

  test_output(res, exp, "add_minus_plus_num1", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(add_minus_plus_eq) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-9852";
  char *b = "9852";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("0", &exp);

  s21_add(num1, num2, &res);

  test_output(res, exp, "add_minus_plus_eq", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

// -a + -b = -c
START_TEST(add_minus_minus_num1) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-79228162514264337593543900000";
  char *b = "-50334";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("-79228162514264337593543950334", &exp);

  s21_add(num1, num2, &res);

  test_output(res, exp, "add_minus_minus_num1", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(add_minus_minus_num2) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-79200000";
  char *b = "-502156198334";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("-502235398334", &exp);

  s21_add(num1, num2, &res);

  test_output(res, exp, "add_minus_minus_num2", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(add_minus_minus_eq) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-79200000";
  char *b = "-79200000";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("-158400000", &exp);

  s21_add(num1, num2, &res);

  test_output(res, exp, "add_minus_minus_eq", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(add_mantissa_overflow) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "79228162514264337593543950334";
  char *b = "0.6";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("79228162514264337593543950335", &exp);

  s21_add(num1, num2, &res);

  test_output(res, exp, "add_mantissa_overflow", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

// ---------------------------------------------------------------------------------------------------------------------------------

START_TEST(sub_cycle) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  // s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "5";
  char *b = "2";
  char *name = "sub_cycle";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("3", &exp);

  printf("\n\033[33m%s:\033[39m\n", name);
  for (size_t i = 1; i <= 10; i++) {
    int exp_int = 5 - (int)i * 2;
    char exp_str[96];
    sprintf(exp_str, "%d", exp_int);
    s21_from_string_to_decimal(exp_str, &exp);

    char b2[96];
    int b2_int = (int)i * 2;
    sprintf(b2, "%d", b2_int);

    s21_sub(num1, num2, &num1);

    char in[20];
    char name_i[96] = {0};
    sprintf(in, ", i = %d (1-10)", (int)i);
    strcat(name_i, name);
    strcat(name_i, in);
    test_output(num1, exp, name_i, a, b2);

    ck_assert_msg((s21_is_equal(num1, exp) == 1),
                  "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
  }
}
END_TEST

START_TEST(sub_plus_plus_num1) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "5";
  char *b = "2";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("3", &exp);

  s21_sub(num1, num2, &res);

  test_output(res, exp, "sub_plus_plus_num1", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(sub_plus_plus_num2) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "5";
  char *b = "200";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("-195", &exp);

  s21_sub(num1, num2, &res);

  test_output(res, exp, "sub_plus_plus_num2", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(sub_plus_plus_eq) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "2525914985";
  char *b = "2525914985";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("0", &exp);

  s21_sub(num1, num2, &res);

  test_output(res, exp, "sub_plus_plus_eq", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(sub_plus_minus_num1) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "5";
  char *b = "-152";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("157", &exp);

  s21_sub(num1, num2, &res);

  test_output(res, exp, "sub_plus_minus_num1", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(sub_plus_minus_num2) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "841166855";
  char *b = "-200";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("841167055", &exp);

  s21_sub(num1, num2, &res);

  test_output(res, exp, "sub_plus_minus_num2", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(sub_plus_minus_eq) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "2525914985";
  char *b = "-2525914985";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("5051829970", &exp);

  s21_sub(num1, num2, &res);

  test_output(res, exp, "sub_plus_minus_eq", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(sub_minus_plus_num2) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-98";
  char *b = "1152";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("-1250", &exp);

  s21_sub(num1, num2, &res);

  test_output(res, exp, "sub_minus_plus_num2", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(sub_minus_plus_num1) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-841155";
  char *b = "200";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("-841355", &exp);

  s21_sub(num1, num2, &res);

  test_output(res, exp, "sub_minus_plus_num1", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(sub_minus_plus_eq) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-635";
  char *b = "635";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("-1270", &exp);

  s21_sub(num1, num2, &res);

  test_output(res, exp, "sub_minus_plus_eq", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(sub_minus_minus_num2) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-908";
  char *b = "-8884521152";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("8884520244", &exp);

  s21_sub(num1, num2, &res);

  test_output(res, exp, "sub_minus_minus_num2", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(sub_minus_minus_num1) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-841151541515";
  char *b = "-28441200";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("-841123100315", &exp);

  s21_sub(num1, num2, &res);

  test_output(res, exp, "sub_minus_minus_num1", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(sub_minus_minus_eq) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-63261695885";
  char *b = "-63261695885";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("0", &exp);

  s21_sub(num1, num2, &res);

  test_output(res, exp, "sub_minus_minus_eq", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(sub_inf_minus) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-79228162514264337593543950335";
  char *b = "9999999999999999";
  char *name = "sub_inf_minus";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);

  int result = s21_sub(num1, num2, &res);
  if (result == 0)
    test_output(res, exp, name, a, b);
  else if (result == 2) {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOSMALL\n");
  } else {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOHIGH\n");
  }

  ck_assert_msg((result == 2),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(sub_inf_plus) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "536695";
  char *b = "-79228162514264337593543950335";
  char *name = "sub_inf_plus";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);

  int result = s21_sub(num1, num2, &res);
  if (result == 0)
    test_output(res, exp, name, a, b);
  else if (result == 1) {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOHIGH\n");
  } else {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOSMALL\n");
  }

  ck_assert_msg((result == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(sub_mantissa_overflow) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "79228162514264337593543950335";
  char *b = "0.6";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("79228162514264337593543950334", &exp);

  s21_sub(num1, num2, &res);

  test_output(res, exp, "sub_mantissa_overflow", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

// ---------------------------------------------------------------------------------------------------------------------------------

START_TEST(mul_inf_plus) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "536695";
  char *b = "79228162514264337593543950335";
  char *name = "mul_inf_plus";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);

  int result = s21_mul(num1, num2, &res);
  if (result == 0)
    test_output(res, exp, name, a, b);
  else if (result == 1) {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOHIGH\n");
  } else {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOSMALL\n");
  }

  ck_assert_msg((result == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(mul_inf_minus1) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "5301056695";
  char *b = "-79214264337593543950335";
  char *name = "mul_inf_minus1";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);

  int result = s21_mul(num1, num2, &res);
  if (result == 0)
    test_output(res, exp, name, a, b);
  else if (result == 2) {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOSMALL\n");
  } else {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOHIGH\n");
  }

  ck_assert_msg((result == 2),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(mul_inf_minus2) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-5301056695";
  char *b = "79214264337593543950335";
  char *name = "mul_inf_minus2";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);

  int result = s21_mul(num1, num2, &res);
  if (result == 0)
    test_output(res, exp, name, a, b);
  else if (result == 2) {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOSMALL\n");
  } else {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOHIGH\n");
  }

  ck_assert_msg((result == 2),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(mul_zero) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "5";
  char *b = "0";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);

  s21_mul(num1, num2, &res);

  test_output(res, exp, "mul_zero", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(mul_plus_plus) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "5";
  char *b = "8";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("40", &exp);

  s21_mul(num1, num2, &res);

  test_output(res, exp, "mul_plus_plus", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(mul_plus_minus) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "10";
  char *b = "-5.18";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("-51.8", &exp);

  s21_mul(num1, num2, &res);

  test_output(res, exp, "mul_plus_minus", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(mul_minus_plus) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-0.0006364485";
  char *b = "51264854984";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("-32627440.057284324", &exp);

  s21_mul(num1, num2, &res);

  test_output(res, exp, "mul_minus_plus", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(mul_minus_minus) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-180";
  char *b = "-695.128";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("125123.04", &exp);

  s21_mul(num1, num2, &res);

  test_output(res, exp, "mul_minus_minus", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST
// ---------------------------------------------------------------------------------------------------------------------------------

START_TEST(div_by_zero) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "79228162517593543950335";
  char *b = "0";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);

  test_output(res, exp, "div_by_zero", a, b);

  ck_assert_msg((s21_div(num1, num2, &res) == DIVIDE0),
                "\n\n\033[91mFAIL\033[39m\nexp: DIVIDE0\n");
}
END_TEST

START_TEST(div_zero) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "0";
  char *b = "79228162517593543950335";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);

  s21_div(num1, num2, &res);

  test_output(res, exp, "div_zero", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nexp: 0\n");
}
END_TEST

START_TEST(div_plus_plus) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "50";
  char *b = "8";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("6.25", &exp);

  s21_div(num1, num2, &res);

  test_output(res, exp, "div_plus_plus", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(div_plus_minus) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "5.5";
  char *b = "-110";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("-0.05", &exp);

  s21_div(num1, num2, &res);

  test_output(res, exp, "div_plus_minus", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(div_minus_plus) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-6669";
  char *b = "3";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("-2223", &exp);

  s21_div(num1, num2, &res);

  test_output(res, exp, "div_minus_plus", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(div_minus_minus) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "-180";
  char *b = "-160000";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("0.001125", &exp);

  s21_div(num1, num2, &res);

  test_output(res, exp, "div_minus_minus", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(div_period) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "1";
  char *b = "3";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);
  s21_from_string_to_decimal("0.3333333333333333333333333333", &exp);

  s21_div(num1, num2, &res);

  test_output(res, exp, "div_minus_minus", a, b);

  ck_assert_msg((s21_is_equal(res, exp) == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(div_inf_plus) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "79228162514264337593543950335";
  char *b = "0.5";
  char *name = "div_inf_plus";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);

  int result = s21_div(num1, num2, &res);
  if (result == 0)
    test_output(res, exp, name, a, b);
  else if (result == 1) {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOHIGH\n");
  } else {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOSMALL\n");
  }

  ck_assert_msg((result == 1),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(div_inf_minus1) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "79228162514264337593543950335";

  char *b = "-0.285";
  char *name = "div_inf_minus1";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);

  int result = s21_div(num1, num2, &res);

  printf("res = %d\n", result);
  if (result == 0)
    test_output(res, exp, name, a, b);
  else if (result == 2) {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOSMALL\n");
  } else {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOHIGH\n");
  }

  ck_assert_msg((result == 2),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

START_TEST(div_inf_minus2) {
  s21_decimal num1 = {0};
  s21_decimal num2 = {0};
  s21_decimal res = {0};
  s21_decimal exp = {0};

  char *a = "79228162514264337593543950335";
  char *b = "-0.75";
  char *name = "div_inf_minus2";

  s21_from_string_to_decimal(a, &num1);
  s21_from_string_to_decimal(b, &num2);

  int result = s21_div(num1, num2, &res);
  if (result == 0)
    test_output(res, exp, name, a, b);
  else if (result == 2) {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOSMALL\n");
  } else {
    printf("\n\033[33m%s:\033[39m\n", name);
    printf("TOOHIGH\n");
  }

  ck_assert_msg((result == 2),
                "\n\n\033[91mFAIL\033[39m\nres does not match exp value\n");
}
END_TEST

// ---------------------------------------------------------------------------------------------------------------------------------

Suite *create_arithmetic_suite(void) {
  Suite *suite = suite_create("arithmetic");

  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_add = tcase_create("add");
  TCase *tcase_sub = tcase_create("sub");
  TCase *tcase_mul = tcase_create("mul");
  TCase *tcase_div = tcase_create("div");

  /*добавляем тесты в группу, некоторые тесты вызываются в цикле от -10 до 10 -
  зацикленный тест нужен, чтобы выводилась не только первая ошибка */
  tcase_add_test(tcase_add, add_plus_plus_num1);
  tcase_add_test(tcase_add, add_plus_plus_num2);
  tcase_add_test(tcase_add, add_plus_plus_eq);
  tcase_add_test(tcase_add, add_plus_minus_num1);
  tcase_add_test(tcase_add, add_plus_minus_num2);
  tcase_add_test(tcase_add, add_plus_minus_eq);
  tcase_add_test(tcase_add, add_minus_plus_num1);
  tcase_add_test(tcase_add, add_minus_plus_num2);
  tcase_add_test(tcase_add, add_minus_plus_eq);
  tcase_add_test(tcase_add, add_minus_minus_num1);
  tcase_add_test(tcase_add, add_minus_minus_num2);
  tcase_add_test(tcase_add, add_minus_minus_eq);
  tcase_add_test(tcase_add, add_inf_plus);
  tcase_add_test(tcase_add, add_inf_minus);
  tcase_add_test(tcase_add, add_cycle);
  tcase_add_test(tcase_add, add_mantissa_overflow);

  tcase_add_test(tcase_sub, sub_mantissa_overflow);
  tcase_add_test(tcase_sub, sub_plus_plus_num1);
  tcase_add_test(tcase_sub, sub_plus_plus_num2);
  tcase_add_test(tcase_sub, sub_plus_plus_eq);
  tcase_add_test(tcase_sub, sub_plus_minus_num1);
  tcase_add_test(tcase_sub, sub_plus_minus_num2);
  tcase_add_test(tcase_sub, sub_plus_minus_eq);
  tcase_add_test(tcase_sub, sub_minus_plus_num1);
  tcase_add_test(tcase_sub, sub_minus_plus_num2);
  tcase_add_test(tcase_sub, sub_minus_plus_eq);
  tcase_add_test(tcase_sub, sub_minus_minus_num1);
  tcase_add_test(tcase_sub, sub_minus_minus_num2);
  tcase_add_test(tcase_sub, sub_minus_minus_eq);
  tcase_add_test(tcase_sub, sub_inf_plus);
  tcase_add_test(tcase_sub, sub_inf_minus);
  tcase_add_test(tcase_add, sub_cycle);

  tcase_add_test(tcase_mul, mul_zero);
  tcase_add_test(tcase_mul, mul_plus_plus);
  tcase_add_test(tcase_mul, mul_plus_minus);
  tcase_add_test(tcase_mul, mul_minus_plus);
  tcase_add_test(tcase_mul, mul_minus_minus);
  tcase_add_test(tcase_mul, mul_inf_plus);
  tcase_add_test(tcase_mul, mul_inf_minus1);
  tcase_add_test(tcase_mul, mul_inf_minus2);

  tcase_add_test(tcase_div, div_by_zero);
  tcase_add_test(tcase_div, div_zero);
  tcase_add_test(tcase_div, div_plus_plus);
  tcase_add_test(tcase_div, div_plus_minus);
  tcase_add_test(tcase_div, div_minus_plus);
  tcase_add_test(tcase_div, div_minus_minus);
  tcase_add_test(tcase_div, div_period);
  tcase_add_test(tcase_div, div_inf_plus);
  tcase_add_test(tcase_div, div_inf_minus1);
  tcase_add_test(tcase_div, div_inf_minus2);

  /*Добавление групп в тестовый набор.*/
  suite_add_tcase(suite, tcase_add);
  suite_add_tcase(suite, tcase_sub);
  suite_add_tcase(suite, tcase_mul);
  suite_add_tcase(suite, tcase_div);

  return suite;
}