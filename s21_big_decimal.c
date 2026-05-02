
#include "s21_decimal.h"
#include "s21_output.h"

// функция copyMantissa копирует мантису src в dst числа big_decimal
void s21_copyMantissa(s21_big_decimal src, s21_big_decimal *dst) {
  for (int i = 0; i < 6; i++) dst->bits[i] = src.bits[i];
}

// инициализация big_decimal (во все элементы записываем 0)
void s21_initialBigDecimal(s21_big_decimal *number) {
  for (int i = 0; i < 7; i++) number->bits[i] = 0;
}

// функция преобразования числа decimal в big_decimal
// копируем 3 bits из decimal, остальные обнуляем
int s21_from_decimal_to_big_decimal(s21_decimal src, s21_big_decimal *dst) {
  s21_initialBigDecimal(dst);
  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[3] = 0;
  dst->bits[4] = 0;
  dst->bits[5] = 0;
  dst->bits[6] = src.bits[3];
  return OK;
}

// функция преобразования числа big_decimal в decimal
// делаем проверку на переполнение decimal
int s21_from_big_decimal_to_decimal(s21_big_decimal src, s21_decimal *dst) {
  s21_removeZero(&src);

  int result = OK;
  int ext = s21_getExt(src);
  s21_big_decimal intValue = {{0}};
  // если первый установленный бит бигдецимал числа больше 95,
  // то имеем переполнение мантиссы (нужно банковское окруление)
  // или степень больше 28 (нужно банковское окруление)
  if (s21_firstBit_find(src) > 95 || ext > 28) {
    // нужно определить, либо это слишком большое число, либо это много знаков
    // после точки, для этого возьмем целую часть числа и проверим его первый
    // установленный бит
    s21_big_truncate(src, &intValue);

    // если первый установленный бит целого бигдецимал числа больше 95,
    // то имеем слишком большое (маленькое) число
    if (s21_firstBit_find(intValue) > 95) {
      result = s21_decimal_overflow(src);
    } else {
      // иначе, имеем много цифр после точки или степень больше 28,
      // нужнобанковское округление
      result = s21_big_bankRound(&src);
      s21_big_truncate(src, &intValue);

      // если первый установленный бит целого бигдецимал числа больше 95,
      // то имеем слишком большое (маленькое) число
      if (s21_firstBit_find(intValue) > 95) {
        result = s21_decimal_overflow(src);
      }
    }
  } else {
    // нет переполнения мантиссы, не требуется округление
  }

  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[3] = src.bits[6];
  return result;
}

// функция умножения числа big_decimal на 10
// быстрый вариант (без перебора битов big_digital)
void s21_mulMantissa10(s21_big_decimal *value) {
  // чтобы умножить мантиссу на 10, нужно сложить результаты
  // умножения мантиссы на 8 и результат умножения мантиссы на 2, а потом
  // сложить
  s21_big_decimal value8 = {0};
  s21_big_decimal value2 = {0};
  s21_copyMantissa(*value, &value8);

  // умножение на 8 (сдвинули биты влево 2 раза)
  s21_rolMantissa(&value8);
  s21_rolMantissa(&value8);
  s21_rolMantissa(&value8);

  s21_copyMantissa(*value, &value2);
  // умножение на 2 (сдвинули биты влево 1 раз)
  s21_rolMantissa(&value2);
  // сложение
  s21_addMantissa(value2, value8, value);
}

// функция decimal_norm приводит два числа к одной степени
void s21_big_decimal_norm(s21_big_decimal *big_value1,
                          s21_big_decimal *big_value2) {
  unsigned char exp1 = s21_getExt(*big_value1);
  unsigned char exp2 = s21_getExt(*big_value2);

  if (exp1 > exp2) {
    for (int i = 0; i < exp1 - exp2; i++) s21_mulMantissa10(big_value2);
    s21_setExt(big_value2, exp1);
  } else if (exp2 > exp1) {
    for (int i = 0; i < exp2 - exp1; i++) s21_mulMantissa10(big_value1);
    s21_setExt(big_value1, exp2);
  }
  s21_big_positive_zero(big_value1);
  s21_big_positive_zero(big_value2);
}

// функция преобразования отрицательного нуля в положительный
void s21_big_positive_zero(s21_big_decimal *value) {
  // если value равно 0, то сбрасываем флаг знака и записываем 0 в степень
  if (s21_is_big_zero(*value)) {
    s21_resetSign(value);
    s21_setExt(value, 0);
  }
}

// функция возвращает признак переполнения числа decimal
// если флаг знака сброшен (число положительное) возвращаем TOOHIGH
// если флаг знака установлен (число отрицательное) возвращаем TOOSMALL
int s21_decimal_overflow(s21_big_decimal value) {
  unsigned char sign = s21_getSign(value);
  int result = TOOSMALL;

  if (sign == 0) result = TOOHIGH;

  return result;
}

// Проверка на 0
int s21_is_big_zero(s21_big_decimal number) {
  // Проверяем только биты данных (0-5)
  int cntZero = 0;
  for (int i = 0; i < 6; i++) {
    if (number.bits[i] == 0) cntZero++;
  }
  return cntZero == 6;  // Ноль
}

// функция удаляет незначащие нули после точки
void s21_removeZero(s21_big_decimal *value) {
  unsigned char ext = s21_getExt(*value);
  unsigned zeroRemainder = 1;

  s21_big_decimal quotient = {0};
  s21_big_decimal remainder = {0};

  BIG_TEN;

  // пока степень больше 0 и остаток от деления числа на 10 равен 0
  while (ext > 0 && zeroRemainder == 1) {
    s21_divMantissa(*value, bigTen, &quotient, &remainder);

    zeroRemainder = s21_is_big_zero(remainder);
    if (zeroRemainder) {
      s21_copyMantissa(quotient, value);
      ext--;
    }
  }
  s21_setExt(value, ext);
}

int s21_firstBit_find(s21_big_decimal number) {
  int notNullBit = 191;

  while (notNullBit >= 0 && !s21_getBit(number, notNullBit)) notNullBit--;
  return notNullBit;
}
