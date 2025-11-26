#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

struct tcp_server {
  int socket_fd;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  socklen_t client_len;
};

void read_and_reply(int connection_fd) {
  char rbuf[64] = {};
  ssize_t n = read(connection_fd, rbuf, sizeof(rbuf) - 1);
  if (n < 0) {
    printf("%s\n", strerror(errno));
    return;
  }
  printf("Simon says: %s", rbuf);

  char wbuf[] = "What does simon say";
  write(connection_fd, wbuf, strlen(wbuf));
}

int tcp_server_serve(struct tcp_server *server) {
  int connection_fd =
      accept(server->socket_fd, (struct sockaddr *)&server->client_addr,
             &server->client_len);
  if (connection_fd < 0)
    return -1;

  read_and_reply(connection_fd);
  close(connection_fd);
  return 0;
}

int create_socket(struct tcp_server *server) {
  server->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server->socket_fd < 0) {
    printf("Could not create socket... %s\n", strerror(errno));
    exit(1);
  }
  return 0;
}

int bind_socket(struct tcp_server *server) {
  int err = bind(server->socket_fd, (struct sockaddr *)&server->server_addr,
                 sizeof(server->server_addr));
  if (err < 0)
    return -1;
  return 0;
}

void close_socket(struct tcp_server *server) {
  shutdown(server->socket_fd, SHUT_RD);
  close(server->socket_fd);
}

void tcp_server_close_unref(struct tcp_server *server) {
  close_socket(server);
  free(server);
}

struct tcp_server *new_tcp_server(void) {
  struct tcp_server *server = calloc(1, sizeof(struct tcp_server));

  const int port = 8080;

  server->server_addr.sin_family = AF_INET;
  server->server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server->server_addr.sin_port = htons(port);
  server->client_len = sizeof(server->client_addr);
  create_socket(server);

  bind_socket(server);

  listen(server->socket_fd, 10);

  return server;
}
