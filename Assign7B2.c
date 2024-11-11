#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#define SHM_KEY 12345
#define SHM_SIZE 1024
int main() {
int shmid;
char *shmaddr;
shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
if (shmid < 0) {
perror("shmget");
exit(1);
}
shmaddr = shmat(shmid, NULL, 0);
if (shmaddr == (char *) -1) {
perror("shmat");
exit(1);
}
printf("Writing to shared memory...\n");
char *message = "Hello from DVVPCOE,Ahmednagar Server!";
strncpy(shmaddr, message, SHM_SIZE);
if (shmdt(shmaddr) == -1) {
perror("shmdt");
exit(1);
}
printf("Message written to shared memory: %s\n", message);
return 0; }
