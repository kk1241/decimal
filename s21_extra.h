#include "s21_decimal.h"

#ifndef EXTRA
#define EXTRA

void test_output(s21_decimal res, s21_decimal exp, const char *test_name,
                 char *a, char *b);

char find_op(char s);

#endif