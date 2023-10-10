#include <check.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

START_TEST(to_upper_1) {
  char *str = "amor28";
  char *str_s21 = (char *)s21_to_upper(str);
  ck_assert_str_eq(str_s21, "AMOR28");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_upper_2) {
  char *str = " amor";
  char *str_s21 = (char *)s21_to_upper(str);
  ck_assert_str_eq(str_s21, " AMOR");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_upper_3) {
  char *str = "amor\n\0";
  char *str_s21 = (char *)s21_to_upper(str);
  ck_assert_str_eq(str_s21, "AMOR\n");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_upper_4) {
  char *str = " \n\0";
  char *str_s21 = (char *)s21_to_upper(str);
  ck_assert_str_eq(str_s21, " \n");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_upper_5) {
  char *str = " \0";
  char *str_s21 = (char *)s21_to_upper(str);
  ck_assert_str_eq(str_s21, " ");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_upper_6) {
  char *str = "\n\0";
  char *str_s21 = (char *)s21_to_upper(str);
  ck_assert_str_eq(str_s21, "\n");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_upper_7) {
  char *str = "\0";
  char *str_s21 = (char *)s21_to_upper(str);
  ck_assert_str_eq(str_s21, "");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_upper_8) {
  char *str = "";
  char *str_s21 = (char *)s21_to_upper(str);
  ck_assert_str_eq(str_s21, "");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_upper_9) {
  char str[] = "AMOR";
  char *str_s21 = (char *)s21_to_upper(str);
  ck_assert_str_eq(str_s21, "AMOR");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_upper_10) {
  char *str = "EL_ganador se lo lleva TODO!./,,";
  char *str_s21 = (char *)s21_to_upper(str);
  ck_assert_str_eq(str_s21, "EL_GANADOR SE LO LLEVA TODO!./,,");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_upper_11) {
  char str[] = "NULL";
  char *str_s21 = (char *)s21_to_upper(str);
  ck_assert_str_eq(str_s21, "NULL");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_lower_1) {
  char *str = "AMOR28";
  char *str_s21 = (char *)s21_to_lower(str);
  ck_assert_str_eq(str_s21, "amor28");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_lower_2) {
  char *str = " AMOR";
  char *str_s21 = (char *)s21_to_lower(str);
  ck_assert_str_eq(str_s21, " amor");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_lower_3) {
  char *str = "AMOR\n\0";
  char *str_s21 = (char *)s21_to_lower(str);
  ck_assert_str_eq(str_s21, "amor\n");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_lower_4) {
  char *str = " \n\0";
  char *str_s21 = (char *)s21_to_lower(str);
  ck_assert_str_eq(str_s21, " \n");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_lower_5) {
  char *str = " \0";
  char *str_s21 = (char *)s21_to_lower(str);
  ck_assert_str_eq(str_s21, " ");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_lower_6) {
  char *str = "\n\0";
  char *str_s21 = (char *)s21_to_lower(str);
  ck_assert_str_eq(str_s21, "\n");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_lower_7) {
  char *str = "\0";
  char *str_s21 = (char *)s21_to_lower(str);
  ck_assert_str_eq(str_s21, "");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_lower_8) {
  char *str = "";
  char *str_s21 = (char *)s21_to_lower(str);
  ck_assert_str_eq(str_s21, "");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_lower_9) {
  char str[] = "amor";
  char *str_s21 = (char *)s21_to_lower(str);
  ck_assert_str_eq(str_s21, "amor");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_lower_10) {
  char *str = "EL_GANADOR SE LO LLEVA TODO!./,,";
  char *str_s21 = (char *)s21_to_lower(str);
  ck_assert_str_eq(str_s21, "el_ganador se lo lleva todo!./,,");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(to_lower_11) {
  char str[] = "NULL";
  char *str_s21 = (char *)s21_to_lower(str);
  ck_assert_str_eq(str_s21, "null");
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(insert_1) {
  const char *str1 = {"Como"};
  const char *str2 = {"estas"};
  s21_size_t start_index = 2;
  char *str3 = s21_insert(str1, str2, start_index);
  ck_assert_str_eq(str3, "Coestasmo");
  free(str3);
}
END_TEST

START_TEST(insert_2) {
  const char str1[] = "Como\0";
  const char str2[] = "Estas\0";
  s21_size_t start_index = 2;
  char *str3 = s21_insert(str1, str2, start_index);
  ck_assert_str_eq(str3, "CoEstasmo");
  free(str3);
}
END_TEST

START_TEST(insert_3) {
  const char str1[] = "Como\0";
  const char str2[] = "Estas\0";
  s21_size_t start_index = 4;
  char *str3 = s21_insert(str1, str2, start_index);
  ck_assert_str_eq(str3, "ComoEstas");
  free(str3);
}
END_TEST

START_TEST(insert_4) {
  const char *str1 = "Como\0";
  const char *str2 = "Estas\0";
  s21_size_t start_index = 0;
  char *str3 = s21_insert(str1, str2, start_index);
  ck_assert_pstr_eq(str3, "EstasComo");
  free(str3);
}
END_TEST

START_TEST(insert_5) {
  const char *str1 = "M";
  const char *str2 = "amor";
  s21_size_t start_index = 1;
  char *str3 = s21_insert(str1, str2, start_index);
  ck_assert_str_eq(str3, "Mamor");
  free(str3);
}
END_TEST

START_TEST(insert_6) {
  const char *str1 = "M";
  const char *str2 = "amor";
  s21_size_t start_index = 1;
  char *str3 = s21_insert(str1, str2, start_index);
  ck_assert_str_eq(str3, "Mamor");
  free(str3);
}
END_TEST

START_TEST(insert_7) {
  const char *str1 = "Hello\n\0";
  const char *str2 = "Man\n\0";
  s21_size_t start_index = 1;
  char *str3 = s21_insert(str1, str2, start_index);
  ck_assert_str_eq(str3, "HMan\nello\n\0");
  free(str3);
}
END_TEST

START_TEST(insert_8) {
  const char *str1 = " s\0";
  const char *str2 = " s\0";
  s21_size_t start_index = 1;
  char *str3 = s21_insert(str1, str2, start_index);
  ck_assert_str_eq(str3, "  ss");
  free(str3);
}
END_TEST

START_TEST(insert_9) {
  const char str1[] = "\n\0";
  const char str2[] = "\n\0";
  s21_size_t start_index = 1;
  char *str3 = s21_insert(str1, str2, start_index);
  ck_assert_str_eq(str3, "\n\n");
  free(str3);
}
END_TEST

START_TEST(insert_10) {
  const char str1[] = " \0";
  const char str2[] = " \0";
  s21_size_t start_index = 1;
  char *str3 = s21_insert(str1, str2, start_index);
  ck_assert_str_eq(str3, "  ");
  free(str3);
}
END_TEST

START_TEST(trim_1) {
  const char *src = "Comoestas";
  const char *trim_chars = "o";
  char *str = s21_trim(src, trim_chars);
  ck_assert_pstr_eq(str, "Comoestas");
  free(str);
}
END_TEST

START_TEST(trim_2) {
  const char *src = "Comoestas";
  const char *trim_chars = "C";
  char *str = s21_trim(src, trim_chars);
  ck_assert_pstr_eq(str, "omoestas");
  free(str);
}
END_TEST

START_TEST(trim_3) {
  const char *src = "Comoestas";
  const char *trim_chars = "ats";
  char *str = s21_trim(src, trim_chars);
  ck_assert_pstr_eq(str, "Comoe");
  free(str);
}
END_TEST

START_TEST(trim_4) {
  const char *src = "Comoestas";
  const char *trim_chars = " ";
  char *str = s21_trim(src, trim_chars);
  ck_assert_pstr_eq(src, "Comoestas");
  free(str);
}
END_TEST

START_TEST(trim_5) {
  const char *src = "Helloworld";
  const char *trim_chars = "world";
  char *str = s21_trim(src, trim_chars);
  ck_assert_pstr_eq(str, "He");
  free(str);
}
END_TEST

START_TEST(trim_6) {
  const char *src = "";
  const char *trim_chars = "w";
  char *str = s21_trim(src, trim_chars);
  ck_assert_pstr_eq(str, "");
  free(str);
}
END_TEST

START_TEST(trim_7) {
  const char *src = "-Hola\n\0";
  const char *trim_chars = "-";
  char *str = s21_trim(src, trim_chars);
  ck_assert_pstr_eq(str, "Hola\n");
  free(str);
}
END_TEST

START_TEST(trim_8) {
  const char *src = "f\0";
  const char *trim_chars = "f";
  char *str = s21_trim(src, trim_chars);
  ck_assert_pstr_eq(str, "");
  free(str);
}
END_TEST

START_TEST(trim_9) {
  const char *src = " \0";
  const char *trim_chars = " ";
  char *str = s21_trim(src, trim_chars);
  ck_assert_pstr_eq(str, "");
  free(str);
}
END_TEST

START_TEST(trim_10) {
  const char *src = " \n\0";
  const char *trim_chars = "\n";
  char *str = s21_trim(src, trim_chars);
  ck_assert_pstr_eq(str, " ");
  free(str);
}
END_TEST

START_TEST(trim_11) {
  const char *src = "";
  const char *trim_chars = "";
  char *str = s21_trim(src, trim_chars);
  ck_assert_pstr_eq(str, "");
  free(str);
}
END_TEST

START_TEST(trim_12) {
  const char *src = "Comoestas";
  const char *trim_chars = "Comoestas";
  char *str = s21_trim(src, trim_chars);
  ck_assert_pstr_eq(str, "");
  free(str);
}
END_TEST

START_TEST(trim_13) {
  const char *src = "  Comoestas    ";
  const char *trim_chars = " ";
  char *str = s21_trim(src, trim_chars);
  ck_assert_pstr_eq(str, "Comoestas");
  free(str);
}
END_TEST

int main(void) {
  int number_failed = 0;  // для хранения количества неудачных тестов
  Suite *s;  // указатель на suite
  s = suite_create(
      "dopfunk");  // вызываем функцию, чтобы создать и вернуть test suite
  SRunner *sr;     // указатель на srunner
  sr = srunner_create(
      s);  // используем test suite и передаем их функции srunner_create, чтобы
           // получить указатель на test suite runner
  TCase *tc_to_upper = tcase_create("to_upper");
  suite_add_tcase(s, tc_to_upper);
  tcase_add_test(tc_to_upper, to_upper_1);
  tcase_add_test(tc_to_upper, to_upper_2);
  tcase_add_test(tc_to_upper, to_upper_3);
  tcase_add_test(tc_to_upper, to_upper_4);
  tcase_add_test(tc_to_upper, to_upper_5);
  tcase_add_test(tc_to_upper, to_upper_6);
  tcase_add_test(tc_to_upper, to_upper_7);
  tcase_add_test(tc_to_upper, to_upper_8);
  tcase_add_test(tc_to_upper, to_upper_9);
  tcase_add_test(tc_to_upper, to_upper_10);
  tcase_add_test(tc_to_upper, to_upper_11);

  TCase *tc_to_lower = tcase_create("to_lower");
  suite_add_tcase(s, tc_to_lower);
  tcase_add_test(tc_to_lower, to_lower_1);
  tcase_add_test(tc_to_lower, to_lower_2);
  tcase_add_test(tc_to_lower, to_lower_3);
  tcase_add_test(tc_to_lower, to_lower_4);
  tcase_add_test(tc_to_lower, to_lower_5);
  tcase_add_test(tc_to_lower, to_lower_6);
  tcase_add_test(tc_to_lower, to_lower_7);
  tcase_add_test(tc_to_lower, to_lower_8);
  tcase_add_test(tc_to_lower, to_lower_9);
  tcase_add_test(tc_to_lower, to_lower_10);
  tcase_add_test(tc_to_lower, to_lower_11);

  TCase *tc_insert = tcase_create("insert");
  suite_add_tcase(s, tc_insert);
  tcase_add_test(tc_insert, insert_1);
  tcase_add_test(tc_insert, insert_2);
  tcase_add_test(tc_insert, insert_3);
  tcase_add_test(tc_insert, insert_4);
  tcase_add_test(tc_insert, insert_5);
  tcase_add_test(tc_insert, insert_6);
  tcase_add_test(tc_insert, insert_7);
  tcase_add_test(tc_insert, insert_8);
  tcase_add_test(tc_insert, insert_9);
  tcase_add_test(tc_insert, insert_10);

  TCase *tc_trim = tcase_create("trim");
  suite_add_tcase(s, tc_trim);
  tcase_add_test(tc_trim, trim_1);
  tcase_add_test(tc_trim, trim_2);
  tcase_add_test(tc_trim, trim_3);
  tcase_add_test(tc_trim, trim_4);
  tcase_add_test(tc_trim, trim_5);
  tcase_add_test(tc_trim, trim_6);
  tcase_add_test(tc_trim, trim_7);
  tcase_add_test(tc_trim, trim_8);
  tcase_add_test(tc_trim, trim_9);
  tcase_add_test(tc_trim, trim_10);
  tcase_add_test(tc_trim, trim_11);
  tcase_add_test(tc_trim, trim_12);
  tcase_add_test(tc_trim, trim_13);

  srunner_run_all(sr, CK_NORMAL);  // распечатывает все неудачные тесты
  number_failed =
      srunner_ntests_failed(sr);  // вызываем srunner_ntests_failed чтобы
                                  // получить количество неудачных тестов
  srunner_free(sr);
  return (number_failed == 0)
             ? EXIT_SUCCESS
             : EXIT_FAILURE;  // успешно возвращаемся, если количество неудачных
                              // тестов равно 0, иначе мы не проходим тест
}
