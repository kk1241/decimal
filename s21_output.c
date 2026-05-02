#include "s21_output.h"

#include <stdio.h>
#include <string.h>

// функция s21_strreverse переворачивает строку str
void s21_strreverse(char *str) {
  int size = strlen(str);
  for (int i = 0; i < size / 2; i++) {
    char c1 = *(str + i);
    char c2 = *(str + size - 1 - i);
    *(str + i) = c2;
    *(str + size - 1 - i) = c1;
  }
}

// функция printDecimalBin выводит все элементы числа в двоичном представлении
// плюс значение знака и степени в десятичном представлении
void s21_printDecimalBin(s21_decimal value) {
  s21_big_decimal big_value = {};
  s21_from_decimal_to_big_decimal(value, &big_value);

  printf("Sign=%u, Ext=%u\n", s21_getSign(big_value), s21_getExt(big_value));
  for (int i = 127; i >= 0; i--) {
    printf("%d", s21_getBit(big_value, i));
    if (i % 8 == 0) printf(" ");
    if (i % 32 == 0) printf("| ");
  }

  printf("\n");
}

// функция выводит число value в десятичное системе
// если calcResult отличен от 0, то выводим сообщение об ошибке
void s21_printDecimalDec(s21_decimal value, int calcResult) {
  // if (calcResult != 0) s21_printCalcResult(calcResult);

  s21_big_decimal big_value = {0};
  s21_from_decimal_to_big_decimal(value, &big_value);
  s21_printBigDecimalDec(big_value);
  printf("error id = %d\n", calcResult);
}

// максимальное big_decimal число для вывода 2^191-1
// старший разряд не используется
void s21_printBigDecimalDec(s21_big_decimal big_value) {
  char strNumber[192] = {0};
  char mantissa[192] = {0};
  unsigned char ext = s21_getExt(big_value);
  unsigned char sign = s21_getSign(big_value);
  BIG_TEN;
  s21_big_decimal quotient = {0};
  s21_big_decimal remainder = {0};

  s21_resetBit(&big_value, 191);
  int index = 0;

  do {
    s21_divMantissa(big_value, bigTen, &quotient, &remainder);

    strNumber[index++] = remainder.bits[0] + 48;
    s21_copyMantissa(quotient, &big_value);

  } while (!s21_is_big_zero(quotient));

  strcpy(mantissa, strNumber);
  s21_strreverse(mantissa);

  printf("Мантисса: %s, Степень: %u, Знак: %u", mantissa, ext, sign);

  if (ext >= strlen(strNumber)) {
    int cnt = ext - strlen(strNumber);
    for (int i = 0; i < cnt; i++) {
      strNumber[index++] = '0';
    }
    strNumber[index++] = '.';
    strNumber[index++] = '0';
  } else if (ext > 0) {
    for (int i = index; i > ext; i--) {
      strNumber[i] = strNumber[i - 1];
    }

    strNumber[ext] = '.';
    index++;
  }

  if (sign == 0)
    strNumber[index] = '+';
  else
    strNumber[index] = '-';

  s21_strreverse(strNumber);

  printf(", Значение: %s\n", strNumber);
}
