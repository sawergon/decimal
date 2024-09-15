#include "../../s21_decimal.h"
#include "../help/s21_decimal_help.h"
#include "math.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int code = S21_CODE_OK;
  if (!dst) {
    code = S21_CODE_CONVERT_ERROR;
  } else if (!s21_is_correct_decimal(src)) {
    code = S21_CODE_CONVERT_ERROR;
    *dst = 0.0f;
  } else {
    double tmp = (unsigned int)src.bits[0] +
                 (double)((unsigned int)src.bits[1]) * pow(2.0, 32) +
                 (double)((unsigned int)src.bits[2] * pow(2, 64));
    double sign = s21_get_sign(src), d_pow = s21_get_pow(src);
    double power = pow(10.0, d_pow);
    tmp /= power;
    tmp *= sign;
    *dst = (float)tmp;
  }
  return code;
}