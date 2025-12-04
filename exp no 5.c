#include <stdio.h>

struct Process {
    int pid;        
    int bt;         
    int priority;   
    int wt;         
    int tat;        
};

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];


    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("\nEnter Burst Time for Process %d: ", p[i].pid);
        scanf("%d", &p[i].bt);

        printf("Enter Priority for Process %d (Higher number = Higher priority): ", p[i].pid);
        scanf("%d", &p[i].priority);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[j].priority > p[i].priority) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

  
    p[0].wt = 0; // First process waits 0
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
    }

   
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].wt + p[i].bt;
    }

    
    printf("\n--- Highest Priority First Scheduling ---\n");
    printf("PID\tBT\tPriority\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\t%d\n",
               p[i].pid, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
    }

    return 0;
}


