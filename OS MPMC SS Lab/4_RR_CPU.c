#include <stdio.h>
struct Process {
int id, burst_time, arrival_time, remaining_time, completion_time, waiting_time, turnaround_time;
};
void main()
{
    int n, quantum;
    float ttat=0, twt=0;
    struct Process p[10];
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Burst Time and Arrival Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].burst_time, &p[i].arrival_time);
        p[i].remaining_time = p[i].burst_time;
    }
    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);
    int time = 0, completed = 0, i;
    while (completed < n) {
    int flag = 0;
    for (i = 0; i < n; i++) {
        if (p[i].remaining_time > 0 && p[i].arrival_time <= time) {
            flag = 1;
            if (p[i].remaining_time > quantum) {
                time += quantum;
                p[i].remaining_time -= quantum;
            } else {
                time += p[i].remaining_time;
                p[i].completion_time = time;
                p[i].remaining_time = 0;
                p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
                p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
                completed++;
            }
        }
    }
    if (!flag) {
      time++;
    }
    }
    printf("Process ID\tBurst Time\tArrival Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].burst_time, p[i].arrival_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
        ttat=ttat+p[i].turnaround_time;
        twt=twt+p[i].waiting_time;
    }
    printf("Average Turnaround time = %f\n",ttat/n);
    printf("Average Waiting time = %f\n",twt/n);
}


/*
OUTPUT

Enter the number of processes: 4
Enter Burst Time and Arrival Time for Process 1: 5 2
Enter Burst Time and Arrival Time for Process 2: 8 3
Enter Burst Time and Arrival Time for Process 3: 2 0
Enter Burst Time and Arrival Time for Process 4: 9 1
Enter Time Quantum: 4
Process ID      Burst Time      Arrival Time    Completion Time Turnaround Time Waiting Time
1               5               2               19              17              12
2               8               3               23              20              12
3               2               0               2               2               0
4               9               1               24              23              14
Average Turnaround time = 15.500000
Average Waiting time = 9.500000
*/