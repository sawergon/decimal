#include <math.h>

#include "../../s21_decimal.h"
#include "../help/s21_decimal_help.h"
#include "../types/s21_int256.h"

/**
 * получение степени 10 для успешного приведения decimal к int256
 * @param val число для приведения
 * @param ten_pow 10^x число на которое нужно поделить исходное число
 * @return степень х, в которую надо возвести 10 для успешного перевода
 */
int get_shifts(s21_int256 val, s21_int256 *ten_pow);

void help_add(s21_int256 *src1, s21_int256 *src2, s21_decimal value_1,
              s21_decimal value_2, int power1, int power2);

/**
 * 7.9999
 *
 * суть алгоритма.
 * ВХОД: два числа типа децимал
 * 1) получить степени этих чисел
 * 2) привести их домножением на 10 к максимальной
 * 3) сложить
 * 4) вычислить новую степень при этом убрав незначащие нули
 * 5) выдать полученный результат
 * @param value_1
 * @param value_2
 * @param result
 * @return
 */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = S21_CODE_OK;
  if (result == NULL || !s21_is_correct_decimal(value_1) ||
      !s21_is_correct_decimal(value_2)) {
    code = S21_CODE_CALC_ERROR;
  } else {
    s21_int256 src1 = int256_init_arr(value_1.bits, 3),
               src2 = int256_init_arr(value_2.bits, 3);
    int power1 = s21_get_pow(value_1), power2 = s21_get_pow(value_2),
        max_pow = fmax(power1, power2);
    help_add(&src1, &src2, value_1, value_2, power1, power2);
    s21_int256 int_res = int256_sum(src1, src2);
    int sign = int256_get_sign(int_res);
    if (sign) {
      int256_negate(&int_res);
    }
    s21_int256 ten_pow = int256_init();
    int shifts = get_shifts(int_res, &ten_pow);  /// получение сдвига
    s21_int256 rem = int256_init();
    int_res = int256_div(int_res, ten_pow, &rem);  /// приведение по 10^x
    s21_decimal remain =
        s21_get_decimal_zero();  /// преобразуем остаток в decimal
    int256_to_decimal(rem, &remain);
    s21_set_pow(shifts, &remain);
    int_res =
        s21_banking(int_res, remain);  /// банковское округление целой части
    *result = s21_get_decimal_zero();
    code = int256_to_decimal(int_res, result);  /// преобразование целой части
    int new_pow = max_pow - shifts;
    s21_set_pow(new_pow, result);         /// установка степени
    s21_set_sign(sign ? -1 : 1, result);  /// установка знака
    if (0 > new_pow || new_pow > 28 || code == S21_CODE_CONVERT_ERROR) {
      if (sign) {
        code = S21_CODE_INF_NEG;
        *result = s21_get_decimal_inf_neg();
      } else {
        code = S21_CODE_INF_POS;
        *result = s21_get_decimal_inf_pos();
      }
    }
  }
  return code;
}

void help_add(s21_int256 *src1, s21_int256 *src2, s21_decimal value_1,
              s21_decimal value_2, int power1, int power2) {
  int max_pow = fmax(power1, power2);
  s21_int256 int256_ten = int256_init_int(10);
  if (s21_get_sign(value_1) < 0) {  /// устанавливаем правильные знаки
    int256_negate(src1);
  }
  if (s21_get_sign(value_2) < 0) {
    int256_negate(src2);
  }
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

int get_shifts(s21_int256 val, s21_int256 *ten_pow) {
  int shifts = 0;
  s21_int256 int256_ten = int256_init_int(10);
  *ten_pow = int256_init_int(1);
  s21_int256 src = int256_copy(val);
  while (src.bits[3] || src.bits[4] || src.bits[5] || src.bits[6] ||
         src.bits[7]) {
    *ten_pow = int256_mul(*ten_pow, int256_ten);
    src = int256_div(val, *ten_pow, NULL);
    shifts++;
  }
  return shifts;
}
