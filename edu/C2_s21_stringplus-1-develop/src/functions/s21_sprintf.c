#include <math.h>
#include <stdio.h>

#include "../s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  char *p = str;
  specifier_builder specifiers;

  int negative_status = 0;
  int num = 0;
  va_list args_copy;
  va_copy(args_copy, ap);
  num = va_arg(args_copy, double);
  va_end(args_copy);

  if (num < 0) negative_status = 1;

  for (size_t i = 0; i < s21_strlen(format); ++i) {
    if (format[i] == '%') {
      if (format[i + 1] == '%') {
        *p = '%';
        p++;
        *p = '\0';
        continue;
      }
      int shift = 0;
      specifiers = ParserForSpecifier(format + (i + 1), &ap, &shift);

      i += shift;

      if (specifiers.specifier == 'g' || specifiers.specifier == 'G') {
        if (num < 0.0001 || num >= 1e6) {
          if (specifiers.specifier == 'G')
            specifiers.specifier = 'E';
          else
            specifiers.specifier = 'e';
        } else {
          specifiers.specifier = 'f';
        }
      }
      switch (specifiers.specifier) {
        case 'c':
          str = SprintForC(str, specifiers, &ap, negative_status);
          p = &(str[s21_strlen(str)]);
          *p = '\0';
          break;
        case 'd':
        case 'i':
          str = SprintForD(str, specifiers, &ap, negative_status);
          p = &(str[s21_strlen(str)]);
          *p = '\0';
          break;
        case 'e':
        case 'E':
          str = SprintForE(str, specifiers, &ap, negative_status);
          p = &(str[s21_strlen(str)]);
          *p = '\0';
          break;
        case 'f':
          str = SprintForF(str, specifiers, &ap, negative_status);
          p = &(str[s21_strlen(str)]);
          *p = '\0';
          break;
        case 'o':
          str = SprintForO(str, specifiers, &ap, negative_status);
          p = &(str[s21_strlen(str)]);
          *p = '\0';
          break;
        case 's':
          str = SprintForS(str, specifiers, &ap, negative_status);
          p = &(str[s21_strlen(str)]);
          *p = '\0';
          break;
        case 'u':
          str = SprintForU(str, specifiers, &ap, negative_status);
          p = &(str[s21_strlen(str)]);
          *p = '\0';
          break;
        case 'x':
          str = SprintForX(str, specifiers, &ap, negative_status);
          p = &(str[s21_strlen(str)]);
          *p = '\0';
          break;
        case 'X':
          str = SprintForX(str, specifiers, &ap, negative_status);
          p = &(str[s21_strlen(str)]);
          *p = '\0';
          break;
        case 'p':
          str = SprintForP(str, specifiers, &ap, negative_status);
          p = &(str[s21_strlen(str)]);
          *p = '\0';
          break;
        case 'n':
          str = SprintForN(str, &ap);
          p = &(str[s21_strlen(str)]);
          *p = '\0';
          break;
      }
    } else {
      *p = format[i];
      p++;
      *p = '\0';
    }
  }
  va_end(ap);
  return 0;
}

specifier_builder ParserForSpecifier(const char *format, va_list *ap,
                                     int *shift) {
  specifier_builder specifiers = {{0}, -1, -1, 0, 0, 0};
  char specifier_list[MAX_SPEC + 1] = {'c', 'd', 'i', 'e', 'E', 'f', 'g', 'G',
                                       'o', 's', 'u', 'x', 'X', 'p', 'n', '\0'};
  char flag_list[MAX_FLAG + 1] = {'-', '+', ' ', '#', '0', '\0'};
  char length_list[MAX_LENGTH + 1] = {'h', 'l', 'L', '\0'};
  int break_status = 6;

  for (size_t i = 0; break_status != 0 && i < s21_strlen(format); ++i) {
    *shift += 1;
    if (break_status == 6 && s21_strchr(flag_list, format[i]) != NULL) {
      if (s21_strchr(specifiers.flags, format[i]) == NULL) {
        int length_of_flags = (int)s21_strlen(specifiers.flags);
        specifiers.flags[length_of_flags] = format[i];
        specifiers.flags[length_of_flags + 1] = '\0';
      }
    } else if (break_status == 6)
      break_status = 5;

    if (break_status == 5 &&
        ((format[i] - '0' >= 0 && format[i] - '0' <= 9) || format[i] == '*')) {
      if (specifiers.width == -1) specifiers.width = 0;
      specifiers.width = specifiers.width * 10 + (format[i] - '0');
      if (format[i] == '*') {
        specifiers.width = va_arg(*ap, int);
        break_status = 4;
        continue;
      }
    } else if (break_status == 5)
      break_status = 4;

    if (break_status == 4 && format[i] == '.') {
      break_status = 3;
      continue;
    } else if (break_status == 4)
      break_status = 3;

    if (break_status == 3 &&
        ((format[i] - '0' >= 0 && format[i] - '0' <= 9) || format[i] == '*')) {
      if (specifiers.precision == -1) specifiers.precision = 0;
      specifiers.precision = specifiers.precision * 10 + (format[i] - '0');
      if (format[i] == '*') {
        specifiers.precision = va_arg(*ap, int);
        break_status = 2;
        continue;
      }
    } else if (break_status == 3)
      break_status = 2;

    if (break_status == 2 && s21_strchr(length_list, format[i]) != NULL) {
      specifiers.length = format[i];
      break_status = 1;
    } else if (break_status == 2)
      break_status = 1;

    if (s21_strchr(specifier_list, format[i]) != NULL) {
      specifiers.specifier = format[i];
      break_status = 0;
    }
  }

  switch (specifiers.specifier) {
    case 'e':
    case 'E':
    case 'f':
      if (specifiers.precision == -1) {
        specifiers.precision = 6;
      }
      break;
    case 'g':
    case 'G':
      if (specifiers.precision == -1) {
        specifiers.precision = 5;
      }
      break;
    default:
      if (specifiers.precision == -1) {
        specifiers.precision = 1;
      }
  }

  return specifiers;
}

char *SprintForC(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status) {
  char buffer_str[2] = {(char)va_arg(*ap, int), '\0'};

  str = BuilderForStr(str, specifiers, buffer_str, negative_status);

  return str;
}

char *SprintForD(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status) {
  char buffer_str[12] = {};

  int num = va_arg(*ap, int);
  int i = 0;

  if (num < 0 && s21_strchr(specifiers.flags, '0') == NULL)
    buffer_str[i++] = '-';

  if (num == 0) {
    buffer_str[i++] = '0';
  } else {
    char int_buffer[20];
    int int_len = 0;
    while (num > 0) {
      int_buffer[int_len++] = '0' + (num % 10);
      num /= 10;
    }
    for (int j = int_len - 1; j >= 0; j--) {
      buffer_str[i++] = int_buffer[j];
    }
  }

  str = BuilderForStr(str, specifiers, buffer_str, negative_status);
  return str;
}

char *SprintForE(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status) {
  int precision = specifiers.precision;

  char buffer_str[50] = {};

  double num = va_arg(*ap, double);
  int i = 0;
  int counter = 0;

  while (num >= 10) {
    num /= 10.0;
    counter++;
  }

  while (num < 1) {
    num *= 10.0;
    counter--;
  }

  int intPart = (int)num;
  i = 0;
  while (intPart > 0) {
    buffer_str[i] = '0' + intPart % 10;
    intPart /= 10;
    i++;
  }

  buffer_str[i] = '.';
  i++;

  double fractionalPart = fabs(num - (double)((int)num));
  fractionalPart = my_round(fractionalPart, specifiers.precision);
  for (int j = 0; j < precision; j++) {
    fractionalPart *= 10;
    fractionalPart = my_round(fractionalPart, specifiers.precision);
    buffer_str[i] = '0' + (int)fractionalPart;
    i++;
    fractionalPart -= (int)fractionalPart;
  }

  buffer_str[i] = specifiers.specifier;
  i++;
  if (counter > 0) {
    buffer_str[i] = '+';
    i++;
  } else {
    buffer_str[i] = '-';
    counter *= -1;
    i++;
  }

  int temp = 0;

  if (counter < 10) buffer_str[i] = '0';
  i++;

  while (counter != 0) {
    temp = temp * 10 + counter % 10;
    counter /= 10;
  }

  while (temp != 0) {
    buffer_str[i] = '0' + temp % 10;
    buffer_str[i + 1] = '\0';
    i++;
    temp /= 10;
  }

  buffer_str[i] = '\0';

  str = BuilderForStr(str, specifiers, buffer_str, negative_status);
  return str;
}

char *SprintForF(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status) {
  int error_status = 0;
  int precision = specifiers.precision;

  char buffer_str[50] = {};

  double num = va_arg(*ap, double);
  int i = 0;

  if (isnan(num)) {
    s21_strncpy(buffer_str, "NaN", 3);
    error_status = 1;
  } else if (isinf(num)) {
    if (num > 0) {
      s21_strncpy(buffer_str, "inf", 3);
    } else {
      buffer_str[0] = '\0';
      s21_strncpy(buffer_str, "-inf", 4);
    }
    error_status = 1;
  }

  long int intPart = (long int)fabs(num);

  if (error_status == 0) {
    if (num < 0 && s21_strchr(specifiers.flags, '0') == NULL)
      buffer_str[i++] = '-';

    if (intPart == 0) {
      buffer_str[i++] = '0';
    } else {
      char int_buffer[20];
      int int_len = 0;
      while (intPart > 0) {
        int_buffer[int_len++] = '0' + (intPart % 10);
        intPart /= 10;
      }
      for (int j = int_len - 1; j >= 0; j--) {
        buffer_str[i++] = int_buffer[j];
      }
    }

    buffer_str[i++] = '.';

    double fractionalPart = fabs(num - (double)((int)num));
    fractionalPart = my_round(fractionalPart, specifiers.precision);
    for (int j = 0; j < precision; j++) {
      fractionalPart *= 10;
      fractionalPart = my_round(fractionalPart, specifiers.precision);
      buffer_str[i] = '0' + (int)fractionalPart;
      i++;
      fractionalPart -= (int)fractionalPart;
    }

    buffer_str[i] = '\0';
  }
  str = BuilderForStr(str, specifiers, buffer_str, negative_status);
  return str;
}

char *SprintForO(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status) {
  char buffer_str[50] = {};

  unsigned int num = va_arg(*ap, unsigned int);
  int buf_num = num;
  int i = 0;

  if (num == 0) {
    buffer_str[i++] = '0';
  } else {
    while (num > 0) {
      buffer_str[i++] = '0' + (num % 8);
      num /= 8;
    }
  }

  if (s21_strchr(specifiers.flags, '#') != NULL && buf_num != 0) {
    buffer_str[i] = '0';
    i++;
  }

  buffer_str[i] = '\0';

  int len = i;
  for (int j = 0; j < len / 2; j++) {
    char temp = buffer_str[j];
    buffer_str[j] = buffer_str[len - j - 1];
    buffer_str[len - j - 1] = temp;
  }

  str = BuilderForStr(str, specifiers, buffer_str, negative_status);
  return str;
}

double my_round(double value, int n) {
  double scale = pow(10, n);
  return round(value * scale) / scale;
}

char *SprintForS(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status) {
  char *input_str = va_arg(*ap, char *);

  char buffer_str[4096] = {};
  int i = 0;

  while (input_str[i] != '\0') {
    buffer_str[i] = input_str[i];
    i++;
  }
  buffer_str[i] = '\0';

  str = BuilderForStr(str, specifiers, buffer_str, negative_status);
  return str;
}

char *SprintForU(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status) {
  char buffer_str[50] = {};

  unsigned int num = va_arg(*ap, unsigned int);
  int i = 0;

  if (num == 0) {
    buffer_str[i++] = '0';
  } else {
    unsigned int temp = num;
    while (temp > 0) {
      buffer_str[i++] = '0' + (temp % 10);
      temp /= 10;
    }
  }

  buffer_str[i] = '\0';

  int len = i;
  for (int j = 0; j < len / 2; j++) {
    char temp = buffer_str[j];
    buffer_str[j] = buffer_str[len - j - 1];
    buffer_str[len - j - 1] = temp;
  }

  str = BuilderForStr(str, specifiers, buffer_str, negative_status);
  return str;
}

char *SprintForX(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status) {
  char buffer_str[50] = {};
  const char *hex_digits =
      (specifiers.specifier == 'x') ? "0123456789abcdef" : "0123456789ABCDEF";

  unsigned int num = va_arg(*ap, unsigned int);
  int i = 0;

  if (num == 0) {
    buffer_str[i++] = '0';
  } else {
    unsigned int temp = num;
    while (temp > 0) {
      buffer_str[i++] = hex_digits[temp % 16];
      temp /= 16;
    }
  }

  if (s21_strchr(specifiers.flags, '#') != NULL && num != 0) {
    if (specifiers.specifier == 'x') {
      buffer_str[i++] = 'x';
      buffer_str[i++] = '0';
    } else {
      buffer_str[i++] = 'X';
      buffer_str[i++] = '0';
    }
  }

  buffer_str[i] = '\0';

  int len = i;
  for (int j = 0; j < len / 2; j++) {
    char temp = buffer_str[j];
    buffer_str[j] = buffer_str[len - j - 1];
    buffer_str[len - j - 1] = temp;
  }

  str = BuilderForStr(str, specifiers, buffer_str, negative_status);
  return str;
}

char *SprintForP(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status) {
  char buffer_str[50] = {};
  const char *hex_digits = "0123456789abcdef";

  void *ptr = va_arg(*ap, void *);
  unsigned long num = (unsigned long)ptr;
  int i = 0;

  buffer_str[i++] = '0';
  buffer_str[i++] = 'x';

  if (num == 0) {
    buffer_str[i++] = '0';
  } else {
    unsigned long temp = num;
    while (temp > 0) {
      buffer_str[i++] = hex_digits[temp % 16];
      temp /= 16;
    }
  }

  buffer_str[i] = '\0';

  int start = 2;
  int len = i;
  for (int j = start; j < (start + len) / 2; j++) {
    char temp = buffer_str[j];
    buffer_str[j] = buffer_str[len - (j - start) - 1];
    buffer_str[len - (j - start) - 1] = temp;
  }

  str = BuilderForStr(str, specifiers, buffer_str, negative_status);
  return str;
}

char *SprintForN(char *str, va_list *ap) {
  int *ptr = va_arg(*ap, int *);

  *ptr = (int)s21_strlen(str);

  return str;
}

// char *SprintForSpecialValues(char *str, va_list *ap) {
//     int *ptr = va_arg(*ap,
//     int*);
//
//     *ptr = (int) s21_strlen(str);
//
//     return str;
// }

char *BuilderForStr(char *str, specifier_builder specifiers, char *buffer_str,
                    int negative_status) {
  int chars_in_specifier = s21_strlen(buffer_str);
  int chars_to_print = 0;
  if (specifiers.specifier == 'd' && specifiers.precision >= 0 &&
      chars_in_specifier < specifiers.precision)
    chars_in_specifier = specifiers.precision;
  char *p = str;
  int i = s21_strlen(str);
  if (specifiers.width == -1) specifiers.width = s21_strlen(buffer_str);

  while (chars_to_print < specifiers.width) {
    if (s21_strchr(specifiers.flags, '0') != NULL && chars_to_print == 0) {
      if (negative_status == 1) {
        p[i] = '-';
      } else {
        if (s21_strchr(specifiers.flags, '+') != NULL) p[i] = '+';
      }

      if (s21_strchr(specifiers.flags, '+') != NULL || negative_status == 1) {
        p[i + 1] = '\0';
        i += 1;
        chars_to_print += 1;
      }
    }

    if ((s21_strchr(specifiers.flags, '-') != NULL && chars_to_print == 0) ||
        (s21_strchr(specifiers.flags, '-') == NULL &&
         chars_to_print >= specifiers.width - chars_in_specifier)) {
      str = BuilderForPrecision(str, buffer_str, &i, &chars_to_print,
                                specifiers, negative_status);

    } else {
      if (s21_strchr(specifiers.flags, '0') != NULL)
        p[i] = '0';
      else
        p[i] = ' ';
      p[i + 1] = '\0';
      i++;
      chars_to_print++;
    }
  }

  return str;
}

char *BuilderForPrecision(char *str, char *buffer_str, int *i,
                          int *chars_to_print, specifier_builder specifiers,
                          int negative_status) {
  char *p = str;
  int precision_counter = 0;

  if (s21_strchr(specifiers.flags, '+') != NULL &&
      s21_strchr(specifiers.flags, '0') == NULL) {
    if (negative_status == 1) {
      p[*i] = '-';
    } else {
      p[*i] = '+';
    }
    p[*i + 1] = '\0';
    *i += 1;
    *chars_to_print += 1;
  }

  if (s21_strchr(specifiers.flags, ' ') != NULL &&
      s21_strchr(specifiers.flags, '+') == NULL) {
    p[*i] = ' ';

    p[*i + 1] = '\0';
    *i += 1;
    *chars_to_print += 1;
  }

  switch (specifiers.specifier) {
    case 'c':
      while (*buffer_str != '\0') {
        p[*i] = *buffer_str;
        buffer_str++;
        p[*i + 1] = '\0';
        *i += 1;
        *chars_to_print += 1;
      }
      break;
    case 'E':
    case 'e':
    case 'f':
    case 'o':
    case 's':
    case 'u':
    case 'x':
    case 'X':
    case 'p':
    case 'n':
      while (*buffer_str != '\0') {
        p[*i] = *buffer_str;
        buffer_str++;
        p[*i + 1] = '\0';
        *i += 1;
        *chars_to_print += 1;
      }
      break;
    case 'i':
    case 'd':
      while (precision_counter + s21_strlen(buffer_str) <
             (size_t)specifiers.precision) {
        p[*i] = '0';
        p[*i + 1] = '\0';
        *i += 1;
        *chars_to_print += 1;
        precision_counter++;
      }
      while (*buffer_str != '\0') {
        p[*i] = *buffer_str;
        buffer_str++;
        p[*i + 1] = '\0';
        *i += 1;
        *chars_to_print += 1;
      }
      break;
    default:
      break;
  }

  return str;
}