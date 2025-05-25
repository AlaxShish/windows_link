#include <windows.h>
#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

std::vector<fs::path> get_all_files(const fs::path& baseDir) {
    std::vector<fs::path> files;
    for (const auto& entry : fs::recursive_directory_iterator(baseDir)) {
        if (entry.is_regular_file()) {
            fs::path rel = fs::relative(entry.path(), baseDir);
            files.push_back(rel);
        }
    }
    return files;
}

void create_hard_links(const fs::path& copyRoot, const fs::path& linkRoot) {
    auto files = get_all_files(copyRoot);

    for (const auto& relPath : files) {
        fs::path targetFile = copyRoot / relPath;
        fs::path linkPath   = linkRoot / relPath;

        fs::create_directories(linkPath.parent_path());

        if (CreateHardLinkW(linkPath.c_str(), targetFile.c_str(), NULL)) {
            std::wcout << L"[✓] Жёсткая ссылка: " << linkPath.wstring() << std::endl;
        } else {
            DWORD err = GetLastError();
            std::wcerr << L"[!] Ошибка (" << err << L") при создании: " << linkPath.wstring() << std::endl;
        }
    }
}

int main() {
    fs::path copyDir = L"C:\\Copied";
    fs::path linkDir = L"C:\\Links";

    if (!fs::exists(copyDir)) {
        std::wcerr << L"[!] Каталог не найден: " << copyDir << std::endl;
        return 1;
    }

    create_hard_links(copyDir, linkDir);

    return 0;
}