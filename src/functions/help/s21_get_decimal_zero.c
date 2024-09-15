#include "s21_decimal_help.h"

s21_decimal s21_get_decimal_zero() {
  s21_decimal res = {{0, 0, 0, 0}};
  return res;
}

s21_decimal s21_get_decimal_inf_pos() {
  s21_decimal res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  return res;
}

s21_decimal s21_get_decimal_inf_neg() {
  s21_decimal res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  return res;
}