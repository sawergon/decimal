#include "../../s21_decimal.h"
#include "../help/s21_decimal_help.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int code = S21_CODE_OK;
  if (dst == NULL)
    code = S21_CODE_CONVERT_ERROR;
  else {
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    if (src < 0) {
      s21_set_bit_in_int(&((*dst).bits[3]), 31, 1);
      src = -src;
    }
    dst->bits[0] = src;  // max = 2147483647 / min = -2147483649
  }
  return code;
}
