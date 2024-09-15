#include "s21_decimal_help.h"

void s21_set_bit_in_int(int *inti, int index, int value) {
  int change = s21_get_bit_from_int(*inti, index);
  if (!(change == value)) {
    if (change == 1) {
      *inti = (*inti) & (~(1 << index));
    } else {
      *inti = (*inti) | (1 << index);
    }
  }
}