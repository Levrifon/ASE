#include <stdio.h>
#include <ctype.h>

/* dump buffer to stdout,
   and octal dump if octal_dump; an ascii dump if ascii_dump! */
void dump(unsigned char *buffer,
     unsigned int buffer_size,
     int ascii_dump,
     int octal_dump);
