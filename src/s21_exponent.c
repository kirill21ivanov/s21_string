#include "s21_string.h"

void s21_spec_eE(char **str, format_token att, va_list args) {
  long double var_long = 0;
  long double int_part = 0;
  int scale = 0;
  if (att.prec == -1) att.prec = 6;
  if (att.prec == 0 && (att.spec == 'g' || att.spec == 'G')) att.prec = 1;
  if (att.length != 'L') {
    var_long = va_arg(args, double);
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
    if (int_part == 0) {
      s21_zero_int_part(&att, str, negative, fractional, int_part,
                        scale);  // рассмотрим если в целой части нооль
    } else {  // если есть целая часть
      s21_not_zero_int_part(&att, str, int_part, fractional, negative, scale);
    }
  }
}

void s21_not_zero_int_part(format_token *att, char **str, long double int_part,
                           long double fractional, int negative, int scale) {
  int minus_stepen = 0;
  int for_g = 0;
  long double ex = int_part;
  while (ex >= 1) {
    ex /= 10;
    scale++;
    minus_stepen--;
  }
  minus_stepen += 1;
  for_g = minus_stepen * -1;
  if (att->prec > for_g && (att->spec == 'g' || att->spec == 'G')) {
    att->prec = att->prec - (for_g + 1);
    if (att->minus == 1) {  // выравнивание по левой стороне
      s21_left_side_float(*att, str, negative, fractional, int_part, scale);
    } else {
      s21_right_side_float(*att, str, negative, fractional, int_part, scale);
    }
  } else {
    if (att->spec == 'g' || att->spec == 'G') att->prec -= 1;
    fractional =
        fractional /
        pow(10,
            scale - 1);  // Что мы делаем // взяли целую часть например 123 //
                         // нам нужна только первая цифра // поэтому мы
                         // посчитали кол во цифр и осавили первую // в нашем
                         // остаттке освободили нули под ту целую часть которая
                         // перейдет из целой части // 123.456 - 123 0.456 -
                         // 0.123 0.456 - 1.23 0.456 - 1.23 0.00456 - 1.23456
    long double new_value = ex * 10;
    new_value += fractional;
    if (att->prec == 0) new_value = roundl(new_value);
    if (new_value == 10) {
      new_value /= 10;
      minus_stepen--;
    }
    fractional = modfl(new_value, &int_part);
    if (att->minus == 1) {  // выравнивание по левой стороне
      s21_left_side_eE(att, str, negative, fractional, int_part, 1,
                       minus_stepen);
    } else {
      s21_right_side_eE(att, str, negative, fractional, int_part, 1,
                        minus_stepen);
    }
  }
}

void s21_zero_int_part(format_token *att, char **str, int negative,
                       long double fractional, long double int_part,
                       int scale) {
  int minus_stepen = 0;
  int scale1 = 0;
  int flag = 1;
  if (att->spec == 'g' || att->spec == 'G') att->prec--;
  if (int_part || fractional) {  // проверка что не чистый ноль
    s21_preparing_ex(att, str, &negative, &fractional, &int_part, &scale,
                     &minus_stepen, &flag, &scale1);
  } else {
    fractional = 0;
    int_part = 0;
    scale1 = 1;
    if (att->spec == 'g' || att->spec == 'G') {
      flag = 0;
      if (!att->hash) att->prec = 0;
      if (att->minus == 1) {  // выравнивание по левой стороне
        s21_left_side_float(*att, str, negative, fractional, int_part, scale1);
      } else {
        s21_right_side_float(*att, str, negative, fractional, int_part, scale1);
      }
    }
  }
  if (flag) {
    if (att->minus == 1) {  // выравнивание по левой стороне
      s21_left_side_eE(att, str, negative, fractional, int_part, scale1,
                       minus_stepen);
    } else {
      s21_right_side_eE(att, str, negative, fractional, int_part, scale1,
                        minus_stepen);
    }
  }
}

void s21_preparing_ex(format_token *att, char **str, int *negative,
                      long double *fractional, long double *int_part,
                      int *scale, int *minus_stepen, int *flag, int *scale1) {
  long double ex = *fractional;  // рассмотрим если в целой части нооль
  if (*scale == 0) {  // нам надо найти число отличное от нуля в дробной части
    while (*fractional - 1 < 0) {  // 0.0088888 -> 8.8888
      *fractional = *fractional * 10;
      *minus_stepen = *minus_stepen + 1;
    }
  }  // теперь fractional это число которое нам надо преобразовать в строку как
     // во флоате // надо fractional подготовить к функции
  int for_g = *minus_stepen * -1;
  if (att->prec > for_g && (att->spec == 'g' || att->spec == 'G') &&
      for_g >= -4) {
    *flag = 0;
    att->prec = att->prec - (for_g + 1);
    if (att->minus == 1) {  // выравнивание по левой стороне
      s21_left_side_float(*att, str, *negative, ex, *int_part, *scale);
    } else {
      s21_right_side_float(*att, str, *negative, ex, *int_part, *scale);
    }
  } else {
    long double new_value = *fractional;
    *fractional = modfl(new_value, int_part);  // перезапишем в те же переменные
    double after_point =
        *fractional * pow(10.0, att->prec);  // сколько нам надо для точности
    double rounded_frac = 0;
    if (after_point >= 1) {
      rounded_frac = roundl(after_point);
    }
    s21_smart_rounding(
        after_point, rounded_frac, int_part,
        fractional);  // зачем эта функция? нам нужно вначале было просто
                      // округлить нашу дробную часть, пример 998.999 = 999. Но
                      // может быть такое что число перейдет в новые разряды
                      // тогда нам надо уже просто будет увелить целую часть
                      // пример 999.99 = 1000
    if (att->prec == 0) *int_part = roundl(new_value);
    if (*int_part == 10) {
      *int_part = 1;
      *minus_stepen = *minus_stepen - 1;
    }
    long double ex1 =
        *int_part;  // вообще здесь инт парт может быть только из одной цифры и
                    // если он перейдет в новый разред то это будет уже число 10
                    // // поэтмоу на него и провери
    while (ex1 >= 1) {
      ex1 /= 10;
      *scale1 = *scale1 + 1;  // находи количество цифр в числе
    }
  }
}

void s21_right_side_eE(format_token *att, char **str, int negative,
                       long double fractional, long double int_part, int scale1,
                       int minus_stepen) {
  int test = minus_stepen;
  int plus = 0;
  int minus_scale = 0;
  att->width = att->width - 2;  // отняли букву и знак
  if (minus_stepen <= 0) {
    minus_stepen *= -1;
    plus = 1;
  }
  if (minus_stepen >
      9) {  // вычли + сколько если вдруг больше двузначного число
    test = minus_stepen;
    minus_scale = 0;
    while (test) {
      test /= 10;
      minus_scale++;
      att->width--;
    }
  } else {
    att->width = att->width - 2;
  }
  int dot = 1;  // вычесть точку. добавил как переменннуб для читаемости
  att->width -= scale1;  // вычли число
  if (att->prec > 0 || att->hash) att->width -= dot;
  s21_first_sym_in_str(att, str, negative, 1, 0);
  long double after_point =
      fractional *
      pow(10.0, att->prec);  // следующие строчки превращают дробную часть в
                             // целую в// соответствии с указанной точностью и
                             // округляют, ПРИМЕР// Преобразования - 0,699 ->
                             // 698.9951252 -> 699.00000
  long double rounded_frac = 0;
  if (after_point >= 1) {
    rounded_frac = roundl(after_point);
  }
  s21_check_round(&int_part, &minus_stepen, &rounded_frac, &after_point);
  if (rounded_frac == 0 && (att->spec == 'g' || att->spec == 'G') && !att->hash)
    att->prec = 0;
  if ((att->spec == 'g' || att->spec == 'G') && att->hash == 0) {
    while (fmodl(rounded_frac, 10.0) < 1 && rounded_frac > 0) {
      rounded_frac /= 10;
      s21_minus_prec(att);
    }
  }
  if (att->prec > 0) att->width -= att->prec;
  s21_handle_zero_in_float(att, str, negative);
  s21_handle_int_part_in_float(att, str, scale1, int_part,
                               0);  // рисуем после запятой
  long double ex = rounded_frac;
  scale1 = 0;
  while (ex >= 1) {
    ex /= 10;
    scale1++;
  }
  s21_handle_fractional_part_in_float(att, str, scale1, rounded_frac);
  s21_also_print_exp(att, str, plus, minus_stepen, minus_scale);
}

void s21_check_round(long double *int_part, int *minus_stepen,
                     long double *rounded_frac, long double *after_point) {
  int counter = 0;
  int counter2 = 0;
  long double test_after_point = *after_point;
  long double test_rounded_frac = *rounded_frac;

  while (test_after_point >= 1) {
    test_after_point /= 10;
    counter++;
  }

  while (test_rounded_frac >= 1) {
    test_rounded_frac /= 10;
    counter2++;
  }
  if (counter != counter2) {
    *rounded_frac = 0;
    *int_part = *int_part + 1;
    if (*int_part == 10) {
      *int_part = 1;
      *minus_stepen = *minus_stepen + 1;
    }
  }
}

void s21_left_side_eE(format_token *att, char **str, int negative,
                      long double fractional, long double int_part, int scale1,
                      int minus_stepen) {
  s21_first_sym_in_str(att, str, negative, 1,
                       1);  // в функции обрабатывается первый возможный символ
                            // // числа - пробел/+/-
  long double after_point =
      fractional *
      pow(10.0, att->prec);  // следующие строчки превращают дробную часть в
                             // целую в // соответствии с указанной точностью и
                             // округляют, ПРИМЕР // Преобразования - 0,699 ->
                             // 698.9951252 -> 699.00000
  long double rounded_frac = 0;
  if (after_point >= 1) {  // условие необходимое для округления и приданию
    // нужной точность(выше пример работы)
    rounded_frac = roundl(after_point);
  }
  s21_check_round(&int_part, &minus_stepen, &rounded_frac, &after_point);
  if (rounded_frac == 0 && (att->spec == 'g' || att->spec == 'G') && !att->hash)
    att->prec = 0;
  if ((att->spec == 'g' || att->spec == 'G') && att->hash == 0) {
    while (fmodl(rounded_frac, 10.0) < 1 && rounded_frac > 0) {
      rounded_frac /= 10;
      s21_minus_prec(att);
    }
  }
  if (!scale1 && !int_part) scale1 = 1;  // если наше число ноль
  att->width -= scale1;
  s21_handle_int_part_in_float(att, str, scale1, int_part,
                               1);  // пишет целую часть в строку. В конце флаг
  // для понимания обработки ширины
  long double ex = rounded_frac;
  scale1 = 0;
  while (ex >= 1) {
    ex /= 10;
    scale1++;
  }
  s21_handle_fractional_part_in_float(att, str, scale1, rounded_frac);

  s21_print_exponent(att, str, minus_stepen);
  while (att->width > 0) {
    att->width--;
    *((*str)++) = ' ';
  }
}

void s21_also_print_exp(format_token *att, char **str, int plus,
                        int minus_stepen, int minus_scale) {
  if (att->spec == 'E' || att->spec == 'G') {
    *((*str)++) = 'E';
  }
  if (att->spec == 'e' || att->spec == 'g') {
    *((*str)++) = 'e';
  }
  if (!plus) {
    *((*str)++) = '-';
  }
  if (plus) {
    *((*str)++) = '+';
  }
  if (minus_stepen == 0) {
    *((*str)++) = '0';
    *((*str)++) = '0';
  }
  if (minus_stepen > 0 && minus_stepen < 10) {
    *((*str)++) = '0';
    *((*str)++) = 48 + minus_stepen;
  }
  if (minus_stepen > 9) {
    while (minus_scale--) {
      *((*str)++) = minus_stepen / (int)pow(10, minus_scale) % 10 + 48;
    }
  }
}

void s21_print_exponent(format_token *att, char **str, int minus_stepen) {
  if (att->spec == 'E' || att->spec == 'G') {
    *((*str)++) = 'E';
    att->width--;
  }
  if (att->spec == 'e' || att->spec == 'g') {
    *((*str)++) = 'e';
    att->width--;
  }
  if (minus_stepen > 0) {
    *((*str)++) = '-';
    att->width--;
  }
  if (minus_stepen <= 0) {
    *((*str)++) = '+';
    att->width--;
    minus_stepen *= -1;
  }
  if (minus_stepen == 0) {
    *((*str)++) = '0';
    att->width--;
    *((*str)++) = '0';
    att->width--;
  }
  if (minus_stepen > 0 && minus_stepen < 10) {
    *((*str)++) = '0';
    att->width--;
    *((*str)++) = 48 + minus_stepen;
    att->width--;
  }
  if (minus_stepen > 9) {
    int test = minus_stepen;
    int minus_scale = 0;
    while (test) {
      test /= 10;
      minus_scale++;
      att->width--;
    }
    while (minus_scale--) {
      *((*str)++) = minus_stepen / (int)pow(10, minus_scale) % 10 + 48;
    }
  }
}
