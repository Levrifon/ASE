# $Id: Makefile,v 1.2 2004/10/12 09:06:17 marquet Exp $
##############################################################################

ROOTDIR=/home/enseign/ASE

CC	= gcc
#CFLAGS	= -Wall -ansi -pedantic 
CFLAGS  = -g -m32
LIBDIR  = $(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -L$(LIBDIR) -lhardware

###------------------------------
### Main targets 
###------------------------------------------------------------
BINARIES= mkhd dmps frmt
OBJECTS	 = $(addsuffix .o,\
	   mkhd)
OBJECTS	+= $(addsuffix .o,\
	   dmps)
OBJECTS	+= $(addsuffix .o,\
	   frmt)
OBJECTS	+= $(addsuffix .o,\
	   drive)
OBJECTS	+= $(addsuffix .o,\
	   dump)
OBJECTS	+= $(addsuffix .o,\
	   mbr)

all: $(BINARIES) $(OBJECTS)


###------------------------------
### Main rules 
###------------------------------------------------------------
mkhd.o: mkhd.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

mkhd: mkhd.o drive.o 
	$(CC) $(CFLAGS) -o mkhd $^ $(LIBS)
	
dmps.o: dmps.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

dmps: dmps.o drive.o dump.o
	$(CC) $(CFLAGS) -o dmps $^ $(LIBS)
	
frmt.o: frmt.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

frmt: frmt.o drive.o dump.o
	$(CC) $(CFLAGS) -o frmt $^ $(LIBS)
	
drive.o:drive.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)
	
dump.o:dump.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)
	
mbr.o:mbr.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES)
realclean: clean 
	$(RM) vdiskA.bin vdiskB.bin
