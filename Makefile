VERCMD  ?= git describe --tags 2> /dev/null
VERSION := $(shell $(VERCMD) || cat VERSION)
NAME := xled

CPPFLAGS += -D_POSIX_C_SOURCE=200809L -DVERSION=\"$(VERSION)\"
CFLAGS   += -std=c11 --optimize=3 -pedantic -Wall -Wextra -I/usr/include/X11
LDLIBS   := -lX11

PREFIX    ?= /usr/local
BINPREFIX ?= $(PREFIX)/bin

SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
DEF := $(wildcard *.h)

all: $(NAME)

install: $(NAME)
	mkdir -p "$(DESTDIR)$(BINPREFIX)"
	cp -p $(NAME) "$(DESTDIR)$(BINPREFIX)"

uninstall:
	rm -f "$(DESTDIR)$(BINPREFIX)/$(NAME)"

debug: build
debug: CFLAGS += -O0 -g
debug:
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDLIBS)

$(NAME): build
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDLIBS)

build:
	$(CC) -c $(shell printf "%s\n" $(strip $1) | tac)$(SRC)

clean:
	rm -f $(OBJ) $(NAME)

format:
	clang-format -i $(SRC) $(DEF)

ubuntu:
	sudo apt-get update
	sudo apt-get install libxi-dev
	sudo apt-get install libx11-dev

.PHONY: clean format build install uninstall debug all
