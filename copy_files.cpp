#include <filesystem>
#include <iostream>
#include <vector>
#include <string>

namespace fs = std::filesystem;

std::vector<fs::path> get_all_files(const fs::path& baseDir) {
    std::vector<fs::path> files;

    for (const auto& entry : fs::recursive_directory_iterator(baseDir)) {
        if (entry.is_regular_file()) {
            fs::path relative = fs::relative(entry.path(), baseDir);
            files.push_back(relative);
        }
    }

    return files;
}

void copy_all_files(const fs::path& sourceRoot, const fs::path& copyRoot) {
    auto files = get_all_files(sourceRoot);

    for (const auto& relPath : files) {
        fs::path from = sourceRoot / relPath;
        fs::path to   = copyRoot / relPath;

        fs::create_directories(to.parent_path());

        try {
            fs::copy_file(from, to, fs::copy_options::overwrite_existing);
            std::wcout << L"[✓] " << from.wstring() << L" → " << to.wstring() << std::endl;
        } catch (fs::filesystem_error& e) {
            std::wcerr << L"[!] Ошибка копирования: " << e.what() << std::endl;
        }
    }
}

int main() {
    fs::path sourceDir = L"C:\\Input";
    fs::path copyDir   = L"C:\\Copied";

    if (!fs::exists(sourceDir)) {
        std::wcerr << L"[!] Каталог не найден: " << sourceDir << std::endl;
        return 1;
    }

    copy_all_files(sourceDir, copyDir);

    return 0;
}