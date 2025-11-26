IDIR =include
CC=clang
CFLAGS=-v -Wall -Wextra -I$(IDIR)

ODIR=obj
LDIR=lib

_DEPS = include/dbus.h

_OBJ = obj/main.o obj/dbus.o obj/server.o

$(ODIR)/%.o: src/%.c #$(_DEPS)
	$(CC) -std=c23 -c -o $@ $< $(CFLAGS)

goctl-agent: $(_OBJ)
	$(CC) -o $@ $^ -lsystemd $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

