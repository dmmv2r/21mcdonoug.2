#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/time.h>
#include <signal.h>

//struct used for shared memory
typedef struct {
   int id;
   int turn;
   int children;
   int flags[20];
   int ints[20][20];
   pid_t ppid;
}sharedMem;

sharedMem *ptr;

//forking process
void createChild(int index);

//free shared memory
void freeMem(struct sharedMem *ptr, int shmid);

//ctrl-c handler
void handler(int signal, int shmid);

void timer(int signal, int shmid);

int shmid;
int counter = 0;
int index;

int main(int argc, char* argv[]) {

   printf("IN MASTER\n");

   int opt;
   int maxC; //number of lines to read
   int tTime; //max time alotted
   char* input; //input file

   maxC = 20;
   tTime = 100;
   input = argv[argc - 1];

   int key = ftok("master", 0); //creates shared memory key

   while((opt = getopt(argc, argv, "hs:t:")) != -1) {
      switch(opt) {
         case 'h':
            printf("Usage: ./master -h -s x -t time datafile\n");
            printf("x = number of children allowed at once (optional)\n");
            printf("time = max program time (optional)\n");
            printf("datafile = name of input file to read from (required)\n");
            return -1;
         case's':
            maxC = atoi(optarg);
            break;
         case 't':
            tTime = atoi(optarg);
            break;
         default:
            printf("Arguments required\n");
            return -1;
      }
   }

   printf("max = %i\n", maxC);
   printf("time = %i\n", tTime);
   printf("input file = %s\n", input);

   
   shmid = shmget(key, sizeof(sharedMem), 0600 | IPC_CREAT | IPC_EXCL); //sets id of shared memory
   if(shmid == -1) {
      freeMem(ptr, shmid);
      perror("Failure in shmid");
      return -1;
   }

   ptr = (sharedMem*) shmat(shmid, NULL, 0); //attaches shared memory

   if(ptr == (void*)-1) {
      freeMem(ptr, shmid);
      perror("Failure in shared memory");
      return -1;
   }

   /*FILE *file = fopen(input, "r");
   if(file == NULL) {
      perror("Error in opening file");
      exit(1);
   }

   while(fgets(ptr->ints[i], 40, file)) {
      ptr-
      i++;
   }
   fclose(file);
   */

   pid_t pid;
   pid = fork();
   if(pid == 0) {
      ptr->ppid = getpid();
   }

   execl("./bin_adder", "bin_adder", number, (char*) NULL);
   exit(1);



   printf("exiting master\n");
   return 0;
}

void timer(struct sharedMem *ptr, int signal, int shmid) {
   killpg(ptr->ppid, SIGUSR1);
   do[]while(wait(NULL) > 0);
   freeMem(ptr, shmid);
   exit(1);
}

void handler(struct sharedMem *ptr, int signal, int shmid) {
   killpg(ptr->ppid, SIGTERM); //kills process

   do{}while(wait(NULL) > 0);

   freeMem(ptr, shmid);
}

void freeMem(struct sharedMem *ptr, int shmid) {
   if(shmctl(shmid, IPC_RMID, NULL) == -1) {
      perror("Error in memory: fault detach");
   } else if(shmdt(ptr) == -1) {
      perror("Error in memory: fault delete");
   }
}

