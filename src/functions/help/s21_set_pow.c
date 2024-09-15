#include "s21_decimal_help.h"

/**
 * Установка степени
 * @param new_pow новая степень
 * @param dst число для установки
 */
void s21_set_pow(int new_pow, s21_decimal* dst) {
  int mask = 16711680;
  dst->bits[3] &= (~mask);
  new_pow &= (mask >> 16);
  new_pow <<= 16;
  dst->bits[3] |= new_pow;
}