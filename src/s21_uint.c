#include "s21_string.h"

void s21_uint(char **str, format_token att, va_list args) {
  int zero_case = 0;
  att.plus = 0;
  att.space = 0;
  unsigned long int var_int = va_arg(args, unsigned long int);
  if (att.length == 'h') {
    var_int = (unsigned short int)var_int;
  } else if (att.length != 'l') {
    var_int = (unsigned int)var_int;
  }
  unsigned long int ex = var_int;
  int scale = 0;
  while (ex) {
    ex /= 10;
    scale++;  // находи количество цифр в числе
  }
  if (!scale && !var_int) {
    scale = 1;
    if (att.prec == 0) {
      s21_first_sym_in_str(&att, str, 0, 1, 1);
      while (att.width > 0) {
        att.width--;
        *((*str)++) = ' ';
      }
      zero_case = 1;  // костыль для s21_sprintf(buf, "Ab%.dab", 0);
    }
  }
  if (!zero_case) {
    if (att.minus) {  // выравнивание по левому краю
      s21_left_side_uint(att, str, scale, var_int);
    } else {  // выравнивание по правому краю
      s21_right_side_uint(att, str, scale, var_int);
    }
  }
}

void s21_right_side_uint(format_token att, char **str, int scale,
                         unsigned long int var_int) {
  att.width -= scale;
  if (var_int == 0 && att.prec > 1) att.width++;
  if (att.prec > scale) att.width -= att.prec - scale;
  if (att.prec >= 0) {  // если есть точность, то 0 не работает
    att.zero = 0;
  }
  if (!att.zero) {
    while (att.width > 0) {
      att.width--;
      *((*str)++) = ' ';
    }
  }
  s21_first_sym_in_str(&att, str, 0, 0, 1);
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
    *((*str)++) = var_int / (long int)pow(10, scale) % 10 + 48;
  }
}

void s21_left_side_uint(format_token att, char **str, int scale,
                        unsigned long int var_int) {
  att.width -= scale;
  if (att.space) {
    *((*str)++) = ' ';
    att.width--;
  }
  while (att.prec-- > scale) {
    *((*str)++) = '0';
    att.width--;
  }
  while (scale--)
    *((*str)++) = var_int / (unsigned long int)pow(10, scale) % 10 + 48;
  while (att.width > 0) {
    att.width--;
    *((*str)++) = ' ';
  }
}
