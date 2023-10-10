#include "s21_string.h"

char *s21_parse_width(char *f, format_token *tok, va_list ap) {
  if (s21_isdigit(*f)) {
    char temp_buf[s21_buf_size];
    int i = 0;
    while (s21_isdigit(*f)) {
      temp_buf[i] = *f;
      i++;
      temp_buf[i] = '\0';
      f++;
    }
    tok->width = s21_atoi(temp_buf);
  } else if (*f == '*') {
    tok->width = va_arg(ap, int);
    f++;
  }
  return f;
}

char *s21_parse_width_scan(char *f, format_token *tok) {
  if (s21_isdigit(*f)) {
    char temp_buf[s21_buf_size];
    int i = 0;
    while (s21_isdigit(*f)) {
      temp_buf[i] = *f;
      i++;
      temp_buf[i] = '\0';
      f++;
    }
    tok->width = s21_atoi(temp_buf);
  }
  return f;
}

char *s21_parse_flag(char *f, format_token *tok) {
  while (*f == ' ' || *f == '+' || *f == '-' || *f == '0' || *f == '#') {
    if (*f == ' ') tok->space = 1;
    if (*f == '+') tok->plus = 1;
    if (*f == '-') tok->minus = 1;
    if (*f == '0') tok->zero = 1;
    if (*f == '#') tok->hash = 1;
    f++;
  }
  return f;
}

char *s21_parse_length(char *f, format_token *tok) {
  if (*f == 'l' || *f == 'L' || *f == 'h') {
    tok->length = *f;
    f++;
  }
  return f;
}

char *s21_parse_prec(char *f, format_token *tok, va_list ap) {
  if (*f == '.') {
    tok->prec = 0;
    f++;
    if (s21_isdigit(*f)) {
      char temp_buf[s21_buf_size];
      int i = 0;
      while (s21_isdigit(*f)) {
        temp_buf[i] = *f;
        i++;
        temp_buf[i] = '\0';
        f++;
      }
      tok->prec = s21_atoi(temp_buf);
    } else if (*f == '*') {
      tok->prec = va_arg(ap, int);
      f++;
    }
  }
  return f;
}

void s21_init_format_token(format_token *tok) {
  tok->minus = 0;
  tok->plus = 0;
  tok->space = 0;
  tok->zero = 0;
  tok->hash = 0;
  tok->length = 'n';
  tok->spec = 'n';
  tok->prec = -1;
  tok->width = 0;
  tok->star = 0;
}

void s21_char_format_token(format_token *tok) {
  tok->plus = 0;
  tok->space = 0;
  tok->prec = -1;
  tok->hash = 0;
}

int s21_isdigit(int ch) { return (ch >= '0' && ch <= '9' ? 1 : 0); }

int s21_atoi(char *str) {
  int i = 0;
  int res = 0;
  while (s21_isdigit(str[i])) {
    res *= 10;
    res += str[i] - '0';
    i++;
  }
  return res;
}

char *s21_parse_star(char *f, format_token *tok) {
  if (*f == '*') {
    tok->star = 1;
    f++;
  }
  return f;
}

long double s21_atold(char *str, char **strlim, format_token *att) {
  char *start = str;
  long double a, decplace, b;
  int sign = 1;
  while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r' ||
         *str == '\x0B' || *str == '\f')
    ++str;
  if (*str == '+') {
    att->width--;
    ++str;
  }
  if (*str == '-') {
    sign = -1;
    ++str;
    att->width--;
  }
  for (a = 0; *str && s21_isdigit(*str) && att->width > 0; ++str, att->width--)
    a = a * 10 + (*str - '0');
  if (*str == '.') {
    ++str;
    att->width--;
  }
  for (decplace = 1.; *str && s21_isdigit(*str) && att->width > 0;
       ++str, decplace *= 10., att->width--)
    a = a * 10. + (*str - '0');
  if (*str == 'e' || *str == 'E') {
    int esign = 1;
    if (a <= 1e-6) a = 1;
    ++str;
    att->width--;
    if (*str == '-') {
      esign = -1;
      ++str;
      att->width--;
    }
    if (*str == '+') {
      ++str;
      att->width--;
    }
    for (b = 0; *str && s21_isdigit(*str) && att->width > 0;
         ++str, att->width--)
      b = b * 10 + (*str - '0');
    b *= esign;
  } else {
    b = 0;
  }
  if ((*str == 'n' || *str == 'N') && (str[1] == 'a' || str[1] == 'A') &&
      (str[2] == 'n' || str[2] == 'N')) {
    str += 3;
    a = NAN * sign;
  }
  if ((*str == 'i' || *str == 'I') && (str[1] == 'n' || str[1] == 'N') &&
      (str[2] == 'f' || str[2] == 'F')) {
    str += 3;
    a = INFINITY * sign;
  }
  if (strlim) *strlim = start + (str - start);
  return (isnan(a) || isinf(a)) ? a : (a * sign / decplace) * powl(10, b);
}

double s21_atod(char *str, char **strlim, format_token *att) {
  return s21_atold(str, strlim, att);
}

float s21_atof(char *str, char **strlim, format_token *att) {
  return s21_atold(str, strlim, att);
}

unsigned long s21_atoul_scan(char *str, char **strlim, format_token *att,
                             int base) {
  return s21_atoi_scan(str, strlim, base, att, 1);
}

long s21_atoi_scan(char *str, char **strlim, int base, format_token *att,
                   int sign) {
  char *start = str;
  long int res = 0;
  if (base == 0 && *str == '0' && *(str + 1) == 'x')
    base = 16;
  else if (base == 0 && *str == '0')
    base = 8;
  else if (base == 0)
    base = 10;
  if (base == 16 && *str == '0' && *(str + 1) == 'x') str += 2;
  if (base == 10) {
    for (; *str >= '0' && *str <= '9' && att->width != 0;
         str++, res *= 10, att->width--)
      res += *str - 48;
    res /= 10;
  } else if (base == 8) {
    for (; *str >= '0' && *str <= '9' && att->width != 0;
         str++, res *= 8, att->width--)
      res += *str - 48;
    res /= 8;
  } else if (base == 16) {
    for (; ((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F') ||
            (*str >= 'a' && *str <= 'f')) &&
           att->width != 0;
         str++, res *= 16, att->width--) {
      if (*str >= '0' && *str <= '9')
        res += *str - 48;
      else if ((*str >= 'A' && *str <= 'F'))
        res += +*str - 55;
      else
        res += +*str - 87;
    }
    res /= 16;
  }
  if (strlim) *strlim = start + (str - start);
  return sign * res;
}
