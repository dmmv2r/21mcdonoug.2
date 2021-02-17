//master

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <signal.h>

int shmid;

int main(int argc, char* argv[]) {

   printf("IN MASTER\n");

   int opt;
   int maxC;
   int tTime;
   char* input;

   maxC = 20;
   tTime = 100;
   input = argv[argc - 1];

   int key = ftok("master", 0);

   while((opt = getopt(argc, argv, "hs:t:")) != -1) {
      switch(opt) {
         case 'h':
            printf("%s: Usage ...\n", argv[0]);
            return -1;
         case's':
            maxC = atoi(optarg);
            break;
         case 't':
            tTime = atoi(optarg);
            break;
         default:
            printf("usage\n");
            return -1;
      }

   }

   printf("max = %i\n", maxC);
   printf("time = %i\n", tTime);
   printf("input file = %s\n", input);

   printf("Out of getopt\n");




   printf("exiting master\n");
   return 0;
}
