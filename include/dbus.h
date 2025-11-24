typedef struct systemd_bus systemd_bus;

struct systemd_bus *new_systemd_bus(void);
int systemd_bus_call(struct systemd_bus *dbus);
char *systemd_bus_message_read(struct systemd_bus *dbus);
