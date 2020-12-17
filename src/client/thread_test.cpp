#include <iostream>
#include <Windows.h>

DWORD WINAPI print(LPVOID lpParameter) {
    std::cout << "WOLF" << std::endl;

    return 0;
}

int main() {
    HANDLE ht = CreateThread(
        NULL,
        0,
        print,
        NULL,
        0,
        NULL
    );
    if (ht == NULL) {
        throw std::exception();
    }
    std::cout << "LION" << std::endl;

    WaitForSingleObject(ht, INFINITE);
    CloseHandle(ht);

    return 0;
}
