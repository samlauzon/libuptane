##
# Uptane data decoder
#
CC = gcc
CFLAGS = -Wall -I. -L../ -I./codec/
LDFLAGS = 
LDLIBS = 
OUT = uptanedecoder

OBJS := $(patsubst %.c,%.o,$(wildcard *.c))
OBJS += $(patsubst codec/%.c,codec/%.o,$(wildcard codec/*.c))

application: $(OBJS)
#ifneq (,$(findstring cygwin,$(MAKE_HOST)))   ## Cygwin links .dll & ignores .so
#	@echo "WARNING: Breaking the rules for a windows build on $(MAKE_HOST)"
#	cp ../libuptane.so ../libuptane.dll
#endif
	$(CC) $(CFLAGS) $(OBJS) -o $(OUT) $(LDLIBS)
	cp $(OUT) ../   
   
clean:
	-rm -f $(OUT) $(OBJS) ../$(OUT)
#ifneq (,$(findstring cygwin,$(MAKE_HOST)))   ## Cygwin links .dll & ignores .so
#	@echo "WARNING: Breaking the rules for a windows clean on $(MAKE_HOST)"
#	rm ../libuptane.dll
#endif
   
all: $(application) 
