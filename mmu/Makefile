# $Id: Makefile,v 1.1 2002/12/06 14:25:18 marquet Exp $
##############################################################################

ROOTDIR=..

CC	= gcc
#CFLAGS	= -Wall -ansi -pedantic 
CFLAGS  += -g -m32
LIBDIR  = -L$(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -lhardware

###------------------------------
### Main targets 
###------------------------------------------------------------
BINARIES= mi_kernel
OBJECTS	= $(addsuffix .o,\
	   mi_user)

all: $(BINARIES) $(OBJECTS)

###------------------------------
### Binaries
###------------------------------------------------------------

mi_kernel: mi_user.o mi_kernel.o swap.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIBS)



###------------------------------
### #include dependences 
###------------------------------------------------------------
# you may fill these lines with "make depend"
mi_user.o: mi_user.c mi_kernel.c mi_syscall.h
mi_kernel.o: mi_kernel.c mi_user.c mi_syscall.h
swap.o: swap.h
%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INCDIR)

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES) *~
realclean: clean 
	$(RM) vdiskA.bin vdiskB.bin
depend : 
	$(CC) -MM $(INCDIR) *.c
