#include "s21_decimal.h"

// функция инвертирования значения
// 1 -> 0
// 0 -> 1
unsigned char s21_NOT(unsigned char value) { return 1 - value; }

void s21_initialDecimal(s21_decimal *number) {
  for (int i = 0; i < 4; i++) number->bits[i] = 0;
}

// функция getBit получает бит с номером bit из s21_big_decimal числа value
// (223 - бит знака, 0 - младший бит мантиссы)
unsigned char s21_getBit(s21_big_decimal value, unsigned char bit) {
  unsigned char bitsIndex = bit / 32;
  unsigned char bitNumber = bit % 32;
  return (value.bits[bitsIndex] >> bitNumber) & 1;
}

// функция setBit устанавливает бит с номером bit в s21_big_decimal числе value
void s21_setBit(s21_big_decimal *value, unsigned char bit) {
  unsigned char bitsIndex = bit / 32;
  unsigned char bitNumber = bit % 32;
  value->bits[bitsIndex] = value->bits[bitsIndex] | (1 << bitNumber);
}

// функция resetBit сбрасывает бит с номером bit в s21_big_decimal числе value
void s21_resetBit(s21_big_decimal *value, unsigned char bit) {
  unsigned char bitsIndex = bit / 32;
  unsigned char bitNumber = bit % 32;
  value->bits[bitsIndex] = value->bits[bitsIndex] & ~(1 << bitNumber);
}

void s21_writeBit(s21_big_decimal *value, unsigned char bit,
                  unsigned char bitValue) {
  if (bitValue == 0)
    s21_resetBit(value, bit);
  else
    s21_setBit(value, bit);
}

// функция getSign получает значение знака в s21_big_decimal числе value
// (возвращает значение 223 бита)
unsigned char s21_getSign(s21_big_decimal value) {
  return s21_getBit(value, SIGN_INDEX);
}

// функция setSign устанавливает знак в s21_big_decimal числе value
// (устанавливает 223 бит)
void s21_setSign(s21_big_decimal *value) { s21_setBit(value, SIGN_INDEX); }

// функция resetSign сбрасывает знак в s21_big_decimal числе value
// (сбрасывает 223 бит)
void s21_resetSign(s21_big_decimal *value) { s21_resetBit(value, SIGN_INDEX); }

// функция rolMantissa циклически сдвигает все биты мантиссы влево
// (0->1, 1->2 .. 190->191, 0-ой бит сбрасываем в 0)
// (умножение мантиссы на 2)
void s21_rolMantissa(s21_big_decimal *value) {
  for (int i = 191; i > 0; i--) {
    unsigned char bit = s21_getBit(*value, i - 1);
    s21_writeBit(value, i, bit);
  }
  s21_resetBit(value, 0);
}

// функция rorMantissa циклически сдвигает все биты мантиссы вправо
// (0<-1, 1<-2 .. 190<-191, 191-ой бит сбрасываем в 0)
// (деление мантиссы на 2)
void s21_rorMantissa(s21_big_decimal *value) {
  for (int i = 0; i < 191; i++) {
    unsigned char bit = s21_getBit(*value, i + 1);
    s21_writeBit(value, i, bit);
  }
  s21_resetBit(value, 191);
}

// функция negativeMantissa инвертирует все биты мантиссы в s21_big_decimal
// числа value
void s21_negativeMantissa(s21_big_decimal *value) {
  for (int i = 0; i < 192; i++) {
    unsigned char bit = s21_getBit(*value, i);
    s21_writeBit(value, i, 1 - bit);
  }
}

// функция addMantissa складывает мантиссы s21_big_decimal чисел value_1 и
// value_2, результат сложения сохраняется в result
// функция возвращает 0, если не было переполнения мантиссы
// 1 - если было переполнение
void s21_addMantissa(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  unsigned char c = 0;
  for (int i = 0; i < 192; i++) {
    unsigned char s = s21_getBit(value_1, i) + s21_getBit(value_2, i) + c;
    c = s / 2;
    unsigned char o = s % 2;
    s21_writeBit(result, i, o);
  };
}

// Двоичное вычитание с дополнением позволяет заменить вычитание сложением
// функция subMantissa вычитает мантиссы s21_big_decimal чисел value_1 и
// value_2, разность сохраняется в result
// (value_1 должно быть больше или равно value_2)
void s21_subMantissa(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  BIG_ONE;

  s21_negativeMantissa(&value_2);

  s21_addMantissa(value_1, value_2, result);
  s21_addMantissa(*result, bigOne, result);
};

// функция mulMantissa умножает мантиссы s21_big_decimal чисел value_1 и
// value_2, результат умножения сохраняется в result
void s21_mulMantissa(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  s21_big_decimal temp = {0};

  for (int i = 0; i < 192; i++) {
    if (s21_getBit(value_2, i) == 1) {
      s21_copyMantissa(value_1, &temp);
      for (int j = 0; j < i; j++) s21_rolMantissa(&temp);
      s21_addMantissa(*result, temp, result);
    }
  }
};

// функция divMantissa делит мантиссы s21_big_decimal чисел a и b
// целая часть записывается в quotient, остаток в remainder
void s21_divMantissa(s21_big_decimal a, s21_big_decimal b,
                     s21_big_decimal *quotient, s21_big_decimal *remainder) {
  // избавляется от степени и знаков, иначе некорректно отрабатываем сравнение
  s21_big_decimal s = {{0}};
  s21_big_decimal shifted_b = {{0}};
  s21_setExt(&a, 0);
  s21_setExt(&b, 0);
  s21_resetSign(&a);
  s21_resetSign(&b);

  // максимальное биг децимал числа, которое мы можем поделить это 2^191-1
  // самый старший разряд должен быть равен 0, иначе будет зацикливание
  s21_resetBit(&a, 191);
  s21_resetBit(&b, 191);
  s21_initialBigDecimal(quotient);
  s21_initialBigDecimal(remainder);

  if (s21_is_big_zero(a) == FALSE && s21_is_big_zero(b) == FALSE) {
    while (s21_is_big_greater_or_equal(a, b)) {
      int q = 0;

      s21_copyMantissa(b, &shifted_b);

      while (s21_is_big_less_or_equal(shifted_b, a)) {
        s21_rolMantissa(&shifted_b);
        q++;
      }

      s21_rorMantissa(&shifted_b);
      q--;

      BIG_ONE;
      for (int i = 1; i <= q; i++) s21_rolMantissa(&bigOne);
      s21_addMantissa(s, bigOne, &s);

      s21_subMantissa(a, shifted_b, &a);
    }
  }
  s21_copyMantissa(s, quotient);
  s21_copyMantissa(a, remainder);
}

// функция getExt возвращает степень числа value
unsigned char s21_getExt(s21_big_decimal value) {
  return (value.bits[6] >> 16 & 0b111111);
}

// функция setExt записывает степень ext в число value
void s21_setExt(s21_big_decimal *value, unsigned char ext) {
  unsigned char sign = s21_getSign(*value);
  value->bits[6] = ext << 16;
  value->bits[6] |= sign << 31;
}

// функция s21_isMantissaFull проверяет биты 96-191 big_decimal числа
// если есть установленные, значит есть переполнение
// мантиссы decimal числа
unsigned char s21_isMantissaFull(s21_big_decimal value) {
  int cnt = 0;
  // считаем единицы в старших битах числа big_decimal
  for (int i = 96; i < 192; i++) cnt += s21_getBit(value, i);
  return cnt > 0;
}