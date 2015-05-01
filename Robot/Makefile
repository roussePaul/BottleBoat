CC=gcc
CFLAGS=-c -g -Wall -I/usr/include/ -IModele/matlab_include/ -IModele/rtw_include/ -IModele/simulink_include/ -IModele/rtw_include/ext_mode/common/ -IModele/
LDFLAGS= -L/usr/lib/ -lgsl -lgslcblas -lm -L/Modele
SOURCES=$(shell echo *.c)
OBJECTS=$(SOURCES:.c=.o)
MODELE_DIR=Modele/
MODELE_OBJ=$(shell echo Modele/*.o) $(shell echo Modele/rtw_include/*.o)
WEBPLOT_DIR=webPlot/
WEBPLOT_OBJ=$(shell echo webPlot/*.o)
EXECUTABLE=prog


all: $(SOURCES) modele webplot $(EXECUTABLE)
	
	
modele:
	@(cd $(MODELE_DIR) && $(MAKE))
	
webplot:
	@(cd $(WEBPLOT_DIR) && $(MAKE))
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) $(MODELE_OBJ) $(WEBPLOT_OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -f $(OBJECTS)
	rm -f gmon.out