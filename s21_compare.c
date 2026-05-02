#include "s21_decimal.h"

// возвращает TRUE если число value_1 СТРОГО МЕНЬШЕ value_2, иначе FALSE
int s21_is_big_less(s21_big_decimal big_value_1, s21_big_decimal big_value_2) {
  s21_big_decimal_norm(&big_value_1, &big_value_2);

  int resultCompare = FALSE;
  unsigned char bit1;
  unsigned char bit2;

  unsigned char signValue_1 = s21_getSign(big_value_1);
  unsigned char signValue_2 = s21_getSign(big_value_2);
  // если числа равны => результат FALSE
  if (s21_is_big_equal(big_value_1, big_value_2))
    resultCompare = FALSE;
  else if (signValue_1 == 0 && signValue_2 == 1) {
    // первое число положительное, второе отрицательное => результат FALSE
    resultCompare = FALSE;
  } else if (signValue_1 == 1 && signValue_2 == 0) {
    // первое число отрицательное, второе положительное => результат TRUE
    resultCompare = TRUE;
  } else if (signValue_1 == signValue_2) {
    for (int i = 191; i >= 0; i--) {
      bit1 = s21_getBit(big_value_1, i);
      bit2 = s21_getBit(big_value_2, i);
      if (bit1 < bit2) {
        resultCompare = TRUE;
        break;
      } else if (bit1 > bit2) {
        resultCompare = FALSE;
        break;
      }
    }

    // если числа были отрицательными, то инвертируем результат
    // то есть число с меньшей мантиссой будет больше, чем с большей
    // и число с большей мантиссой будет меньшь
    // проверку на равенство делаем в начале функции
    if (signValue_1 == 1) resultCompare = s21_NOT(resultCompare);
  }
  return resultCompare;
}

// возвращает TRUE если число value_1 СТРОГО БОЛЬШЕ value_2, иначе FALSE
int s21_is_big_greater(s21_big_decimal big_value_1,
                       s21_big_decimal big_value_2) {
  s21_big_decimal_norm(&big_value_1, &big_value_2);

  int resultCompare = FALSE;

  unsigned char signValue_1 = s21_getSign(big_value_1);
  unsigned char signValue_2 = s21_getSign(big_value_2);

  // если числа равны => результат FALSE
  if (s21_is_big_equal(big_value_1, big_value_2))
    resultCompare = FALSE;
  else if (signValue_1 == 0 && signValue_2 == 1) {
    // первое число положительное, второе отрицательное => результат TRUE
    resultCompare = TRUE;
  } else if (signValue_1 == 1 && signValue_2 == 0) {
    // первое число отрицательное, второе положительное => результат FALSE
    resultCompare = FALSE;
  } else if (signValue_1 == signValue_2) {
    for (int i = 191; i >= 0; i--) {
      unsigned char bit1 = s21_getBit(big_value_1, i);
      unsigned char bit2 = s21_getBit(big_value_2, i);
      if (bit1 > bit2) {
        resultCompare = TRUE;
        break;
      } else if (bit1 < bit2) {
        resultCompare = FALSE;
        break;
      }
    }
    // если числа были отрицательными, то инвертируем результат
    // то есть число с меньшей мантиссой будет больше, чем с большей
    // и число с большей мантиссой будет меньшь
    // проверку на равенство делаем в начале функции
    if (signValue_1 == 1) resultCompare = s21_NOT(resultCompare);
  }
  return resultCompare;
}

// возвращает TRUE если число value_1 РАВНО value_2, иначе FALSE
int s21_is_big_equal(s21_big_decimal big_value_1, s21_big_decimal big_value_2) {
  s21_big_decimal_norm(&big_value_1, &big_value_2);
  int resultCompare = FALSE;

  unsigned char signValue_1 = s21_getSign(big_value_1);
  unsigned char signValue_2 = s21_getSign(big_value_2);

  // если знаки равны, проверяем мантиссы

  if (signValue_1 == signValue_2) {
    int cnt = 0;
    for (int i = 191; i >= 0; i--) {
      unsigned char bit1 = s21_getBit(big_value_1, i);
      unsigned char bit2 = s21_getBit(big_value_2, i);
      if (bit1 == bit2) cnt++;
    }
    // знаки равны и все 192 биты мантисс равны
    if (cnt == 192) resultCompare = TRUE;
  }
  return resultCompare;
}

// возвращает TRUE если число value_1 МЕНЬШЕ ИЛИ РАВНО value_2, иначе FALSE
// (value_1 НЕ БОЛЬШЕ value_2)
int s21_is_big_less_or_equal(s21_big_decimal big_value_1,
                             s21_big_decimal big_value_2) {
  return s21_NOT(s21_is_big_greater(big_value_1, big_value_2));
}

// возвращает TRUE если число value_1 БОЛЬШЕ ИЛИ РАВНО value_2, иначе FALSE
// (value_1 НЕ МЕНЬШЕ value_2)
int s21_is_big_greater_or_equal(s21_big_decimal big_value_1,
                                s21_big_decimal big_value_2) {
  return s21_NOT(s21_is_big_less(big_value_1, big_value_2));
}

// возвращает TRUE если число value_1 НЕ РАВНО value_2, иначе FALSE
// (value_1 НЕ РАВНО value_2)
int s21_is_big_not_equal(s21_big_decimal big_value_1,
                         s21_big_decimal big_value_2) {
  return s21_NOT(s21_is_big_equal(big_value_1, big_value_2));
}

// возвращает TRUE если число value_1 СТРОГО МЕНЬШЕ value_2, иначе FALSE
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};

  s21_from_decimal_to_big_decimal(value_1, &big_value_1);
  s21_from_decimal_to_big_decimal(value_2, &big_value_2);

  return s21_is_big_less(big_value_1, big_value_2);
}

// возвращает TRUE если число value_1 СТРОГО БОЛЬШЕ value_2, иначе FALSE
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};

  s21_from_decimal_to_big_decimal(value_1, &big_value_1);
  s21_from_decimal_to_big_decimal(value_2, &big_value_2);

  return s21_is_big_greater(big_value_1, big_value_2);
}

// возвращает TRUE если число value_1 МЕНЬШЕ ИЛИ РАВНО value_2, иначе FALSE
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};

  s21_from_decimal_to_big_decimal(value_1, &big_value_1);
  s21_from_decimal_to_big_decimal(value_2, &big_value_2);

  return s21_is_big_less_or_equal(big_value_1, big_value_2);
}

// возвращает TRUE если число value_1 БОЛЬШЕ ИЛИ РАВНО value_2, иначе FALSE
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};

  s21_from_decimal_to_big_decimal(value_1, &big_value_1);
  s21_from_decimal_to_big_decimal(value_2, &big_value_2);

  return s21_is_big_greater_or_equal(big_value_1, big_value_2);
}

// возвращает TRUE если число value_1 РАВНО value_2, иначе FALSE
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};

  s21_from_decimal_to_big_decimal(value_1, &big_value_1);
  s21_from_decimal_to_big_decimal(value_2, &big_value_2);

  return s21_is_big_equal(big_value_1, big_value_2);
}

// возвращает TRUE если число value_1 НЕ РАВНО value_2, иначе FALSE
// (value_1 НЕ РАВНО value_2)
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};

  s21_from_decimal_to_big_decimal(value_1, &big_value_1);
  s21_from_decimal_to_big_decimal(value_2, &big_value_2);

  return s21_is_big_not_equal(big_value_1, big_value_2);
}