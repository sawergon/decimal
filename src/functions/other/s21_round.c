#include "../../s21_decimal.h"
#include "../help/s21_decimal_help.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int code = S21_CODE_OK;
  if (result == NULL || !s21_is_correct_decimal(value)) {
    code = S21_CODE_CALC_ERROR;
  } else {
    s21_decimal res = s21_get_decimal_zero();
    int sign = s21_get_sign(value);
    s21_set_sign(0, &value);
    s21_truncate(value, &res);
    s21_decimal fraction = s21_get_decimal_zero();
    s21_sub(value, res, &fraction);
    s21_decimal zero_five = {{0x5, 0, 0, 0x10000}};
    if (s21_is_not_equal(fraction, s21_get_decimal_zero())) {
      s21_decimal one = {{0x1, 0x0, 0x0, 0x0}};
      if (s21_is_equal(zero_five, fraction)) {
        if (res.bits[0] & 1) {
          s21_add(res, one, &res);
        }
      } else if (s21_is_greater(fraction, zero_five)) {
        s21_add(res, one, &res);
      }
    }
    s21_set_sign(sign, &res);
    *result = res;
  }
  return code;
}