DEBUG=yes
CC=gcc
ifeq ($(DEBUG),yes)
	CFLAGS=-std=c99 -Wall -g -I include/ardupilotmega
	LDFLAGS=-lpthread
else
	CFLAGS=-std=c99 -Wall -I include/ardupilotmega
	LDFLAGS=-lpthread
endif
EXEC=mavlink_udp
SRC= $(wildcard *.c)
LIB= $(wildcard *.h)
OBJ= $(SRC:.c=.o)

all : $(EXEC)
ifeq ($(DEBUG),yes)
	@echo "Génération en mode debug"
else
	@echo "Génération en mode release"
endif

%.o:%.c  $(LIB)
	$(CC) $(CFLAGS) -c $<

$(EXEC) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean :
	rm -f  mavlink_udp *.o
