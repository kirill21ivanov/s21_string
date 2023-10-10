#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>

#include "errors_list.h"

#define s21_buf_size 1000

typedef struct format_token {
  int minus;
  int plus;
  int space;
  int zero;
  int hash;
  int width;
  int prec;
  char length;
  char spec;
  int count;
  int star;
} format_token;

#define s21_NULL ((void *)0)

typedef unsigned long s21_size_t;
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

s21_size_t s21_pointers(const char *str1, const char *str2);  // для ссканф

void *s21_to_upper(const char *str);  // возвращает копию строки (str),
                                      // преобразованную в верхний регистр
void *s21_to_lower(const char *str);  // возвращает копию строки (str),
                                      // преобразованную в нижний регистр
void *s21_insert(
    const char *src, const char *str,
    size_t start_index);  // возвращает новую строку, в которой
                          // указанная строка (str) вставлена
                          // ​​в указанную позицию
                          // индекса (start_index) в заданной строке (src)
void *s21_trim(
    const char *src,
    const char *trim_chars);  // возвращает новую строку, в которой удалены все
                              // начальные и конечные вхождения набора указанных
                              // символов (trim_chars) из заданной строки (src)

int s21_sscanf(const char *str, const char *format, ...);
int s21_spec_s_scan(char **str, format_token *att, va_list args);
int s21_spec_c_scan(char **str, format_token *att, va_list args);
int s21_spec_i_scan(char **str, va_list args, format_token *att, int base);
long s21_atoi_scan(char *str, char **strlim, int base, format_token *att,
                   int sign);
int s21_check_spec_scan(format_token *tok, char **str, va_list ap);
void nice_symb(char **str, format_token *att);
char *s21_sputsf(char **src, format_token *att);
int s21_isspace(int c);
int s21_spec_u_scan(char **str, va_list args, format_token *att, int base);
unsigned long s21_atoul_scan(char *str, char **strlim, format_token *att,
                             int base);
int s21_spec_f_scan(char **str, format_token *att, va_list args);
float s21_atof(char *str, char **strlim, format_token *att);
double s21_atod(char *str, char **strlim, format_token *att);
long double s21_atold(char *str, char **strlim, format_token *att);
char *s21_parse_star(char *f, format_token *tok);
void s21_spec_n_scan(va_list args, format_token *att);
int s21_spec_p_scan(char **str, va_list args, format_token *att);
char *s21_parse_width_scan(char *f, format_token *tok);

// support
void s21_left_side_int(format_token att, char **str, int scale, int negative,
                       long int var_int);
void s21_right_side_int(format_token att, char **str, int scale, int negative,
                        long int var_int, unsigned long int crutch);

void s21_left_side_float(format_token att, char **str, int negative,
                         long double fractional, long double int_part,
                         int scale);
void s21_right_side_float(format_token att, char **str, int negative,
                          long double fractional, long double int_part,
                          int scale);
void s21_handle_int_part_in_float(format_token *att, char **str, int scale,
                                  long double int_part, int minus_width);
void s21_handle_fractional_part_in_float(format_token *att, char **str,
                                         int scale, double rounded_frac);
void s21_handle_zero_in_float(format_token *att, char **str, int negative);
void s21_smart_rounding(double after_point, double rounded_frac,
                        long double *int_part, long double *fractional);

void s21_left_side_uint(format_token att, char **str, int scale,
                        unsigned long int var_int);
void s21_right_side_uint(format_token att, char **str, int scale,
                         unsigned long int var_int);
// support

void s21_check_spec(format_token *tok, char **str, va_list ap, int count_for_n);
// spec
void s21_spec_c(char **str, format_token att, va_list args);
void s21_spec_i(char **str, format_token att, va_list args);
// void spec_n(char *str, format_token att, va_list args);
void s21_spec_s(char **str, format_token att, va_list args, double no_num);
void s21_spec_f(char **str, format_token att, va_list args);
void s21_uint(char **str, format_token att, va_list args);
// spec

// pars
char *s21_parse_length(char *f, format_token *tok);
char *s21_parse_flag(char *f, format_token *tok);
char *s21_parse_prec(char *f, format_token *tok, va_list args);
char *s21_parse_width(char *f, format_token *tok, va_list args);
// pars

int s21_sprintf(char *str, const char *format, ...);

void s21_init_format_token(format_token *tok);
void s21_char_format_token(format_token *tok);

void s21_empty_space_zero(char **str, format_token att, char option);

void s21_first_sym_in_str(format_token *att, char **str, int negative,
                          int count, int print);

int s21_isdigit(int ch);
int s21_atoi(char *str);

void s21_spec_eE(char **str, format_token att, va_list args);
void s21_zero_int_part(format_token *att, char **str, int negative,
                       long double fractional, long double int_part, int scale);
void s21_right_side_eE(format_token *att, char **str, int negative,
                       long double fractional, long double int_part, int scale1,
                       int minus_stepen);
void s21_left_side_eE(format_token *att, char **str, int negative,
                      long double fractional, long double int_part, int scale1,
                      int minus_stepen);
void s21_not_zero_int_part(format_token *att, char **str, long double int_part,
                           long double fractional, int negative, int scale);
void s21_print_exponent(format_token *att, char **str, int minus_stepen);
void s21_count_e(format_token *att, int *minus_stepen, int *minus_scale,
                 int *plus);
void s21_also_print_exp(format_token *att, char **str, int plus,
                        int minus_stepen, int minus_scale);

void s21_spec_p(char **str, format_token att, va_list args);
void s21_print_p(format_token *att, char **str, int count,
                 const char inverted[]);
void s21_create_output(format_token att, char inverted[], int *count,
                       unsigned long long int *var_point);
void s21_minus_prec(format_token *att);

void s21_check_round(long double *int_part, int *minus_stepen,
                     long double *rounded_frac, long double *after_point);
void s21_preparing_ex(format_token *att, char **str, int *negative,
                      long double *fractional, long double *int_part,
                      int *scale, int *minus_stepen, int *flag, int *scale1);

#endif  //  SRC_S21_STRING_H_
