#include <math.h>

#include "../../s21_decimal.h"
#include "../help/s21_decimal_help.h"
#include "../types/s21_int256.h"

void help_div(s21_int256 *src1, s21_int256 *src2, int power1, int power2);

bool from_3_to_7_zero(s21_int256 val) {
  return !val.bits[3] && !val.bits[4] && !val.bits[5] && !val.bits[6] &&
         !val.bits[7];
}

s21_int256 get_fractional(s21_int256 prev_res, s21_int256 rem, s21_int256 del,
                          int *shift);
/**
 *
 * 1   10 res 2 move 0
 * 0.5  5
 *
 * 10   1000 res 200 move 0
 * 0.05    5
 *
 * 10   1000 res 40 move 0
 * 0.25   25
 *
 * 10  100
 * 1.5  15
 *
 * 0.5 5 res 1 move 0
 * 0.5 5
 *
 * 0.25 25 res
 * 0.5  50
 * @param value_1
 * @param value_2
 * @param result
 * @return
 */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = S21_CODE_OK;
  if (result == NULL || !s21_is_correct_decimal(value_1) ||
      !s21_is_correct_decimal(value_2)) {
    code = S21_CODE_CALC_ERROR;
  } else if (s21_is_equal(value_2, s21_get_decimal_zero())) {
    code = S21_CODE_DIV_ZERO;
    *result = s21_get_decimal_inf_pos();
  } else {
    int power1 = s21_get_pow(value_1), power2 = s21_get_pow(value_2),
        sign1 = s21_get_sign(value_1), sign2 = s21_get_sign(value_2);
    s21_int256 src1 = int256_init_arr(value_1.bits, 3),
               src2 = int256_init_arr(value_2.bits, 3);
    help_div(&src1, &src2, power1, power2);
    s21_int256 rem = int256_init();
    s21_int256 int_res = int256_div(src1, src2, &rem);
    s21_decimal res = s21_get_decimal_zero();
    int shift = 0;
    if (!int256_is_zero(rem)) {
      int_res = get_fractional(int_res, rem, src2, &shift);
    }
    if (!from_3_to_7_zero(int_res) ||
        (s21_is_not_equal(value_1, s21_get_decimal_zero()) &&
         int256_is_zero(int_res))) {
      if (sign1 == sign2) {
        code = S21_CODE_INF_POS;
        *result = s21_get_decimal_inf_pos();
      } else {
        code = S21_CODE_INF_NEG;
        *result = s21_get_decimal_inf_neg();
      }
    }
    int256_to_decimal(int_res, &res);
    if (sign1 != sign2) {
      s21_set_sign(-1, &res);
    }
    s21_set_pow(shift, &res);
    *result = res;
  }
  return code;
}

/**
 * вычислим дробную часть по методу дополнения
 * будем умножать остаток на 10 так, чтобы он был больше делителя
 * поделим и получим первый знак дробной части
 * добавим его к уже известной целой части и увеличим число сдвигов
 * повторяем пока число сдвигов меньше 28(предел decimal) или
 * остаток не равен 0(число поделилось нацело)
 * также будем держать биты с 3 по 7 в prev_res нулевыми, для того, чтобы
 * вместилось в decimal
 * @param rem остаток от предыдущего деления
 * @param del делитель
 * @param shift число сдвигов
 * @return целая часть decimal но в int_256
 */
s21_int256 get_fractional(s21_int256 prev_res, s21_int256 rem, s21_int256 del,
                          int *shift) {
  s21_int256 ten = int256_init_int(10);
  s21_int256 fractional_digit = int256_init();
  while (!int256_is_zero(rem) && *shift < 28 && from_3_to_7_zero(prev_res)) {
    rem = int256_mul(rem, ten);
    prev_res = int256_mul(prev_res, ten);
    (*shift)++;
    if (!int256_is_greater(del, rem)) {
      fractional_digit = int256_div(rem, del, &rem);
      prev_res = int256_sum(prev_res, fractional_digit);
    }
  }
  if (!from_3_to_7_zero(prev_res)) {
    prev_res = int256_div(prev_res, ten, NULL);
    (*shift)--;
  }
  return prev_res;
}

void help_div(s21_int256 *src1, s21_int256 *src2, int power1, int power2) {
  int max_pow = fmax(power1, power2);
  s21_int256 int256_ten = int256_init_int(10);
  if (power1 == max_pow) {  /// преобразуем к наибольшей степени
    for (int i = 0; i < power1 - power2; i++) {
      *src2 = int256_mul(*src2, int256_ten);
    }
  } else {
    for (int i = 0; i < power2 - power1; i++) {
      *src1 = int256_mul(*src1, int256_ten);
    }
  }
}