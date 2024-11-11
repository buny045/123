#include <stdlib.h>
#include <stdio.h>

struct process {
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turn_around_time;
    int remain_time;
};

int main() {
    int n, i, j;
    printf("Enter Number of processes: ");
    scanf("%d", &n);

    struct process proc[n], temp;

    for (i = 0; i < n; i++) {
        printf("Enter Arrival time for process %d: ", i + 1);
        scanf("%d", &proc[i].arrival_time);
        printf("Enter Burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        proc[i].remain_time = proc[i].burst_time;
        proc[i].process_id = i + 1;
    }

    int quantum_time;
    printf("Enter Time Quantum: ");
    scanf("%d", &quantum_time);

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (proc[i].arrival_time > proc[j].arrival_time) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    int processes_remaining = n;
    int totalExecutionTime = 0, wait_time_total = 0, turn_around_time_total = 0;

    i = 0;
    while (processes_remaining > 0) {
        if (proc[i].remain_time > 0) {
            if (proc[i].remain_time <= quantum_time) {
                totalExecutionTime += proc[i].remain_time;
                proc[i].remain_time = 0;
                proc[i].waiting_time = totalExecutionTime - proc[i].arrival_time - proc[i].burst_time;
                proc[i].turn_around_time = proc[i].waiting_time + proc[i].burst_time;
                wait_time_total += proc[i].waiting_time;
                turn_around_time_total += proc[i].turn_around_time;
                processes_remaining--;
            } else {
                proc[i].remain_time -= quantum_time;
                totalExecutionTime += quantum_time;
            }
        }

  
        i = (i + 1) % n;
        while (proc[i].remain_time <= 0 && processes_remaining > 0) {
            i = (i + 1) % n;
        }
    }

    printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurn Around Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].process_id, proc[i].burst_time, proc[i].arrival_time, proc[i].waiting_time, proc[i].turn_around_time);
    }

    printf("Average Waiting Time: %f\n", (float)wait_time_total / n);
    printf("Average Turn Around Time: %f\n", (float)turn_around_time_total / n);

    return 0;
}

