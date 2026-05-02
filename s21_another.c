#include "s21_decimal.h"

BIG_TEN;
BIG_FIVE;
BIG_ONE;

// Округление указанного dig_decimal числа до ближайшего целого числа
// в сторону отрицательной бесконечности
int s21_big_floor(s21_big_decimal big_value, s21_big_decimal *big_result) {
  s21_copyMantissa(big_value, big_result);
  int exp = s21_getExt(big_value);
  int isNotNull = 0;
  while (exp > 0) {
    s21_big_decimal remainder = {0};
    s21_div10(big_result, &remainder);
    if (!s21_is_big_zero(remainder)) isNotNull = 1;
    exp--;
  }
  if (s21_getSign(big_value)) {
    if (isNotNull) s21_big_add(*big_result, bigOne, big_result);
    s21_setSign(big_result);
  }
  return 0;
}

// Округление big_decimal до ближайшего целого числа
int s21_big_round(s21_big_decimal big_value, s21_big_decimal *big_result) {
  s21_copyMantissa(big_value, big_result);
  int exp = s21_getExt(big_value);
  while (exp > 1) {
    s21_big_decimal remainder = {0};
    s21_div10(big_result, &remainder);
    exp--;
  }
  if (exp) {
    s21_big_decimal quotient = {0};
    s21_big_decimal remainder = {0};
    s21_divMantissa(*big_result, bigTen, &quotient, &remainder);
    s21_copyMantissa(quotient, big_result);
    if (s21_is_big_greater_or_equal(remainder, bigFive))
      s21_big_add(quotient, bigOne, big_result);
  }
  if (s21_getSign(big_value)) s21_setSign(big_result);
  return 0;
}

// Возврат целых цифр указанного big_decimal числа; любые дробные цифры
// отбрасываются, включая конечные нули.
int s21_big_truncate(s21_big_decimal big_value, s21_big_decimal *big_result) {
  s21_copyMantissa(big_value, big_result);
  if (s21_getSign(big_value)) s21_setSign(big_result);
  int exp = s21_getExt(big_value);
  while (exp) {
    s21_big_decimal remainder = {0};
    s21_div10(big_result, &remainder);
    exp--;
  }
  return 0;
}

// Возврат результата умножения указанного big_decimal на -1.
int s21_big_negate(s21_big_decimal big_value, s21_big_decimal *big_result) {
  unsigned char sign = s21_getSign(big_value);
  for (int i = 0; i < 7; i++) big_result->bits[i] = big_value.bits[i];
  s21_writeBit(big_result, SIGN_INDEX, 1 - sign);
  s21_big_positive_zero(big_result);
  return 0;
}

// Округление указанного Decimal числа до ближайшего целого числа
// в сторону отрицательной бесконечности
int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_big_decimal big_value = {0};
  s21_big_decimal big_result = {0};
  s21_from_decimal_to_big_decimal(value, &big_value);
  s21_big_floor(big_value, &big_result);
  s21_from_big_decimal_to_decimal(big_result, result);
  return OK;
}

// Округление Decimal до ближайшего целого числа
int s21_round(s21_decimal value, s21_decimal *result) {
  s21_big_decimal big_value = {0};
  s21_big_decimal big_result = {0};
  s21_from_decimal_to_big_decimal(value, &big_value);
  s21_big_round(big_value, &big_result);
  s21_from_big_decimal_to_decimal(big_result, result);
  return OK;
}

// Возврат целых цифр указанного Decimal числа; любые дробные цифры
// отбрасываются, включая конечные нули.
int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_big_decimal big_value = {0};
  s21_big_decimal big_result = {0};
  s21_from_decimal_to_big_decimal(value, &big_value);
  s21_big_truncate(big_value, &big_result);
  s21_from_big_decimal_to_decimal(big_result, result);
  return OK;
}

int s21_big_bankRound(s21_big_decimal *value) {
  s21_big_decimal tmp = {0};
  s21_copyMantissa(*value, &tmp);
  int exp = s21_getExt(*value);
  s21_big_decimal remainder = {0};
  int isNotNull = s21_value_shot_to_decimal(&tmp, &remainder, &exp);
  s21_value_shot_bankRound(&tmp, &remainder, isNotNull);
  s21_setExt(value, exp);
  s21_copyMantissa(tmp, value);

  return 0;
}
// Возврат результата умножения указанного Decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_big_decimal big_value = {0};
  s21_big_decimal big_result = {0};
  s21_from_decimal_to_big_decimal(value, &big_value);
  s21_big_negate(big_value, &big_result);
  s21_from_big_decimal_to_decimal(big_result, result);
  return OK;
}

int s21_value_shot_to_decimal(s21_big_decimal *value,
                              s21_big_decimal *remainder, int *exp) {
  int isNotNull = 0;
  int i = 0;
  s21_big_decimal quotient = {0};
  do {
    s21_divMantissa(*value, bigTen, &quotient, remainder);
    s21_copyMantissa(quotient, value);
    if (!s21_is_big_zero(*remainder)) isNotNull = 1;
    (*exp)--;
    i++;
  } while ((s21_firstBit_find(*value) > 95 && *exp > 0) || *exp > 28);
  if (i == 1 && s21_is_big_equal(*remainder, bigFive)) isNotNull = 0;
  return isNotNull;
}

int s21_value_shot_bankRound(s21_big_decimal *value, s21_big_decimal *remainder,
                             int isNotNull) {
  // банковское округление если последння цифра остатка 5 и больше в остатке
  // цифр нет либо все 0
  if (s21_is_big_equal(*remainder, bigFive) && !isNotNull) {
    if (s21_getBit(*value, 0)) s21_big_add(*value, bigOne, value);
  }
  // обычное округление во всех остальных случаях
  else {
    if (s21_is_big_greater_or_equal(*remainder, bigFive))
      s21_big_add(*value, bigOne, value);
  }
  return 0;
}

int s21_div10(s21_big_decimal *big_result, s21_big_decimal *remainder) {
  s21_big_decimal quotient = {0};
  s21_divMantissa(*big_result, bigTen, &quotient, remainder);
  s21_copyMantissa(quotient, big_result);
  return 0;
}