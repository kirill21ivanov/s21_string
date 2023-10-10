#include <check.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

// 1
START_TEST(memchr_1) {
  int f1 = 5;
  const int *str = &f1;
  int c = ' ';
  s21_size_t n = 3;
  ck_assert_pstr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(memchr_2) {
  int f1 = 5;
  const int *str = &f1;
  char c = ' ';
  s21_size_t n = 5;
  ck_assert_pstr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(memchr_3) {
  const char *str = "ХЕЙ!!! ВАЧИ";
  int c = 'u';
  s21_size_t n = 1;
  ck_assert_pstr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(memchr_4) {
  const char *str = "БУЛЕТ БУЛЕТ";
  int c = 'u';
  s21_size_t n = 1;
  ck_assert_pstr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(memchr_5) {
  const char *str = "ГТА РУЛИТ!";
  int c = 'b';
  s21_size_t n = 1;
  ck_assert_pstr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(memchr_6) {
  const char *str = "123456789";
  int c = '6';
  s21_size_t n = 1;
  ck_assert_pstr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(memchr_7) {
  const char *str = "1";
  int c = '1';
  s21_size_t n = 1;
  ck_assert_pstr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(memchr_8) {
  const char *str = "Blablu";
  int c = 'u';
  s21_size_t n = 1;
  ck_assert_pstr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(memchr_9) {
  const char *str = "Blutuze";
  int c = 'u';
  s21_size_t n = 1;
  ck_assert_pstr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(memchr_10) {
  const char *str = "I love kiss my cat";
  int c = 'c';
  s21_size_t n = 1;
  ck_assert_pstr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(memchr_11) {
  const char *str =
      "Uudhqslkjdnlkehiwrjvlkewrnvbkqerufjolmwenifuhouw;ielfkjnl1i3oruhijo";
  int c = 'u';
  s21_size_t n = 1;
  ck_assert_pstr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(memchr_12) {
  const char *str =
      "ghjukidemitkk,ui,myjmyjmjmjmjmjmjyttryrfdsfwbryuiopmngbfvdcrtryuiopoi";
  int c = 'u';
  s21_size_t n = 1;
  ck_assert_pstr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

// 2
START_TEST(memcmp_1) {
  const char *str1 = "1";
  const char *str2 = "-1";
  s21_size_t n = 1;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(memcmp_2) {
  const char *str1 = "SASASASASA";
  const char *str2 = "";
  s21_size_t n = 0;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(memcmp_3) {
  const char *str1 = "HELLOWORD";
  const char *str2 = "";
  s21_size_t n = 0;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(memcmp_4) {
  const char *str1 = "Kiss";
  const char *str2 = "Kiss";
  s21_size_t n = 3;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(memcmp_5) {
  const char *str1 = "K";
  const char *str2 = "";
  s21_size_t n = 0;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(memcmp_6) {
  const char *str1 = "123456";
  const char *str2 = "";
  s21_size_t n = 0;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(memcmp_7) {
  const char *str1 = "asas";
  const char *str2 = "asas";
  s21_size_t n = 10;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(memcmp_8) {
  const char *str1 = "Bulite";
  const char *str2 = "Bulite";
  s21_size_t n = 7;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(memcmp_9) {
  const char *str1 = "Bulite";
  const char *str2 = "";
  s21_size_t n = 0;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(memcmp_10) {
  const char *str1 = "School 21";
  const char *str2 = "School 21";
  s21_size_t n = 1;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

//(3)
START_TEST(memcpy_1) {
  char dest[] = "Hola";
  const char src[] = "aloH";
  s21_size_t n = 1;
  ck_assert_str_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
}
END_TEST

START_TEST(memcpy_2) {
  char *dest = "";
  const char *src = "_Good_";
  s21_size_t n = 0;
  ck_assert_str_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
}
END_TEST

START_TEST(memcpy_3) {
  char dest[] = "\n\n\n";
  const char src[] = "_Good_1234..//,,";
  s21_size_t n = 3;
  ck_assert_str_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
}
END_TEST

START_TEST(memcpy_4) {
  char dest[] = "Hello\0world";
  const char src[] = "Ke\0lly\0";
  s21_size_t n = 3;
  ck_assert_str_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
}
END_TEST

START_TEST(memcpy_5) {
  char dest[] = "AIUGCW\0\0\0\0UD";
  const char src[] = "Kelly\0";
  s21_size_t n = 3;
  ck_assert_str_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
}
END_TEST

START_TEST(memcpy_6) {
  char dest[] = "\0WFIYQIWUDFOQD";
  const char src[] = "KeDSDSDSDlly\0";
  s21_size_t n = 3;
  ck_assert_str_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
}
END_TEST

START_TEST(memcpy_7) {
  char dest[] = "Hello\0world";
  const char src[] = "KeSDSDSDSlly\0";
  s21_size_t n = 3;
  ck_assert_str_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
}
END_TEST

START_TEST(memcpy_8) {
  char dest[] = "HDSFSDFSD\0\0ello\0woDSDFSDFSrld";
  const char src[] = "KeSDFSDFlly\0";
  s21_size_t n = 3;
  ck_assert_str_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
}
END_TEST

START_TEST(memcpy_9) {
  char dest[] = "H\0V\0\0\0\0\0\0el\0\0lo\0world";
  const char src[] = "K\0\0\0\0\0\0elly\0";
  s21_size_t n = 3;
  ck_assert_str_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
}
END_TEST

//(4)

START_TEST(memset_1) {
  char str[] = "Hello_1235";
  int c = ' ';
  s21_size_t n = 5;
  ck_assert_str_eq(s21_memset(str, c, n), memset(str, c, n));
}
END_TEST

START_TEST(memset_2) {
  char str[] = "Hello_1235";
  int c = ' ';
  s21_size_t n = 1;
  ck_assert_str_eq(s21_memset(str, c, n), memset(str, c, n));
}
END_TEST

START_TEST(memset_3) {
  char str[] = "Hello_1235";
  int c = ' ';
  s21_size_t n = 11;
  ck_assert_str_eq(s21_memset(str, c, n), memset(str, c, n));
}
END_TEST

START_TEST(memset_4) {
  char str[] = "Hello_1235";
  int c = ' ';
  s21_size_t n = 6;
  ck_assert_str_eq(s21_memset(str, c, n), memset(str, c, n));
}
END_TEST

START_TEST(memset_5) {
  char str[] = "Hell";
  int c = ' ';
  s21_size_t n = 2;
  ck_assert_str_eq(s21_memset(str, c, n), memset(str, c, n));
}
END_TEST

START_TEST(memset_6) {
  char str[] = "Hello_1235";
  int c = '/';
  s21_size_t n = 11;
  ck_assert_str_eq(s21_memset(str, c, n), memset(str, c, n));
}
END_TEST

START_TEST(memset_7) {
  char str[] = "Hello_45454545454554";
  int c = ' ';
  s21_size_t n = 20;
  ck_assert_str_eq(s21_memset(str, c, n), memset(str, c, n));
}
END_TEST

START_TEST(memset_8) {
  char str[] = "Hello_1235";
  int c = '1';
  s21_size_t n = 11;
  ck_assert_str_eq(s21_memset(str, c, n), memset(str, c, n));
}
END_TEST

START_TEST(memset_9) {
  char str[] = "Hello_1235678910";
  int c = '4';
  s21_size_t n = 11;
  ck_assert_str_eq(s21_memset(str, c, n), memset(str, c, n));
  ;
}
END_TEST

START_TEST(memset_10) {
  char str[] = "Hello";
  int c = 'r';
  s21_size_t n = 5;
  ck_assert_str_eq(s21_memset(str, c, n), memset(str, c, n));
}
END_TEST

// (5) s21_strncat

START_TEST(strncat_1) {  // добавляет n символов к строке (добавляет строку, на
                         // которую указывает src, в конец строки, на которую
                         // указывает dest, длиной до n символов)
  char dest_1[] = "";
  char dest_2[] = "";
  const char src[] = "";
  s21_size_t n = 0;
  s21_strncat(dest_1, src, n);
  strncat(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(strncat_2) {
  char dest_1[5] = "Hola";
  char dest_2[5] = "Hola";
  const char src[] = "";
  s21_size_t n = 2;
  s21_strncat(dest_1, src, n);
  strncat(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(strncat_3) {
  char dest_1[20] = "Hola";
  char dest_2[20] = "Hola";
  const char src[] = "Como estas?";
  s21_size_t n = 9;
  s21_strncat(dest_1, src, n);
  strncat(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(strncat_4) {
  char dest_1[10] = "";
  char dest_2[10] = "";
  const char src[] = "Hola";
  s21_size_t n = 3;
  s21_strncat(dest_1, src, n);
  strncat(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(strncat_5) {
  char dest_1[10] = "Hola\n";
  char dest_2[10] = "Hola\n";
  const char src[] = "\0!";
  s21_size_t n = 3;
  s21_strncat(dest_1, src, n);
  strncat(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(strncat_6) {
  char dest_1[10] = "Hola";
  char dest_2[10] = "Hola";
  const char src[] = "\n!";
  s21_size_t n = 5;
  s21_strncat(dest_1, src, n);
  strncat(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(strncat_7) {
  char dest_1[10] = "Hola";
  char dest_2[10] = "Hola";
  const char src[5] = "GM!";
  s21_size_t n = -3;
  s21_strncat(dest_1, src, n);
  strncat(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(strncat_8) {
  char dest_1[10] = "Hola";
  char dest_2[10] = "Hola";
  const char src[] = "Hola";
  s21_size_t n = 3;
  s21_strncat(dest_1, src, n);
  strncat(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(strncat_9) {
  char dest_1[10] = "Bitch";
  char dest_2[10] = "Bitch";
  const char src[] = "Hola";
  s21_size_t n = 3;
  s21_strncat(dest_1, src, n);
  strncat(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(strncat_10) {
  char dest_1[10] = "Bitch";
  char dest_2[10] = "Bitch";
  const char src[] = "Hola";
  s21_size_t n = 4;
  s21_strncat(dest_1, src, n);
  strncat(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

// (6) strchr

START_TEST(strchr_1) {
  const char *str = "Figna";
  int c = ' ';
  ck_assert_pstr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(strchr_2) {
  const char *str = "q";
  int c = 'q';
  ck_assert_str_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(strchr_3) {
  const char *str = "Bygaga";
  int c = 'g';
  ck_assert_str_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(strchr_4) {
  const char *str = " Net";
  int c = '\0';
  ck_assert_str_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(strchr_5) {
  const char *str = "Hello word!";
  int c = 'o';
  ck_assert_str_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(strchr_6) {
  const char *str = "Hell\0o  word";
  int c = ' ';
  ck_assert_pstr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(strchr_7) {
  const char *str = "Hello/word!";
  int c = '/';
  ck_assert_str_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(strchr_8) {
  const char str[] = {'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'd', '\0'};
  int c = 'l';
  ck_assert_str_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(strchr_9) {
  const char str[] = {'p', 'r', 'i', 'v', 'e', 't', '\0'};
  int c = 't';
  ck_assert_str_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(strchr_10) {
  const char str[] = {'\0', 'q', 'i', 'i', 'e', 'a', 'e'};
  int c = '\0';
  ck_assert_str_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

// (7) strncmp
START_TEST(strncmp_1) {
  const char str1[] = "Yello word!";
  const char str2[] = "Yello word!";
  s21_size_t n = 0;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST

START_TEST(strncmp_2) {
  const char str1[] = "Aloxa";
  const char str2[] = "Aloxa";
  s21_size_t n = 3;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST

START_TEST(strncmp_3) {
  const char str1[] = "byu";
  const char str2[] = "i\byu";
  s21_size_t n = 3;
  int a, b;
  a = s21_strncmp(str1, str2, n);
  if (a < 0) a = -1;
  b = strncmp(str1, str2, n);
  if (b < 0) b = -1;
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(strncmp_4) {
  const char str1[] = "aaaaa";
  const char str2[] = "aaaaandashbdsa";
  s21_size_t n = -3;
  int a, b;
  a = s21_strncmp(str1, str2, n);
  if (a < 0) a = -1;
  b = strncmp(str1, str2, n);
  if (b < 0) b = -1;
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(strncmp_5) {
  const char str1[] = "cwtyfgusahjas";
  const char str2[] = "cwtyfgusahjaslsadau";
  s21_size_t n = -3;
  int a, b;
  a = s21_strncmp(str1, str2, n);
  if (a < 0) a = -1;
  b = strncmp(str1, str2, n);
  if (b < 0) b = -1;
  ck_assert_int_eq(a, b);
}
END_TEST

// (8)  strncpy
START_TEST(strncpy_1) {
  char dest_1[] = "Hello_word !";
  char dest_2[] = "Hello_word !";
  const char src[] = "Hi! My name";
  s21_size_t n = 3;
  ck_assert_str_eq(s21_strncpy(dest_1, src, n), strncpy(dest_2, src, n));
}
END_TEST

START_TEST(strncpy_2) {
  char dest_1[] = "Hello\0Word";
  char dest_2[] = "Hello\0Word";
  const char src[] = "o\n";
  s21_size_t n = 3;
  ck_assert_str_eq(s21_strncpy(dest_1, src, n), strncpy(dest_2, src, n));
}
END_TEST

START_TEST(strncpy_3) {
  char dest_1[] = "gv,maw,gbn ...../../.. 3....fg;l bkdvaalmsv";
  char dest_2[] = "gv,maw,gbn ...../../.. 3....fg;l bkdvaalmsv";
  const char src[] = "=/\\/\\/\\/\\/\\=";
  s21_size_t n = 6;
  ck_assert_str_eq(s21_strncpy(dest_1, src, n), strncpy(dest_2, src, n));
}
END_TEST

START_TEST(strncpy_4) {
  char dest_1[] = "By\0";
  char dest_2[] = "By\0";
  const char src[] = "By\n";
  s21_size_t n = 4;
  ck_assert_str_eq(s21_strncpy(dest_1, src, n), strncpy(dest_2, src, n));
}
END_TEST

START_TEST(strncpy_5) {
  char dest_1[] = "L.N. Tolstoy was born in 1828)";
  char dest_2[] = "L.N. Tolstoy was born in 1828)";
  const char src[] = "e = 2,718281828";
  s21_size_t n = 11;
  ck_assert_str_eq(s21_strncpy(dest_1, src, n), strncpy(dest_2, src, n));
}
END_TEST
// (9)   strcspn
START_TEST(strcspn_1) {  // поиск первого вхождения в строку str1 любого из
                         // символов строки str2, и возвращает количество
                         // символов до найденного первого вхождения
  const char str1[] = "";
  const char str2[] = "";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(strcspn_2) {
  const char str1[] = "Hola";
  const char str2[] = "";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(strcspn_3) {
  const char str1[] = "Hola";
  const char str2[] = "l";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(strcspn_4) {
  const char str1[] = "";
  const char str2[] = "amor";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(strcspn_5) {
  const char str1[] = "G0ogle";
  const char str2[] = "0oo";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(strcspn_6) {
  const char str1[] = "0123";
  const char str2[] = "123";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(strcspn_7) {
  const char str1[] = "01erg78f on w4 pmv../j./...,,,.l";
  const char str2[] = " .";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(strcspn_8) {
  const char str1[] = "\n";
  const char str2[] = "01erg78fonw4pmv../j./...,,,.l";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(strcspn_9) {
  const char str1[] = "MY: name is 'S', 'T', 'R', 'C', 'S', 'P', 'N' - 1";
  const char str2[] = "01erg78fonw4pmv../j./...,,,.l";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(strcspn_10) {
  const char str1[] = "Quiero volar a un pais calido";
  const char str2[] = "\0";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST
// (10) strerror
START_TEST(strerror_1) { ck_assert_str_eq(s21_strerror(7), strerror(7)); }
END_TEST

START_TEST(strerror_2) { ck_assert_str_eq(s21_strerror(1), strerror(1)); }
END_TEST

START_TEST(strerror_3) { ck_assert_pstr_eq((s21_strerror(44)), strerror(44)); }
END_TEST

START_TEST(strerror_4) { ck_assert_str_eq((s21_strerror(100)), strerror(100)); }
END_TEST

START_TEST(strerror_5) { ck_assert_pstr_eq(s21_strerror(0), strerror(0)); }
END_TEST

// (11)  strlen
START_TEST(strlen_1) {  // вычисляет длину строки str, не включая завершающий
                        // нулевой символ
  const char str[] = {""};
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_2) {
  const char str[] = {"abcdefg"};
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_3) {
  const char str[] = {"0123456789"};
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_4) {
  const char str[] = {"0123456789ABCDEFGabcdefg\0"};
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_5) {
  const char str[] = {"ABCDEFGab\0cdefg"};
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_6) {
  const char str[] = {"ABCDEFG_ab(54321)..//,\n"};
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_7) {
  const char str[] = {"First_line\nSecond_line"};
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_8) {
  const char str[] = {"\n"};
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_9) {
  const char str[] = {" "};
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strlen_10) {
  char str[] = {"x"};
  for (int i = 0; i < (int)strlen(str); i++) {
    if (str[i] == '\0') str[i] = '\n';
  }
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST
// (12)  strpbrk
START_TEST(strpbrk_1) {  // выполняет поиск первого вхождения в строку str1
                         // любого из символов строки str2, и возвращает
                         // указатель на найденный символ
  const char str1[] = {'q', 'r', 's', 't', 'w', '\0'};
  const char str2[] = {'q', 'r', 's', 't', 'w', '\0'};
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_2) {
  const char str1[] = "Bla bla bla";
  const char str2[] = "l";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_3) {
  const char str1[] = " Bla bla bla";
  const char str2[] = " ";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_4) {
  const char str1[] = "Bla bla bla";
  const char str2[] = "\0";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_5) {
  const char str1[] = "Bla bla bla";
  const char str2[] = "";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_6) {
  const char str1[] = "Bla bla bla";
  const char str2[] = "\n";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST
// (13)  strrchr
START_TEST(
    strrchr_1) {  // выполняет поиск последнего вхождения символа c (беззнаковый
                  // тип) в строке, на которую указывает аргумент str
  const char str[] = "koi";
  int c = 'k';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_2) {
  const char str[] = "j8888888888j";
  int c = 'j';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_3) {
  const char str[] = "";
  int c = 'j';
  ck_assert_pstr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_4) {
  const char str[] = "123456781556155615";
  int c = '1';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST
// (14)  strstr
START_TEST(
    strstr_1) {  // функция ищет первое вхождение подстроки str2 в строке str1
  const char haystack[] = "opjbqajknp'qbjk";
  const char needle[] = "8op";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_2) {
  const char haystack[] = "[piojhicyfg'0iuj[pl]";
  const char needle[] = "\0";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_3) {
  const char haystack[] = "yfkud7d7tdyug8yg";
  const char needle[] = "yg";
  ck_assert_str_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_4) {
  const char haystack[] = "wtf";
  const char needle[] = "qtjnamywrnswynwrysfqthas";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_5) {
  const char *haystack = "zb./../.../ghrrwsnbnbb";
  const char *needle = "/";
  ck_assert_str_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST
// (15)  strtok
START_TEST(strtok_1) {
  char str[] = "Hello word";
  const char delim[] = "word";
  ck_assert_str_eq(s21_strtok(str, delim), strtok(str, delim));
}
END_TEST

START_TEST(strtok_2) {
  char str[] = "Byyyratino";
  const char delim[] = "ratino";
  ck_assert_str_eq(s21_strtok(str, delim), strtok(str, delim));
}
END_TEST

START_TEST(strtok_3) {
  char str[] = "Hello word!";
  const char delim[] = "";
  ck_assert_str_eq(s21_strtok(str, delim), strtok(str, delim));
}
END_TEST

START_TEST(strtok_4) {
  char str[] = "He llo";
  const char delim[] = " ";
  ck_assert_str_eq(s21_strtok(str, delim), strtok(str, delim));
}
END_TEST

START_TEST(strtok_5) {
  char str[] = "By Hello";
  const char delim[] = "\0";
  ck_assert_str_eq(s21_strtok(str, delim), strtok(str, delim));
}
END_TEST

START_TEST(strtok_6) {
  char str[] = " \0";
  const char delim[] = "Heloo 95645";
  ck_assert_pstr_eq(s21_strtok(str, delim), strtok(str, delim));
}
END_TEST

START_TEST(strtok_7) {
  char str[] = "1";
  const char delim[] = "1";
  ck_assert_pstr_eq(s21_strtok(str, delim), strtok(str, delim));
}
END_TEST

START_TEST(strtok_8) {
  char str[] = "3";
  const char delim[] = "4";
  ck_assert_pstr_eq(s21_strtok(str, delim), strtok(str, delim));
}
END_TEST

START_TEST(strtok_9) {
  char str[] = "00";
  const char delim[] = "00";
  ck_assert_pstr_eq(s21_strtok(str, delim), strtok(str, delim));
}
END_TEST

START_TEST(strtok_10) {
  char str[] = "\0";
  const char delim[] = "\0";
  ck_assert_pstr_eq(s21_strtok(str, delim), strtok(str, delim));
}
END_TEST

int main(void) {
  int number_failed = 0;  // для хранения количества неудачных тестов
  Suite *s;  // указатель на suite
  s = suite_create(
      "string");  // вызываем функцию, чтобы создать и вернуть test suite
  SRunner *sr;    // указатель на srunner
  sr = srunner_create(
      s);  // используем test suite и передаем их функции srunner_create, чтобы
           // получить указатель на test suite runner

  TCase *tc_memchr = tcase_create("memchr");
  suite_add_tcase(s, tc_memchr);
  tcase_add_test(tc_memchr, memchr_1);
  tcase_add_test(tc_memchr, memchr_2);
  tcase_add_test(tc_memchr, memchr_3);
  tcase_add_test(tc_memchr, memchr_4);
  tcase_add_test(tc_memchr, memchr_5);
  tcase_add_test(tc_memchr, memchr_6);
  tcase_add_test(tc_memchr, memchr_7);
  tcase_add_test(tc_memchr, memchr_8);
  tcase_add_test(tc_memchr, memchr_9);
  tcase_add_test(tc_memchr, memchr_10);
  tcase_add_test(tc_memchr, memchr_11);
  tcase_add_test(tc_memchr, memchr_12);

  TCase *tc_memcmp = tcase_create("memcmp");
  suite_add_tcase(s, tc_memcmp);
  tcase_add_test(tc_memcmp, memcmp_1);
  tcase_add_test(tc_memcmp, memcmp_2);
  tcase_add_test(tc_memcmp, memcmp_3);
  tcase_add_test(tc_memcmp, memcmp_4);
  tcase_add_test(tc_memcmp, memcmp_5);
  tcase_add_test(tc_memcmp, memcmp_6);
  tcase_add_test(tc_memcmp, memcmp_7);
  tcase_add_test(tc_memcmp, memcmp_8);
  tcase_add_test(tc_memcmp, memcmp_9);
  tcase_add_test(tc_memcmp, memcmp_10);

  TCase *tc_memcpy = tcase_create("memcpy");
  suite_add_tcase(s, tc_memcpy);
  tcase_add_test(tc_memcpy, memcpy_1);
  tcase_add_test(tc_memcpy, memcpy_2);
  tcase_add_test(tc_memcpy, memcpy_3);
  tcase_add_test(tc_memcpy, memcpy_4);
  tcase_add_test(tc_memcpy, memcpy_5);
  tcase_add_test(tc_memcpy, memcpy_6);
  tcase_add_test(tc_memcpy, memcpy_7);
  tcase_add_test(tc_memcpy, memcpy_8);
  tcase_add_test(tc_memcpy, memcpy_9);

  TCase *tc_memset = tcase_create("memset");
  suite_add_tcase(s, tc_memset);
  tcase_add_test(tc_memset, memset_1);
  tcase_add_test(tc_memset, memset_2);
  tcase_add_test(tc_memset, memset_3);
  tcase_add_test(tc_memset, memset_4);
  tcase_add_test(tc_memset, memset_5);
  tcase_add_test(tc_memset, memset_6);
  tcase_add_test(tc_memset, memset_7);
  tcase_add_test(tc_memset, memset_8);
  tcase_add_test(tc_memset, memset_9);
  tcase_add_test(tc_memset, memset_10);

  TCase *tc_strncat = tcase_create("strncat");
  suite_add_tcase(s, tc_strncat);
  tcase_add_test(tc_strncat, strncat_1);
  tcase_add_test(tc_strncat, strncat_2);
  tcase_add_test(tc_strncat, strncat_3);
  tcase_add_test(tc_strncat, strncat_4);
  tcase_add_test(tc_strncat, strncat_5);
  tcase_add_test(tc_strncat, strncat_6);
  tcase_add_test(tc_strncat, strncat_7);
  tcase_add_test(tc_strncat, strncat_8);
  tcase_add_test(tc_strncat, strncat_9);
  tcase_add_test(tc_strncat, strncat_10);

  TCase *tc_strchr = tcase_create("strchr");
  suite_add_tcase(s, tc_strchr);
  tcase_add_test(tc_strchr, strchr_1);
  tcase_add_test(tc_strchr, strchr_2);
  tcase_add_test(tc_strchr, strchr_3);
  tcase_add_test(tc_strchr, strchr_4);
  tcase_add_test(tc_strchr, strchr_5);
  tcase_add_test(tc_strchr, strchr_6);
  tcase_add_test(tc_strchr, strchr_7);
  tcase_add_test(tc_strchr, strchr_8);
  tcase_add_test(tc_strchr, strchr_9);
  tcase_add_test(tc_strchr, strchr_10);

  TCase *tc_strncmp = tcase_create("strncmp");
  suite_add_tcase(s, tc_strncmp);
  tcase_add_test(tc_strncmp, strncmp_1);
  tcase_add_test(tc_strncmp, strncmp_2);
  tcase_add_test(tc_strncmp, strncmp_3);
  tcase_add_test(tc_strncmp, strncmp_4);
  tcase_add_test(tc_strncmp, strncmp_5);

  TCase *tc_strtok = tcase_create("strtok");
  suite_add_tcase(s, tc_strtok);
  tcase_add_test(tc_strtok, strtok_1);
  tcase_add_test(tc_strtok, strtok_2);
  tcase_add_test(tc_strtok, strtok_3);
  tcase_add_test(tc_strtok, strtok_4);
  tcase_add_test(tc_strtok, strtok_5);
  tcase_add_test(tc_strtok, strtok_6);
  tcase_add_test(tc_strtok, strtok_7);
  tcase_add_test(tc_strtok, strtok_8);
  tcase_add_test(tc_strtok, strtok_9);
  tcase_add_test(tc_strtok, strtok_10);

  TCase *tc_strncpy = tcase_create("strncpy");
  suite_add_tcase(s, tc_strncpy);
  tcase_add_test(tc_strncpy, strncpy_1);
  tcase_add_test(tc_strncpy, strncpy_2);
  tcase_add_test(tc_strncpy, strncpy_3);
  tcase_add_test(tc_strncpy, strncpy_4);
  tcase_add_test(tc_strncpy, strncpy_5);

  TCase *tc_strcspn = tcase_create("strcspn");
  suite_add_tcase(s, tc_strcspn);
  tcase_add_test(tc_strcspn, strcspn_1);
  tcase_add_test(tc_strcspn, strcspn_2);
  tcase_add_test(tc_strcspn, strcspn_3);
  tcase_add_test(tc_strcspn, strcspn_4);
  tcase_add_test(tc_strcspn, strcspn_5);
  tcase_add_test(tc_strcspn, strcspn_6);
  tcase_add_test(tc_strcspn, strcspn_7);
  tcase_add_test(tc_strcspn, strcspn_8);
  tcase_add_test(tc_strcspn, strcspn_9);
  tcase_add_test(tc_strcspn, strcspn_10);

  TCase *tc_strerror = tcase_create("strerror");
  suite_add_tcase(s, tc_strerror);
  tcase_add_test(tc_strerror, strerror_1);
  tcase_add_test(tc_strerror, strerror_2);
  tcase_add_test(tc_strerror, strerror_3);
  tcase_add_test(tc_strerror, strerror_4);
  tcase_add_test(tc_strerror, strerror_5);

  TCase *tc_strlen = tcase_create("strlen");
  suite_add_tcase(s, tc_strlen);
  tcase_add_test(tc_strlen, strlen_1);
  tcase_add_test(tc_strlen, strlen_2);
  tcase_add_test(tc_strlen, strlen_3);
  tcase_add_test(tc_strlen, strlen_4);
  tcase_add_test(tc_strlen, strlen_5);
  tcase_add_test(tc_strlen, strlen_6);
  tcase_add_test(tc_strlen, strlen_7);
  tcase_add_test(tc_strlen, strlen_8);
  tcase_add_test(tc_strlen, strlen_9);
  tcase_add_test(tc_strlen, strlen_10);

  TCase *tc_strpbrk = tcase_create("strpbrk");
  suite_add_tcase(s, tc_strpbrk);
  tcase_add_test(tc_strpbrk, strpbrk_1);
  tcase_add_test(tc_strpbrk, strpbrk_2);
  tcase_add_test(tc_strpbrk, strpbrk_3);
  tcase_add_test(tc_strpbrk, strpbrk_4);
  tcase_add_test(tc_strpbrk, strpbrk_5);
  tcase_add_test(tc_strpbrk, strpbrk_6);

  TCase *tc_strrchr = tcase_create("strrchr");
  suite_add_tcase(s, tc_strrchr);
  tcase_add_test(tc_strrchr, strrchr_1);
  tcase_add_test(tc_strrchr, strrchr_2);
  tcase_add_test(tc_strrchr, strrchr_3);
  tcase_add_test(tc_strrchr, strrchr_4);

  TCase *tc_strstr = tcase_create("strstr");
  suite_add_tcase(s, tc_strstr);
  tcase_add_test(tc_strstr, strstr_1);
  tcase_add_test(tc_strstr, strstr_2);
  tcase_add_test(tc_strstr, strstr_3);
  tcase_add_test(tc_strstr, strstr_4);
  tcase_add_test(tc_strstr, strstr_5);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}