DEBUG=no
CC=gcc

ifeq ($(DEBUG),yes)
	CFLAGS=-std=c99 -Wall -g -I ../include/ardupilotmega
else
	CFLAGS=-std=c99 -Wall -I ../include/ardupilotmega
endif

CFLAGS+= `pkg-config --cflags gstreamer-1.0`
LDFLAGS=-lpthread `pkg-config --libs gstreamer-1.0`

EXEC=mavlink_udp
SRC= $(wildcard *.c)
LIB= $(wildcard *.h)
OBJ= $(SRC:.c=.o)

all : $(EXEC)
ifeq ($(DEBUG),yes)
	@echo "Génération en mode debug"
endif

$(EXEC) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean :
	rm -f  $(EXEC) $(OBJ)
