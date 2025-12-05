#include <stdio.h>

int main() {
    int n, i, j;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], pt[n], rt[n], wt[n], tat[n], ct[n];
    int time = 0, completed = 0, min_priority, current;
    
    // Input burst times and priorities
    for (i = 0; i < n; i++) {
        printf("Enter burst time for P%d: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];  // remaining time
        printf("Enter priority for P%d (smaller number = higher priority): ", i+1);
        scanf("%d", &pt[i]);
    }

    printf("\nGantt Chart:\n");

    while (completed < n) {
        min_priority = 9999;
        current = -1;

        // Find the process with highest priority (smallest number) and remaining time > 0
        for (i = 0; i < n; i++) {
            if (rt[i] > 0 && pt[i] < min_priority) {
                min_priority = pt[i];
                current = i;
            }
        }

        if (current != -1) {
            printf("P%d(%d) ", current+1, time);
            rt[current]--;  // execute for 1 unit
            time++;

            if (rt[current] == 0) {
                completed++;
                ct[current] = time;             // completion time
                tat[current] = ct[current];     // will adjust later
            }
        } else {
            time++; // CPU idle
        }
    }

    // Calculate TAT and WT
    for (i = 0; i < n; i++) {
        tat[i] = ct[i];       // assuming arrival time = 0
        wt[i] = tat[i] - bt[i];
    }

    // Display results
    printf("\n\nProcess\tBT\tPriority\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t\t%d\t%d\n", i+1, bt[i], pt[i], wt[i], tat[i]);

    return 0;
}

