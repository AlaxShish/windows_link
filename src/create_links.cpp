#include <windows.h>
#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

std::vector<fs::path> get_all_files(const fs::path& baseDir);

// Создание жёстких ссылок в linkRoot на файлы из copyRoot
void create_hard_links(const fs::path& copyRoot, const fs::path& linkRoot) {
    auto files = get_all_files(copyRoot);
    for (const auto& relPath : files) {
        fs::path targetFile = copyRoot / relPath;
        fs::path linkPath = linkRoot / relPath;
        fs::create_directories(linkPath.parent_path()); // сохранить структуру
        if (!CreateHardLinkW(linkPath.c_str(), targetFile.c_str(), NULL)) {
            DWORD err = GetLastError();
            std::wcerr << L"[!] Ошибка (" << err << L") при создании: " << linkPath.wstring() << std::endl;
        }
    }
}