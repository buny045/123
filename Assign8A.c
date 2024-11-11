#include <stdio.h>
#include <stdlib.h>
int main() {
int n, i, j, head, total_movement = 0;
printf("Enter the number of requests: ");
scanf("%d", &n);
int requests[n], completed[n];
printf("Enter the request sequence: ");
for (i = 0; i < n; i++) {
scanf("%d", &requests[i]);
completed[i] = 0; 
}
printf("Enter the initial head position: ");
scanf("%d", &head);
for (i = 0; i < n; i++) {
int min = 100000, min_index = -1;
for (j = 0; j < n; j++) {
if (!completed[j] && abs(head - requests[j]) < min) {
min = abs(head - requests[j]);
min_index = j;}
}
completed[min_index] = 1; 
total_movement += abs(head - requests[min_index]);
head = requests[min_index];
printf("Serviced request: %d\n", head);
}
printf("Total head movement: %d\n", total_movement);
return 0;
}
