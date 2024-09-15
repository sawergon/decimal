#include "s21_decimal_help.h"

int s21_get_sign(s21_decimal value) {
  int mask = -2147483648;
  return ((value.bits[3] & mask) == mask) ? -1 : 1;
}