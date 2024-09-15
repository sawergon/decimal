#include <math.h>

#include "../../s21_decimal.h"
#include "../help/s21_decimal_help.h"
#include "../types/s21_int256.h"
#define s21_MAXDEC 2e96 - 1

int s21_clear_decimal(s21_decimal *value) {
  value->bits[0] = 0;
  value->bits[1] = 0;
  value->bits[2] = 0;
  value->bits[3] = 0;
  return 0;
}

int s21_set_sign_1(s21_decimal *value) {
  value->bits[3] = value->bits[3] | ((unsigned long)1 << (31));
  return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int status = S21_CODE_OK;
  if (fabs(src) < 2e-28 || isnan(src)) {
    s21_clear_decimal(dst);
    status = S21_CODE_CONVERT_ERROR;
  } else if (fabs(src) > s21_MAXDEC || dst == NULL) {
    status = S21_CODE_CONVERT_ERROR;
  } else {
    s21_clear_decimal(dst);
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src = -(src);
    }
    long int new = (long int)src;
    long int exp = 0;
    while (src - ((float)new / (long int)(pow(10, exp))) != 0) {
      exp++;
      new = src *(long int)(pow(10, exp));
    }
    s21_from_int_to_decimal(new, dst);
    if (sign) {
      s21_set_sign_1(dst);
    }
    dst->bits[3] += exp << 16;
  }
  return status;
}