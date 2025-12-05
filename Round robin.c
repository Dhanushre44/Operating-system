#include <stdio.h>

int main() {
    int n, i, j, time = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], rem_bt[n], qt;
    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i+1);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i]; // remaining burst time
    }

    printf("Enter time quantum: ");
    scanf("%d", &qt);

    int wt[n], tat[n];
    for (i = 0; i < n; i++) wt[i] = 0;

    int done;
    printf("\nGantt Chart: \n");
    do {
        done = 1;
        for (i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = 0;
                if (rem_bt[i] > qt) {
                    printf("P%d(%d->%d) ", i+1, time, time+qt);
                    time += qt;
                    rem_bt[i] -= qt;
                } else {
                    printf("P%d(%d->%d) ", i+1, time, time+rem_bt[i]);
                    time += rem_bt[i];
                    wt[i] = time - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
    } while (!done);

    // Calculate turnaround time
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }

    // Display results
    printf("\n\nProcess\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", i+1, bt[i], wt[i], tat[i]);

    return 0;
}

