

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"
#include "s21_output.h"

// Преобразование из decimal в int
// src - исходное число decimal
// dst - указатель на число int
// возвращает OK или CONVERT_ERROR
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int return_value = OK;
  if (dst) {
    s21_big_decimal src_big;
    s21_initialBigDecimal(&src_big);
    s21_from_decimal_to_big_decimal(src, &src_big);
    return_value = s21_from_big_decimal_to_int(src_big, dst);
  } else
    return_value = CONVERT_ERROR;
  return return_value;
}

int s21_from_big_decimal_to_int(s21_big_decimal src, int *dst) {
  int return_value = OK;
  if (dst) {
    int neg = 1;
    if (s21_getSign(src) == 1) neg = -1;

    // целочисленная копия
    s21_big_decimal src_copy;
    s21_initialBigDecimal(&src_copy);

    // макс и мин инт
    s21_big_decimal max;
    s21_initialBigDecimal(&max);
    s21_big_decimal min;
    s21_initialBigDecimal(&min);

    s21_big_truncate(src, &src_copy);
    s21_from_int_to_big_decimal(2147483647, &max);
    s21_from_int_to_big_decimal(-2147483648, &min);

    if (s21_is_big_greater(src_copy, max) || s21_is_big_less(src_copy, min)) {
      return_value = CONVERT_ERROR;
    } else {
      int bit_num = src_copy.bits[0];
      *dst = bit_num * neg;
    }
  } else
    return_value = CONVERT_ERROR;
  return return_value;
}

// // Преобразование из decimal в float
// // src - исходное число decimal
// // dst - указатель на число float
// // возвращает OK или CONVERT_ERROR
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int return_value = OK;
  if (dst) {
    s21_big_decimal src_big;
    s21_initialBigDecimal(&src_big);
    s21_from_decimal_to_big_decimal(src, &src_big);
    return_value = s21_from_big_decimal_to_float(src_big, dst);
  } else
    return_value = CONVERT_ERROR;
  return return_value;
}

int s21_from_big_decimal_to_float(s21_big_decimal src, float *dst) {
  int return_value = OK;
  if (dst) {
    // получаем знак
    int neg = 1;
    if (s21_getSign(src) == 1) neg = -1;

    // получаем мантиссу
    double bit_num = 0;
    for (size_t i = 0; i < 96; i++) {
      if (s21_getBit(src, i) == 1) bit_num += pow(2, i);
    }

    // собираем
    bit_num *= neg / pow(10, (s21_getExt(src)));
    *dst = bit_num;
  } else
    return_value = CONVERT_ERROR;

  return return_value;
}

// Преобразование из int в decimal
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int return_value = OK;
  if (dst) {
    s21_initialDecimal(dst);
    s21_big_decimal dst_big;
    s21_initialBigDecimal(&dst_big);
    return_value = s21_from_int_to_big_decimal(src, &dst_big);
    s21_from_big_decimal_to_decimal(dst_big, dst);
  } else
    return_value = CONVERT_ERROR;
  return return_value;
}

// Преобразование из int в big_decimal
int s21_from_int_to_big_decimal(int src, s21_big_decimal *dst) {
  int return_value = OK;
  if (dst) {
    s21_initialBigDecimal(dst);
    return_value = OK;
    int usrc = src;
    if (src < 0) {
      usrc = src * -1;
      s21_setSign(dst);
    }
    dst->bits[0] = usrc;
  } else
    return_value = CONVERT_ERROR;

  return return_value;
}

// Преобразование из float в decimal
// src - исходное число float
// dst - указатель на число decimal
// возвращает OK или CONVERT_ERROR
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int result1;
  int result2;
  int result;
  s21_big_decimal dst_big = {{0}};
  result1 = s21_from_float_to_big_decimal(src, &dst_big);
  result2 = s21_from_big_decimal_to_decimal(dst_big, dst);
  if (result1 == OK)
    result = result2;
  else
    result = result1;
  return result;
}

// Преобразование из float в big_decimal
int s21_from_float_to_big_decimal(float src, s21_big_decimal *dst) {
  int return_value = OK;

  if (fabs(src) >= pow(2, 96) || isinf(src) || fabs(src) < pow(10, -28) ||
      isnan(src) || !dst || src == INFINITY || src == NAN) {
    return_value = CONVERT_ERROR;
  } else {
    // если число отрицательное, устанавливаем знак big_decimal
    // и делаем число положительным
    char float_str[32] = {0};
    char mantissa_str[32] = {0};
    // переводим float в str
    sprintf(float_str, "%+e", src);
    // берем только часть строки до e
    strncpy(mantissa_str, float_str, 9);

    s21_from_string_to_big_decimal(mantissa_str, dst);

    char *pExtStr = strchr(float_str, 'e') + 1;

    int ext = 6 - atoi(pExtStr);

    while (ext < 0) {
      s21_mulMantissa10(dst);
      ext++;
    }
    s21_setExt(dst, ext);
  }

  return return_value;
}

int s21_from_string_to_big_decimal(char *strNumber, s21_big_decimal *dst) {
  s21_initialBigDecimal(dst);

  for (int i = 0; i < (int)strlen(strNumber); i++) {
    if (strNumber[i] >= '0' && strNumber[i] <= '9') {
      s21_mulMantissa10(dst);
      s21_big_decimal n = {0};
      n.bits[0] = strNumber[i] - 48;
      s21_addMantissa(*dst, n, dst);
    };
  }

  char *p = strchr(strNumber, '.');
  if (p != NULL) {
    unsigned char e = strlen(strNumber) - (p - strNumber) - 1;
    s21_setExt(dst, e);
  }

  if (strNumber[0] == '-') s21_setSign(dst);
  return OK;
}

int s21_from_string_to_decimal(char *strNumber, s21_decimal *dst) {
  s21_big_decimal dst_big = {0};
  s21_from_decimal_to_big_decimal(*dst, &dst_big);
  s21_from_string_to_big_decimal(strNumber, &dst_big);
  s21_from_big_decimal_to_decimal(dst_big, dst);
  return OK;
}
