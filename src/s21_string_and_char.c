#include "s21_string.h"

void s21_spec_s(char **str, format_token att, va_list args, double no_num) {
  int i = 0, check = 1;
  if (no_num) att.length = 'n';
  if (att.length == 'l') {
    wchar_t *var_str = va_arg(args, wchar_t *);
    if (var_str == NULL) var_str = L"(null)";
    int size = wcslen(var_str) * sizeof(wchar_t) / sizeof(char) + 1;
    char *wchar_s = calloc(size, sizeof(char));
    int size_t = wcstombs(wchar_s, var_str, size - 1);
    if (size_t >= att.prec && att.prec != -1) {  // char *str3 = "%010.3s %s";
      att.width -= att.prec;
    } else {
      att.width -= size_t;
    }
    s21_empty_space_zero(str, att, att.minus);
    while (wchar_s[i] != '\0' && check)
      if (att.prec > -1 && i >= att.prec)
        check = 0;
      else
        *((*str)++) = wchar_s[i++];
    free(wchar_s);
    s21_empty_space_zero(str, att, !att.minus);
  } else {
    char *var_str = NULL;
    if (no_num == 0) var_str = va_arg(args, char *);
    if (isnan(no_num)) var_str = "nan";
    if (isinf(no_num)) var_str = "inf";
    if (var_str == NULL) var_str = "(null)";
    if ((int)s21_strlen(var_str) >= att.prec &&
        att.prec != -1) {  // char *str3 = "%010.3s %s";
      att.width -= att.prec;
    } else {
      att.width -= s21_strlen(var_str);
    }
    s21_empty_space_zero(str, att, att.minus);
    while (*var_str != '\0' && check)
      if (att.prec > -1 && i++ >= att.prec)
        check = 0;
      else
        *((*str)++) = *(var_str++);
    s21_empty_space_zero(str, att, !att.minus);
  }
}

void s21_spec_c(char **str, format_token att, va_list args) {
  wchar_t var_char = va_arg(
      args,
      wchar_t);  // считываем символ из листа в формате расширенного символа
  char wchar_s[5] = {0};  // необходимый массив символов для успешной работы
  // функция записывает расширенный символ в наш новый массив
  if (att.length == 'l') {
    wctomb(wchar_s, var_char);
    if (var_char <= 0x7F)
      att.width--;  // корректируем значение ширины
    else if (var_char <= 0x7FF)
      att.width -= 2;
    else if (var_char <= 0xFFFF)
      att.width -= 3;
    else
      att.width -= 4;
  } else {
    att.width--;
  }
  s21_empty_space_zero(str, att, att.minus);
  if (att.length != 'l') {
    *((*str)++) = var_char;
  } else {  // если присутствует атрибут l, то работаем с символами как с
            // расширенными
    int max = 0;
    if (var_char <= 0x7F)
      max = 1;  // корректируем значение ширины
    else if (var_char <= 0x7FF)
      max = 2;
    else if (var_char <= 0xFFFF)
      max = 3;
    else
      max = 3;
    for (int i = 0; i < max; i++) {
      *((*str)++) = wchar_s[i];
    }
  }
  att.zero = 0;
  s21_empty_space_zero(str, att, !att.minus);
}

void s21_empty_space_zero(
    char **str, format_token att,
    char option) {  // option (0 - minus off, 1 - minus on)
  if (!option) {  // если нет атрибута минус, то выравнивание по правому краю
    while (att.width-- > 0) {
      *((*str)++) =
          (att.zero)
              ? '0'
              : ' ';  // т.е. все ячейки до символа заполняем пустотой или 0
    }
  }
}

int s21_spec_s_scan(char **str, format_token *att, va_list args) {
  char *buf = NULL;
  int res = 0;
  buf = s21_sputsf(str, att);
  if (!att->star) {
    if (buf != NULL) {
      char *arg = va_arg(args, char *);
      int i = 0;
      while (buf[i] != '\0') {
        arg[i] = buf[i];
        i++;
      }
      arg[i] = '\0';
      if (*buf == '\0' && att->count == 0) res--;
      if (*buf != '\0') res++;
    }
  }
  if (buf != NULL) {
    att->count += s21_strlen(buf);
    free(buf);
  }
  return res;
}

int s21_isspace(int c) {
  return (c == '\x20' || c == '\r' || c == '\n' || c == '\t' || c == '\v' ||
          c == '\f');
}

char *s21_sputsf(char **src, format_token *att) {
  char *outp = calloc(sizeof(char), s21_strlen(*src) + 1);
  if (outp != NULL) {
    int i = 0;
    while (s21_isspace(**src)) {
      (*src)++;
      att->count++;
    }
    while (**src != '\0' && !s21_isspace(**src) &&
           ((att->width != 0) ? (i < att->width) : 1)) {
      outp[i] = **src;
      i++;
      (*src)++;
    }
    outp[i] = '\0';
  }
  return outp;
}

int s21_spec_c_scan(char **str, format_token *att, va_list args) {
  int res = 0;
  if (!att->star) {
    if (**str != '\0') res++;
    if (**str == '\0' && att->count == 0) res--;
    if (att->length == 'l')
      mbtowc((wchar_t *)va_arg(args, wchar_t *), *str, att->width);
    else
      *(char *)va_arg(args, char *) = **str;
  }
  if (**str < 0 && att->length == 'l') {
    (*str)++;
    att->count++;
  }
  (*str)++;
  att->count++;
  return res;
}