#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

struct tcp_server {
  int socket_fd;
  struct sockaddr_in socket_addr;
};

int create_socket(struct tcp_server *server) {
  server->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server->socket_fd < 0) {
    printf("Could not create socket... %s\n", strerror(errno));
    return -1;
  }
  return 0;
}

int bind_socket(struct tcp_server *server) {
  int err = bind(server->socket_fd, (struct sockaddr *)&server->socket_addr,
                 sizeof(server->socket_addr));
  if (err < 0)
    return -1;
  return 0;
}

struct tcp_server *initialize_server(void) {
  struct tcp_server *server = calloc(1, sizeof(struct tcp_server));

  const int port = 8080;

  server->socket_addr.sin_family = AF_INET;
  server->socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server->socket_addr.sin_port = htons(port);

  create_socket(server);

  listen(server->socket_fd, 10);

  return 0;
}
