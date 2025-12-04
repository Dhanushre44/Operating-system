#include <stdio.h>

int main() {
    int n, frames, i, j, flag, pos = 0;

   
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);


    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    int frame[frames];
    for (i = 0; i < frames; i++)
        frame[i] = -1; 

    int page_faults = 0;

    printf("\nFIFO Page Replacement Process:\n");
    printf("Step\tPages\t\tFrames\n");

    for (i = 0; i < n; i++) {
        flag = 0;
        
        for (j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                flag = 1; 
                break;
            }
        }

        if (flag == 0) {
            frame[pos] = pages[i];      
            pos = (pos + 1) % frames;  
            page_faults++;
        }

        
        printf("%d\t%d\t\t", i + 1, pages[i]);
        for (j = 0; j < frames; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", page_faults);

    return 0;
}


