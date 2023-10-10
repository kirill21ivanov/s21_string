#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  char *str_start = (char *)str;
  format_token tok;
  char *f = (char *)format;
  int symbol_count = 0;
  if (format == NULL || *format == '\0') {
  } else {
    va_list(ap);
    va_start(ap, format);
    tok.count = 0;
    for (; *f; f++) {
      while (*f == *str_start) {
        f++;
        str_start++;
      }
      if (*f != '%' &&
          *str_start != '%') {  // если не процент, то сразу выходим
      } else if (*f == '%') {
        f++;
        s21_init_format_token(&tok);
        f = s21_parse_flag(f, &tok);
        tok.width = 2147483647;
        f = s21_parse_width_scan(f, &tok);
        f = s21_parse_star(f, &tok);
        f = s21_parse_length(f, &tok);

        while (*f == ' ') f++;  // лишние пробелы перед специфекатором

        if (*f == 'c' || *f == 'd' || *f == 'i' || *f == 'e' || *f == 'E' ||
            *f == 'f' || *f == 'g' || *f == 'G' || *f == 'o' || *f == 's' ||
            *f == 'u' || *f == 'X' || *f == 'x' || *f == 'p' || *f == 'n') {
          tok.spec = *f;
          symbol_count += s21_check_spec_scan(&tok, &str_start, ap);
        }
      }
    }
    va_end(ap);
  }
  return symbol_count;
}

int s21_check_spec_scan(format_token *tok, char **str, va_list ap) {
  int symbol_count = 0;
  if (tok->spec == 'd') {
    symbol_count += s21_spec_i_scan(str, ap, tok, 10);
  }
  if (tok->spec == 'i') {
    symbol_count += s21_spec_i_scan(str, ap, tok, 0);
  }
  if (tok->spec == 'c') {
    symbol_count += s21_spec_c_scan(str, tok, ap);
  }
  if (tok->spec == 's') {
    symbol_count += s21_spec_s_scan(str, tok, ap);
  }
  if (tok->spec == 'f' || tok->spec == 'e' || tok->spec == 'E' ||
      tok->spec == 'g' || tok->spec == 'G') {
    symbol_count += s21_spec_f_scan(str, tok, ap);
  }
  if (tok->spec == 'u') {
    symbol_count += s21_spec_u_scan(str, ap, tok, 10);
  }
  if (tok->spec == 'x' || tok->spec == 'X') {
    symbol_count += s21_spec_u_scan(str, ap, tok, 16);
  }
  if (tok->spec == 'o') {
    symbol_count += s21_spec_u_scan(str, ap, tok, 8);
  }
  if (tok->spec == 'n') {
    s21_spec_n_scan(ap, tok);
  }
  if (tok->spec == 'p') {
    symbol_count += s21_spec_p_scan(str, ap, tok);
  }
  return symbol_count;
}
