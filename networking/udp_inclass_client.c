#include <errno.h>
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
  int sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0); // DGRAM FOR UDP

  if (sock_fd == -1) {

    perror("socket");
    exit(EXIT_FAILURE);
  }

  // conect
  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, PATH, sizeof(addr.sun_path) - 1);

  for (;;) {

    char buf[1024];
    int size_read = read(STDIN_FILENO, buf, sizeof(buf));

    if (size_read > 0) {
      if (connect(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {

        if (sendto
        perror("write");
        exit(EXIT_FAILURE);
      }
    } else {
      break;
    } // unfinished
  }

  // read()

  // close()
  //

  close(sock_fd);

  return 0;
}
