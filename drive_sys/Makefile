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
BINARIES= mkhd dmps frmt mkvol dvol dfs mknfs
#OBJECTS	 = $(addsuffix .o,\
#	   mkhd dmps frmt drive dump mbr volume bloc mkvol dvol dfs)
OBJECTS	 = $(addsuffix .o,\
	   drive dump mbr volume bloc)

all: $(BINARIES) $(OBJECTS)


###------------------------------
### Main rules 
###------------------------------------------------------------
mkhd: mkhd.o drive.o 
	$(CC) $(CFLAGS) -o mkhd $^ $(LIBS)

dmps: dmps.o drive.o dump.o
	$(CC) $(CFLAGS) -o dmps $^ $(LIBS)

frmt: frmt.o drive.o dump.o
	$(CC) $(CFLAGS) -o frmt $^ $(LIBS)
	
mkvol: mkvol.o drive.o dump.o volume.o mbr.o
	$(CC) $(CFLAGS) -o mkvol $^ $(LIBS)
	
dfs: dfs.o bloc.o drive.o dump.o volume.o mbr.o
	$(CC) $(CFLAGS) -o dfs $^ $(LIBS)
	
mknfs: mknfs.o bloc.o drive.o dump.o volume.o mbr.o
	$(CC) $(CFLAGS) -o mknfs $^ $(LIBS)

dvol: dvol.o drive.o dump.o volume.o mbr.o
	$(CC) $(CFLAGS) -o dvol $^ $(LIBS)
	
dvol.o: dvol.c
mkhd.o: mkhd.c
dmps.o: dmps.c
frmt.o: frmt.c
mkvol.o: mkvol.c
dfs.o: dfs.c
mknfs.o: dfs.c
drive.o:drive.c
dump.o:dump.c
mbr.o:mbr.c
bloc.o:bloc.c
current.o:current.c
volume.o:volume.c

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INCDIR)

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES)
realclean: clean 
	$(RM) vdiskA.bin vdiskB.bin
