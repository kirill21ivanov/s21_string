#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

START_TEST(S21_SSCANF_1) {
  char a, b, c;  // chars
  char a1, b1, c1;
  s21_sscanf("abcdefABCDEF", "%c %*c %c %c   ", &a, &b, &c);
  sscanf("abcdefABCDEF", "%c %*c %c %c   ", &a1, &b1, &c1);
  s21_sscanf("ab", "%2c", &c);
  s21_sscanf("ab", "%2c", &c1);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
  ck_assert_int_eq(c, c1);
}
END_TEST

START_TEST(S21_SSCANF_2) {
  int x, y, z = 0;  // ints
  int x1, y1, z1 = 0;
  int res = s21_sscanf("+12 -23 .54", "%3d %d%d", &x, &y, &z);
  int res1 = sscanf("+12 -23 .54", "%3d %d %d", &x1, &y1, &z1);
  ck_assert_int_eq(x, x1);
  ck_assert_int_eq(y, y1);
  ck_assert_int_eq(z, z1);
  ck_assert_int_eq(res, res1);

  res = s21_sscanf("+0775 1-0x1324--123", " %i %*i %i- %i", &x, &y, &z);
  res1 = sscanf("+0775 1-0x1324--123", " %i %*i %i- %i", &x1, &y1, &z1);
  ck_assert_int_eq(x, x1);
  ck_assert_int_eq(y, y1);
  ck_assert_int_eq(z, z1);
  ck_assert_int_eq(res, res1);

  x = 0, x1 = 0;  // errors
  res = s21_sscanf("a21", "%d", &x);
  res1 = sscanf("a21", "%d", &x1);
  ck_assert_int_eq(x, x1);
  ck_assert_int_eq(res, res1);
  s21_sscanf("a21", "b%d", &x);
  sscanf("a21", "b%d", &x1);
  ck_assert_int_eq(x, x1);
  s21_sscanf("--a21", "%d", &x);
  sscanf("--a21", "%d", &x1);
  ck_assert_int_eq(x, x1);
  s21_sscanf("-21", "%1d", &x);
  sscanf("-21", "%1d", &x1);
  ck_assert_int_eq(x, x1);
  s21_sscanf("-21", "%%%1d", &x);
  sscanf("-21", "%%%1d", &x1);
  ck_assert_int_eq(x, x1);
  s21_sscanf("-21   ", "%d %d", &x, &y);
  sscanf("-21   ", "%d %d", &x1, &y1);
  ck_assert_int_eq(x, x1);
}
END_TEST

START_TEST(S21_SSCANF_3) {
  unsigned short usx, usx1;
  unsigned int ux, ux1;
  unsigned long ulx, ulx1;
  s21_sscanf("0 +2112 -12324", "%o %lo", &ux, &ulx);
  sscanf("0 +2112 -12324", "%o %lo", &ux1, &ulx1);
  ck_assert_int_eq(ux, ux1);
  ck_assert_int_eq(ulx, ulx1);

  s21_sscanf("0 0x211a 0x1", "%x %lx %hx", &ux, &ulx, &usx);
  sscanf("0 0x211a 0x1", "%x %lx %hx", &ux1, &ulx1, &usx1);
  ck_assert_int_eq(usx, usx1);
  ck_assert_int_eq(ux, ux1);
  ck_assert_int_eq(ulx, ulx1);
}
END_TEST

START_TEST(S21_SSCANF_4) {
  float fx, fx1;  // floats
  double lfx, lfx1;
  long double llfx, llfx1;
  s21_sscanf("1 2 -123232.001 .995123 999.99.1", "%*E %*G %g %le %Lf", &fx,
             &lfx, &llfx);
  sscanf("1 2 -123232.001 .995123 999.99.1", "%*E %*G %g %le %Lf", &fx1, &lfx1,
         &llfx1);
  ck_assert_double_eq(fx, fx1);
  ck_assert_double_eq(lfx, lfx1);
  ck_assert_double_eq(llfx, llfx1);
}
END_TEST

START_TEST(S21_SSCANF_5) {
  int x, y, z = 0;
  int x1, y1, z1 = 0;
  char str[100], str1[100];  // strings
  char p_str[100], p_str1[100];
  s21_sscanf("abc\n\r\t%%cba\faaa?.123", "%*s %s%s%n", str, str1, &x);
  sscanf("abc\n\r\t%%cba\faaa?.123", "%*s %s%s%n", p_str, p_str1, &x1);
  ck_assert_msg(strcmp(str, p_str) == 0, "str fail");
  ck_assert_msg(strcmp(str1, p_str1) == 0, "str1 fail");
  ck_assert_int_eq(x, x1);

  void *addr1 = s21_NULL, *addr2 = s21_NULL, *addr3 = s21_NULL;
  void *paddr1 = NULL, *paddr2 = NULL, *paddr3 = NULL;
  s21_sscanf("0x1abcd -0xfffffffff +0xffffffffffffffffffaaa", "%p %n%p %p",
             &addr1, &x, &addr2, &addr3);
  sscanf("0x1abcd -0xfffffffff +0xffffffffffffffffffaaa", "%p %n%p %p", &paddr1,
         &x1, &paddr2, &paddr3);

  float af1 = 0, af2 = 0, bf1 = 0, bf2 = 0, cf1 = 0, cf2 = 0, df1 = 0, df2 = 0;

  const char strf[] =
      "nAN           INF                   -0.1111         1e-10";
  const char fstr[] = "%G %G %G %G";

  int res1 = s21_sscanf(strf, fstr, &af1, &bf1, &cf1, &df1);
  int res2 = sscanf(strf, fstr, &af2, &bf2, &cf2, &df2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_nan(af1);
  ck_assert_float_nan(af2);
  ck_assert_ldouble_eq(bf1, bf2);
  ck_assert_ldouble_eq(cf1, cf2);
  ck_assert_ldouble_eq(df1, df2);

  const char strf2[] = "-inF InF inF INF";

  res1 = s21_sscanf(strf2, fstr, &af1, &bf1, &cf1, &df1);
  res2 = sscanf(strf2, fstr, &af2, &bf2, &cf2, &df2);
  ck_assert_ldouble_eq(bf1, bf2);
  ck_assert_ldouble_eq(cf1, cf2);
  ck_assert_ldouble_eq(df1, df2);

  char *format = "%c";
  char *strc = "\t\n\n  1 \n  \t";
  char c11, c22;

  res1 = s21_sscanf(strc, format, &c11);
  res2 = sscanf(strc, format, &c22);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c22);
}
END_TEST

START_TEST(S21_SSCANF_6) {
  int res1, res2;
  long double al1 = 0, al2 = 0, bl1 = 0, bl2 = 0, cl1 = 0, cl2 = 0, dl1 = 0,
              dl2 = 0;
  const char strf3[] = "1.4441 1.31e3 -3.31e-2 0.444e-1";

  res1 = s21_sscanf(strf3, "%LG %LG %LG %LG", &al1, &bl1, &cl1, &dl1);
  res2 = sscanf(strf3, "%LG %LG %LG %LG", &al2, &bl2, &cl2, &dl2);

  ck_assert_ldouble_eq(al1, al2);
  ck_assert_ldouble_eq(bl1, bl2);
  ck_assert_ldouble_eq(cl1, cl2);
  ck_assert_ldouble_eq(dl1, dl2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(S21_SSCANF_7) {
  char *format = "%p";
  char *str = "0xFFFFFF";
  int *p1 = 0, *p2 = 0;

  int res1 = s21_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);

  str = "0x0000";
  res1 = s21_sscanf(str, format, &p1);
  res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);

  str = "0xdksajh";
  res1 = s21_sscanf(str, format, &p1);
  res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);

  str = "0xAGAGUIYUYGFSV";
  res1 = s21_sscanf(str, format, &p1);
  res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);

  format = "%3o %3o %3o";
  str = "01236 +04 -3723";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  res2 = sscanf(str, format, &d2, &q2, &z2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(q1, q2);
  ck_assert_int_eq(z1, z2);
}
END_TEST

Suite *make_s21string_suite() {
  Suite *suite = suite_create("TESTING - s21_sscanf");

  TCase *tc_s21_sscanf_1;
  tc_s21_sscanf_1 = tcase_create("S21_SSCANF_1");
  suite_add_tcase(suite, tc_s21_sscanf_1);
  tcase_add_test(tc_s21_sscanf_1, S21_SSCANF_1);

  TCase *tc_s21_sscanf_2;
  tc_s21_sscanf_2 = tcase_create("S21_SSCANF_2");
  suite_add_tcase(suite, tc_s21_sscanf_2);
  tcase_add_test(tc_s21_sscanf_2, S21_SSCANF_2);

  TCase *tc_s21_sscanf_3;
  tc_s21_sscanf_3 = tcase_create("S21_SSCANF_3");
  suite_add_tcase(suite, tc_s21_sscanf_3);
  tcase_add_test(tc_s21_sscanf_3, S21_SSCANF_3);

  TCase *tc_s21_sscanf_4;
  tc_s21_sscanf_4 = tcase_create("S21_SSCANF_4");
  suite_add_tcase(suite, tc_s21_sscanf_4);
  tcase_add_test(tc_s21_sscanf_4, S21_SSCANF_4);

  TCase *tc_s21_sscanf_5;
  tc_s21_sscanf_5 = tcase_create("S21_SSCANF_5");
  suite_add_tcase(suite, tc_s21_sscanf_5);
  tcase_add_test(tc_s21_sscanf_5, S21_SSCANF_5);

  TCase *tc_s21_sscanf_6;
  tc_s21_sscanf_6 = tcase_create("S21_SSCANF_6");
  suite_add_tcase(suite, tc_s21_sscanf_6);
  tcase_add_test(tc_s21_sscanf_6, S21_SSCANF_6);

  TCase *tc_s21_sscanf_7;
  tc_s21_sscanf_7 = tcase_create("S21_SSCANF_7");
  suite_add_tcase(suite, tc_s21_sscanf_7);
  tcase_add_test(tc_s21_sscanf_7, S21_SSCANF_7);

  return suite;
}

int main() {
  SRunner *suite_runner = srunner_create(make_s21string_suite());
  srunner_run_all(suite_runner, CK_NORMAL);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return failed_count ? EXIT_FAILURE : EXIT_SUCCESS;
}
