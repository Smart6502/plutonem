CC = gcc
LIBSRCDIR = src/
EXDIR := examples/
LIBSRCS := $(shell find $(LIBSRCDIR) -name '*.c')
EXSRCS := $(shell find $(EXDIR) -name '*.c')
LIBOBJS := $(addsuffix .o,$(basename $(LIBSRCS)))
LIBA := libpluto.a
EXBINS := $(basename $(EXSRCS))
CFLAGS = -Wall -Wextra -Werror 
LIBCFLAGS = $(CFLAGS) -D PLUTO_EXTRAS -D PLUTO_PIX_CHAR_OFF=0x2800

all: $(LIBA)
test: $(EXBINS)

%: %.c $(LIBA)
	@echo "Compiling example $<"
	@$(CC) -o $@ $< $(CFLAGS) -L. -lpluto

%.o: %.c
	@echo "Compiling object $<"
	@$(CC) $(LIBCFLAGS) -c $< -o $@

%.a: $(LIBOBJS)
	@echo "Generating $(LIBA)"
	@ar rcs $@ $(LIBOBJS)

clean:
	@$(RM) $(LIBOBJS) $(LIBA) $(EXBINS)
