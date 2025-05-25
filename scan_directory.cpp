#include <filesystem>
#include <iostream>
#include <vector>
#include <string>

namespace fs = std::filesystem;

std::vector<fs::path> get_all_files(const fs::path& baseDir) {
    std::vector<fs::path> files;

    if (!fs::exists(baseDir) || !fs::is_directory(baseDir)) {
        std::cerr << "Каталог не существует: " << baseDir << std::endl;
        return files;
    }

    for (const auto& entry : fs::recursive_directory_iterator(baseDir)) {
        if (entry.is_regular_file()) {
            fs::path relative = fs::relative(entry.path(), baseDir);
            files.push_back(relative);
        }
    }

    return files;
}

int main() {
    fs::path sourceDir = L"C:\\Input";

    std::vector<fs::path> allFiles = get_all_files(sourceDir);

    std::wcout << L"[+] Найдено файлов: " << allFiles.size() << std::endl;

    for (const auto& relPath : allFiles) {
        std::wcout << L" - " << relPath.wstring() << std::endl;
    }

    return 0;
}