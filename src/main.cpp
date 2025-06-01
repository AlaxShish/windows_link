#include <windows.h>
#include <filesystem>
#include <iostream>
#include <vector>

// Пространство имён для std::filesystem
namespace fs = std::filesystem;

// Объявления функций, определённых в других .cpp
std::vector<fs::path> get_all_files(const fs::path& baseDir);
void copy_all_files(const fs::path& sourceRoot, const fs::path& copyRoot);
void create_hard_links(const fs::path& copyRoot, const fs::path& linkRoot);

int wmain(int argc, wchar_t* argv[]) {
    if (argc != 4) {
        std::wcerr << L"Использование: HardLinkCopier.exe <source_dir> <copy_dir> <link_dir>\n";
        return 1;
    }

    fs::path sourceDir = argv[1];
    fs::path copyDir = argv[2];
    fs::path linkDir = argv[3];

    if (!fs::exists(sourceDir)) {
        std::wcerr << L"[!] Исходная директория не найдена: " << sourceDir << std::endl;
        return 1;
    }

    std::wcout << L"[1] Копируем файлы...\n";
    copy_all_files(sourceDir, copyDir);

    std::wcout << L"[2] Создаём жёсткие ссылки...\n";
    create_hard_links(copyDir, linkDir);

    std::wcout << L"[✓] Готово.\n";
    return 0;
}