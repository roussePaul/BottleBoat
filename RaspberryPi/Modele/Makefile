CC=gcc
CFLAGS=-c -Wall -Imatlab_include/ -Irtw_include/ -Isimulink_include/ -Irtw_include/ext_mode/common/ -I.
LDFLAGS= -lm
SOURCES=$(shell echo *.c) rtw_include/rt_logging.c rtw_include/rt_sim.c
OBJECTS=$(SOURCES:.c=.o)
DEFINES=-DMODEL=BoatModele -DNUMST=2 -DNCSTATES=11 -DHAVESTDIO -DRT -DUSE_RTMODEL -DMAT_FILE=1 -DINTEGER_CODE=0 -DMT=0 -DCLASSIC_INTERFACE=0 -DONESTEPFCN=1 -DTERMFCN=1 -DMULTI_INSTANCE_CODE=0


all: $(OBJECTS)
	

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(DEFINES) $< -o $@
	
clean:
	rm -f $(OBJECTS)
	rm -f gmon.out