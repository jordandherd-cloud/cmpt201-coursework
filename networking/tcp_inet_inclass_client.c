#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#define PATH "tmp_sock"

// tcp server copied in class
//

int main() {

  // socket()
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (sock_fd == -1) {

    perror("socket");
    exit(EXIT_FAILURE);
  }

  // conect
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8000);

  if (inet_pton(AF_INET, "127.0.0.1", addr.sin_addr.s_addr) != 1) {
    perror("inet");
    exit(EXIT_FAILURE);
  }

  if (connect(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {

    perror("connect");
    exit(EXIT_FAILURE);
  }

  for (;;) {
    char buf[1024];
    int size_read = read(STDIN_FILENO, buf, sizeof(buf));

    if (size_read > 0) {
      if (connect(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {

        perror("connect");

        exit(EXIT_FAILURE);
      }
    }

    // read()

    // close()
    //

    close(sock_fd);

    return 0;
  }
