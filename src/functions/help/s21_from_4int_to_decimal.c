#include "s21_decimal_help.h"

s21_decimal s21_from_4int_to_decimal(int a0, int a1, int a2, int a3) {
  s21_decimal res = {{a0, a1, a2, a3}};
  return res;
}