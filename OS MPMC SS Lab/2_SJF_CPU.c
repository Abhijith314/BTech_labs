#include<stdio.h>

struct process {
    int pno, at, bt, ct, tt, wt;
};

void main() {
    int n, i, j, pos;
    float sumtt = 0, sumwt = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
   
    struct process p[n], temp;
   
    printf("Enter the Process number, Arrival time, and Burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].pno, &p[i].at, &p[i].bt);
    }

    // Sort by arrival time
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate completion time, turnaround time, and waiting time
    int currentTime = 0;
    for (i = 0; i < n; i++) {
        pos = i;
       
        // Find the process with the smallest burst time that has arrived
        for (j = i + 1; j < n; j++) {
            if (p[j].at <= currentTime && p[j].bt < p[pos].bt) {
                pos = j;
            }
        }

        // Swap the selected process with the current process
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;

        // Update current time and calculate completion, turnaround, and waiting times
        if (currentTime < p[i].at) {
            currentTime = p[i].at;
        }
        p[i].ct = currentTime + p[i].bt;
        p[i].tt = p[i].ct - p[i].at;
        p[i].wt = p[i].tt - p[i].bt;

        // Accumulate total turnaround and waiting times
        sumtt += p[i].tt;
        sumwt += p[i].wt;

        // Update current time for the next process
        currentTime = p[i].ct;
    }

    // Output Gantt Chart
    printf("\nGANTT CHART\n");
    printf("%d", p[0].at);
    for (i = 0; i < n; i++) {
        printf(" -> P%d -> %d", p[i].pno, p[i].ct);
    }

    // Output process details
    printf("\n\nProcess no.\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pno, p[i].at, p[i].bt, p[i].tt, p[i].wt);
    }

    // Output average turnaround time and waiting time
    printf("Average Turnaround Time = %.2f\n", sumtt / n);
    printf("Average Waiting Time = %.2f\n", sumwt / n);
}
