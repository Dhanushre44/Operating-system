#include <stdio.h>

int main() {
    int n, m, i, j, worst;
    printf("Enter number of memory blocks: ");
    scanf("%d",&n);
    int block[n];
    printf("Enter block sizes: ");
    for(i=0;i<n;i++) scanf("%d",&block[i]);

    printf("Enter number of processes: ");
    scanf("%d",&m);
    int process[m];
    printf("Enter process sizes: ");
    for(i=0;i<m;i++) scanf("%d",&process[i]);

    int allocation[m];
    for(i=0;i<m;i++) allocation[i]=-1;

    for(i=0;i<m;i++) {
        worst=-1;
        for(j=0;j<n;j++)
            if(block[j]>=process[i])
                if(worst==-1 || block[j]>block[worst])
                    worst=j;
        if(worst!=-1) {
            allocation[i]=worst;
            block[worst]-=process[i];
        }
    }

    printf("Process No\tProcess Size\tBlock Allocated\n");
    for(i=0;i<m;i++)
        printf("%d\t\t%d\t\t%d\n", i+1, process[i], allocation[i]+1);
    return 0;
}

