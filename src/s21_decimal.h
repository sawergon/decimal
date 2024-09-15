#ifndef C5_S21_DECIMAL_1_SRC_S21_DECIMAL_H_
#define C5_S21_DECIMAL_1_SRC_S21_DECIMAL_H_

#include <stdbool.h>

/**
 * @mainpage Реализация типа decimal
 * Данный проект представляет реализацию типа decimal
 * @section s1 Представление типа decimal
 * Тип decimal представляется в виде массива из 4 int
 *
 */
/**
 * @file
 * @brief заголовочный файл библиотеки s21_decimal.a
 */
/** @addtogroup error_code Коды ошибок
 * @brief
 * Коды ошибок, которые могут возвращаться при работе: арифметических операций,
 * операций преобразования типа и операций округления
 * @{
 */
/// успешное выполнение операции
#define S21_CODE_OK 0
/// число слишком велико или равно @f$+\infty@f$
#define S21_CODE_INF_POS 1
/// число слишком мало или равно @f$-\infty@f$
#define S21_CODE_INF_NEG 2
/// ошибка деления на 0
#define S21_CODE_DIV_ZERO 3
/// ошибка при конвертации числа
#define S21_CODE_CONVERT_ERROR 1
/// ошибка при округлении числа
#define S21_CODE_CALC_ERROR 1
/** @} */
/// длинна массива в представлении типа {@link s21_decimal}
#define LEN_DECIMAL 4
/**
 * десятичные числа в диапазоне от положительных
 * 79,228,162,514,264,337,593,543,950,335 до отрицательных
 *  79,228,162,514,264,337,593,543,950,335
 * 170,141,183,460,469,231,731,687,303,715,884,105,727
 * 57,896,044,618,658,097,711,785,492,504,343,953,926,634,992,332,820,282,019,728,792,003,956,564,819,967
 *
 */
typedef struct {
  /// массив из int для хранения битов числа типа decimal
  int bits[LEN_DECIMAL];
} s21_decimal;

/**
 * @addtogroup arithmetic Арифметические операции
 * @brief Операции +, -, *, /
 * @{
 */

/**
 * функция для сложения двух чисел типа {@link s21_decimal}
 * @param value_1, value_2 числа для сложения
 * @param result указатель на результат сложения
 * @return  код ошибки {@link error_code}
 */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/**
 * функция разности двух чисел типа {@link s21_decimal}
 * @param value_1, value_2 числа для разности
 * @param result указатель на результат разности
 * @return  код ошибки {@link error_code}
 */
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/**
 * функция произведения двух чисел типа {@link s21_decimal}
 * @param value_1, value_2 числа для произведения
 * @param result указатель на результат произведения
 *
 * @return  код ошибки {@link error_code}
 */
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/**
 * функция частного двух чисел типа {@link s21_decimal}
 * @param value_1, value_2 числа для разности
 * @param result указатель на результат частного
 *
 * @return  код ошибки {@link error_code}
 */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
/// @}

/**
 * @addtogroup compare Операции сравнения
 * @brief Операции <, <=, >, >=, ==, !=
 * @{
 */

/**
 * операция < для типа {@link s21_decimal}
 * @param value_1, value_2 числа для сравнения
 * @return результат сравнения 0 или 1
 */
int s21_is_less(s21_decimal value_1, s21_decimal value_2);

/**
 * операция <= для типа {@link s21_decimal}
 * @param value_1, value_2 числа для сравнения
 * @return результат сравнения 0 или 1
 */
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

/**
 * операция > для типа {@link s21_decimal}
 * @param value_1, value_2 числа для сравнения
 * @return результат сравнения 0 или 1
 */
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);

/**
 * операция >= для типа {@link s21_decimal}
 * @param value_1, value_2 числа для сравнения
 * @return результат сравнения 0 или 1
 */
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);

/**
 * операция == для типа {@link s21_decimal}
 * @param value_1, value_2 числа для сравнения
 * @return результат сравнения 0 или 1
 */
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);

/**
 * операция != для типа {@link s21_decimal}
 * @param value_1, value_2 числа для сравнения
 * @return результат сравнения 0 или 1
 */
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
/// @}

/**
 * @addtogroup convert Операции преобразования типа
 *
 * @{
 */

/**
 * Преобразование из int в {@link s21_decimal}
 * @param src число для преобразования
 * @param dst указатель на результат преобразования
 *
 * @return код ошибки {@link error_code}
 */
int s21_from_int_to_decimal(int src, s21_decimal *dst);

/**
 * Преобразование из float в {@link s21_decimal}
 * @param src число для преобразования
 * @param dst указатель на результат преобразования
 *
 * @return код ошибки {@link error_code}
 */
int s21_from_float_to_decimal(float src, s21_decimal *dst);

/**
 * Преобразование из {@link s21_decimal} в int
 * @param src число для преобразования
 * @param dst указатель на результат преобразования
 *
 * @return код ошибки {@link error_code}
 */
int s21_from_decimal_to_int(s21_decimal src, int *dst);

/**
 * Преобразование из {@link s21_decimal} в float
 * @param src число для преобразования
 * @param dst указатель на результат преобразования
 *
 * @return код ошибки {@link error_code}
 */
int s21_from_decimal_to_float(s21_decimal src, float *dst);
/// @}

/**
 * @addtogroup round Операции округления, смены знака, отбрасывания 0
 * @{
 */

/**
 * Округление вниз в сторону @f$-\infty@f$
 * @param value число для округления тип {@link s21_decimal}
 * @param result указатель на результат округления тип *{@link s21_decimal}
 *
 * @return код ошибки {@link error_code}
 */
int s21_floor(s21_decimal value, s21_decimal *result);

/**
 * Округление до ближайшего целого
 * @param value число для округления тип {@link s21_decimal}
 * @param result указатель на результат округления тип *{@link s21_decimal}
 *
 * @return код ошибки {@link error_code}
 */
int s21_round(s21_decimal value, s21_decimal *result);

/**
 * Отбрасывание дробной части
 * @param value число для отбрасывания тип {@link s21_decimal}
 * @param result указатель на результат отбрасывания тип *{@link s21_decimal}
 *
 * @return код ошибки {@link error_code}
 */
int s21_truncate(s21_decimal value, s21_decimal *result);

/**
 * Смена знака
 * @param value число для смены знака тип {@link s21_decimal}
 * @param result указатель на результат смены знака тип *{@link s21_decimal}
 *
 * @return код ошибки {@link error_code}
 */
int s21_negate(s21_decimal value, s21_decimal *result);
/// @}
#endif  // C5_S21_DECIMAL_1_SRC_S21_DECIMAL_H_
