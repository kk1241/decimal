#include "s21_extra.h"

#include <stdio.h>

#include "s21_output.h"

char find_op(char s) {
  char op;
  switch (s) {
    case 'a':
      op = '+';
      break;
    case 's':
      op = '-';
      break;
    case 'm':
      op = '*';
      break;
    case 'd':
      op = '/';
      break;

  }
  return op;
}

void test_output(s21_decimal res, s21_decimal exp, const char *test_name,
                 char *a, char *b) {
  char op = find_op(test_name[0]);

  printf("\n");
  printf("\033[33m%s:\033[39m\n", test_name);
  printf("\033[39m%s %c %s\033[39m\n", a, op, b);
  printf("\033[32mres:\033[39m\n");
  s21_printDecimalBin(res);
  s21_printDecimalDec(res, 0);
  printf("\033[32mexp:\033[39m\n");
  s21_printDecimalBin(exp);
  s21_printDecimalDec(exp, 0);
  printf("\n");
}
