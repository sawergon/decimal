#include "../../s21_decimal.h"
#include "../help/s21_decimal_help.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int code = S21_CODE_OK;
  if (dst == NULL)  /// проверка валидности указателя на результат
  {
    code = S21_CODE_CONVERT_ERROR;
  } else if (!s21_is_correct_decimal(src))  /// проверка валидности decimal
  {
    *dst = 0;
    code = S21_CODE_CONVERT_ERROR;
  } else {
    *dst = 0;
    s21_decimal res =
        s21_get_decimal_zero();  /// результат отбрасывания дробной части
    code = s21_truncate(src, &res);
    int sign = s21_get_sign(res);
    int max_int = -2147483648;
    /// проверка вместимости числа в int
    if (res.bits[1] ||
        res.bits[2] ||  /// число заведомо не входит в int
                        /// число имеет значение больше 2147483647 или меньше
                        /// -2147483648 при этом знак может быть любой
        (s21_get_bit_from_int(res.bits[0], 31) && res.bits[0] != max_int) ||
        /// число в бите 0 имеет значение > 2147483647
        (res.bits[0] == max_int && sign > 0)) {
      code = S21_CODE_CONVERT_ERROR;
    } else {
      *dst = sign * res.bits[0];
    }
  }
  return code;
}