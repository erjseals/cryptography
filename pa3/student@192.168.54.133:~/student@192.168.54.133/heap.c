#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 128

int main(int argc, char *argv[])
{
   char *a, *b, *c;

   if(argc < 2) {
      printf("Usage: %s <buffer>\n", argv[0]);
      exit(-1);
   }

   a = (char *) malloc(BUFSIZE);
   b = (char *) malloc(BUFSIZE+16);
   c = (char *) malloc(BUFSIZE+32);

   printf("address of a: %p\n", a);
   printf("address of b: %p\n", b);
   printf("address of c: %p\n", c);

   strcpy(b, "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB");
   strcpy(c, "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");
   strcpy(a, argv[1]);

   free(a);
   free(b);
   free(c);
}
