#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <systemd/sd-bus-protocol.h>
#include <systemd/sd-bus.h>
#include <unistd.h>

struct systemd_bus {
  sd_bus *bus;
  sd_bus_error *err;
  sd_bus_message *mes;
  const char *dest;
  const char *path;
  const char *iface;
};

struct systemd_bus *new_systemd_bus(void) {
  struct systemd_bus *dbus = calloc(1, sizeof(struct systemd_bus));
  int err = sd_bus_open_system(&dbus->bus);
  if (err < 0)
    return NULL;
  return dbus;
}

void systemd_bus_conn_close(struct systemd_bus *dbus) {
  sd_bus_close_unref(dbus->bus);
  free(dbus);
}

void systemd_bus_set_dest(struct systemd_bus *dbus) {
  dbus->dest = "org.freedesktop.systemd1";
  dbus->path = "/org/freedesktop/systemd1";
  dbus->iface = "org.freedesktop.systemd1.Manager";
}
// Not too sure what to do with this to be frank :/
// Needs to be flexible, so that we are able to call whatever
// Yet i am not too sure how to go about it
// Might pass parameters directly into it, though it is dumb, since it does
// exactly what it does under the hood
int systemd_bus_call(struct systemd_bus *dbus, const char *member,
                     const char *types, ...) {
  va_list args;
  va_start(args, types);
  int err = sd_bus_call_methodv(dbus->bus, dbus->dest, dbus->path, dbus->iface,
                                member, dbus->err, &dbus->mes, types, args);
  va_end(args);
  if (err < 0)
    return 1;
  return 0;
}

char *systemd_bus_message_read(struct systemd_bus *dbus, const char *types) {
  char *ans;
  int err = sd_bus_message_read(dbus->mes, types, &ans);
  if (err < 0)
    return NULL;
  return ans;
}
