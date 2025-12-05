#include <stdio.h>
#include <windows.h>

#define NUM_ITERATIONS 5

HANDLE mutex;  // Mutex handle
int counter = 0;  // Shared resource

DWORD WINAPI ThreadFunction(LPVOID lpParam) {
    int id = *(int*)lpParam;
    int i;  // declare loop variable outside

    for (i = 0; i < NUM_ITERATIONS; i++) {
        // Wait for mutex
        WaitForSingleObject(mutex, INFINITE);

        // Critical Section
        counter++;
        printf("Thread %d incremented counter to %d\n", id, counter);

        // Release mutex
        ReleaseMutex(mutex);

        Sleep(500); // simulate work
    }
    return 0;
}

int main() {
    mutex = CreateMutex(NULL, FALSE, NULL);
    if (mutex == NULL) {
        printf("Mutex creation failed.\n");
        return 1;
    }

    HANDLE t1, t2;
    int id1 = 1, id2 = 2;

    // Create threads
    t1 = CreateThread(NULL, 0, ThreadFunction, &id1, 0, NULL);
    t2 = CreateThread(NULL, 0, ThreadFunction, &id2, 0, NULL);

    // Wait for threads to finish
    WaitForSingleObject(t1, INFINITE);
    WaitForSingleObject(t2, INFINITE);

    printf("Final counter value: %d\n", counter);

    // Close handles
    CloseHandle(t1);
    CloseHandle(t2);
    CloseHandle(mutex);

    return 0;
}

