#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {

  int fd = open("tmp", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

  if (fd == -1) {
    perror("Open failed");

    exit(0);
  }

  char *msg = "Hello, hope this works well!\n";
  int res = write(fd, msg, strlen(msg));

  for (;;) {

    sleep(30);
  }

  return 0;
}
