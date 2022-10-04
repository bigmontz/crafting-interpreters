#include <stdio.h>

#define mu_assert(message, test) \
  do                             \
  {                              \
    if (!(test))                 \
      return message;            \
  } while (0)
#define mu_run_test(description, test) \
  do                                   \
  {                                    \
    printf("\t");                      \
    printf(description);               \
    printf("...");                     \
    char *message = test();            \
    tests_run++;                       \
    if (message)                       \
    {                                  \
      puts("\033[0;31mFAIL\033[0m");   \
      printf("\t\t Reason: ");         \
      puts(message);                   \
      return message;                  \
    }                                  \
    puts(" \033[0;32mOK\033[0m");      \
  } while (0);

extern int tests_run;

#define mu_test_suite(name, run_tests)    \
  int tests_run = 0;                      \
  int main(int argc, char **argv)         \
  {                                       \
    printf("Running ");                   \
    puts(name);                           \
    char *result = run_tests();           \
    if (result == 0)                      \
    {                                     \
      printf("ALL TESTS PASSED\n");       \
    }                                     \
    printf("Tests run: %d\n", tests_run); \
    return result != 0;                   \
  }
