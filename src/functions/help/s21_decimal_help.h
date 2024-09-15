#ifndef C5_S21_DECIMAL_1_SRC_FUNCTIONS_HELP_S21_DECIMAL_HELP_H_
#define C5_S21_DECIMAL_1_SRC_FUNCTIONS_HELP_S21_DECIMAL_HELP_H_

#include <stdio.h>
#include "../../s21_decimal.h"
#include "../types/s21_int256.h"

/**
 * @file
 * @brief заголовочный файл для вспомогательных функций библиотеки s21_decimal.a
 * @addtogroup help Вспомогательные функции
 * @details
 * функции представленные здесь, не являются частью задания, но существенно
 * упрощают отладку и работу с основными функциями
 * @{
 */

/**
 * выводит int в битовой форме
 * @param[in] value число для перевода
 */
void s21_print_bits_int(int value);

/**
 * выводит float в битовой форме
 * @param value число для перевода
 */
void s21_print_bits_float(float value);

/**
 * выводит decimal в битовой форме
 * @param[in] value тип {@link s21_decimal}
 */
void s21_print_bits_decimal(s21_decimal value);

/**
 * Проверка на корректную запись decimal
 * @details
 * корректно, если
 * <ul>
 *   <li>bits[3] биты от 0 до 15 равны 0</li>
 *   <li>bits[3] биты с 16 по 23 содержат степень 0..28</li>
 *   <li>bits[3] биты с 24 по 30 равны 0</li>
 * </ul>
 * @param value число для проверки
 * @return true/false верная ли запись
 */
bool s21_is_correct_decimal(s21_decimal value);

/**
 * Возвращает показатель степени от 0 до 28, который указывает степень 10 для
 * разделения целого числа
 * @param value число для взятия показателя степени
 * @return показатель степени
 */
int s21_get_pow(s21_decimal value);

/**
 * Возвращает знак числа decimal
 * @param value число для получения знака
 * @return -1 или 1 знак числа
 */
int s21_get_sign(s21_decimal value);

/**
 * Возвращает значение указанного бита decimal
 * @param value число для получения значение указанного бита
 * @param index индекс бита
 * @return 0 или 1 значение бита
 */
int s21_get_bit_from_int(int value, int index);

/**
 * Меняет значаение указанного бита
 * @param inti число, в котором будет произведена замена
 * @param index индекс бита
 * @param value значение
 */
void s21_set_bit_in_int(int *inti, int index, int value);

/**
 * Удаление незначащих нулей
 *
 * Пример:
 * 1.00000   1
 * 1.04500   1.045
 * 100.00    100
 * @param value
 * @return успешность удаления нулей
 */
void s21_clear_zeros(s21_decimal value);

/**
 * Получение значения бита в decimal в позиции pos
 * @param value число
 * @param pos позиция
 * @return значение бита
 */
int s21_get_bit_from_decimal(s21_decimal value, int pos);

void s21_set_pow(int new_pow, s21_decimal* dst);

void s21_set_sign(int sign, s21_decimal* dst);

/**
 * банковское округление
 * @param integral целая часть
 * @param fractional дробная часть
 * @return результат округления
 */
s21_int256 s21_banking(s21_int256 integral, s21_decimal fractional);

void s21_set_bit_in_int(int* inti, int index, int value);

int s21_get_bit_from_int(int value, int index);
/**
 * @}
 */

/**
 * @addtogroup constructors Конструкторы decimal
 * @details
 * конструирование decimal из сложных структур: массив, строка и тд.
 * @{
 */
/**
 * получение decimal из одной строки
 * @param str строка для конвертирования, состоящая из 0 и 1
 * @return decimal
 */
s21_decimal s21_from_string_to_decimal(char* str);

/**
 * Построение decimal из 4 чисел типа int
 * @param a0, a1, a2, a3 числа для построения
 * @return число типа {@link s21_decimal}
 */
s21_decimal s21_from_4int_to_decimal(int a0, int a1, int a2, int a3);

/**
 * Получение нуля
 * @return 0
 */
s21_decimal s21_get_decimal_zero();

/**
 * Получение положительной бесконечности
 * @return
 */
s21_decimal s21_get_decimal_inf_pos();

/**
 * Получение отрицательной бесконечности
 * @return
 */
s21_decimal s21_get_decimal_inf_neg();
///@}
#endif  // C5_S21_DECIMAL_1_SRC_FUNCTIONS_HELP_S21_DECIMAL_HELP_H_
