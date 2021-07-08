AXIS_USABLE_LIBS = UCLIBC GLIBC
include $(AXIS_TOP_DIR)/tools/build/rules/common.mak

PROGS     = axStorageExample

CFLAGS   += -Wall -g -O2 -Werror

PKGS = glib-2.0 gio-2.0 axstorage
CFLAGS += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags $(PKGS))
LDLIBS += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs $(PKGS))

SRCS      = ax_storage_example.c
OBJS      = $(SRCS:.c=.o)

# Add libraries here
ifeq ($(AXIS_OPT_DEBUG),y)
CFLAGS	+= -DDEBUG
endif

all:	$(PROGS)

# Link and strip the binary
$(PROGS): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) $(LDLIBS) -o $@
	$(STRIP) $@

# Install the package on the camera
install:	$(PROGS)
#	@$(AXIS_TOP_DIR)/tools/scripts/create-package.sh
#	@$(AXIS_TOP_DIR)/tools/scripts/install-onto-target.sh install

clean:
	rm -f $(PROGS) *.o *.a core

