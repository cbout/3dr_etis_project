DEBUG=no
CC=gcc
CFLAGS = -std=c99 -Wall

ifeq ($(DEBUG),yes)
	CFLAGS+= -g -I ../include/mavlink/ardupilotmega
else
	CFLAGS+= -I ../include/mavlink/ardupilotmega
endif

CFLAGS+= `pkg-config --cflags gstreamer-1.0`

LDFLAGS=-lpthread `pkg-config --libs gstreamer-1.0`

EXEC=mavlink_udp
SRC= $(wildcard *.c)
LIB= $(wildcard *.h)
OBJ= $(SRC:.c=.o)

all : git_submodule $(EXEC)
ifeq ($(DEBUG),yes)
	@echo "Génération en mode debug"
endif

$(EXEC) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

git_submodule:
	git submodule update --init --recursive

.PHONY: clean

clean :
	rm -f  $(EXEC) $(OBJ)