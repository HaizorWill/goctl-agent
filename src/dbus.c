#include <stddef.h>
#include <stdlib.h>
#include <systemd/sd-bus-protocol.h>
#include <systemd/sd-bus.h>
#include <unistd.h>

struct systemd_bus {
  sd_bus *bus;
  sd_bus_error *err;
  sd_bus_message *mes;
};

struct systemd_bus *new_systemd_bus(void) {
  struct systemd_bus *dbus = calloc(1, sizeof(struct systemd_bus));
  int err = sd_bus_open_system(&dbus->bus);
  if (err < 0)
    return NULL;
  return dbus;
}

// Not too sure what to do with this to be frank :/
// Needs to be flexible, so that we are able to call whatever
// Yet i am not too sure how to go about it
// Might pass parameters directly into it, though it is dumb, since it does
// exactly what it does under the hood
int systemd_bus_call(struct systemd_bus *dbus) {
  // int err = sd_bus_call_method();
  int err = sd_bus_call_method(
      dbus->bus, "org.freedesktop.systemd1", "/org/freedesktop/systemd1",
      "org.freedesktop.systemd1.Manager", "GetUnitByPID", dbus->err, &dbus->mes,
      "u", (unsigned)getpid());
  if (err < 0)
    return 1;
  return 0;
}

char *systemd_bus_message_read(struct systemd_bus *dbus) {
  char *ans;
  int err = sd_bus_message_read(dbus->mes, "", &ans);
  if (err < 0)
    return NULL;
  return ans;
}
