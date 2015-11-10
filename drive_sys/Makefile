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
BINARIES= mkhd dmps frmt create_vol print_vol
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
OBJECTS	+= $(addsuffix .o,\
	   volume)
OBJECTS	+= $(addsuffix .o,\
	   bloc)
OBJECTS	+= $(addsuffix .o,\
	   create_vol)
OBJECTS	+= $(addsuffix .o,\
	   print_vol)

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
	
create_vol.o: create_vol.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

create_vol: create_vol.o drive.o dump.o volume.o mbr.o
	$(CC) $(CFLAGS) -o frmt $^ $(LIBS)
	
print_vol.o: print_vol.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

print_vol: print_vol.o drive.o dump.o volume.o mbr.o
	$(CC) $(CFLAGS) -o frmt $^ $(LIBS)
	
drive.o:drive.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)
	
dump.o:dump.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)
	
mbr.o:mbr.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)
	
bloc.o:bloc.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)
	
current.o:current.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)
	
volume.o:volume.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES)
realclean: clean 
	$(RM) vdiskA.bin vdiskB.bin
