CC=gcc
CFLAGS=-c -g -Wall -I/usr/include/ -IModele/matlab_include/ -IModele/simulink_include/ -IModele/rtw_include/ -IModele/rtw_include/ext_mode/common/ -IModele/
LDFLAGS= -L/usr/lib/ -lm -L/Modele
SOURCES=$(shell echo *.c)
OBJECTS=$(SOURCES:.c=.o)
MODELE_DIR=Modele/
MODELE_OBJ=$(shell echo Modele/*.o)
EXECUTABLE=prog

all: $(SOURCES) modele $(EXECUTABLE)
	
	
modele:
	@(cd $(MODELE_DIR) && $(MAKE))
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(MODELE_OBJ) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	@(cd $(MODELE_DIR) && $(MAKE) clean)
	rm -f $(OBJECTS)
	rm -f gmon.out