#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int bt;         // Burst Time
    int priority;   // Priority
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
};

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("\nEnter Burst Time for Process %d: ", p[i].pid);
        scanf("%d", &p[i].bt);

        printf("Enter Priority for Process %d (Higher number = Higher priority): ", p[i].pid);
        scanf("%d", &p[i].priority);
    }

    // Sort processes by priority (descending)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[j].priority > p[i].priority) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate Waiting Time
    p[0].wt = 0; // First process waits 0
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
    }

    // Calculate Turnaround Time
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].wt + p[i].bt;
    }

    // Output
    printf("\n--- Highest Priority First Scheduling ---\n");
    printf("PID\tBT\tPriority\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\t%d\n",
               p[i].pid, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
    }

    return 0;
}

