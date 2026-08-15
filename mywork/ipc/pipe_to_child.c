#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int pipefd[2];

  int snipefd[2];
  char buf;

  pid_t cpid;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <string>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  if (pipe(snipefd) == -1) {
    perror("snipe");
    exit(EXIT_FAILURE);
  }
  cpid = fork();
  if (cpid == -1) {
    perror("fork");

    exit(EXIT_FAILURE);
  }

  if (cpid == 0) { /* Child reads from pipe */

    close(pipefd[1]); /* Close unused write end */

    close(snipefd[0]); // close read end 2nd pipe
    while (read(pipefd[0], &buf, 1) > 0)
      write(snipefd[1], &buf, 1);

    write(snipefd[1], "\n", 1);

    close(pipefd[0]);

    // child has to take msg from buf
    // write it trhough another pipe to paretn

    close(snipefd[1]);
    _exit(EXIT_SUCCESS);

  } else { /* Parent writes argv[1] to pipe */

    close(pipefd[0]); /* Close unused read end */

    close(snipefd[1]);
    write(pipefd[1], argv[1], strlen(argv[1]));

    close(pipefd[1]); /* Reader will see EOF */

    // wait(NULL); /* Wait for child */

    while (read(snipefd[0], &buf, 1) > 0) {

      char as_upper = toupper(buf);
      write(STDOUT_FILENO, &as_upper, 1);
    }

    // printf("TTT\n");
    close(snipefd[0]);

    wait(NULL);
    exit(EXIT_SUCCESS);
  }

  return 0;
}
