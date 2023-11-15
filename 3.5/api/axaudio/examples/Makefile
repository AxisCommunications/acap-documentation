AXIS_USABLE_LIBS = UCLIBC GLIBC
include $(AXIS_TOP_DIR)/tools/build/rules/common.mak

PROGS     = audioApp

CFLAGS   += -Wall -g -O2 -lm
LDFLAGS  += -lm

PKGS = glib-2.0 gio-2.0 axaudio
CFLAGS += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags $(PKGS))
LDLIBS += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs $(PKGS))

SRCS      = axaudioexample.c
OBJS      = $(SRCS:.c=.o)

all: $(PROGS)

$(PROGS): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f $(PROGS) *.o
