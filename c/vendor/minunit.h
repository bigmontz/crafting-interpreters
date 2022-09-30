#include <stdio.h>

#define mu_assert(message, test) \
  do                             \
  {                              \
    if (!(test))                 \
      return message;            \
  } while (0)
#define mu_run_test(test)   \
  do                        \
  {                         \
    char *message = test(); \
    tests_run++;            \
    if (message)            \
      return message;       \
  } while (0)
extern int tests_run;

#define mu_test_suite(name, run_tests)    \
  int tests_run = 0;                      \
  int main(int argc, char **argv)         \
  {                                       \
    printf("Running ");                   \
    puts(name);                           \
    char *result = run_tests();           \
    if (result != 0)                      \
    {                                     \
      printf("%s\n", result);             \
    }                                     \
    else                                  \
    {                                     \
      printf("ALL TESTS PASSED\n");       \
    }                                     \
    printf("Tests run: %d\n", tests_run); \
    return result != 0;                   \
  }
