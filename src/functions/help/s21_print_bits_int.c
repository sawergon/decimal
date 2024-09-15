#include "s21_decimal_help.h"
/**
 * @file
 * @brief реализация вывода на экран целого числа
 */
/**
 * рекурсивная функция для вывода на экран битовое представление int
 * @param value число для перевода
 * @param mask маска для вычисления значения бита
 * @param move сдвиг маски относительно начала числа
 */
void help_print_bits(unsigned int value, unsigned int mask, int move) {
  if (mask != 0) {
    help_print_bits(value, mask << 1, move + 1);
    printf("%d", (value & mask) >> move);
  }
}

void s21_print_bits_int(int value) { help_print_bits(value, 1, 0); }