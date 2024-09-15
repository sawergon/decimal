#include "s21_int256.h"

#include "stdlib.h"

s21_int256 int256_init() {
  s21_int256 a = {{0, 0, 0, 0, 0, 0, 0, 0}};
  return a;
}

s21_int256 int256_get_minus_1() {
  s21_int256 a = {{-1, -1, -1, -1, -1, -1, -1, -1}};
  return a;
}

s21_int256 int256_init_arr(const int *arr, int len) {
  s21_int256 a = int256_init();
  if (0 < len && len < 9) {
    for (int i = 0; i < len; ++i) {
      a.bits[i] = arr[i];
    }
  }
  return a;
}

s21_int256 int256_init_int(int val) {
  s21_int256 result = int256_init();
  int neg = val < 0;
  if (neg) {
    val = ~val;
    val += 1;
  }
  result.bits[0] = val;
  if (neg) {
    int256_negate(&result);
  }
  return result;
}

s21_int256 int256_sum(s21_int256 value_1, s21_int256 value_2) {
  s21_int256 result = int256_init();
  /// bit значение бита для установки
  /// first значение итого бита в первом числе
  /// second значение итого бита во втором числе
  /// move значение переноса разряда, например, при сложение двух единиц
  int bit, first, second, move = 0;
  for (int i = 0; i < INT256_SIZE * INT_SIZE; ++i) {
    first = int256_get_bit(value_1, i);
    second = int256_get_bit(value_2, i);
    bit = first ^ second ^ move;
    move = (first & second) | (first & move) | (second & move);
    int256_set_bit(&result, i, bit);
  }
  return result;
}

int int256_get_bit(s21_int256 value, int pos) {
  int result = -1;
  int bit_number = pos / INT_SIZE;
  pos = pos % INT_SIZE;
  if (bit_number < INT256_SIZE) {
    result = (value.bits[bit_number] >> pos) & 1;
  }
  return result;
}

void int256_set_bit(s21_int256 *value, int pos, int bit) {
  int bit_number = pos / INT_SIZE;
  pos = pos % INT_SIZE;
  int mask = 1 << pos;
  if (!bit) {
    mask = ~mask;
    value->bits[bit_number] &= mask;
  } else {
    value->bits[bit_number] |= mask;
  }
}

int int256_get_sign(s21_int256 value) {
  int mask = -2147483648;
  return (value.bits[7] & mask) != 0;
}

void int256_inverse(s21_int256 *value) {
  value->bits[0] = ~value->bits[0];
  value->bits[1] = ~value->bits[1];
  value->bits[2] = ~value->bits[2];
  value->bits[3] = ~value->bits[3];
  value->bits[4] = ~value->bits[4];
  value->bits[5] = ~value->bits[5];
  value->bits[6] = ~value->bits[6];
  value->bits[7] = ~value->bits[7];
}

void int256_negate(s21_int256 *value) {
  if (int256_get_sign(*value)) {
    s21_int256 int256_1 = int256_init();
    int256_1.bits[0] = 1;
    int256_inverse(value);
    *value = int256_sum(*value, int256_1);
  } else {
    s21_int256 int256_minus_1 = int256_get_minus_1();
    *value = int256_sum(*value, int256_minus_1);
    int256_inverse(value);
  }
}

s21_int256 int256_sub(s21_int256 value_1, s21_int256 value_2) {
  int256_negate(&value_2);
  return int256_sum(value_1, value_2);
}

s21_int256 int256_copy(s21_int256 value) {
  s21_int256 result = int256_init();
  result.bits[0] = value.bits[0];
  result.bits[1] = value.bits[1];
  result.bits[2] = value.bits[2];
  result.bits[3] = value.bits[3];
  result.bits[4] = value.bits[4];
  result.bits[5] = value.bits[5];
  result.bits[6] = value.bits[6];
  result.bits[7] = value.bits[7];
  return result;
}

s21_int256 int256_shift_left_once(s21_int256 value) {
  for (int i = INT256_SIZE - 1; i > 0; --i) {
    value.bits[i] <<= 1;
    int256_set_bit(&value, i * INT_SIZE,
                   int256_get_bit(value, i * INT_SIZE - 1));
  }
  value.bits[0] <<= 1;
  return value;
}

s21_int256 int256_shift_left(s21_int256 value, int times) {
  for (int i = 0; i < times; ++i) {
    value = int256_shift_left_once(value);
  }
  return value;
}

s21_int256 int256_shift_right_once(s21_int256 value) {
  for (int i = 1; i < INT256_SIZE; ++i) {
    value.bits[i - 1] >>= 1;
    int256_set_bit(&value, i * INT_SIZE - 1,
                   int256_get_bit(value, i * INT_SIZE));
  }
  value.bits[7] >>= 1;
  return value;
}

s21_int256 int256_shift_right(s21_int256 value, int times) {
  for (int i = 0; i < times; ++i) {
    value = int256_shift_right_once(value);
  }
  return value;
}

void int256_show(s21_int256 value) {
  for (int i = INT256_SIZE - 1; i >= 0; --i) {
    s21_print_bits_int(value.bits[i]);
  }
  printf("\n");
}

/**
 * @brief Получение знака после умножения или деления
 * @details При делении или умножении удобнее работать с положительными числами
 * поэтому с помощью этой функции делаем числа положительными и возвращаем
 * произведение их знаков между собой
 * @param value_1 первой число
 * @param value_2 второе число
 * @return получился ли знак отрицательным после произведения или деления
 */
bool make_two_pos(s21_int256 *value_1, s21_int256 *value_2) {
  int sign_1 = int256_get_sign(*value_1), sign_2 = int256_get_sign(*value_2);
  bool is_neg = false;
  if (sign_1 && sign_2) {
    int256_negate(value_1);
    int256_negate(value_2);
  } else if (sign_1) {
    is_neg = true;
    int256_negate(value_1);
  } else if (sign_2) {
    is_neg = true;
    int256_negate(value_2);
  }
  return is_neg;
}

s21_int256 int256_mul(s21_int256 value_1, s21_int256 value_2) {
  s21_int256 result = int256_init();
  bool is_neg = make_two_pos(&value_1, &value_2);
  for (int i = 0; i < INT256_SIZE * INT_SIZE; ++i) {
    if (int256_get_bit(value_2, i)) {
      result = int256_sum(result, value_1);
    }
    value_1 = int256_shift_left(value_1, 1);
  }
  if (is_neg) {
    int256_negate(&result);
  }
  return result;
}

bool int256_is_zero(s21_int256 value) {
  bool result = true;
  for (int i = 0; i < INT256_SIZE && result; ++i) {
    if (value.bits[i] != 0) {
      result = false;
    }
  }
  return result;
}
/**
 * получение первой значащей единицы
 * @param value
 * @return позиция первой значащей единицы 0..255
 */
int get_first_one(s21_int256 value) {
  int pos = 0;
  for (int i = INT256_SIZE * INT_SIZE - 1; i > 0 && !pos; --i) {
    if (int256_get_bit(value, i)) {
      pos = i;
    }
  }
  return pos;
}

s21_int256 int256_div(s21_int256 value_1, s21_int256 value_2,
                      s21_int256 *remainder) {
  s21_int256 result = int256_init();
  bool is_neg = make_two_pos(&value_1, &value_2);
  int first_one = get_first_one(value_1);
  int second_one = get_first_one(value_2);
  int shift = abs(first_one - second_one);
  value_2 = int256_shift_left(value_2, shift);
  int i = 0;
  do {
    if (!int256_get_sign(value_1)) {
      value_1 = int256_sub(value_1, value_2);
    } else {
      value_1 = int256_sum(value_1, value_2);
    }
    if (i != shift) {
      value_1 = int256_shift_left_once(value_1);
    }
    result = int256_shift_left_once(result);
    if (!int256_get_sign(value_1)) {
      int256_set_bit(&result, 0, 1);
    }
    i++;
  } while (i <= shift);
  if (remainder) {
    *remainder = int256_copy(value_1);
    if (int256_get_sign(*remainder)) {
      *remainder = int256_sum(*remainder, value_2);
    }
    *remainder = int256_shift_right(*remainder, shift);
  }
  if (is_neg) {
    int256_negate(remainder);
    int256_negate(&result);
  }
  return result;
}

s21_int256 clear_right_zeros(s21_int256 value, int *quantity) {
  if (int256_is_zero(value)) {
    *quantity = 0;
  } else {
    s21_int256 remainder = int256_init();
    *quantity = 0;
    s21_int256 int256_ten = int256_init_int(10);
    s21_int256 main_part = int256_div(value, int256_ten, &remainder);
    while (int256_is_zero(remainder)) {
      (*quantity)++;
      value = main_part;
      main_part = int256_div(value, int256_ten, &remainder);
    }
  }
  return value;
}

int int256_to_decimal(s21_int256 src, s21_decimal *dst) {
  int sign = int256_get_sign(src), code = S21_CODE_OK;
  if (src.bits[3] || src.bits[4] || src.bits[5] || src.bits[6] || src.bits[7]) {
    code = S21_CODE_CONVERT_ERROR;
  } else {
    if (sign) {
      int256_negate(&src);
    }
    dst->bits[0] = src.bits[0];
    dst->bits[1] = src.bits[1];
    dst->bits[2] = src.bits[2];
    s21_set_sign(sign ? -1 : 1, dst);
  }
  return code;
}

bool int256_is_equal(s21_int256 val_1, s21_int256 val_2) {
  return val_1.bits[0] == val_2.bits[0] && val_1.bits[1] == val_2.bits[1] &&
         val_1.bits[2] == val_2.bits[2] && val_1.bits[3] == val_2.bits[3] &&
         val_1.bits[4] == val_2.bits[4] && val_1.bits[5] == val_2.bits[5] &&
         val_1.bits[6] == val_2.bits[6] && val_1.bits[7] == val_2.bits[7];
}

bool int256_is_greater(s21_int256 val_1, s21_int256 val_2) {
  bool compare_result = false;  /// результат сравнения
  for (int i = INT256_SIZE - 1; i >= 0; --i) {
    if ((unsigned int)val_1.bits[i] > (unsigned int)val_2.bits[i]) {
      compare_result = true;
      i = -1;
    } else if ((unsigned int)val_1.bits[i] < (unsigned int)val_2.bits[i]) {
      compare_result = false;
      i = -1;
    }
  }
  return compare_result;
}

void help_normalize_pow(int differ, s21_int256 *val_1, s21_int256 val_2) {
  for (int i = 0; i < differ; ++i) {
    *val_1 = int256_mul(*val_1, val_2);
  }
}

void int256_normalize_pow(s21_int256 *src1, s21_int256 *src2, s21_decimal dec1,
                          s21_decimal dec2) {
  *src1 = int256_init_arr(dec1.bits, 3);
  *src2 = int256_init_arr(dec2.bits, 3);
  int power1 = s21_get_pow(dec1), power2 = s21_get_pow(dec2);
  s21_int256 int256_ten = int256_init_int(10);
  if (power1 < power2) {
    help_normalize_pow(power2 - power1, src1, int256_ten);
  } else {
    help_normalize_pow(power1 - power2, src2, int256_ten);
  }
}