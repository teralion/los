#include "lib.h"

/*
* Reads commands from standard input
* and executes them
*
* If it reminds you shell interpreter
* shall not be confused, it is
*
*/

static void sig_int(int);

int
main(void)
{
  char buf[MAXLINE];
  pid_t pid;
  int status;

  if (signal(SIGINT, sig_int) == SIG_ERR) {
    printf("signal call error\n");
    exit(1);
  }

  printf("%% "); /* echo greeting */

  while (fgets(buf, MAXLINE, stdin) != NULL) {
    if (buf[strlen(buf) - 1] == '\n')
      buf[strlen(buf) - 1] = 0;
    if ((pid = fork()) < 0) {
      printf("fork error\n");
      exit(1);
    } else if (pid == 0) { /* child process */
      execlp(buf, buf, (char *)0);
      printf("cannot execute: %s\n", buf);
      exit(127);
    }

    if ((pid = waitpid(pid, &status, 0)) < 0) {
      printf("error calling waitpid\n");
      exit(0);
    }
    printf("%% ");
  }

  printf("\n");
  exit(0);
}

void
sig_int(int signo)
{
  printf("interrupted\n%% ");
}
