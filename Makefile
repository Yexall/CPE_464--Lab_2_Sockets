# Makefile for CPE464 tcp test code
# written by Hugh Smith - April 2019

LIBS = 
OBJS = networks.o gethostbyname.o pollLib.o safeUtil.o PDU.o
CFLAGS = -g -Wall -Wextra -pedantic -std=gnu99 

all:   client server

client: client.c $(OBJS)
	gcc $(CFLAGS) client.c -o client  $(OBJS) $(LIBS)

server: server.c $(OBJS)
	gcc $(CFLAGS) server.c -o server $(OBJS) $(LIBS)

.c.o:
	gcc -c $(CFLAGS) $< -o $@ $(LIBS)

cleano:
	rm -f *.o

clean:
	rm -f client server PDU *.o




