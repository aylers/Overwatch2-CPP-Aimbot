#include "Config.h"

bool Config::init()
{
    if (!std::filesystem::exists("C:\\AylersConfig"))
    {
        std::filesystem::create_directory("C:\\AylersConfig");
    }

    if (!SetCurrentDirectoryA("C:\\AylersConfig")) {
        return false;
    }

    std::ofstream config("Ayler.cfg");
    if (!config.is_open()) {
        return false;
    }

    config.close();

    return true;
}

std::ostream& operator<<(std::ostream& os, const Settings& settings) {
    os << "gameSens=" << settings.gameSens << std::endl;
    os << "targetColor=" << settings.targetColor.r << "," << settings.targetColor.g << "," << settings.targetColor.b << std::endl;
    os << "colorTolerance=" << settings.colorTolerance << std::endl;
    os << "updateInterval=" << settings.updateInterval << std::endl;
    os << "enabled=" << settings.enabled << std::endl;
    os << "aimSpeed=" << settings.aimSpeed << std::endl;
    os << "fov=" << settings.fov << std::endl;
    os << "smoothing=" << settings.smoothing << std::endl;
    return os;
}
std::istream& operator>>(std::istream& is, Settings& settings) {
    std::string line;
    while (std::getline(is, line)) {
        std::istringstream lineStream(line);
        std::string key;
        if (std::getline(lineStream, key, '=')) {
            if (key == "gameSens") {
                lineStream >> settings.gameSens;
            }
            else if (key == "targetColor") {
                char comma;
                lineStream >> settings.targetColor.r >> comma >> settings.targetColor.g >> comma >> settings.targetColor.b;
            }
            else if (key == "colorTolerance") {
                lineStream >> settings.colorTolerance;
            }
            else if (key == "updateInterval") {
                lineStream >> settings.updateInterval;
            }
            else if (key == "enabled") {
                lineStream >> settings.enabled;
            }
            else if (key == "aimSpeed") {
                lineStream >> settings.aimSpeed;
            }
            else if (key == "fov") {
                lineStream >> settings.fov;
            }
            else if (key == "smoothing") {
                lineStream >> settings.smoothing;
            }
        }
    }
    return is;
}

bool Config::loadConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open() || file.peek() == std::ifstream::traits_type::eof()) {
        return false;
    }
    file >> settings;
    return true;
}

bool Config::SaveConfig(const Settings& settings, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    file << settings;
    return true;
}