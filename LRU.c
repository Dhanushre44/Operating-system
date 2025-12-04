#include <stdio.h>

int main() {
    int n, frames, i, j, k, flag, lru, min, pos;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter page reference sequence: ");
    for(i=0;i<n;i++) scanf("%d",&pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &frames);

    int frame[frames], time[frames];
    for(i=0;i<frames;i++) frame[i]=-1;
    int page_faults=0;

    for(i=0;i<n;i++) {
        flag=0;
        for(j=0;j<frames;j++)
            if(frame[j]==pages[i]) { flag=1; time[j]=i; break; }

        if(!flag) {
            int empty=-1;
            for(j=0;j<frames;j++) if(frame[j]==-1) { empty=j; break; }

            if(empty!=-1) { frame[empty]=pages[i]; time[empty]=i; }
            else {
                min=time[0]; pos=0;
                for(j=1;j<frames;j++)
                    if(time[j]<min) { min=time[j]; pos=j; }
                frame[pos]=pages[i]; time[pos]=i;
            }
            page_faults++;
        }

        printf("Frames: ");
        for(j=0;j<frames;j++) printf("%d ", frame[j]);
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
    return 0;
}

