#include <stddef.h>
#include <stdlib.h>
#include <systemd/sd-bus.h>

struct systemd_bus {
  sd_bus *bus;
  sd_bus_error *err;
  sd_bus_message *mes;
};

struct systemd_bus *new_systemd_bus(void) {
  struct systemd_bus *bus = calloc(1, sizeof(struct systemd_bus));
  int err = sd_bus_open_system(&bus->bus);
  if (err < 0)
    return 0;
  return bus;
}
