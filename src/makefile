CC=gcc
CFLAGS=-std=c99 -Wall -I include/common
LDFLAGS=-lpthread
EXEC=mavlink_udp
SRC= $(wildcard *.c)
LIB= $(wildcard *.h)
OBJ= $(SRC:.c=.o)

all : $(EXEC)

%.o:%.c  $(LIB)
	$(CC) $(CFLAGS) -c $<

$(EXEC) : $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean :
	rm -f  mavlink_udp *.o
