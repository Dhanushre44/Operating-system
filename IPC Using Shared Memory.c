#include <stdio.h>
#include <windows.h>
#include <string.h>

#define SHM_SIZE 1024
#define SHM_NAME "Global\\MySharedMemory"

int main() {
    HANDLE hMapFile;
    LPVOID pBuf;

    // Create a file mapping object (shared memory)
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,   // Use system paging file
        NULL,                   // Default security
        PAGE_READWRITE,         // Read/write access
        0,                      // Maximum object size (high-order DWORD)
        SHM_SIZE,               // Maximum object size (low-order DWORD)
        SHM_NAME                // Name of mapping object
    );

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d).\n", GetLastError());
        return 1;
    }

    // Map view of file into process address space
    pBuf = MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        SHM_SIZE
    );

    if (pBuf == NULL) {
        printf("Could not map view of file (%d).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Simulate writing to shared memory (producer)
    char message[] = "Hello from process 1!";
    memcpy(pBuf, message, strlen(message) + 1);
    printf("Message written to shared memory: %s\n", message);

    // Simulate reading from shared memory (consumer)
    char readBuf[SHM_SIZE];
    memcpy(readBuf, pBuf, SHM_SIZE);
    printf("Message read from shared memory: %s\n", readBuf);

    // Cleanup
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}

