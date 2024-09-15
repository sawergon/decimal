#include "../../s21_decimal.h"
#include "../types/s21_int256.h"
#include "s21_decimal_help.h"

int s21_decimal_mod_2(s21_int256 val) { return (val.bits[0] & 1) != 1; }

s21_int256 s21_banking(s21_int256 integral, s21_decimal fractional) {
  s21_decimal zerofive = {{0x5, 0, 0, 0x10000}};
  s21_int256 one = int256_init_int(1);
  s21_int256 result;

  if (s21_is_equal(fractional, zerofive)) {
    // Если дробная часть ровно 0.5
    if (s21_decimal_mod_2(integral)) {
      // Если целая часть четная, то оставляем её
      result = int256_copy(integral);
    } else {
      // Если целая часть нечетная, то увеличиваем её на 1
      result = int256_sum(integral, one);
    }
  } else if (s21_is_greater(fractional, zerofive)) {
    // Если дробная часть > 0.5, то увеличиваем целую часть на 1
    result = int256_sum(integral, one);
  } else {
    // Если дробная часть < 0.5, то оставляем целую часть без изменений
    result = integral;
  }

  return result;
}