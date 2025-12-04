#include <stdio.h>

struct Process {
    int pid;
    int at;     // arrival time
    int bt;     // burst time
    int ct;     // completion time
    int wt;     // waiting time
    int tat;    // turnaround time
    int done;   // flag to indicate completion
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int i;

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess P%d\n", p[i].pid);
        printf("Arrival time: ");
        scanf("%d", &p[i].at);
        printf("Burst time: ");
        scanf("%d", &p[i].bt);
        p[i].done = 0;
    }

    int completed = 0, time = 0;

    while (completed < n) {
        int idx = -1;
        int mn = 1e9;  // very large

        // find shortest job from ready processes
        for (i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (p[i].bt < mn) {
                    mn = p[i].bt;
                    idx = i;
                } else if (p[i].bt == mn) {
                    // tie breaker: earlier arrival
                    if (p[i].at < p[idx].at)
                        idx = i;
                }
            }
        }

        if (idx == -1) {
            // no process available ? CPU idle
            time++;
            continue;
        }

        // execute the selected process completely (non-preemptive)
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt  = p[idx].tat - p[idx].bt;
        p[idx].done = 1;
        completed++;
    }

    // print output
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
}

