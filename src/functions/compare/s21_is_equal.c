#include "../../s21_decimal.h"
#include "../help/s21_decimal_help.h"
#include "../types/s21_int256.h"

void help_is_equal(int differ, s21_int256* val_1, s21_int256 val_2);
/**
 * 120 1
 * 12 0
 *
 * 1030   2 -> 10.3
 * 103    1 -> 10.3
 * 12001  3 -> 12.001
 * 120010 4 -> 12.001
 * 1002   2 -> 10.02
 * 1      1 -> 0.1
 * @param value_1
 * @param value_2
 * @return
 */
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int compare_code = true;
  if (!s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2)) {
    compare_code = false;
  } else if ((value_1.bits[0] == 0 &&
              value_2.bits[0] ==
                  0 &&  /// если первые 3 бита 0, то считаем 0==-0
              value_1.bits[1] == 0 &&
              value_2.bits[1] == 0 && value_1.bits[2] == 0 &&
              value_2.bits[2] == 0) ||
             (value_1.bits[0] == value_2.bits[0] &&
              value_1.bits[1] == value_2.bits[1] &&
              value_1.bits[2] == value_2.bits[2] &&
              value_1.bits[3] == value_2.bits[3])) {
    compare_code = true;
  } else {
    int sign1 = s21_get_sign(value_1), sign2 = s21_get_sign(value_2);
    int power1 = s21_get_pow(value_1), power2 = s21_get_pow(value_2);
    if (sign1 != sign2 || power2 == power1) {
      compare_code = false;
    } else {
      s21_int256 src1 = int256_init();
      s21_int256 src2 = int256_init();
      int256_normalize_pow(&src1, &src2, value_1, value_2);
      compare_code = int256_is_equal(src1, src2);
    }
  }
  return compare_code;
}