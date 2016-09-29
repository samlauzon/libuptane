########################
# Uptane C Library 
#  Part of the Uptane Framework
#   Copyright 2016 (c) Sam Lauzon, 
#    The Regents of the University of Michigan
#
#  See COPYING for license details
########################
# Add Interfaces below;
#  INTERFACE_OBJS should be source files (patsubst %.c, %.o, wildcard *.c)
#  INTERFACE_LIBRARIES should be any external linkages 
########################  
# Web interfaces
########################

########################
# web-curl
########################
INTERFACE_OBJS += $(patsubst interfaces/web-curl/%.c,interfaces/web-curl/%.o,$(wildcard interfaces/web-curl/*.c))  
INTERFACE_CFLAGS += -Iinterfaces/web-curl 
INTERFACE_LIBRARIES += -lcurl

########################
# web-static 
########################
#INTERFACE_OBJS += $(patsubst interfaces/web-static/%.c,interfaces/web-static/%.o,$(wildcard interfaces/web-static/*.c)) 
#INTERFACE_CFLAGS += -Iinterfaces/web-static 
#INTERFACE_LIBRARIES += 


########################
# crypto-ed25519 
########################
INTERFACE_OBJS += $(patsubst interfaces/crypto-ed25519/%.c,interfaces/crypto-ed25519/%.o,$(wildcard interfaces/crypto-ed25519/*.c)) 
INTERFACE_OBJS += $(patsubst interfaces/crypto-ed25519/libed25519/%.c,interfaces/crypto-ed25519/libed25519/%.o,$(wildcard interfaces/crypto-ed25519/libed25519/*.c)) 
INTERFACE_CFLAGS += -Iinterfaces/crypto-ed25519 -Iinterfaces/crypto-ed25519/libed25519
INTERFACE_LIBRARIES += 

########################
# Core Build
########################
# Definitions
CC = gcc
CFLAGS = -Wall -fpic -I./include -Iinterfaces/include $(INTERFACE_CFLAGS)
LDFLAGS = -shared 
OUTPUT = libuptane.so 
# Core library source + Interfaces
OBJS := $(patsubst src/%.c,src/%.o,$(wildcard src/*.c)) $(INTERFACE_OBJS)

# Library Build Rule
%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

libuptane: $(OBJS)
	$(CC) $(LDFLAGS) -o $(OUTPUT) $(OBJS) $(INTERFACE_LIBRARIES)
	cp $(OUTPUT) ../  


# Clean Rule
clean: 
	rm -f $(OUTPUT) $(OBJS) ../$(OUTPUT)

# Default: Build library 
all: $(libuptane) 

# Useless 
.PHONY: version_bump
version_bump:
	awk -i inplace -v '/VERSION_BUILD/{gsub(/([0-9]+)/, ($$3 + 1) )}; 1' include/libuptane.h
# end
