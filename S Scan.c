#include <stdio.h>
#include <stdlib.h>

int main() {
    int req[100], n, head, total = 0, i, j, temp;
    int disk_size, direction;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk requests: ");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total disk size (max cylinder): ");
    scanf("%d", &disk_size);

    printf("Enter direction (0 = left, 1 = right): ");
    scanf("%d", &direction);

    // Add head, 0, and disk_size-1 to list for proper SCAN boundary handling
    req[n] = head;
    n++;

    // Sort requests
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (req[j] > req[j + 1]) {
                temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }

    // Find head index
    int head_index;
    for (i = 0; i < n; i++) {
        if (req[i] == head) {
            head_index = i;
            break;
        }
    }

    printf("\nSCAN Disk Scheduling Order:\n");

    // Move right
    if (direction == 1) {
        for (i = head_index; i < n; i++) {
            printf("%d ", req[i]);
        }
        for (i = head_index - 1; i >= 0; i--) {
            printf("%d ", req[i]);
        }
    }

    // Move left
    else {
        for (i = head_index; i >= 0; i--) {
            printf("%d ", req[i]);
        }
        for (i = head_index + 1; i < n; i++) {
            printf("%d ", req[i]);
        }
    }

    // Calculate total head movement
    total += abs(head - req[0]);
    for (i = 0; i < n - 1; i++)
        total += abs(req[i + 1] - req[i]);

    printf("\nTotal head movement = %d cylinders\n", total);

    return 0;
}
