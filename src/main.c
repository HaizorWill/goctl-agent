#include <stdbool.h>

#include "../include/dbus.h"
#include <systemd/sd-bus.h>

bool loadConfig(void) { return false; }

int main() {
  struct systemd_bus *bus = new_systemd_bus();
  systemd_bus_call(bus);
  char *ans = systemd_bus_message_read(bus);
  return 0;
}
