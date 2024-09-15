#include <stdio.h>

#include "../../s21_decimal.h"
#include "../help/s21_decimal_help.h"
#include "../types/s21_int256.h"

int get_first(s21_int256 value) {
  int pos = 0;
  for (int i = INT256_SIZE * INT_SIZE - 1; i > 0 && !pos; --i) {
    if (int256_get_bit(value, i)) {
      pos = i;
    }
  }
  return pos;
}

int get_shift(s21_int256 value) {
  int shifts = 0;
  s21_int256 ten = int256_init_int(10);
  while (get_first(value) >= 96) {
    shifts++;
    value = int256_div(value, ten, NULL);
  }
  return shifts;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = S21_CODE_OK;
  if (result == NULL || !s21_is_correct_decimal(value_1) ||
      !s21_is_correct_decimal(value_2)) {
    code = S21_CODE_CALC_ERROR;
  } else {
    int res_sign = -1;
    if (s21_get_sign(value_1) == s21_get_sign(value_2)) {
      res_sign = 1;
    }

    // делаем оба числа положительными
    s21_set_sign(1, &value_1);
    s21_set_sign(1, &value_2);

    // запоминаем степень чисел
    int pow_1 = s21_get_pow(value_1);
    int pow_2 = s21_get_pow(value_2);

    /// выделили целые числа, которые хранятся внутри decimal
    s21_int256 src1 = int256_init_arr(value_1.bits, 3);
    s21_int256 src2 = int256_init_arr(value_2.bits, 3);

    // перемножение больших чесел без степени
    s21_int256 int_res = int256_mul(src1, src2);

    *result = s21_get_decimal_zero();
    int shifts = get_shift(int_res);
    bool is_shift_less =
        false;  /// было ли уменьшение степени для помещения в decimal
    // установка новой степени
    int res_pow = pow_1 + pow_2 - shifts;
    if (res_pow < 0) {
      code = S21_CODE_INF_POS;
      *result = s21_get_decimal_inf_pos();
    } else {
      s21_int256 ten = int256_init_int(10);

      while (shifts > 28) {
        int_res = int256_div(int_res, ten, NULL);
        --shifts;
      }

      if (res_pow > 28) {
        s21_int256 tmp = int_res;
        int tmp_power = res_pow;
        while (tmp_power > 28) {
          tmp = int256_div(tmp, ten, NULL);
          --tmp_power;
          is_shift_less = true;
        }
        shifts = res_pow - tmp_power + shifts;
        res_pow = tmp_power;
      }
      s21_int256 remainder;
      s21_int256 powerten = int256_init_int(1);
      if (shifts != 0) {
        for (int i = 0; i < shifts; i++) {
          powerten = int256_mul(powerten, ten);
        }
      }
      // Уменьшаем результат, чтобы он поместился в 96бит числа decimal
      // remainder - остаток от деления при этом

      int_res = int256_div(int_res, powerten, &remainder);
      s21_decimal remainder_decmal = s21_from_4int_to_decimal(0, 0, 0, 0);
      int256_to_decimal(remainder, &remainder_decmal);
      // Устанавливаем для остатка степень, чтобы выполнить банковское
      // округление чисел decimal
      s21_set_pow(shifts, &remainder_decmal);
      // Выполняем банковское округления результата, исходя из остатка от
      // деления
      int_res = s21_banking(int_res, remainder_decmal);
      code = int256_to_decimal(int_res, result);
    }
    if (code != S21_CODE_CONVERT_ERROR) {
      s21_decimal zero = s21_get_decimal_zero();
      bool is_one_zero =
          s21_is_equal(zero, value_1) || s21_is_equal(zero, value_2);
      // Устанавливаем степень результата
      if (!result->bits[0] && !result->bits[1] && !result->bits[2] &&
          is_shift_less && !is_one_zero) {
        res_pow = 0;
        code = S21_CODE_INF_NEG;
      }
      s21_set_pow(res_pow, result);
      // установка финального знака
      s21_set_sign(res_sign, result);
    } else if (res_sign == 1)
      *result = s21_get_decimal_inf_pos();
    else {
      code = S21_CODE_INF_NEG;
      *result = s21_get_decimal_inf_neg();
    }
  }
  return code;
}
