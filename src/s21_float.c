#include "s21_string.h"

void s21_spec_f(char **str, format_token att, va_list args) {
  long double var_long = 0;
  long double int_part = 0;
  int scale = 0;
  if (att.prec == -1)
    att.prec = 6;  // сразу проверяем точность и ставим стандартную если ее нет
  if (att.length != 'L') {
    var_long =
        va_arg(args, double);  // пока вынимаем дабл но засовываем в лонг дабл
  } else {
    var_long = va_arg(args, long double);
  }
  if (isnan(var_long)) {
    s21_spec_s(str, att, args, var_long);
  } else if (isinf(var_long)) {
    s21_spec_s(str, att, args, var_long);
  } else {
    int negative = 0;  // если число отрицательное
    if (var_long < 0) {
      negative = 1;
      var_long *= -1;
    }
    long double fractional =
        modfl(var_long, &int_part);  // разбиваем наше число на целое и дробное

    double after_point =
        fractional *
        pow(10.0, att.prec);  // следующие строчки превращают дробную часть в
                              // целую в соответствии с указанной точностью и
                              // округляют, ПРИМЕР Преобразования - 0,699 ->
                              // 698.9951252 -> 699.00000
    double rounded_frac = 0;
    if (after_point >= 1) {
      rounded_frac = roundl(after_point);
    }

    s21_smart_rounding(
        after_point, rounded_frac, &int_part,
        &fractional);  // обрабатывает округления такого типа 0.999000, если
                       // будет указано точность 1 то выведет 1.0
    if (att.prec == 0)
      int_part = roundl(
          var_long);  // если у нас нулевая точность то мы округляем наше число

    long double ex = int_part;
    while (ex >= 1) {
      ex /= 10;
      scale++;  // находи количество цифр в числе
    }
    if (att.minus == 1) {  // выравнивание по левой стороне
      s21_left_side_float(att, str, negative, fractional, int_part, scale);
    } else {
      s21_right_side_float(att, str, negative, fractional, int_part, scale);
    }
  }
}

void s21_right_side_float(format_token att, char **str, int negative,
                          long double fractional, long double int_part,
                          int scale) {
  scale = 0;
  if ((att.spec == 'g' || att.spec == 'G') && att.prec == 0 &&
      fractional >= 0.5) {
    int_part++;
  }
  long double after_point =
      fractional *
      pow(10.0,
          att.prec);  // следующие строчки превращают дробную часть в целую в
                      // соответствии с указанной точностью и округляют, ПРИМЕР
                      // Преобразования - 0,699 -> 698.9951252 -> 699.00000
  long double rounded_frac = 0;
  if (after_point >= 1) {
    rounded_frac = roundl(after_point);
  }
  s21_check_round(&int_part, 0, &rounded_frac, &after_point);
  if (rounded_frac == 0 && (att.spec == 'g' || att.spec == 'G') && !att.hash)
    att.prec = 0;
  long double ex1 = int_part;
  while (ex1 >= 1) {
    ex1 /= 10;
    scale++;  // находи количество цифр в числе
  }
  if (!scale && !int_part) scale = 1;
  if ((att.spec == 'g' || att.spec == 'G') && att.hash == 0) {
    while (fmodl(rounded_frac, 10.0) < 1 && rounded_frac > 0) {
      rounded_frac /= 10;
      s21_minus_prec(&att);
    }
  }
  int dot = 1;  // вычесть точку. добавил как переменннуб для читаемости
  att.width -= scale;
  if (att.prec > 0 || att.hash) att.width -= dot;
  s21_first_sym_in_str(&att, str, negative, 1, 0);

  if (att.prec > 0) att.width -= att.prec;
  s21_handle_zero_in_float(&att, str, negative);
  s21_handle_int_part_in_float(&att, str, scale, int_part, 0);
  long double ex = rounded_frac;
  scale = 0;
  while (ex >= 1) {
    ex /= 10;
    scale++;
  }
  s21_handle_fractional_part_in_float(&att, str, scale, rounded_frac);
}

void s21_minus_prec(format_token *att) { att->prec--; }

void s21_handle_zero_in_float(format_token *att, char **str, int negative) {
  if (att->zero) {
    s21_first_sym_in_str(att, str, negative, 0, 1);
    while (att->width > 0) {
      *((*str)++) = '0';
      att->width--;
    }
  } else {
    while (att->width > 0) {
      *((*str)++) = ' ';
      att->width--;
    }
    s21_first_sym_in_str(att, str, negative, 0, 1);
  }
}

void s21_handle_int_part_in_float(format_token *att, char **str, int scale,
                                  long double int_part, int minus_width) {
  while (scale--) {  // пишем целую часть числа в строку
    long double x = int_part / (long double)pow(10L, scale);
    long double y = fmodl(x, 10.0L);
    int find = (int)y;
    *((*str)++) = find + 48;
  }
  if (att->prec > 0 || att->hash) {
    *((*str)++) = '.';
    if (minus_width) att->width--;
  }
}

void s21_handle_fractional_part_in_float(format_token *att, char **str,
                                         int scale, double rounded_frac) {
  while (att->prec >
         scale) {  // если условие саблюлось значит дробная часть началась с
                   // нулей и мы их ставим/ Пример числа -> 0.000123
    *((*str)++) = '0';
    att->prec--;
    att->width--;
  }
  while (scale--) {
    long double x = rounded_frac / (long double)pow(10L, scale);
    long double y = fmodl(x, 10.L);
    int find = (int)y;
    *((*str)++) = find + 48;
    att->width--;
  }
}

void s21_left_side_float(format_token att, char **str, int negative,
                         long double fractional, long double int_part,
                         int scale) {
  if ((att.spec == 'g' || att.spec == 'G') && att.prec == 0 &&
      fractional >= 0.5) {
    int_part++;
  }
  s21_first_sym_in_str(&att, str, negative, 1,
                       1);  // в функции обрабатывается первый возможный символ
                            // числа - пробел/+/-
  long double after_point =
      fractional *
      pow(10.0,
          att.prec);  // следующие строчки превращают дробную часть в целую в
                      // соответствии с указанной точностью и округляют, ПРИМЕР
                      // Преобразования - 0,699 -> 698.9951252 -> 699.00000
  long double rounded_frac = 0;
  if (after_point >= 1) {  // условие необходимое для округления и приданию
                           // нужной точность(выше пример работы)
    rounded_frac = roundl(after_point);
  }
  s21_check_round(&int_part, 0, &rounded_frac, &after_point);
  if (rounded_frac == 0 && (att.spec == 'g' || att.spec == 'G') && !att.hash)
    att.prec = 0;
  if (!scale && !int_part) scale = 1;  // если наше число ноль
  att.width -= scale;
  s21_handle_int_part_in_float(&att, str, scale, int_part,
                               1);  // пишет целую часть в строку. В конце флаг
                                    // для понимания обработки ширины
  scale = 0;
  if ((att.spec == 'g' || att.spec == 'G') && att.hash == 0) {
    while (fmodl(rounded_frac, 10.0) < 1 && rounded_frac > 0) {
      rounded_frac /= 10;
      s21_minus_prec(&att);
    }
  }
  long double ex = rounded_frac;
  while (ex >= 1) {
    ex /= 10;
    scale++;
  }
  s21_handle_fractional_part_in_float(&att, str, scale, rounded_frac);
  while (att.width > 0) {
    att.width--;
    *((*str)++) = ' ';
  }
}

void s21_first_sym_in_str(format_token *att, char **str, int negative,
                          int count, int print) {
  if (negative) {
    if (print) *((*str)++) = '-';
    if (count) att->width--;
  } else if (att->plus) {
    if (print) *((*str)++) = '+';
    if (count) att->width--;
  } else if (att->space) {
    if (print) *((*str)++) = ' ';
    if (count) att->width--;
  }
}

void s21_smart_rounding(double after_point, double rounded_frac,
                        long double *int_part, long double *fractional) {
  long double test1 = rounded_frac;
  long double test2 = after_point;
  int scale1 = 0;
  int scale2 = 0;
  while (test1 >= 1) {
    test1 /= 10;
    scale1++;
  }
  while (test2 >= 1) {
    test2 /= 10;
    scale2++;
  }
  if (scale1 != scale2) *int_part += 1;
  if (scale1 != scale2) *fractional = 0;
}

int s21_spec_f_scan(char **str, format_token *att, va_list args) {
  int res = 0, wid = att->width;
  char *strlim;
  if (**str != '\0') {
    if (fabs(s21_atod(*str, s21_NULL, att)) >= 1e-100 ||
        isnan(s21_atod(*str, s21_NULL, att)) ||
        *(*str + s21_pointers(*str, "\n\t \f\x0B\r+-")) == '0') {
      att->width = wid;
      if (!att->star) {
        res++;
        if (att->length == 'L')
          *(long double *)va_arg(args, void *) = s21_atold(*str, &strlim, att);
        else if (att->length == 'l')
          *(double *)va_arg(args, void *) = s21_atod(*str, &strlim, att);
        else
          *(float *)va_arg(args, void *) = s21_atof(*str, &strlim, att);
      } else {
        s21_atof(*str, &strlim, att);
      }

      att->count += strlim - *str;
      *str = strlim;
    }
  } else {
    res--;
  }

  return res;
}
