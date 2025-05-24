#include <windows.h>
#include <iostream>

int main() {
    LPCWSTR sourcePath = L"C:\\TestData\\original.txt";
    LPCWSTR linkPath   = L"C:\\TestData\\linked.txt";

    BOOL result = CreateHardLinkW(linkPath, sourcePath, NULL);

    if (result) {
        std::wcout << L"[+] Ссылка успешно создана: " << linkPath << std::endl;
    } else {
        DWORD error = GetLastError();
        std::wcerr << L"[!] Ошибка при создании жёсткой ссылки. Код: " << error << std::endl;
    }

    return 0;
}