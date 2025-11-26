typedef struct systemd_bus systemd_bus;

struct systemd_bus *new_systemd_bus(void);
void systemd_bus_conn_close_unref(struct systemd_bus *dbus);
void systemd_bus_set_dest(struct systemd_bus *dbus);
int systemd_bus_call(struct systemd_bus *dbus, const char *member,
                     const char *types, ...);
char *systemd_bus_message_read(struct systemd_bus *dbus, const char *types);
