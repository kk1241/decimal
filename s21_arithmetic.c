#include "s21_decimal.h"

// cложение чисел decimal
// value_1 - первое число decimal
// value_2 - второе число decimal
// result - указатель на число decimal (результат сложения)
// возвращает OK, TOOHIGH, TOOSMALL
int s21_big_add(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result) {
  s21_big_decimal_norm(&big_value_1, &big_value_2);
  unsigned char ext = s21_getExt(big_value_1);
  unsigned char signValue_1 = s21_getSign(big_value_1);
  unsigned char signValue_2 = s21_getSign(big_value_2);

  // если знаки чисел одинаковые (т.е оба отрицательные или оба положительные)
  // производим побитовое сложение
  if (signValue_1 == signValue_2) {
    // (+A) + (+B) = + (A + B)
    // или (-A) + (-B) = - (A + B)
    s21_addMantissa(big_value_1, big_value_2, big_result);
    // записывает в бит знака значение знака числа 1
    s21_writeBit(big_result, SIGN_INDEX, signValue_1);
    s21_setExt(big_result, ext);

  } else if (signValue_1 == 0 && signValue_2 == 1) {
    // (+A) + (-B) = (+A) - (+B)
    s21_big_decimal nBigValue_2 = {0};
    s21_big_negate(big_value_2, &nBigValue_2);
    s21_big_sub(big_value_1, nBigValue_2, big_result);
  } else if (signValue_1 == 1 && signValue_2 == 0) {
    // (-A) + (+B) = (+B) - (+A)
    s21_big_decimal nBigValue_1 = {0};
    s21_big_negate(big_value_1, &nBigValue_1);
    s21_big_sub(big_value_2, nBigValue_1, big_result);
  }
  return OK;
}

// вычитание чисел big_decimal

int s21_big_sub(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result) {
  s21_big_decimal_norm(&big_value_1, &big_value_2);
  unsigned char ext = s21_getExt((big_value_1));

  unsigned char signValue_1 = s21_getSign(big_value_1);
  unsigned char signValue_2 = s21_getSign(big_value_2);

  if (signValue_1 == 0 && signValue_2 == 0) {
    // (+A) - (+B)
    // если A < B, тогда результат равен - (B - A)
    // если A > B, тогда результат равен A - B
    // иначе 0
    if (s21_is_big_less(big_value_1, big_value_2)) {
      s21_big_sub(big_value_2, big_value_1, big_result);
      s21_big_negate(*big_result, big_result);
    } else if (s21_is_big_greater(big_value_1, big_value_2)) {
      s21_subMantissa(big_value_1, big_value_2, big_result);
      s21_setExt(big_result, ext);
    };
  } else if (signValue_1 == 0 && signValue_2 == 1) {
    // (+A) - (-B) = (+A) + (+B)
    s21_big_decimal nBigValue_2 = {0};
    s21_big_negate(big_value_2, &nBigValue_2);
    s21_big_add(big_value_1, nBigValue_2, big_result);
  } else if (signValue_1 == 1 && signValue_2 == 0) {
    // (-A) - (+B) = (-A) + (-B) = - (A + B)
    s21_big_decimal nBigValue_1 = {0};
    s21_big_negate(big_value_1, &nBigValue_1);
    s21_big_add(nBigValue_1, big_value_2, big_result);
    s21_big_negate(*big_result, big_result);

  } else if (signValue_1 == 1 && signValue_2 == 1) {
    // (-A) - (-B) = (-A) + (+B) = (+B) - (+A)
    s21_big_decimal nBigValue_1 = {0};
    s21_big_negate(big_value_1, &nBigValue_1);
    s21_big_decimal nBigValue_2 = {0};
    s21_big_negate(big_value_2, &nBigValue_2);
    s21_big_sub(nBigValue_2, nBigValue_1, big_result);
  }
  return OK;
}

// умножение чисел big_decimal
int s21_big_mul(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result) {
  unsigned char sign = 0;
  unsigned char extValue1 = s21_getExt(big_value_1);
  unsigned char extValue2 = s21_getExt(big_value_2);

  unsigned char signValue_1 = s21_getSign(big_value_1);
  unsigned char signValue_2 = s21_getSign(big_value_2);

  // если знаки множителей разные, то знак результата будет отрицательным
  if (signValue_1 != signValue_2) sign = 1;
  s21_mulMantissa(big_value_1, big_value_2, big_result);
  s21_writeBit(big_result, SIGN_INDEX, sign);
  s21_setExt(big_result, extValue1 + extValue2);
  return OK;
}

// деление чисел big_decimal
// возвращает DIVIDE0, если big_value_2 равен 0 и OK во всех остальных случаях
int s21_big_div(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result) {
  unsigned int res = OK;
  s21_big_decimal_norm(&big_value_1, &big_value_2);

  char singValue_1 = s21_getSign(big_value_1);
  char singValue_2 = s21_getSign(big_value_2);

  s21_resetSign(&big_value_1);
  s21_resetSign(&big_value_2);

  s21_big_decimal big_null = {0};
  s21_big_decimal integer_part = {0};
  s21_big_decimal remainder = {0};

  s21_initialBigDecimal(big_result);

  int cnt = 0;

  if (s21_is_big_zero(big_value_2))
    res = DIVIDE0;
  else if (s21_is_big_zero(big_value_1))
    res = OK;
  else {
    do {
      s21_divMantissa(big_value_1, big_value_2, &integer_part, &remainder);
      cnt++;
      s21_mulMantissa10(big_result);
      s21_addMantissa(*big_result, integer_part, big_result);
      s21_copyMantissa(remainder, &big_value_1);

      if (s21_is_big_less(big_value_1, big_value_2))
        s21_mulMantissa10(&big_value_1);

    } while (s21_is_big_greater(remainder, big_null) > 0 && cnt < 29);

    if (singValue_1 != singValue_2) s21_setSign(big_result);
    s21_setExt(big_result, cnt - 1);
  }

  return res;
}

// cложение чисел decimal
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};
  s21_big_decimal big_result = {0};

  s21_from_decimal_to_big_decimal(value_1, &big_value_1);
  s21_from_decimal_to_big_decimal(value_2, &big_value_2);

  s21_big_add(big_value_1, big_value_2, &big_result);
  return s21_from_big_decimal_to_decimal(big_result, result);
}

// вычитание чисел decimal
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};
  s21_big_decimal big_result = {0};

  s21_from_decimal_to_big_decimal(value_1, &big_value_1);
  s21_from_decimal_to_big_decimal(value_2, &big_value_2);

  s21_big_sub(big_value_1, big_value_2, &big_result);

  return s21_from_big_decimal_to_decimal(big_result, result);
}

// умножение чисел decimal
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};
  s21_big_decimal big_result = {0};

  s21_from_decimal_to_big_decimal(value_1, &big_value_1);
  s21_from_decimal_to_big_decimal(value_2, &big_value_2);

  s21_big_mul(big_value_1, big_value_2, &big_result);

  return s21_from_big_decimal_to_decimal(big_result, result);
}

// деление чисел decimal
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = OK;
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};
  s21_big_decimal big_result = {0};

  s21_from_decimal_to_big_decimal(value_1, &big_value_1);
  s21_from_decimal_to_big_decimal(value_2, &big_value_2);

  res = s21_big_div(big_value_1, big_value_2, &big_result);
  if (res == OK) res = s21_from_big_decimal_to_decimal(big_result, result);

  return res;
}
