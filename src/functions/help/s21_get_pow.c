#include "s21_decimal_help.h"

int s21_get_pow(s21_decimal value) {
  int bits3 = value.bits[3];
  int mask = 16711680;
  return (bits3 & mask) >> 16;
}