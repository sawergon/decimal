#include "s21_decimal_help.h"

void s21_print_bits_float(float value) {
  s21_print_bits_int(*((unsigned int*)&value));
}