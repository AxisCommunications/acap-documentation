AXIS_USABLE_LIBS = UCLIBC GLIBC
include $(AXIS_TOP_DIR)/tools/build/rules/common.mak

PROG	= ax_event_stateless_declaration_example

PKGS = glib-2.0 axevent
CFLAGS += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags $(PKGS))
LDLIBS += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs $(PKGS))

CFLAGS   += -W \
	    -Wformat=2 \
	    -Wpointer-arith \
	    -Wbad-function-cast \
	    -Wstrict-prototypes \
	    -Wmissing-prototypes \
	    -Winline \
	    -Wdisabled-optimization \
	    -Wfloat-equal \
	    -Wall \
	    -Werror

all:	$(PROG)

clean:
	rm -f $(PROG) *.o core
