//
// Created by sp on 14.05.2025.
//

#include "MainMenuStage.hpp"

std::vector<std::string> getFilenamesFromDirectory(const std::string &directoryPath) {
    std::vector<std::string> filenames;

    try {
        for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
            if (std::filesystem::is_regular_file(entry.status())) {
                filenames.push_back(entry.path().filename().string()); // Just the filename
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "General error: " << e.what() << std::endl;
    }

    return filenames;
}
