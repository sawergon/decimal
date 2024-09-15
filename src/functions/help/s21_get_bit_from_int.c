#include "s21_decimal_help.h"

int s21_get_bit_from_int(int value, int index) {
  int check = 1 << index;
  int result = (value & check) >> index;
  if (result < 0) result = -result;
  return (result);
}