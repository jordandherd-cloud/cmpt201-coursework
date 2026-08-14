#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
// task taken from file slides
//
int main() {

  /*  char buf[1024];

    FILE *tmp;

    tmp = fopen("tmp", "w+");

    if (tmp == NULL)
      printf("File not opened\n");

    fprintf(tmp, "Hello World!");

    fseek(tmp, -6, SEEK_CUR);

    fread(buf, 1, 6, tmp);
    buf[6] = '\0';
    printf("%s\n", buf);
    fclose(tmp);
    return 0;*/

  char *str = "hello world";
  char buf[12];

  int fd = open("tmp", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

  if (fd == -1) {
    perror("Open failed");

    exit(0);
  }

  write(fd, str, strlen(str));

  lseek(fd, -6, SEEK_CUR);
  read(fd, buf, 6);
  write(STDOUT_FILENO, buf, 6);
  close(fd);

  printf("\n");
}
