#include <windows.h>
#include <filesystem>
#include <iostream>
#include <vector>
#include <chrono>

namespace fs = std::filesystem;
using Clock = std::chrono::steady_clock;

std::vector<fs::path> get_all_files(const fs::path& baseDir) {
    std::vector<fs::path> files;
    for (const auto& entry : fs::recursive_directory_iterator(baseDir)) {
        if (entry.is_regular_file()) {
            files.push_back(fs::relative(entry.path(), baseDir));
        }
    }
    return files;
}

void create_links_with_timer(const fs::path& copyRoot, const fs::path& linkRoot) {
    auto files = get_all_files(copyRoot);
    size_t total = files.size();

    std::wcout << L"[i] Всего файлов: " << total << std::endl;

    auto start = Clock::now();

    size_t success = 0;

    for (const auto& relPath : files) {
        fs::path target = copyRoot / relPath;
        fs::path link   = linkRoot / relPath;
        fs::create_directories(link.parent_path());

        if (CreateHardLinkW(link.c_str(), target.c_str(), NULL)) {
            success++;
        } else {
            DWORD err = GetLastError();
            std::wcerr << L"[!] Ошибка (" << err << L") на: " << link.wstring() << std::endl;
        }
    }

    auto end = Clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::wcout << L"[✓] Успешно создано: " << success << L" ссылок" << std::endl;
    std::wcout << L"[⏱] Время: " << duration << L" мс" << std::endl;
    if (duration > 0) {
        double per_sec = (double)success / (duration / 1000.0);
        std::wcout << L"[⚡] Скорость: " << per_sec << L" файлов/сек" << std::endl;
    }
}

int main() {
    fs::path copyDir = L"C:\\Copied";
    fs::path linkDir = L"C:\\Links";

    create_links_with_timer(copyDir, linkDir);

    return 0;
}