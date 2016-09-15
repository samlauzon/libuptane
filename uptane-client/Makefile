##
# Uptane Test Client
#
CC = gcc
CFLAGS = -Wall -Werror -I../libuptane/include/ -L../
LDFLAGS = 
LDLIBS = -luptane
OUT = uptaneclient

OBJS := $(patsubst %.c,%.o,$(wildcard *.c))

application: $(OBJS)
ifneq (,$(findstring cygwin,$(MAKE_HOST)))   ## Cygwin links .dll & ignores .so
	@echo "WARNING: Breaking the rules for a windows build on $(MAKE_HOST)"
	cp ../libuptane.so ../libuptane.dll
endif
	$(CC) $(CFLAGS) $(OBJS) -o $(OUT) $(LDLIBS)
	cp $(OUT) ../   
   
clean:
	rm $(OUT) $(OBJS) ../$(OUT)
ifneq (,$(findstring cygwin,$(MAKE_HOST)))   ## Cygwin links .dll & ignores .so
	@echo "WARNING: Breaking the rules for a windows clean on $(MAKE_HOST)"
	rm ../libuptane.dll
endif
   
all: $(application) 
