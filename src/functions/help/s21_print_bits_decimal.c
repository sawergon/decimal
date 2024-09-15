#include "s21_decimal_help.h"

void s21_print_bits_decimal(s21_decimal value) {
  //  for (int i = 0; i < LEN_DECIMAL; ++i) {
  //    s21_print_bits_int(value.bits[i]);
  //  }
  s21_print_bits_int(value.bits[2]);
  s21_print_bits_int(value.bits[1]);
  s21_print_bits_int(value.bits[0]);
  s21_print_bits_int(value.bits[3]);
  printf(
      "\n---_---_---_---_---_---_---_---|"
      "---_---_---_---_---_---_---_---|"
      "---_---_---_---_---_---_---_---|"
      "+"
      "_______"
      "^^^^^^^^"
      "________________\n");
}