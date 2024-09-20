#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <Windows.h>
#include "../Misc/Misc.h"

struct Settings {
    float gameSens;
    Color targetColor;
    int colorTolerance;
    int updateInterval;
    bool enabled;
    float aimSpeed;
    float fov;
    float smoothing;

    friend std::ostream& operator<<(std::ostream& os, const Settings& settings);
    friend std::istream& operator>>(std::istream& is, Settings& settings);
};

class Config {
public:
    bool init(); 
    bool loadConfig(const std::string& filename); 
    bool SaveConfig(const Settings& settings, const std::string& filename); 
private:
    Settings settings;

};