#ifndef C5_S21_DECIMAL_1_SRC_FUNCTIONS_TYPES_S21_INT256_H_
#define C5_S21_DECIMAL_1_SRC_FUNCTIONS_TYPES_S21_INT256_H_
/**
 * @file
 * @brief заголовочный файл для типа int256
 * @addtogroup int256 функции для типа int256
 * @details
 * функции представленные здесь, являются реализацией типа int256. присутствуют
 * основные математические операции и некоторые логические операции. также есть
 * несколько конструкторов и конвертеров
 * @{
 */

#include <stdbool.h>
#include <stdio.h>

#define INT256_SIZE 8  /// размер массива в представлении int256
#define INT_SIZE 32  /// размер типа int

/**
 * Целый тип размером в 256 битов
 */
typedef struct {
  int bits[INT256_SIZE];
} s21_int256;
#include "../help/s21_decimal_help.h"
/**
 * инициализация нулями
 * @return нулевое значение
 */
s21_int256 int256_init();

/**
 * инициализация из массива
 * @param arr массив для инициализации
 * @param len длинна массива < 8
 * @return значение типа int256
 */
s21_int256 int256_init_arr(const int *arr, int len);

/**
 * преобразование из int в int256
 * @param val значение для преобразования
 * @return результат преобразования тип int256
 */
s21_int256 int256_init_int(int val);

/**
 * сложение двух чисел типа int256
 * @warning не предполагается переполнение
 * @param value_1 первое слагаемое
 * @param value_2 второе славгаемое
 * @return сумма
 */
s21_int256 int256_sum(s21_int256 value_1, s21_int256 value_2);

/**
 * получение бита по позиции
 * @param value число для взятие бита
 * @param pos позиция
 * @return значение бита
 */
int int256_get_bit(s21_int256 value, int pos);

/**
 * Установка юита в заданную позицию
 * @param value число для установки бита
 * @param pos позиция
 * @param bit значение устанавливаемого бита
 */
void int256_set_bit(s21_int256 *value, int pos, int bit);

/**
 * смена знака
 * @param value указатель на число для смены знака
 * @warning нет проверки на существование
 */
void int256_negate(s21_int256 *value);

/**
 * инвертирование битов числа
 * @param value число для инвертирования
 * @warning нет проверки на существование
 */
void int256_inverse(s21_int256 *value);

/**
 * получение знака числа
 * @param value
 * @return знак в формате 1 - отрицательное, 0 - положительное
 */
int int256_get_sign(s21_int256 value);

/**
 * разность двух чисел
 * @param value_1
 * @param value_2
 * @return разность
 */
s21_int256 int256_sub(s21_int256 value_1, s21_int256 value_2);

/**
 * Функция копирования числа, при этом создается новое число
 * @param value число для копирования
 * @return результат копирования
 */
s21_int256 int256_copy(s21_int256 value);

/**
 * сдвиг битов числа в право
 * @param value число для сдвига
 * @param times значение сдвига 0..255
 * @return число после сдвига
 */
s21_int256 int256_shift_right(s21_int256 value, int times);

/**
 * сдвиг битов числа в лево
 * @param value число для сдвига
 * @param times значение сдвига 0..255
 * @return число после сдвига
 */
s21_int256 int256_shift_left(s21_int256 value, int times);

/**
 * Вывод битового представления числа на экран
 * @param value число для вывода
 */
void int256_show(s21_int256 value);

/**
 * произведение двух чисел
 * @param value_1
 * @param value_2
 * @return результат произведения
 */
s21_int256 int256_mul(s21_int256 value_1, s21_int256 value_2);

/**
 * Функция проверки на равенство 0
 * @param value
 * @return результат сравнения
 */
bool int256_is_zero(s21_int256 value);

/**
 * деление двух знаковых чисел
 * @param value_1
 * @param value_2
 * @param remainder остаток от деления
 * @return целая часть деления
 * @warning нет проверки деление на 0. функция не ломается, но результат
 * становиться неопределенным
 */
s21_int256 int256_div(s21_int256 value_1, s21_int256 value_2,
                      s21_int256 *remainder);

/**
 * очистка и подсчет нулей с права на лево
 * @param value число для подсчета
 * @param quantity кол-во нулей
 * @return число без нулей справа
 */
s21_int256 clear_right_zeros(s21_int256 value, int *quantity);

/**
 * преобразование из int256 в decial
 * @param src число для преобразования
 * @param dst число после преобразования
 * @return код ошибки. переполнение
 */
int int256_to_decimal(s21_int256 src, s21_decimal *dst);

/**
 * операция сравнения ==
 * @param val_1
 * @param val_2
 * @return результат сравнения
 */
bool int256_is_equal(s21_int256 val_1, s21_int256 val_2);

/**
 * val_1 > val_2 ?
 * @param val_1
 * @param val_2
 * @return результат сравнения
 */
bool int256_is_greater(s21_int256 val_1, s21_int256 val_2);

/**
 * @brief приведение двух чисел decimal к одной степени целой части, путем
 * домножения на 10
 * @details
 * пример:
 * целая часть: a1=120, a2 = 1200
 * степень: p1=1, p2=2
 * эти значения представляют два числа n1=12.0 n2=12.00
 * результат: src1=1200 src2=1200
 *
 * @param src1 приведенное первое число
 * @param src2 приведенное второе число
 * @param dec1 первое число в формате decimal
 * @param dec2 второе число в формате decimal
 */
void int256_normalize_pow(s21_int256 *src1, s21_int256 *src2, s21_decimal dec1,
                          s21_decimal dec2);
///@}

#endif  // C5_S21_DECIMAL_1_SRC_FUNCTIONS_TYPES_S21_INT256_H_
