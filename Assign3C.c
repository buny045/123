#include "stdlib.h"
#include "stdio.h"
struct process
{
int process_id;
int arrival_time;
int burst_time;
int waiting_time;
int turn_around_time;
int remain_time;
};
int main(){
int n,j,i;
int bt=0,k=1,tat=0,sum=0,min;
printf("Enter NUMBER OF PROCESSES: ");
scanf("%d",&n);
struct process proc[n],temp;
for(i=0;i<n;i++)
{
printf("\n");
printf("Enter Arrival time for process%d: ",i+1);
scanf("%d",&proc[i].arrival_time);
printf("Enter Burst time for process%d: ",i+1);
scanf("%d",&proc[i].burst_time);
proc[i].remain_time=proc[i].burst_time;
proc[i].process_id=i+1;
}
for(i=0;i<n;i++)
{
for(j=0;j<n;j++)
{
if(proc[i].arrival_time<proc[j].arrival_time)
{
temp=proc[j];
proc[j]=proc[i];
proc[i]=temp;
}
}
}
for(i=0;i<n;i++){
bt+=proc[i].burst_time;
min=proc[k].burst_time;
for(j=k;j<n;j++)
{
if(bt>=proc[j].arrival_time&&proc[j].burst_time<min){
temp=proc[k];
proc[k]=proc[j];
proc[j]=temp;
}
}
k++;
}
proc[0].waiting_time=0;
int wait_time_total=0;
int turn_around_time_total=0;
for(i=1;i<n;i++)
{
sum+=proc[i-1].burst_time;
proc[i].waiting_time=sum-proc[i].arrival_time;
turn_around_time_total+=proc[i].turn_around_time;
}
printf("Process\tBurst Time\tWaiting Time\tTurn Around Time\n");
for(i=0;i<n;i++)
{
printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",proc[i].process_id,proc[i].burst_time,proc[i].arrival_time,proc[i].waiting_time,proc[i].turn_around_time);
}
printf("Average WAiting time: %f\n",(float)wait_time_total/n);
printf("Average Turn Around Time :%f\n",(float)turn_around_time_total/n);
}
