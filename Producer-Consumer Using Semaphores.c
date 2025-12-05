#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

HANDLE empty;   // Counts empty slots
HANDLE full;    // Counts full slots
HANDLE mutex;   // Binary semaphore for mutual exclusion

DWORD WINAPI producer(LPVOID arg) {
    int i;
    for (i = 0; i < NUM_ITEMS; i++) {
        WaitForSingleObject(empty, INFINITE);  // Wait if buffer is full
        WaitForSingleObject(mutex, INFINITE);  // Enter critical section

        buffer[in] = i + 1; // Produce an item
        printf("Producer produced: %d at buffer[%d]\n", buffer[in], in);
        in = (in + 1) % BUFFER_SIZE;

        ReleaseMutex(mutex);          // Exit critical section
        ReleaseSemaphore(full, 1, NULL); // Increment full slots

        Sleep(500); // Simulate production time
    }
    return 0;
}

DWORD WINAPI consumer(LPVOID arg) {
    int i, item;
    for (i = 0; i < NUM_ITEMS; i++) {
        WaitForSingleObject(full, INFINITE);   // Wait if buffer is empty
        WaitForSingleObject(mutex, INFINITE);  // Enter critical section

        item = buffer[out]; // Consume an item
        printf("Consumer consumed: %d from buffer[%d]\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        ReleaseMutex(mutex);          // Exit critical section
        ReleaseSemaphore(empty, 1, NULL); // Increment empty slots

        Sleep(700); // Simulate consumption time
    }
    return 0;
}

int main() {
    HANDLE prodThread, consThread;

    // Initialize semaphores
    empty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL); // Initially buffer empty slots = BUFFER_SIZE
    full  = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);          // Initially full slots = 0
    mutex = CreateMutex(NULL, FALSE, NULL);                       // Mutex for critical section

    // Create threads
    prodThread = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    consThread = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    // Wait for threads to finish
    WaitForSingleObject(prodThread, INFINITE);
    WaitForSingleObject(consThread, INFINITE);

    // Close handles
    CloseHandle(prodThread);
    CloseHandle(consThread);
    CloseHandle(empty);
    CloseHandle(full);
    CloseHandle(mutex);

    printf("Producer and Consumer have finished execution.\n");
    return 0;
}

