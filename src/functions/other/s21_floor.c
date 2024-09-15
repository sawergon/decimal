#include "../../s21_decimal.h"
#include "../help/s21_decimal_help.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int code = S21_CODE_OK;
  if (result == NULL || !s21_is_correct_decimal(value)) {
    code = S21_CODE_CALC_ERROR;
  } else {
    s21_decimal res = s21_get_decimal_zero();
    s21_truncate(value, &res);
    s21_decimal fraction = s21_get_decimal_zero();
    s21_sub(value, res, &fraction);
    int sign = s21_get_sign(res);
    if (sign < 0 && s21_is_not_equal(fraction, s21_get_decimal_zero())) {
      s21_decimal minus_one = {{0x1, 0x0, 0x0, 0x80000000}};
      s21_add(res, minus_one, &res);
    }
    *result = res;
  }
  return code;
}