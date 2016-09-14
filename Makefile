##
# Batchy
#

UPTANE_CLIENT = ./uptane-client
LIBUPTANE = ./libuptane

all:
	cd $(LIBUPTANE) && make
	cd $(UPTANE_CLIENT) && make
   
clean: 
	cd $(LIBUPTANE) && make clean
	cd $(UPTANE_CLIENT) && make clean
   
