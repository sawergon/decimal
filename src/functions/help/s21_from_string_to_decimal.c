#include <string.h>

#include "s21_decimal_help.h"

int convert(char ch) { return ch == '1' ? 1 : 0; }

s21_decimal s21_from_string_to_decimal(char* str) {
  s21_decimal res = {{0, 0, 0, 0}};
  if (strlen(str) == 128) {
    int a0 = 0, a1 = 0, a2 = 0, a3 = 0;
    for (int i = 0; i < 32; ++i) {
      a0 <<= 1;
      a1 <<= 1;
      a2 <<= 1;
      a3 <<= 1;
      a0 |= convert(str[i]);
      a1 |= convert(str[i + 32]);
      a2 |= convert(str[i + 64]);
      a3 |= convert(str[i + 96]);
    }
    res = s21_from_4int_to_decimal(a0, a1, a2, a3);
  }
  return res;
}