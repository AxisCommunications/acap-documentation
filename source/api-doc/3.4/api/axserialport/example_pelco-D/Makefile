AXIS_USABLE_LIBS = UCLIBC GLIBC
include $(AXIS_TOP_DIR)/tools/build/rules/common.mak

PROG = axserialport_pelco_spectra_mini
OBJS = $(PROG).o
PKGS = glib-2.0

CFLAGS += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags $(PKGS))
CFLAGS += -I../library
CFLAGS += -Wall -O2

LDFLAGS += -L../library
LDLIBS  += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs $(PKGS))
LDLIBS  += -laxserialport

all:	$(PROG)

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

