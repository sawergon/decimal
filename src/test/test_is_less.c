#include "test_runner.h"

START_TEST(fail1) {
  s21_decimal decimal1 = s21_from_4int_to_decimal(0, 0, 0, 1);
  s21_decimal decimal2 = s21_from_4int_to_decimal(0, 0, 0, 0);
  int code = s21_is_less(decimal1, decimal2);
  ck_assert_int_eq(0, code);
}
END_TEST

START_TEST(fail2) {
  s21_decimal decimal1 = s21_from_4int_to_decimal(0, 0xFFFFFFFF, 0xFFFFFFFF, 0);
  s21_decimal decimal2 =
      s21_from_4int_to_decimal(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
  int code = s21_is_less(decimal1, decimal2);
  ck_assert_int_eq(0, code);
}
END_TEST

START_TEST(ok1) {
  s21_decimal decimal1 = s21_from_4int_to_decimal(0, 0xFFFFFFFF, 0xFFFFFFFF, 0);
  s21_decimal decimal2 = s21_from_4int_to_decimal(1, 0xFFFFFFFF, 0, 0);
  int code = s21_is_less(decimal1, decimal2);
  ck_assert_int_eq(0, code);
}
END_TEST

START_TEST(ok2) {
  s21_decimal decimal1 = s21_from_4int_to_decimal(1, 0xFFFFFFFF, 0, 0);
  s21_decimal decimal2 = s21_from_4int_to_decimal(1, 0xFFFFFFFF, 0, 0);
  s21_set_sign(-1, &decimal2);
  int code = s21_is_less(decimal1, decimal2);
  ck_assert_int_eq(0, code);
}
END_TEST

START_TEST(ok3) {
  s21_decimal decimal1 = s21_from_4int_to_decimal(1, 0xFFFFFFFF, 0, 0);
  s21_decimal decimal2 = s21_from_4int_to_decimal(1, 0xFFFFFFFF, 0, 0);
  int code = s21_is_less(decimal1, decimal2);
  ck_assert_int_eq(0, code);
}
END_TEST

Suite *s21_is_less_cases(void) {
  Suite *suite = suite_create("s21_is_less_cases");
  TCase *tc = tcase_create("d_to_f_tc");

  /// краевые случаи
  tcase_add_test(tc, ok1);
  tcase_add_test(tc, ok2);
  tcase_add_test(tc, ok3);
  tcase_add_test(tc, fail1);
  tcase_add_test(tc, fail2);

  suite_add_tcase(suite, tc);
  return suite;
}
