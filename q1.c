#include <stdio.h>

int main() {
    int n, m, i, j;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m], need[n][m];
    printf("Enter Allocation Matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
   
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for(i=0;i<m;i++)
        scanf("%d", &avail[i]);

    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int finish[n], safe[n], k=0;
    for(i=0;i<n;i++) finish[i]=0;

    int flag=1;
    while(flag) {
        flag=0;
        for(i=0;i<n;i++) {
            if(!finish[i]) {
                int exec=1;
                for(j=0;j<m;j++)
                    if(need[i][j]>avail[j])
                        exec=0;
                if(exec) {
                    for(j=0;j<m;j++)
                        avail[j]+=alloc[i][j];
                    safe[k++]=i;
                    finish[i]=1;
                    flag=1;
                }
            }
        }
    }

    int deadlock=0;
    for(i=0;i<n;i++)
        if(finish[i]==0) deadlock=1;

    if(deadlock)
        printf("System is in DEADLOCK state.\n");
    else {
        printf("System is in SAFE state.\nSafe Sequence: ");
        for(i=0;i<n;i++)
            printf("P%d ", safe[i]);
        printf("\n");
    }

    return 0;
}

