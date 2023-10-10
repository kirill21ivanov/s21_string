#include "s21_string.h"

void s21_spec_p(char **str, format_token att, va_list args) {
  unsigned long long int var_point = 0;
  int count = 0;  // сколько цифр в уже переведенно числе
  char inverted[50] = {0};
  int ox = 2;
  int o = 1;
  if (att.prec != -1)
    att.zero = 0;  // если есть точно то флаг 0 не работает как в Инт

  if (att.spec == 'p') {  // размерность переменной
    var_point = (unsigned long long int)va_arg(args, void *);
  } else if (att.length == 'l') {
    var_point = (unsigned long long int)va_arg(args, unsigned long int);
  } else if (att.length == 'h') {
    var_point = (unsigned long long int)va_arg(args, int);
  } else {
    var_point = (unsigned long long int)va_arg(args, unsigned int);
  }
  if (var_point == 0)
    att.hash = 0;  // если значение переменной равно нулю значит 0х и 0 не будет
                   // выведено
  if (att.spec == 'p') att.hash = 1;  // у поинтера всегда есть этот флаг

  s21_create_output(
      att, inverted, &count,
      &var_point);  // создаем инвентированный массив 16 и 8 - ричного числа

  if (att.width == 0 && att.prec == -1 && count == 0)
    att.width = 1;  // условия для отработки оригинала при нулевых значениях
  if (att.width != 0 && att.prec == -1 && count == 0) att.prec = 1;

  att.width -= count;  // корректировка ширины

  if (att.prec != -1) att.prec -= count;  // корректировка точности

  if (att.hash) {  // корректировка числа связанная с его видом 0х....
    if (att.spec == 'o') {
      att.width -= o;
      att.prec -= o;  // Отняли 0х для предания вида указателя
    } else {
      att.width -= ox;
    }
  }

  s21_print_p(&att, str, count, inverted);
}

void s21_create_output(format_token att, char inverted[], int *count,
                       unsigned long long int *var_point) {
  char pattern[16] = {"0123456789abcdef"};
  int count_func = 0;
  if (att.spec == 'X') {
    for (int i = 0; i < 16; i++) {
      pattern[i] = i < 10 ? i + '0' : i - 10 + 'A';
    }
  }
  if (att.spec != 'o') {
    while (*var_point != 0) {
      int mod = *var_point % 16;
      *var_point /= 16;
      inverted[count_func] = pattern[mod];
      count_func++;
    }
  } else {
    while (*var_point != 0) {
      int mod = *var_point % 8;
      *var_point /= 8;
      inverted[count_func] = pattern[mod];
      count_func++;
    }
  }
  inverted[count_func] = '\0';
  *count = count_func;
}

void s21_print_p(format_token *att, char **str, int count,
                 const char inverted[]) {
  if (att->minus) {
    if (att->hash) *((*str)++) = '0';
    if (att->hash && att->spec != 'o') {
      if (att->spec == 'x' || att->spec == 'p') *((*str)++) = 'x';
      if (att->spec == 'X') *((*str)++) = 'X';
    }
    while (att->prec-- > 0) {
      *((*str)++) = '0';
      att->width--;
    }
    while (count--) {
      *((*str)++) = inverted[count];
    }
    while (att->width-- > 0) {
      *((*str)++) = ' ';
    }
  } else {
    if (att->prec >= 0) att->width -= att->prec;
    if (att->zero) {
      while (att->width-- > 0) {
        *((*str)++) = '0';
      }
    } else {
      while (att->width-- > 0) {
        *((*str)++) = ' ';
      }
    }
    if (att->hash) *((*str)++) = '0';
    if (att->hash && att->spec != 'o') {
      if (att->spec == 'x' || att->spec == 'p') *((*str)++) = 'x';
      if (att->spec == 'X') *((*str)++) = 'X';
    }
    while (att->prec-- > 0) {
      *((*str)++) = '0';
    }
    while (count--) {
      *((*str)++) = inverted[count];
    }
  }
}
