#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define PIPE1 "/tmp/pipe1"
#define PIPE2 "/tmp/pipe2"
int main() {
int fd1, fd2;
char input[1000], output[1000];
mkfifo(PIPE1, 0666);
mkfifo(PIPE2, 0666);
printf("Enter a sentence (type 'exit' to quit): ");
fgets(input, sizeof(input), stdin);
if (strncmp(input, "exit", 4) == 0) {
return 0; }
fd1 = open(PIPE1, O_WRONLY);
write(fd1, input, strlen(input) + 1);
close(fd1);
fd2 = open(PIPE2, O_RDONLY);
read(fd2, output, sizeof(output));
close(fd2);
printf("Output from second process:\n%s\n", output);
unlink(PIPE1);
unlink(PIPE2);
return 0;}
