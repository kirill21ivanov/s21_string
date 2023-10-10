#include "s21_string.h"

void s21_spec_i(char **str, format_token att, va_list args) {
  int negative = 0;
  int zero_case = 0;
  unsigned long int crutch = 0;
  long int var_int = va_arg(args, long int);
  if (att.length == 'h')  // если есть флаг h, то работаем с short int
    var_int = (short int)var_int;
  else if (att.length != 'l')  // если нет l, то работаем с int
    var_int = (int)var_int;
  long int ex = var_int;
  int scale = 0;
  while (ex) {
    ex /= 10;
    scale++;  // находи количество цифр в числе
  }
  if (!scale && !var_int) {
    scale = 1;
    if (att.prec == 0) {
      s21_first_sym_in_str(&att, str, negative, 1, 1);
      while (att.width > 0) {
        att.width--;
        *((*str)++) = ' ';
      }
      zero_case = 1;  // костыль для s21_sprintf(buf, "Ab%.dab", 0);
    }
  }
  if (!zero_case) {
    if (att.plus) att.space = 0;
    if (var_int < 0) {
      att.space = 0;  // если число отрицательное то за место пробела знак
      att.width--;  // корректировка ширины если число отрицательное
      negative = 1;
      var_int *= -1;
    }
    if (var_int == INT64_MIN) {  //  костыль для минимального лонг инта
      crutch = (unsigned long int)INT64_MAX + 1;
    }
    if (att.minus) {  // выравнивание по левому краю
      s21_left_side_int(att, str, scale, negative, var_int);
    } else {  // выравнивание по правому краю
      s21_right_side_int(att, str, scale, negative, var_int, crutch);
    }
  }
}

void s21_right_side_int(format_token att, char **str, int scale, int negative,
                        long int var_int, unsigned long int crutch) {
  att.width -= scale;
  if (var_int == 0 && att.prec > 1) att.width++;
  if (att.prec > scale) att.width -= att.prec - scale;
  if (att.space) att.width--;
  if (att.plus && !negative) att.width--;
  if (att.prec >= 0) {  // если есть точность, то 0 не работает
    att.zero = 0;
  }
  if (!att.zero) {
    while (att.width > 0) {
      att.width--;
      *((*str)++) = ' ';
    }
  }
  s21_first_sym_in_str(&att, str, negative, 0, 1);
  if (att.zero) {
    while (att.width > 0) {
      att.width--;
      *((*str)++) = '0';
    }
  }
  while (att.prec-- > scale) {
    *((*str)++) = '0';
    att.width--;
  }
  while (scale--) {
    if (crutch)
      *((*str)++) = crutch / (long int)pow(10, scale) % 10 + 48;
    else
      *((*str)++) = var_int / (long int)pow(10, scale) % 10 + 48;
  }
}

void s21_left_side_int(format_token att, char **str, int scale, int negative,
                       long int var_int) {
  att.width -= scale;
  if (negative) {
    *((*str)++) = '-';
  } else if (att.plus) {
    *((*str)++) = '+';
    att.width--;
  } else if (att.space) {
    *((*str)++) = ' ';
    att.width--;
  }
  while (att.prec-- > scale) {
    *((*str)++) = '0';
    att.width--;
  }
  while (scale--) *((*str)++) = var_int / (long int)pow(10, scale) % 10 + 48;
  while (att.width > 0) {
    att.width--;
    *((*str)++) = ' ';
  }
}

int s21_spec_i_scan(char **str, va_list args, format_token *att, int base) {
  int res = 0, sign = 1, wid = att->width;
  char *strlim;
  while (**str == ' ' || **str == '\n' || **str == '\t' || **str == '\r' ||
         **str == '\x0B' || **str == '\f')
    (*str)++;
  if (**str == '+') {
    (*str)++;
    att->width--;
    wid--;
  }
  if (**str == '-') {
    att->width--;
    wid--;
    (*str)++;
    sign = -1;
  }
  if (**str == '\0' && att->count == 0) {
    res--;
  } else {
    if (s21_atoi_scan(*str, s21_NULL, base, att, sign) ||
        *(*str + s21_pointers(*str, "\n\t \f\x0B\r+-")) == '0') {
      att->width = wid;
      if (!att->star) {
        if (att->length == 'h')
          *(short int *)va_arg(args, void *) =
              s21_atoi_scan(*str, &strlim, base, att, sign);
        else if (att->length == 'l')
          *(long int *)va_arg(args, void *) =
              s21_atoi_scan(*str, &strlim, base, att, sign);
        else
          *(int *)va_arg(args, void *) =
              s21_atoi_scan(*str, &strlim, base, att, sign);
        res++;
      } else {
        s21_atoi_scan(*str, &strlim, base, att, sign);
      }

      att->count += strlim - *str;
      *str = strlim;
    }
  }
  return res;
}

void s21_spec_n_scan(va_list args, format_token *att) {
  if (!att->star) {
    if (att->length == 'h')
      *(short int *)va_arg(args, void *) = att->count;
    else if (att->length == 'l')
      *(long int *)va_arg(args, void *) = att->count;
    else
      *(int *)va_arg(args, void *) = att->count;
  }
}

int s21_spec_p_scan(char **str, va_list args, format_token *att) {
  int res = 0, wid = att->width;
  // char *strlim = s21_NULL;
  char *strlim;
  while (**str == ' ' || **str == '\n' || **str == '\t' || **str == '\r' ||
         **str == '\x0B' || **str == '\f')
    str++;
  if (**str == '\0' && att->count == 0) {
    res--;
  } else {
    if (s21_atoul_scan(*str, s21_NULL, att, 16) ||
        *(*str + s21_pointers(*str, "\n\t \f\x0B\r+-")) == '0') {
      att->width = wid;
      if (!att->star) {
        if (s21_atoul_scan(*str, s21_NULL, att, 16) || **str == '0')
          *(void **)va_arg(args, void **) =
              (void *)s21_atoul_scan(*str, &strlim, att, 16);
        res++;
      } else {
        s21_atoul_scan(*str, &strlim, att, 16);
      }
      att->count += strlim - *str;
      *str = strlim;
    }
  }
  return res;
}

int s21_spec_u_scan(char **str, va_list args, format_token *att, int base) {
  int res = 0, wid = att->width;
  char *strlim;
  while (**str == ' ' || **str == '\n' || **str == '\t' || **str == '\r' ||
         **str == '\x0B' || **str == '\f')
    (*str)++;
  if (**str == '+') {
    wid--;
    att->width--;
    (*str)++;
  }
  if (**str == '-') {
    wid--;
    att->width--;
    (*str)++;
  }

  if (**str == '\0' && att->count == 0) {
    res--;
  } else {
    if (s21_atoul_scan(*str, s21_NULL, att, 16) ||
        *(*str + s21_pointers(*str, "\n\t \f\x0B\r+-")) == '0') {
      att->width = wid;
      if (!att->star) {
        if (att->length == 'h')
          *(short unsigned *)va_arg(args, void *) =
              s21_atoul_scan(*str, &strlim, att, base);
        else if (att->length == 'l')
          *(long unsigned *)va_arg(args, void *) =
              s21_atoul_scan(*str, &strlim, att, base);
        else
          *(int unsigned *)va_arg(args, void *) =
              s21_atoul_scan(*str, &strlim, att, base);
        res++;
      } else {
        s21_atoul_scan(*str, &strlim, att, base);
      }

      att->count += strlim - *str;
      *str = strlim;
    }
  }
  return res;
}

s21_size_t s21_pointers(const char *str1, const char *str2) {
  char *str = (char *)str1, *pattern = (char *)str2;
  s21_size_t i = 0;
  int break_for = 1;
  for (; *(str + i) != '\0' && break_for; i++) {  // идем по символам строки 1
    int inside = 1;
    for (s21_size_t j = 0; *(pattern + j) != '\0' && inside; j++) {
      if (*(str + i) ==
          *(pattern +
            j))  // сравниваем каждый символ строки 1 со всеми символами стр 2
        inside = 0;
    }
    if (inside) {  // если значение флага не изменилось, значит этот символ не
                   // содержится в шаблонах
      break_for = 0;
      i--;
    }
  }
  return i;
}