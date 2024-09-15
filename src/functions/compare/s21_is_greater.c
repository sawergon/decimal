#include "../../s21_decimal.h"
#include "../help/s21_decimal_help.h"
#include "../types/s21_int256.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int compare_code = true;
  if (!s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2) ||
      (!value_1.bits[0] && !value_1.bits[1] && !value_1.bits[2] &&
       !value_2.bits[0] && !value_2.bits[1] && !value_2.bits[2])) {
    compare_code = false;
  } else {
    int sign1 = s21_get_sign(value_1), sign2 = s21_get_sign(value_2);
    if (sign1 > sign2) {
      compare_code = true;
    } else if (sign2 > sign1) {
      compare_code = false;
    } else {
      s21_int256 src1 = int256_init();
      s21_int256 src2 = int256_init();
      int256_normalize_pow(&src1, &src2, value_1, value_2);
      if (int256_is_equal(src1, src2)) {
        compare_code = false;
      } else {
        compare_code = int256_is_greater(src1, src2);
        compare_code = sign1 < 0 ? !compare_code : compare_code;
      }
    }
  }
  return compare_code;
}