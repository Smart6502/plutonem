CC = gcc
LIBSRCDIR = src/
EXDIR := examples/
LIBSRCS := $(shell find $(LIBSRCDIR) -name '*.c')
EXSRCS := $(shell find $(EXDIR) -name '*.c')
LIBOBJS := $(addsuffix .o,$(basename $(LIBSRCS)))
EXBINS := $(basename $(EXSRCS))
CFLAGS = -Wall -Wextra -Werror 
LIBCFLAGS = $(CFLAGS) -D SPACE_CLEAR -D EXTRAS -D PLUTO_PIX_CHAR_OFF=0x2800

all: $(LIBOBJS) $(EXBINS)

%: %.c
	@echo "Compiling example $<"
	@$(CC) $(CFLAGS) $(LIBOBJS) $< -o $@

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(LIBCFLAGS) -c $< -o $@

clean:
	@$(RM) $(LIBOBJS) $(EXBINS)