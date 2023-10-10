#include "s21_string.h"
// Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
// байтах строки, на которую указывает аргумент str, игнорируя символы конца
// строки
//(1)
void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *res = s21_NULL;
  // создаем локальную переменную для обхода типа const
  char *temp = (char *)str;
  int break_for = 1;
  for (s21_size_t i = 0; i < n && break_for; i++) {
    if (*(char *)(temp + i) == c) {
      res = temp + i;
      break_for = 0;
    }
  }
  return res;
}

// Сравнивает первые n байтов str1 и str2, игнорируя символы конца строки
//(2)
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int res = 0, break_for = 1;
  char *temp1 = (char *)str1, *temp2 = (char *)str2;
  for (s21_size_t i = 0; i < n && break_for; i++) {
    if (*(temp1 + i) != *(temp2 + i)) {
      break_for = 0;
      res += *(temp1 + i) - *(temp2 + i);
    }
  }
  return res;
}

// Копирует n символов из src в dest, игнорируя символы
// конца строки
// (3)
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *temp_dest = dest;
  const char *temp_src = src;
  for (s21_size_t i = 0; i < s21_strlen(temp_src) + 1 && i < n; i++)
    temp_dest[i] = temp_src[i];
  return temp_dest;
}

// НЕ ОБРАБОТАН СЛУЧАЙ, ЕСЛИ В STR НЕДОСТАТОЧНО ЭЛЕМЕНТОВ ДЛЯ ЗАПИСИ N (illegal
//  hardware instruction) Копирует символ c (беззнаковый тип) в первые n
//  символов
// строки, на которую указывает аргумент str.
//(4)
void *s21_memset(void *str, int c, s21_size_t n) {
  char *temp = str;
  for (s21_size_t i = 0; i < n; i++) {
    temp[i] = c;
  }
  return temp;
}

// Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest, длиной до n символов.
//  5
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  for (s21_size_t i = 0, j = s21_strlen(dest); i < s21_strlen(src) + 1 && i < n;
       i++)
    dest[j + i] = src[i];
  return dest;
}

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.
//  6
char *s21_strchr(const char *str, int c) {
  char *temp = (char *)str;
  void *res = ((char)c == '\0') ? "\0" : s21_NULL;
  s21_size_t i = 0;
  while (*(temp + i) != '\0' && *(temp + i) != c)
    i++;  // пока не достигли конца строки или не нашли совпадение
  if (*(temp + i) != '\0') res = temp + i;
  return res;
}

// Сравнивает не более первых n байтов str1 и str2.
//  7
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0, break_for = 1;
  char *temp1 = (char *)str1, *temp2 = (char *)str2;
  for (s21_size_t i = 0; i < n && break_for; i++) {
    if (*(temp2 + i) == '\0' || *(temp1 + i) == '\0' ||
        *(temp1 + i) != *(temp2 + i)) {
      break_for = 0;
      res += *(temp1 + i) - *(temp2 + i);
    }
  }
  return res;
}

// Копирует до n символов из строки, на которую указывает src, в dest.
//  8
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  for (s21_size_t i = 0; i < s21_strlen(src) + 1 && i < n; i++)
    dest[i] = src[i];
  return dest;
}

// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов, не входящих в str2.
//  9
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  char *str = (char *)str1, *pattern = (char *)str2;
  s21_size_t i = 0;
  int break_for = 1;
  for (; *(str + i) != '\0' && break_for; i++) {  // идем по символам строки 1
    for (s21_size_t j = 0; *(pattern + j) != '\0' && break_for; j++) {
      if (*(str + i) == *(pattern + j)) {  // сравниваем каждый символ строки 1
                                           // со вм=семи символами стр 2
        break_for = 0;
        i--;  // так как на текущей позиции находимся на элементе, который есть
              // в строке 2
      }
    }
  }
  return i;
}
// Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает
// указатель на строку с сообщением об ошибке. Нужно объявить макросы,
// содержащие массивы сообщений об ошибке для операционных систем mac и linux.
// Описания ошибок есть в оригинальной библиотеке. Проверка текущей ОС
// осуществляется с помощью директив.
//  10
char *s21_strerror(int errnum) {
  static char error[100];
  ERRORS;
  if (errnum >= 0 && errnum < ERRNUM_MAX)
    s21_memcpy(error, error_list[errnum], 100);
  return error;
}

// Вычисляет длину строки str, не включая завершающий нулевой символ.
//  11
s21_size_t s21_strlen(const char *str) {
  s21_size_t result = 0;
  while (*str++) result++;
  return result;
}

// Находит первый символ в строке str1, который соответствует любому символу,
// указанному в str2.
//  12
char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;
  for (int i = 0; str1[i]; i++) {
    if (s21_strchr(str2, str1[i])) {
      result = (char *)str1 + i;
      break;
    }
  }
  return result;
}

// Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.
//  13
char *s21_strrchr(const char *str, int c) {
  char *result = s21_NULL;
  int found = -1;
  for (int i = 0; str[i]; i++) {
    if (str[i] == c) {
      found = i;
    }
  }
  if (found > -1) result = (char *)str + found;
  return result;
}

// Находит первое вхождение всей строки needle (не включая завершающий нулевой
// символ), которая появляется в строке haystack.
//  14
char *s21_strstr(const char *haystack, const char *needle) {
  char *str_long = (char *)haystack, *str_small = (char *)needle,
       *result = s21_NULL;
  s21_size_t i = 0;
  int break_for = 1;
  for (; *(str_long + i) != '\0' && break_for;
       i++) {  // идем по символам строки 1
    int inside = 1;
    for (s21_size_t j = 0; *(str_small + j) != '\0' && inside; j++) {
      if (*(str_long + i + j) !=
          *(str_small +
            j))  // сравниваем каждый символ строки 1 со всеми символами стр 2
        inside = 0;
    }
    if (inside) {  // если значение флага не изменилось, значит эта строка
                   // содержится в большой с i элемента
      break_for = 0;
      result = str_long + i;
    }
  }
  return result;
}

// Разбивает строку str на ряд токенов, разделенных delim.
//  15
char *s21_strtok(char *str, const char *delim) {
  static char *original_string = s21_NULL;
  if (str) original_string = str;
  char *token = s21_NULL, *temp = original_string;
  if (original_string) {
    while (s21_strchr(delim, *temp) && *temp++)
      ;
    if (*temp) token = temp;
    while (!s21_strchr(delim, *temp) && *temp++)
      ;
    if (*temp) {
      *temp = '\0';
      original_string = temp + 1;
    } else {
      original_string = s21_NULL;
    }
    if (*str == *delim) {
      token = s21_NULL;
    }
  }
  return token;
}
