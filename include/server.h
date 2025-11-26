typedef struct tcp_server tcp_server;

int tcp_server_serve(struct tcp_server *server);
int create_socket(struct tcp_server *server);
int bind_socket(struct tcp_server *server);
void close_socket(struct tcp_server *server);
void tcp_server_close_unref(struct tcp_server *server);
struct tcp_server *new_tcp_server(void);
