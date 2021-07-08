AXIS_USABLE_LIBS = UCLIBC GLIBC
include $(AXIS_TOP_DIR)/tools/build/rules/common.mak

PROG = axserialport_example
OBJS = $(PROG).o
PKGS = glib-2.0 axserialport

CFLAGS += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags $(PKGS))
CFLAGS += -I../library
CFLAGS += -Wall -O2

LDFLAGS += -L../library
LDLIBS  += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs $(PKGS))

all:	$(PROG)

install: $(PROG)

$(PROG): $(OBJS)
	$(CC) $^ $(LIBS) $(LDLIBS) $(LDFLAGS) -lgthread-2.0 -o $@
	$(STRIP) $@

cflags:
	$(info $(CFLAGS))

ldlibs:
	$(info $(LDLIBS))

ldflags:
	$(info $(LDFLAGS))

clean:
	rm -f $(PROG) *.o core

