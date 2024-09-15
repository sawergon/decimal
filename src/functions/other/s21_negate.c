#include "../../s21_decimal.h"
#include "../help/s21_decimal_help.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int code = S21_CODE_OK;
  if (!result) {
    code = S21_CODE_CALC_ERROR;
  } else {
    int sign = s21_get_sign(value);
    *result = s21_from_4int_to_decimal(value.bits[0], value.bits[1],
                                       value.bits[2], value.bits[3]);
    result->bits[3] = sign < 0 ? result->bits[3] & 2147483647
                               : result->bits[3] | (int)-2147483648;
    if (!s21_is_correct_decimal(value)) {
      code = S21_CODE_CALC_ERROR;
    }
  }
  return code;
}