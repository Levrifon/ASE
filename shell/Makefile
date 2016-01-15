CC	=  gcc
CFLAGS  += -g


shell : shell.o


%.o: %.c
	$(CC) $(CFLAGS) -c $< 
% : %.o
	$(CC) -o $@ $^ 
