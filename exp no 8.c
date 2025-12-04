#include <stdio.h>

struct Process {
    int pid;
    int at;    // arrival time
    int bt;    // burst time
    int rt;    // remaining time
    int ct;    // completion time
    int tat;   // turnaround time
    int wt;    // waiting time
};

int main() {
    int n, tq;
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
        p[i].rt = p[i].bt;     // remaining time initially = burst time
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;

    while (completed < n) {
        int doneSomething = 0;

        for (i = 0; i < n; i++) {

            if (p[i].rt > 0 && p[i].at <= time) {
                doneSomething = 1;

                if (p[i].rt > tq) {
                    time += tq;
                    p[i].rt -= tq;
                } else {
                    time += p[i].rt;
                    p[i].rt = 0;
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    completed++;
                }
            }
        }

        // No ready process ? CPU idle
        if (!doneSomething)
            time++;
    }

    // Output Section
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
}

