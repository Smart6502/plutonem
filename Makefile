TARGET = example
CC = gcc
SRCDIR = src
SRCS := $(shell find $(SRCDIR) -name '*.c')
OBJS := $(addsuffix .o,$(basename $(SRCS)))
CFLAGS = -Wall -Wextra -Werror -D SPACE_CLEAR -D PLUTO_PIX_CHAR_OFF=0x2800

all: $(TARGET)

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	@$(CC) $(OBJS) -o $@

clean:
	@$(RM) $(OBJS) $(TARGET)