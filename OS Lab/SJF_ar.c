#include <stdio.h>
#include <limits.h>

// Process struct to store process details
struct Process {
    int pid;       // Process ID
    int burst;     // Burst time
    int arrival;   // Arrival time
    int remaining; // Remaining time
    int start;     // Start time
    int completion; // Completion time
    int turnaround; // Turnaround time
    int waiting;   // Waiting time
};

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    
    // Get process details
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter burst time and arrival time for process %d: ", p[i].pid);
        scanf("%d %d", &p[i].burst, &p[i].arrival);
        p[i].remaining = p[i].burst; // Initialize remaining time to burst time
        p[i].start = -1; // Initialize start time to -1 to indicate it hasn't started yet
    }

    // Sort processes based on arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int completed = 0, current_time = 0;
    while (completed != n) {
        int min_idx = -1, min_remaining = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= current_time && p[i].remaining > 0 && p[i].remaining < min_remaining) {
                min_remaining = p[i].remaining;
                min_idx = i;
            }
        }

        if (min_idx != -1) {
            if (p[min_idx].start == -1) {
                p[min_idx].start = current_time; // Set start time if the process is starting for the first time
            }
            current_time++; // Move time forward by 1 unit
            p[min_idx].remaining--; // Decrease remaining time of the current process

            if (p[min_idx].remaining == 0) { // Process completed
                p[min_idx].completion = current_time;
                p[min_idx].turnaround = p[min_idx].completion - p[min_idx].arrival;
                p[min_idx].waiting = p[min_idx].turnaround - p[min_idx].burst;
                completed++;
            }
        } else {
            current_time++; // If no process is ready to execute, just move time forward
        }
    }

    // Print the results
    printf("\nProcess\tBurst\tArrival\tStart\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               p[i].pid, p[i].burst, p[i].arrival, p[i].start,
               p[i].completion, p[i].turnaround, p[i].waiting);
    }

    return 0;
}
