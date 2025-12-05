#include <stdio.h>
#include <windows.h>

DWORD WINAPI thread1_function(LPVOID lpParam) {
    int i;
    for (i = 0; i < 5; i++) {
        printf("Thread 1 is running: %d\n", i);
        Sleep(1000);  // Sleep 1 second
    }
    return 0;
}

DWORD WINAPI thread2_function(LPVOID lpParam) {
    int i;
    for (i = 0; i < 5; i++) {
        printf("Thread 2 is running: %d\n", i);
        Sleep(1000);  // Sleep 1 second
    }
    return 0;
}

int main() {
    HANDLE thread1, thread2;

    // Create two threads
    thread1 = CreateThread(NULL, 0, thread1_function, NULL, 0, NULL);
    thread2 = CreateThread(NULL, 0, thread2_function, NULL, 0, NULL);

    // Check if threads are created successfully
    if (thread1 == NULL || thread2 == NULL) {
        printf("Error creating threads!\n");
        return 1;
    }

    // Wait for both threads to complete
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    printf("Both threads finished execution.\n");

    return 0;
}

