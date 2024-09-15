#include "s21_decimal_help.h"

int s21_get_bit_from_decimal(s21_decimal value, int pos) {
  int bit_value = -1;
  if (-1 < pos) {
    if (pos < 32) {
      bit_value = (value.bits[0] >> pos) & 1;
    } else if (pos < 64) {
      bit_value = (value.bits[1] >> (pos - 32)) & 1;
    } else if (pos < 96) {
      bit_value = (value.bits[2] >> (pos - 64)) & 1;
    } else if (pos < 128) {
      bit_value = (value.bits[3] >> (pos - 128)) & 1;
    }
  }
  return bit_value;
}