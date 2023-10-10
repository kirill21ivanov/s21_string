#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  const char *str_start = (char *)str;
  *str = '\0';
  format_token tok;
  char *f = (char *)format;
  if (format == NULL || *format == '\0') {  // в настоящем вроде сега
  } else {
    va_list(ap);
    va_start(ap, format);
    for (; *f; f++) {
      if (*f != '%') {  // если не процент, то сразу кидаем в массив
        *str = *f;
        str++;
        *str = '\0';
      } else if (*f == '%') {
        s21_init_format_token(&tok);
        char *start = f;  // строчка которая начинается с процента
        f++;
        f = s21_parse_flag(f, &tok);
        f = s21_parse_width(f, &tok, ap);
        f = s21_parse_prec(f, &tok, ap);
        f = s21_parse_length(f, &tok);
        while (*f == ' ') f++;  // лишние пробелы перед специфекатором
        if (*f == 'c' || *f == 'd' || *f == 'i' || *f == 'e' || *f == 'E' ||
            *f == 'f' || *f == 'g' || *f == 'G' || *f == 'o' || *f == 's' ||
            *f == 'u' || *f == 'X' || *f == 'x' || *f == 'p' || *f == 'n') {
          tok.spec = *f;
          int count_for_n = (int)s21_strlen(str_start);
          s21_check_spec(&tok, &str, ap, count_for_n);
        } else {
          while (*start != *f) {
            *str = *start;
            str++;
            *str = '\0';
            start++;
          }
          *str = *f;
          str++;
          *str = '\0';
        }
      }
    }
    va_end(ap);
  }
  return (int)(str - str_start);
}

void s21_check_spec(format_token *tok, char **str, va_list ap,
                    int count_for_n) {
  if (tok->spec == 'd' || tok->spec == 'i') {
    s21_spec_i(str, *tok, ap);
    **str = '\0';
  }
  if (tok->spec == 'c') {
    s21_char_format_token(tok);
    s21_spec_c(str, *tok, ap);
    **str = '\0';
  }
  if (tok->spec == 's') {
    s21_spec_s(str, *tok, ap, 0);
    **str = '\0';
  }
  if (tok->spec == 'f') {
    s21_spec_f(str, *tok, ap);
    **str = '\0';
  }
  if (tok->spec == 'u') {
    s21_uint(str, *tok, ap);
    **str = '\0';
  }
  if (tok->spec == 'e' || tok->spec == 'E' || tok->spec == 'g' ||
      tok->spec == 'G') {
    s21_spec_eE(str, *tok, ap);
    **str = '\0';
  }
  if (tok->spec == 'n') {
    int *arg = va_arg(ap, int *);
    *arg = count_for_n;
    **str = '\0';
  }
  if (tok->spec == 'p' || tok->spec == 'o' || tok->spec == 'x' ||
      tok->spec == 'X') {
    s21_spec_p(str, *tok, ap);
    **str = '\0';
  }
  if (tok->spec == '%') {
    **str = '%';
    str++;
    **str = '\0';
  }
}
