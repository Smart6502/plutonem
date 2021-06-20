CC = gcc
CPPC = g++
LIBSRCDIR = src/
INSTDIR = /usr/lib/
EXDIR := examples/
LIBSRCS := $(shell find $(LIBSRCDIR) -name '*.c')
EXSRCS := $(shell find $(EXDIR) -name '*.c' -o -name '*.cpp')
LIBOBJS := $(addsuffix .o, $(basename $(LIBSRCS)))
LIBA := libpluto.a
EXBINS := $(addsuffix .e, $(basename $(EXSRCS)))
CFLAGS = -Wall -Wextra -Werror -O3
LIBCFLAGS = $(CFLAGS)

.PHONY: clean

all: $(LIBA)
exp: $(EXBINS)

%.math.e: %.math.c $(LIBA)
	@echo "Compiling example [m] $<"
	@$(CC) -o $@ $< $(CFLAGS) -L. -lm -lpluto

%.e: %.c $(LIBA)
	@echo "Compiling example $<"
	@$(CC) -o $@ $< $(CFLAGS) -L. -lpluto

%.e: %.cpp $(LIBA)
	@echo "Compiling example $<"
	@$(CPPC) -o $@ $< $(CFLAGS) -L. -lpluto -lX11 -std=c++11

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
	@cp $(LIBA) $(INSTDIR)
	@cp $(LIBSRCDIR)pluto.h /usr/include/
	@echo "Copied header to /usr/include/ and libpluto.a to $(INSTDIR)"
