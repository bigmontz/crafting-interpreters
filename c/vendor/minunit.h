#include <stdio.h>

#define mu_assert(message, test) \
  do                             \
  {                              \
    if (!(test))                 \
      return message;            \
  } while (0)
#define mu_run_test(description, test)                \
  do                                                  \
  {                                                   \
    printf("\t");                                     \
    printf(description);                              \
    printf("...");                                    \
    char *message = test();                           \
    tests_run++;                                      \
    if (message)                                      \
    {                                                 \
      tests_failed++;                                 \
      printf("\033[0;31mFAIL: %s\033[0m\n", message); \
    }                                                 \
    else                                              \
    {                                                 \
      puts(" \033[0;32mOK\033[0m");                   \
    }                                                 \
  } while (0);

extern int tests_run;
extern int tests_failed;

#define mu_test_suite(name, run_tests)                                \
  int tests_run = 0;                                                  \
  int tests_failed = 0;                                               \
  int main(int argc, char **argv)                                     \
  {                                                                   \
    printf("Running ");                                               \
    puts(name);                                                       \
    char *result = run_tests();                                       \
    printf("Tests run: %d, Failures: %d\n", tests_run, tests_failed); \
    return tests_failed != 0;                                         \
  }
