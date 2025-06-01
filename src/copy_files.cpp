#include <filesystem>
#include <iostream>
#include <vector>

// Используем std::filesystem для работы с путями и файловой системой
namespace fs = std::filesystem;

// Получить список всех файлов в директории и поддиректориях
std::vector<fs::path> get_all_files(const fs::path& baseDir) {
    std::vector<fs::path> files;
    for (const auto& entry : fs::recursive_directory_iterator(baseDir)) {
        if (entry.is_regular_file()) {
            // Получаем путь файла относительно baseDir
            files.push_back(fs::relative(entry.path(), baseDir));
        }
    }
    return files;
}

// Копировать файлы из sourceRoot в copyRoot с сохранением структуры
void copy_all_files(const fs::path& sourceRoot, const fs::path& copyRoot) {
    auto files = get_all_files(sourceRoot);
    for (const auto& relPath : files) {
        fs::path from = sourceRoot / relPath;
        fs::path to = copyRoot / relPath;
        fs::create_directories(to.parent_path()); // создаём подкаталоги при необходимости
        try {
            fs::copy_file(from, to, fs::copy_options::overwrite_existing);
        } catch (fs::filesystem_error& e) {
            std::wcerr << L"[!] Ошибка копирования: " << e.what() << std::endl;
        }
    }
}