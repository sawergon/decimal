#include "s21_decimal_help.h"

bool s21_is_correct_decimal(s21_decimal value) {
  int mask_0_15 = 65535, mask_24_30 = 2130706432, bits3 = value.bits[3],
      pow = s21_get_pow(value);
  bool code = true;
  if (mask_0_15 & bits3 || mask_24_30 & bits3 || pow > 28) {
    code = false;
  }
  return code;
}