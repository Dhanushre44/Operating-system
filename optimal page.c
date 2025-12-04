#include <stdio.h>

int main() {
    int n, frames, i, j, k, flag;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter page reference sequence: ");
    for(i=0;i<n;i++) scanf("%d",&pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &frames);

    int frame[frames];
    for(i=0;i<frames;i++) frame[i]=-1;
    int page_faults=0;

    for(i=0;i<n;i++) {
        flag=0;
        for(j=0;j<frames;j++)
            if(frame[j]==pages[i]) flag=1;

        if(!flag) {
            int far[frames];
            for(j=0;j<frames;j++) {
                far[j]=n;
                for(k=i+1;k<n;k++)
                    if(frame[j]==pages[k]) {
                        far[j]=k;
                        break;
                    }
            }
            int max_index=0;
            for(j=1;j<frames;j++)
                if(far[j]>far[max_index]) max_index=j;

            frame[max_index]=pages[i];
            page_faults++;
        }

        printf("Frames: ");
        for(j=0;j<frames;j++)
            printf("%d ", frame[j]);
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
    return 0;
}

