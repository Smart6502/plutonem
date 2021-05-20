CC = gcc
LIBSRCDIR = src/
EXDIR := examples/
LIBSRCS := $(shell find $(LIBSRCDIR) -name '*.c')
EXSRCS := $(shell find $(EXDIR) -name '*.c')
LIBOBJS := $(addsuffix .o,$(basename $(LIBSRCS)))
LIBA := libpluto.a
EXBINS := $(basename $(EXSRCS))
CFLAGS = -Wall -Wextra -Werror -O2
LIBCFLAGS = $(CFLAGS) -D PLUTO_PIX_CHAR_OFF=0x2800

.PHONY: clean

all: $(LIBA)
exp: $(EXBINS)

%: %.c $(LIBA)
	@echo "Compiling example $<"
	@$(CC) -o $@ $< $(CFLAGS) -L. -lpluto

%.o: %.c
	@echo "Compiling object $<"
	@$(CC) $(LIBCFLAGS) -c $< -o $@

%.a: $(LIBOBJS)
	@echo "Generating $(LIBA)"
	@ar rcs $@ $(LIBOBJS)

eclean:
	@$(RM) $(EXBINS)

lclean:
	@$(RM) $(LIBOBJS) $(LIBA)

clean: eclean lclean

install: $(LIBA)
	@cp $(LIBA) /usr/lib/
	@cp $(LIBSRCDIR)/inc/pluto.h /usr/include/
	@echo "Copied header to /usr/include/ and libpluto.a to /usr/lib/"
