##
# Uptane C Library 
#

CC = gcc
CFLAGS = -c -Wall -fpic
LDFLAGS = -shared -lcurl
OUTPUT = libuptane.so 

OBJS := $(patsubst %.c,%.o,$(wildcard *.c))

libuptane: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)
	$(CC) $(LDFLAGS) -o $(OUTPUT) $(OBJS) 
	cp $(OUTPUT) ../   

clean: 
	rm $(OUTPUT) $(OBJS) ../$(OUTPUT)
   
all: $(libuptane) 
   
