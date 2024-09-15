#include "../../s21_decimal.h"
#include "../help/s21_decimal_help.h"

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int compare_code = true;
  if (!s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2)) {
    compare_code = false;
  } else
    compare_code = !s21_is_equal(value_1, value_2);
  return compare_code;
}