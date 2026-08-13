#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// task taken from file slides
//
int main() {

  char buf[1024];

  FILE *tmp;

  tmp = fopen("tmp", O_CREAT);

  if (tmp == NULL)
    printf("File not opened\n");

  fprintf(tmp, "Hello World!");

  fseek(tmp, 6, 0);

  fclose(tmp);
  return 0;
}

char *str = "hello world";
char buf[12];

int fd = open("tmp", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

if (fd == -1) {
  perror("Open failed");

  exit(SYSTEM_FAILED);
}

write(fd, str, strlen(str));

lseek(fd, -6, SEEK_CUR);
read(fd, buf, 6);
write(STDOUT_FILENO, buf, 6);
close(fd);

printf("\n");
