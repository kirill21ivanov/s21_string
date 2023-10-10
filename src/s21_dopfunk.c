#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *temp = (char *)str;
  char *string = s21_NULL;
  if (temp) {
    string = calloc(s21_strlen(str) + 1, sizeof(char));
    if (string) {
      for (int i = 0; temp[i] != '\0'; i++) {
        if (temp[i] >= 97 && temp[i] <= 122)
          string[i] = temp[i] - 32;
        else
          string[i] = temp[i];
      }
    }
  }
  return (void *)string;
}

void *s21_to_lower(const char *str) {
  char *temp = (char *)str;
  char *string = s21_NULL;
  if (temp) {
    string = calloc(s21_strlen(str) + 1, sizeof(char));
    if (string) {
      for (int i = 0; temp[i] != '\0'; i++) {
        if (str[i] >= 65 && str[i] <= 90)
          string[i] = temp[i] + 32;
        else
          string[i] = temp[i];
      }
    }
  }
  return (void *)string;
}

// Возвращает новую строку, в которой указанная строка (str) вставлена в
// указанную позицию (start_index) в данной строке (src). В случае какой-либо
// ошибки следует вернуть значение NULL
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t length_src =
      (src) ? s21_strlen(src)
            : 0;  // Надо будет использовать написанную функцию
  s21_size_t length_str =
      (str) ? s21_strlen(str)
            : 0;  // Надо будет использовать написанную функцию
  char *temp1 = (char *)src;
  char *temp2 = (char *)str;
  char *string = s21_NULL;
  if (temp1 && temp2 && start_index <= s21_strlen(src)) {
    string = calloc(length_src + length_str + 1, sizeof(char));
    if (string) {
      for (s21_size_t i = 0; i < start_index; i++) string[i] = temp1[i];
      for (s21_size_t i = start_index; i < start_index + length_str; i++)
        string[i] = temp2[i - start_index];
      for (s21_size_t i = start_index + length_str; i < length_src + length_str;
           i++)
        string[i] = temp1[i - length_str];
    }
  }
  return (void *)string;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = s21_NULL;
  if (src != s21_NULL) {
    if (trim_chars == NULL || trim_chars[0] == '\0') {
      trim_chars = " ";
    }
    s21_size_t len = s21_strlen(src);
    if (len) {
      int start = -1, end = -1, flag_first = 1, flag_last = 1, flag_break = 1;
      for (s21_size_t i = 0, j = len - 1; i < len && flag_break; i++, j--) {
        if (s21_strchr(trim_chars, src[i]) == s21_NULL && flag_first) {
          start = i;
          flag_first = 0;
        }
        if (s21_strchr(trim_chars, src[j]) == s21_NULL && flag_last) {
          end = j;
          flag_last = 0;
        }
        if (!flag_first && !flag_last) {
          flag_break = 0;
        }
      }
      result = calloc(end - start + 2, sizeof(char));
      if (result != s21_NULL) {
        for (int i = start, j = 0; i <= end; i++, j++) {
          result[j] = src[i];
        }
      }
    } else {
      result = calloc(2, sizeof(char));
    }
  }
  return result;
}
