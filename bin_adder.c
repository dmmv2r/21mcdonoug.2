#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//shared memory struct
typedef struct {
   int id;
   int turn;
   int children;
   int flags[20];
   pid_t ppid;
}sharedMem;

sharedMem *ptr;

//frees shared memory when done
void freeMem(struct sharedMem *ptr, int shmid);

//handles ctrl-c
void handler(struct sharedMem *ptr, int signal, int shmid);


int main(int argc, char* argv[]) {
   
   printf("IN BIN_ADDER\n");

   printf("LEAVING BIN_ADDER\n");

   return 0;
}

void handler(struct sharedMem *ptr, int signal, int shmid) {
   freeMem(ptr, shmid);
   exit(1);
}

void freeMem(struct sharedMem *ptr, int shmid) {
   if(shmctl(shmid, IPC_RMID, NULL) == -1) {
      perror("Error in memory: fault detach");
   } else if(shmdt(ptr) == -1) {
      perror("Error in memory: fault delete");
   }
}
