#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PASSWORD_MIN_LEN 1
#define PASSWORD_MAX_LEN 32
#define ARRAY_SIZE(x)    (sizeof(x) / sizeof(*(x)))

static const char valid_characters[] = {
  ' ',  '!',  '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/', 
  '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?', 
  '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O', 
  'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  '[', '\\',  ']',  '^',  '_', 
  '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'o', 
  'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',  '{',  '|',  '}',  '~'
};

int main(int argc, const char** argv)
{
  char password[PASSWORD_MAX_LEN + 1];
  size_t minlen, maxlen, len;
  size_t i;
  int n;

  /* Set seed. */
  srandom(time(NULL));

  /* Check arguments. */
  if (argc == 2) {
    if (((n = atoi(argv[1])) < PASSWORD_MIN_LEN) || (n > PASSWORD_MAX_LEN)) {
      fprintf(stderr,
              "Invalid length '%s' (valid range: %u .. %u).\n",
              argv[1],
              PASSWORD_MIN_LEN,
              PASSWORD_MAX_LEN);
      return -1;
    }

    len = n;
  } else if (argc == 3) {
    if (((n = atoi(argv[1])) < PASSWORD_MIN_LEN) || (n > PASSWORD_MAX_LEN)) {
      fprintf(stderr,
              "Invalid length '%s' (valid range: %u .. %u).\n",
              argv[1],
              PASSWORD_MIN_LEN,
              PASSWORD_MAX_LEN);
      return -1;
    }

    minlen = n;

    if (((n = atoi(argv[2])) < PASSWORD_MIN_LEN) || (n > PASSWORD_MAX_LEN)) {
      fprintf(stderr,
              "Invalid length '%s' (valid range: %u .. %u).\n",
              argv[2],
              PASSWORD_MIN_LEN,
              PASSWORD_MAX_LEN);
      return -1;
    }

    maxlen = n;

    if (minlen > maxlen) {
      fprintf(stderr,
              "The minimum length (%s) is greater than "
              "the maximum length (%s).\n",
              argv[1],
              argv[2]);

      return -1;
    }

    /* Generate random length between minlen and maxlen. */
    len = (random() % (maxlen - minlen + 1)) + minlen;
  } else {
    fprintf(stderr, "Usage: %s <length> [<maximum-length>]\n", argv[0]);
    fprintf(stderr,
            "\t<length> ::= %u .. %u\n",
            PASSWORD_MIN_LEN,
            PASSWORD_MAX_LEN);

    return -1;
  }

  /* Generate random password of length 'len'. */
  for (i = 0; i < len; i++) {
    password[i] = valid_characters[random() % ARRAY_SIZE(valid_characters)];
  }

  password[i] = 0;

  printf("Password length: %lu, password: '%s'.\n", len, password);

  return 0;
}
