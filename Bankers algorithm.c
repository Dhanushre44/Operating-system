#include <stdio.h>

int main() {
    int n, m; // n = processes, m = resources
    int alloc[10][10], max[10][10], avail[10];
    int need[10][10], finish[10] = {0};
    int safeSeq[10], work[10];
    int i, j, k, count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    // INPUT ALLOCATION MATRIX
    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    // INPUT MAX MATRIX
    printf("Enter Max Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    // INPUT AVAILABLE RESOURCES
    printf("Enter Available Resources:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // CALCULATE NEED MATRIX
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // COPY AVAILABLE TO WORK
    for (i = 0; i < m; i++)
        work[i] = avail[i];

    // SAFETY ALGORITHM
    while (count < n) {
        int found = 0;

        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        flag = 1;
                        break;
                    }
                }

                if (!flag) {
                    for (k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("\nSystem is NOT in a safe state (DEADLOCK POSSIBLE!)\n");
            return 0;
        }
    }

    printf("\nSystem is in a SAFE STATE.\nSafe Sequence: ");
    for (i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

    return 0;
}

