#include "s21_decimal_help.h"

/**
 * установка знака
 * @param sign знак в формате 1 -1
 * @param dst число для установки знака
 */
void s21_set_sign(int sign, s21_decimal *dst) {
  int mask = -2147483648;
  if (sign < 0) {
    dst->bits[3] |= mask;
  } else {
    mask = ~mask;
    dst->bits[3] &= mask;
  }
}