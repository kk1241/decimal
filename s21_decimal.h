#ifndef S21_DECIMAL
#define S21_DECIMAL

#define OK 0
#define TOOHIGH 1
#define TOOSMALL 2
#define DIVIDE0 3

#define CALC_ERROR 1
#define CONVERT_ERROR 1

#define FALSE 0
#define TRUE 1

#define SIGN_INDEX 223

#define BIG_TEN s21_big_decimal bigTen = {{10, 0, 0, 0, 0, 0, 0}}
#define BIG_ONE s21_big_decimal bigOne = {{1, 0, 0, 0, 0, 0, 0}}
#define BIG_FIVE s21_big_decimal bigFive = {{5, 0, 0, 0, 0, 0, 0}}

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];
} s21_big_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int s21_from_string_to_decimal(char *strNumber, s21_decimal *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// ----------------------------------------------------------
int s21_value_shot_to_decimal(s21_big_decimal *value,
                              s21_big_decimal *remainder, int *exp);

int s21_value_shot_bankRound(s21_big_decimal *value, s21_big_decimal *remainder,
                             int isNotNull);
int s21_big_bankRound(s21_big_decimal *value);
int s21_div10(s21_big_decimal *big_result, s21_big_decimal *remainder);

int s21_big_floor(s21_big_decimal big_value, s21_big_decimal *big_result);
int s21_big_round(s21_big_decimal big_value, s21_big_decimal *big_result);
int s21_big_truncate(s21_big_decimal big_value, s21_big_decimal *big_result);
int s21_big_negate(s21_big_decimal big_value, s21_big_decimal *big_result);
int s21_big_bankRound(s21_big_decimal *value);

// ----------------------

int s21_big_add(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result);
int s21_big_sub(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result);
int s21_big_mul(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result);
int s21_big_div(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal *big_result);

// -------------------

unsigned char s21_NOT(unsigned char value);

unsigned char s21_getBit(s21_big_decimal value, unsigned char bit);
void s21_setBit(s21_big_decimal *value, unsigned char bit);
void s21_resetBit(s21_big_decimal *value, unsigned char bit);
void s21_writeBit(s21_big_decimal *value, unsigned char bit,
                  unsigned char bitValue);
unsigned char s21_getSign(s21_big_decimal value);
void s21_setSign(s21_big_decimal *value);
void s21_resetSign(s21_big_decimal *value);

void s21_rolMantissa(s21_big_decimal *value);
void s21_rorMantissa(s21_big_decimal *value);
void s21_negativeMantissa(s21_big_decimal *value);
void s21_addMantissa(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);

void s21_subMantissa(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);

void s21_mulMantissa(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);

void s21_divMantissa(s21_big_decimal a, s21_big_decimal b,
                     s21_big_decimal *quotient, s21_big_decimal *remainder);
unsigned char s21_isMantissaFull(s21_big_decimal value);

unsigned char s21_getExt(s21_big_decimal value);
void s21_setExt(s21_big_decimal *value, unsigned char ext);

void s21_initialDecimal(s21_decimal *number);

// -------------------------------------

void s21_copyMantissa(s21_big_decimal src, s21_big_decimal *dst);

void s21_initialBigDecimal(s21_big_decimal *number);

void s21_mulMantissa10(s21_big_decimal *value);

int s21_from_decimal_to_big_decimal(s21_decimal src, s21_big_decimal *dst);
int s21_from_big_decimal_to_decimal(s21_big_decimal src, s21_decimal *dst);

void s21_big_decimal_norm(s21_big_decimal *big_value1,
                          s21_big_decimal *big_value2);
void s21_prepare(s21_decimal value_1, s21_decimal value_2,
                 s21_big_decimal *big_value1, s21_big_decimal *big_value2);

void s21_big_positive_zero(s21_big_decimal *value);

int s21_is_big_zero(s21_big_decimal number);
void s21_removeZero(s21_big_decimal *value);

int s21_decimal_overflow(s21_big_decimal value);

int s21_firstBit_find(s21_big_decimal number);

// -------------------

int s21_is_big_less(s21_big_decimal big_value_1, s21_big_decimal big_value_2);
int s21_is_big_greater(s21_big_decimal big_value_1,
                       s21_big_decimal big_value_2);
int s21_is_big_equal(s21_big_decimal big_value_1, s21_big_decimal big_value_2);
int s21_is_big_less_or_equal(s21_big_decimal big_value_1,
                             s21_big_decimal big_value_2);
int s21_is_big_greater_or_equal(s21_big_decimal big_value_1,
                                s21_big_decimal big_value_2);
int s21_is_big_not_equal(s21_big_decimal big_value_1,
                         s21_big_decimal big_value_2);

// ---------------------------

int s21_from_string_to_big_decimal(char *strNumber, s21_big_decimal *dst);
int s21_from_int_to_big_decimal(int src, s21_big_decimal *dst);
int s21_from_float_to_big_decimal(float src, s21_big_decimal *dst);
int s21_from_big_decimal_to_int(s21_big_decimal src, int *dst);
int s21_from_big_decimal_to_float(s21_big_decimal src, float *dst);

#endif