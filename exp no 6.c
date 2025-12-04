#include <stdio.h>

struct Process {
    int pid;
    int at;        
    int bt;       
    int rt;        
    int priority; 
    int ct;        
    int wt;       
    int tat;       
};

int main() {
    int n, i;
    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    struct Process p[n];
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess P%d\n", p[i].pid);
        printf("Arrival time: ");
        scanf("%d", &p[i].at);
        printf("Burst time: ");
        scanf("%d", &p[i].bt);
        printf("Priority (lower value = higher priority): ");
        scanf("%d", &p[i].priority);
        p[i].rt = p[i].bt;
        p[i].ct = p[i].wt = p[i].tat = 0;
    }

    int time = 0;
    int completed = 0;

    
    while (completed < n) {
        int idx = -1;
        int best_pr = 1<<30; 

        for (i = 0; i < n; i++) {
            if (p[i].rt > 0 && p[i].at <= time) {
                if (p[i].priority < best_pr) {
                    best_pr = p[i].priority;
                    idx = i;
                } else if (p[i].priority == best_pr) {
                   
                    if (p[i].at < p[idx].at || (p[i].at == p[idx].at && p[i].pid < p[idx].pid)) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
           
            time++;
            continue;
        }

        
        p[idx].rt--;
        time++;

      
        if (p[idx].rt == 0) {
            completed++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            if (p[idx].wt < 0) p[idx].wt = 0; 
        }
    }

    
    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    double total_wt = 0, total_tat = 0;
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time   = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}

