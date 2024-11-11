#include <stdio.h>
void printFrames(int frames[], int frameSize) {
for (int i = 0; i < frameSize; i++) {
if (frames[i] == -1) {
printf(" - ");
} else {
printf(" %d ", frames[i]);
}
}
printf("\n");
}
void lru(int refString[], int refSize, int frameSize) {
int frames[frameSize];
int time[frameSize];
for (int i = 0; i < frameSize; i++) frames[i] = -1;
int pageFaults = 0;
printf("\nLRU Page Replacement:\n");
for (int i = 0; i < refSize; i++) {int found = 0, leastRecentlyUsed = 0;
for (int j = 0; j < frameSize; j++) {
if (frames[j] == refString[i]) {
found = 1;
time[j] = i;
break;
}
if (time[j] < time[leastRecentlyUsed]) {
leastRecentlyUsed = j;
}
}
if (!found) {
frames[leastRecentlyUsed] = refString[i];
time[leastRecentlyUsed] = i;
pageFaults++;
}
printFrames(frames, frameSize);
}
printf("Total Page Faults: %d\n", pageFaults);
}
int main() {
int refSize, frameSize;
printf("Enter the number of pages in the reference string: ");
scanf("%d", &refSize);
int refString[refSize];
printf("Enter the reference string:\n");
for (int i = 0; i < refSize; i++) {
scanf("%d", &refString[i]);
}
printf("Enter the number of frames (minimum 3): ");
scanf("%d", &frameSize);
if (frameSize < 3) {
printf("Frame size should be at least 3.\n");
return 1;
}
lru(refString, refSize, frameSize);
return 0;
}
