#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define FIFO_FILE "myfifo"

int main() {

  char buf[1024];

  mkfifo(FIFO_FILE, S_IRUSR | S_IWUSR);

  int fd = open(FIFO_FILE, O_RDONLY);
  if (fd == -1) {
    perror("open");
    exit(1);
  }

  while (read(fd, &buf, 1) > 0) {

    write(STDOUT_FILENO, &buf, 1);
  }

  close(fd);
  return 0;
}
