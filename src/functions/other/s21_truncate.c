#include "../../s21_decimal.h"
#include "../help/s21_decimal_help.h"
#include "../types/s21_int256.h"
#include "math.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int code = S21_CODE_OK;
  if (result == NULL || !s21_is_correct_decimal(value)) {
    code = S21_CODE_CONVERT_ERROR;
  } else {
    s21_int256 int_value = int256_init_arr(value.bits, 3);
    s21_int256 int_result = int256_init();
    int pow = s21_get_pow(value);
    s21_int256 ten_in_power = int256_init_int(1);
    s21_int256 ten = int256_init_int(10);
    for (int i = 0; i < pow; ++i) {
      ten_in_power = int256_mul(ten_in_power, ten);
    }
    int_result = int256_div(int_value, ten_in_power, NULL);
    s21_decimal res = s21_get_decimal_zero();
    int256_to_decimal(int_result, &res);
    if (s21_get_bit_from_decimal(value, 127)) {
      s21_set_bit_in_int(&((res).bits[3]), 31, 1);
    }
    *result = res;
  }
  return code;
}
