#include <stdbool.h>

#include "dbus.h"
#include "server.h"
#include <stdint.h>
#include <stdio.h>
#include <systemd/sd-bus.h>
#include <unistd.h>

bool loadConfig(void) { return false; }

int main() {
  struct systemd_bus *bus = new_systemd_bus();
  systemd_bus_set_dest(bus);
  unsigned pid = 1;
  systemd_bus_call(bus, "GetUnitByPID", "u", pid);
  char *ans = systemd_bus_message_read(bus, "o");
  printf("Here: %s\n", ans);
  systemd_bus_conn_close_unref(bus);
  struct tcp_server *server = new_tcp_server();
  while (true) {
    int err = tcp_server_serve(server);
    if (err < 0) {
      tcp_server_close_unref(server);
      break;
    }
  }
  tcp_server_close_unref(server);
  return 0;
}
