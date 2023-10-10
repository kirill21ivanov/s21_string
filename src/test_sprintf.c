#include <check.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

START_TEST(sprintf_test_s) {
  char str1[100] = "\0";
  char str2[100] = "\0";
  ck_assert_int_eq((int)s21_sprintf(str1, "Watsp %s", "tomorrow"),
                   (int)sprintf(str2, "Watsp %s", "tomorrow"));
  ck_assert_int_eq((int)s21_sprintf(str1, "Watsp %-s", "tomorrow"),
                   (int)sprintf(str2, "Watsp %-s", "tomorrow"));
  ck_assert_int_eq((int)s21_sprintf(str1, "Watsp %-20s", "tomorrow"),
                   (int)sprintf(str2, "Watsp %-20s", "tomorrow"));
  ck_assert_int_eq((int)s21_sprintf(str1, "Watsp %-20.s", "tomorrow"),
                   (int)sprintf(str2, "Watsp %-20.s", "tomorrow"));
  ck_assert_int_eq((int)s21_sprintf(str1, "Watsp %.5s", "tomorrow"),
                   (int)sprintf(str2, "Watsp %.5s", "tomorrow"));
  ck_assert_int_eq((int)s21_sprintf(str1, "Watsp %-10.20s", "tomorrow"),
                   (int)sprintf(str2, "Watsp %-10.20s", "tomorrow"));
  ck_assert_int_eq((int)s21_sprintf(str1, "Watsp %-.20ls", L"tomorrow"),
                   (int)sprintf(str2, "Watsp %-.20ls", L"tomorrow"));
  ck_assert_int_eq((int)s21_sprintf(str1, "Watsp %ls", L"tomorrow"),
                   (int)sprintf(str2, "Watsp %ls", L"tomorrow"));
  ck_assert_int_eq(
      (int)s21_sprintf(str1, "Watsp %21.20s and %-2.4s", "tomorrow", "school"),
      (int)sprintf(str2, "Watsp %21.20s and %-2.4s", "tomorrow", "school"));
}
END_TEST

START_TEST(sprintf_test_c) {
  char str1[100] = "\0";
  char str2[100] = "\0";
  ck_assert_int_eq(s21_sprintf(str1, "Watsp school %c %lc", '2', '&'),
                   sprintf(str2, "Watsp school %c %lc", '2', '&'));
  ck_assert_int_eq(s21_sprintf(str1, "Watsp school %-c %c %%%%", '2', '1'),
                   sprintf(str2, "Watsp school %-c %c %%%%", '2', '1'));
  ck_assert_int_eq(s21_sprintf(str1, "Watsp school %20c %-10lc", '2', 0x61),
                   sprintf(str2, "Watsp school %20c %-10lc", '2', 0x61));
  ck_assert_int_eq(s21_sprintf(str1, "Watsp school %-c %c", '2', '1'),
                   sprintf(str2, "Watsp school %-c %c", '2', '1'));
}
END_TEST

START_TEST(sprintf_test_c2) {
  char *str1 = (char *)calloc(10000000, sizeof(char));
  char *str2 = (char *)calloc(10000000, sizeof(char));
  str1[0] = '\0';
  str2[0] = '\0';
  int r1 = sprintf(str1, "(%100000c%-10c%25c%-30c%25c%*c%2c%*c)", 'a', 'e', 'f',
                   'R', 'Q', 10, 'P', 'L', 20, 'x');
  int r2 = s21_sprintf(str2, "(%100000c%-10c%25c%-30c%25c%*c%2c%*c)", 'a', 'e',
                       'f', 'R', 'Q', 10, 'P', 'L', 20, 'x');
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
  free(str1);
  free(str2);
}
END_TEST

START_TEST(sprintf_test_d) {
  char *str1 = (char *)calloc(100000, sizeof(char));
  char *str2 = (char *)calloc(100000, sizeof(char));
  str1[0] = '\0';
  str2[0] = '\0';

  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = %10000d ! = %d", +4, -1),
                   sprintf(str2, "2 + 2 = %10000d ! = %d", +4, -1));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = %-d ! = %d", 4, 10),
                   sprintf(str2, "2 + 2 = %-d ! = %d", 4, 10));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = % -d ! = %-d", +4, 10),
                   sprintf(str2, "2 + 2 = % -d ! = %-d", +4, 10));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = % 10d ! = %+-20d", -4, 10),
                   sprintf(str2, "2 + 2 = % 10d ! = %+-20d", -4, 10));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = % 10.d ! = %+-20.20d", 0, -182),
                   sprintf(str2, "2 + 2 = % 10.d ! = %+-20.20d", 0, -182));
  ck_assert_int_eq(
      s21_sprintf(str1, "2 + 2 = % 10.hd ! = %-20.20ld", 4, 276892067102856),
      sprintf(str2, "2 + 2 = % 10.hd ! = %-20.20ld", (short)4,
              276892067102856));
  ck_assert_int_eq(
      s21_sprintf(str1, "2 + 2 = % 10.hd ! = %-20.20ld", 010, 0x1275623445),
      sprintf(str2, "2 + 2 = % 10.hd ! = %-20.20ld", (short)010, 0x1275623445));
  free(str1);
  free(str2);
}
END_TEST

START_TEST(sprintf_test_i) {
  char str1[100] = "\0";
  char str2[100] = "\0";

  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = %i ! = %i", 4, 10),
                   sprintf(str2, "2 + 2 = %i ! = %i", 4, 10));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = %-i ! = %i", 4, 10),
                   sprintf(str2, "2 + 2 = %-i ! = %i", 4, 10));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = % -i ! = %+-i", 4, -10),
                   sprintf(str2, "2 + 2 = % -i ! = %+-i", 4, -10));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = % 10d ! = %+-20i", 4, 10),
                   sprintf(str2, "2 + 2 = % 10i ! = %+-20i", 4, 10));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = % 10.i ! = %+-20.20i", 4, -10),
                   sprintf(str2, "2 + 2 = % 10.i ! = %+-20.20i", 4, -10));
  ck_assert_int_eq(
      s21_sprintf(str1, "2 + 2 = % 10.hi ! = %-20.20li", -4, +276892067102856),
      sprintf(str2, "2 + 2 = % 10.hi ! = %-20.20li", (short)-4,
              +276892067102856));
  ck_assert_int_eq(
      s21_sprintf(str1, "2 + 2 = % 10.hi ! = %-20.20li", 010, 0x1275623445),
      sprintf(str2, "2 + 2 = % 10.hi ! = %-20.20li", (short)010, 0x1275623445));
}
END_TEST

START_TEST(sprintf_test_u) {
  char str1[100] = "\0";
  char str2[100] = "\0";

  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = %d ! = %u", -4, 10),
                   sprintf(str2, "2 + 2 = %d ! = %u", -4, 10));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = %-d ! = %u", 4, 10),
                   sprintf(str2, "2 + 2 = %-d ! = %u", 4, 10));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = % -i ! = %-u", 4, 10),
                   sprintf(str2, "2 + 2 = % -i ! = %-u", 4, 10));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = % 10d ! = %-20u", 4, 10),
                   sprintf(str2, "2 + 2 = % 10d ! = %-20u", 4, 10));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = % 10.i ! = %-20.20u", 4, 10),
                   sprintf(str2, "2 + 2 = % 10.i ! = %-20.20u", 4, 10));
  ck_assert_int_eq(
      s21_sprintf(str1, "2 - 2 = %10.hu ! = %-20.20lu", 0, 276892067102856),
      sprintf(str2, "2 - 2 = %10.hu ! = %-20.20lu", (unsigned short)0,
              276892067102856));
}
END_TEST

START_TEST(sprintf_test_f) {
  char str1[100] = "\0";
  char str2[100] = "\0";

  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = %f ! = %f", -4.21, +42.21),
                   sprintf(str2, "2 + 2 = %f ! = %f", -4.21, +42.21));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = %-f ! = %f", -4.21, +42.21),
                   sprintf(str2, "2 + 2 = %-f ! = %f", -4.21, +42.21));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = %-10f ! = %+12f", -4.21, +42.21),
                   sprintf(str2, "2 + 2 = %-10f ! = %+12f", -4.21, +42.21));
  ck_assert_int_eq(
      s21_sprintf(str1, "2 + 2 = %- 10.f ! = %+12.5f", -4.21, +42.21),
      sprintf(str2, "2 + 2 = %- 10.f ! = %+12.5f", -4.21, +42.21));
  ck_assert_int_eq(
      s21_sprintf(str1, "2 + 2 = %- 10.f ! = %+12.5lf", -4.21, +42.21),
      sprintf(str2, "2 + 2 = %- 10.f ! = %+12.5lf", -4.21, +42.21));
}
END_TEST

START_TEST(sprintf_test_o) {
  char str1[100] = "\0";
  char str2[100] = "\0";

  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = %d ! = %o", -4, 10),
                   sprintf(str2, "2 + 2 = %d ! = %o", -4, 10));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = %-d ! = %-o", 4, 00210),
                   sprintf(str2, "2 + 2 = %-d ! = %-o", 4, 00210));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = % 10d ! = %-20.o", 4, 0),
                   sprintf(str2, "2 + 2 = % 10d ! = %-20.o", 4, 0));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = % 10.i ! = %-20.20o", 0, 0x124),
                   sprintf(str2, "2 + 2 = % 10.i ! = %-20.20o", 0, 0x124));
  ck_assert_int_eq(
      s21_sprintf(str1, "2 + 2 = %10.ho ! = %-20.20lo", 4, 276892067102856),
      sprintf(str2, "2 + 2 = %10.ho ! = %-20.20lo", (unsigned short)4,
              276892067102856));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = %10.ho ! = %-20.20lo", 4, 0),
                   sprintf(str2, "2 + 2 = %10.ho ! = %-20.20lo",
                           (unsigned short)0, 276892067102856));
}
END_TEST

START_TEST(sprintf_test_x_X) {
  char str1[100] = "\0";
  char str2[100] = "\0";

  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = %X ! = %x", 4, 10),
                   sprintf(str2, "2 + 2 = %X ! = %x", 4, 10));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = %-X ! = %-x", 4, 132445),
                   sprintf(str2, "2 + 2 = %-X ! = %-x", 4, 132445));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = %10X ! = %-20.x", 4, 0),
                   sprintf(str2, "2 + 2 = %10X ! = %-20.x", 4, 0));
  ck_assert_int_eq(s21_sprintf(str1, "2 + 2 = %10.X ! = %04x", 0, 0x124),
                   sprintf(str2, "2 + 2 = %10.X ! = %04x", 0, 0x124));
  ck_assert_int_eq(
      s21_sprintf(str1, "2 + 2 = %10.hX ! = %-20.20lx", 5, 276892067102856),
      sprintf(str2, "2 + 2 = %10.hX ! = %-20.20lx", (unsigned short)5,
              276892067102856));
  ck_assert_int_eq(
      s21_sprintf(str1, "2 + 2 = %10.hX ! = %-20.lx", 21, 276892067102856),
      sprintf(str2, "2 + 2 = %10.hX ! = %-20.lx", (unsigned short)21,
              276892067102856));
}
END_TEST

START_TEST(sprintf_test_x2) {
  char str1[1000] = "\0";
  char str2[1000] = "\0";
  unsigned short h = 345;
  unsigned long l = 52342353242l;
  int r1 = sprintf(str1,
                   "(%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%20.*"
                   "x%#10.*x%*.5hx%10.25lx)",
                   235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452,
                   8, 23452, 10, 34254, 3, 33334, 10, h, l);
  int r2 = s21_sprintf(str2,
                       "(%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%"
                       "20.*x%#10.*x%*.5hx%10.25lx)",
                       235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15,
                       3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test_n) {
  char str1[100] = "\0";
  char str2[100] = "\0";
  int val1 = 0;
  int val2 = 0;
  int sval1 = 0;
  int sval2 = 0;

  ck_assert_int_eq(s21_sprintf(str1, "What is n?%n is", &val1),
                   sprintf(str2, "What is n?%n is", &val2));
  ck_assert_int_eq(s21_sprintf(str1, "What is n?%n is %n", &val1, &sval1),
                   sprintf(str2, "What is n?%n is %n", &val2, &sval2));
}
END_TEST

START_TEST(sprintf_test_percent) {
  char str1[1000] = "\0";
  char str2[1000] = "\0";
  int r1 = sprintf(str1, "%%%%");
  int r2 = s21_sprintf(str2, "%%%%");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_1_e) {
  char str1[100];
  char str2[100];
  char *str3 = "%e Test %5e Test %5.e";
  double num = -764231539.;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_e) {
  char str1[100];
  char str2[100];
  char *str3 = "%e\n%.e\n%4e\n%4.e\n%5.10e!";
  double num = -764231539.;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_e) {
  char str1[100];
  char str2[100];
  char *str3 = "%#e\n%#.e\n%#5.e\n%#.0e\n%#0.0e!";
  double num = -665695342471359.;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_e) {
  char str1[300];
  char str2[300];
  char *str3 = "New test: %020e\nSecond test: %020.e!";
  double num = -5921563224775967.;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_e) {
  char str1[300];
  char str2[300];
  double num1 = -.3529373967;
  double num4 = -0000000000000.3529373967;
  char *str3 = "test: %20.E\ntest: %-20.E\n!";
  ck_assert_int_eq(sprintf(str1, str3, num4, num1),
                   s21_sprintf(str2, str3, num4, num1));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_6_e) {
  char str1[300];
  char str2[300];
  char *str3 = "Fifth test: %0.0e!";
  double num = -5921563224775967.;
  ck_assert_int_eq(sprintf(str1, str3, num), s21_sprintf(str2, str3, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%g TEST %.g TEST %4g TEST %4.g TEST %5.10g!";
  double num = 76.756589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%g TEST %.g TEST %4g TEST %4.g TEST %5.10g!";
  double num = -76.756589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%25.18g TEST\n%.6g TEST\n";
  double num = 838.65400000;
  double num1 = 640.783289182;
  ck_assert_int_eq(sprintf(str1, str3, num, num1),
                   s21_sprintf(str2, str3, num, num1));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%.2g TEST\n%.3g TEST\n";
  double num = 838.65400000;
  double num1 = 640.783289182;
  ck_assert_int_eq(sprintf(str1, str3, num, num1),
                   s21_sprintf(str2, str3, num, num1));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%g TEST %.g TEST %4g TEST %4.g TEST %#5.10g!";
  double num = 0.0000756589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_6_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%g TEST %.g TEST %4g TEST %4.g TEST %#5.10g!";
  double num = 0;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

int main(void) {
  int number_failed = 0;  // для хранения количества неудачных тестов
  Suite *s;  // указатель на suite
  s = suite_create(
      "sprintf");  // вызываем функцию, чтобы создать и вернуть test suite
  SRunner *sr;     // указатель на srunner
  sr = srunner_create(
      s);  // используем test suite и передаем их функции srunner_create, чтобы
           // получить указатель на test suite runner

  TCase *tc_sprintf = tcase_create("sprintf");
  suite_add_tcase(s, tc_sprintf);
  tcase_add_test(tc_sprintf, sprintf_test_s);
  tcase_add_test(tc_sprintf, sprintf_test_c);
  tcase_add_test(tc_sprintf, sprintf_test_c2);
  tcase_add_test(tc_sprintf, sprintf_test_d);
  tcase_add_test(tc_sprintf, sprintf_test_i);
  tcase_add_test(tc_sprintf, sprintf_test_u);
  tcase_add_test(tc_sprintf, sprintf_test_f);
  tcase_add_test(tc_sprintf, sprintf_test_o);
  tcase_add_test(tc_sprintf, sprintf_test_x_X);
  tcase_add_test(tc_sprintf, sprintf_test_x2);
  tcase_add_test(tc_sprintf, sprintf_test_n);
  tcase_add_test(tc_sprintf, sprintf_test_percent);
  tcase_add_test(tc_sprintf, sprintf_1_e);
  tcase_add_test(tc_sprintf, sprintf_2_e);
  tcase_add_test(tc_sprintf, sprintf_3_e);
  tcase_add_test(tc_sprintf, sprintf_4_e);
  tcase_add_test(tc_sprintf, sprintf_5_e);
  tcase_add_test(tc_sprintf, sprintf_6_e);
  tcase_add_test(tc_sprintf, sprintf_1_g);
  tcase_add_test(tc_sprintf, sprintf_2_g);
  tcase_add_test(tc_sprintf, sprintf_3_g);
  tcase_add_test(tc_sprintf, sprintf_4_g);
  tcase_add_test(tc_sprintf, sprintf_5_g);
  tcase_add_test(tc_sprintf, sprintf_6_g);

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
