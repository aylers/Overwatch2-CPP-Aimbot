#include <Windows.h>
#include <iostream>
#include <algorithm>
#include "../Config/Config.h"

class Colorbot {
public:
    Colorbot(const Settings& settings);
    void run();

private:
    Settings settings;
    bool isRunning;

    bool isColorClose(unsigned char r, unsigned char g, unsigned char b, const Color& target, int tolerance);
    void scanScreenForColor(const char* data, int width, int height);
    void moveMouseToTarget(int targetX, int targetY);
    unsigned char* captureScreen(int width, int height, HWND hwnd); 

    bool isKeyPressed(int vkCode);
};

