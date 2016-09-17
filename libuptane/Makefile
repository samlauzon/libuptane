######
# Uptane C Library 
#  Part of the Uptane Framework
#   Copyright 2016 (c) Sam Lauzon, 
#    The Regents of the University of Michigan
#
#  See COPYING for license details
############
# Add any wrappers below;
#  WRAPPER_OBJS should be object/source files
#  WRAPPER_LIBRARIES should be any external linkages 
#  
#### Wrappers
#
# web-curl
#

WRAPPER_OBJS += $(patsubst interfaces/web-curl/%.c,interfaces/web-curl/%.o,$(wildcard interfaces/web-curl/*.c))  
WRAPPER_CFLAGS += -Iinterfaces/web-curl 
WRAPPER_LIBRARIES += -lcurl

#
# web-static 
#

# WRAPPER_OBJS += $(pathsubst interfaces/web-static/%.c,interfaces/web-static/%.o,interfaes/web-static/*.c) 

########
# Core Build things 
########

CC = gcc
CFLAGS = -c -Wall -fpic -I./include $(WRAPPER_CFLAGS)
LDFLAGS = -shared 
OUTPUT = libuptane.so 

OBJS := $(patsubst src/%.c,src/%.o,$(wildcard src/*.c)) $(WRAPPER_OBJS)

libuptane: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)
	$(CC) $(LDFLAGS) -o $(OUTPUT) $(OBJS) $(WRAPPER_LIBRARIES)
	cp $(OUTPUT) ../   

clean: 
	rm $(OUTPUT) $(OBJS) ../$(OUTPUT)
   
all: $(libuptane) 
   
