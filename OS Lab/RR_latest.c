#include<stdio.h>
struct process {
    int pno, arrival_time, burst_time, remain_bt;
} p[10],temp1;

int main() {
    int i, j, limit, total = 0, x, counter = 0, time_quantum;
    int wait_time = 0, turnaround_time = 0;
    //int arrival_time[10], burst_time[10], temp[10];
    float average_wait_time, average_turnaround_time;
    int gantt_chart[100]; // To store the order of execution for Gantt chart
    int time_line[100]; // To store the time points for Gantt chart
    int k = 0; // Gantt chart index
    
    printf("\nEnter Total Number of Processes:\t");
    scanf("%d", &limit);
    x = limit;
    
    for(i = 0; i < limit; i++) {
        printf("\nEnter Details of Process[%d]\n", i + 1);
        p[i].pno=i+1;
        printf("Arrival Time:\t");
        scanf("%d", &p[i].arrival_time);
        printf("Burst Time:\t");
        scanf("%d", &p[i].burst_time);
        p[i].remain_bt = p[i].burst_time;
    }

    printf("\nEnter Time Quantum:\t");
    scanf("%d", &time_quantum);

    for(i=0;i<limit-1;i++) {
        for(j=i+1;j<limit;j++) {
            if(p[i].arrival_time > p[j].arrival_time) {
                temp1 = p[i];
                p[i] = p[j];
                p[j] = temp1;
            }
        }
    }

    printf("\nProcess ID\t\tBurst Time\t Turnaround Time\t Waiting Time\n");

    for(total = 0, i = 0; x != 0;) {
        if(p[i].remain_bt <= time_quantum && p[i].remain_bt > 0) {
            total = total + p[i].remain_bt;
            gantt_chart[k] = p[i].pno; // Store the process ID in the Gantt chart
            time_line[k] = total;   // Store the corresponding time
            k++;                    // Increment Gantt chart index
            p[i].remain_bt = 0;
            counter = 1;
        } else if(p[i].remain_bt > 0) {
            p[i].remain_bt = p[i].remain_bt - time_quantum;
            total = total + time_quantum;
            gantt_chart[k] = p[i].pno;
            time_line[k] = total;
            k++;
        }
        if(p[i].remain_bt == 0 && counter == 1) {
            x--;
            printf("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d", p[i].pno, p[i].burst_time, total - p[i].arrival_time,
                   total - p[i].arrival_time - p[i].burst_time);
            wait_time = wait_time + total - p[i].arrival_time - p[i].burst_time;
            turnaround_time = turnaround_time + total - p[i].arrival_time;
            counter = 0;
        }
        if(i == limit - 1) {
            i = 0;
        } else if(p[i+1].arrival_time <= total) {
            i++;
        } else {
            i = 0;
        }
    }

    average_wait_time = wait_time * 1.0 / limit;
    average_turnaround_time = turnaround_time * 1.0 / limit;
    printf("\n\nAverage Waiting Time:\t%f", average_wait_time);
    printf("\nAvg Turnaround Time:\t%f\n", average_turnaround_time);

    // Printing the Gantt chart
    printf("\nGantt Chart:\n");
    printf("|");
    for(i = 0; i < k; i++) {
        printf("  P%d  |", gantt_chart[i]); // Print the process execution order
    }
    printf("0"); // Start time is always 0
    for(i = 0; i < k; i++) {
        printf("\t%d", time_line[i]); // Print the time slots
    }
    printf("\n");

    return 0;
}
