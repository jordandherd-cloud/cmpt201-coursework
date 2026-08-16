#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_FILE "myfifo"

int main() {

  char test[] = "Hello world";

  int fd = open(FIFO_FILE, O_WRONLY);
  if (fd == -1) {
    perror("open");
    exit(1);
  }

  write(fd, test, sizeof(test) - 1);

  close(fd);
  return 0;
}
