#include "Colorbot.h"
#include <Windows.h>
#include <iostream>
#include <cmath>

Colorbot::Colorbot(const Settings& settings) : settings(settings), isRunning(true) {
}

bool Colorbot::isColorClose(unsigned char r, unsigned char g, unsigned char b, const Color& target, int tolerance) {
    return std::abs(r - target.r) <= tolerance &&
        std::abs(g - target.g) <= tolerance &&
        std::abs(b - target.b) <= tolerance;
}
void Colorbot::run() {
    HWND hwnd = FindWindow(NULL, "Overwatch"); 
    if (!hwnd) {
        return;
    }

    RECT rect;
    GetWindowRect(hwnd, &rect);  
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;


    while (isRunning) {
        unsigned char* screenData = captureScreen(width, height, hwnd);

        scanScreenForColor(reinterpret_cast<const char*>(screenData), width, height);

        delete[] screenData;

        Sleep(settings.updateInterval);

        if (isKeyPressed(VK_END)) {
            isRunning = false;
        }
    }
}
unsigned char* Colorbot::captureScreen(int width, int height, HWND hwnd) {
    HDC hdcWindow = GetDC(hwnd); 
    HDC hdcMem = CreateCompatibleDC(hdcWindow);

    HBITMAP hBitmap = CreateCompatibleBitmap(hdcWindow, width, height);
    SelectObject(hdcMem, hBitmap);

    BitBlt(hdcMem, 0, 0, width, height, hdcWindow, 0, 0, SRCCOPY);

    BITMAPINFOHEADER bmi = { 0 };
    bmi.biSize = sizeof(BITMAPINFOHEADER);
    bmi.biWidth = width;
    bmi.biHeight = -height; 
    bmi.biPlanes = 1;
    bmi.biBitCount = 32;  
    bmi.biCompression = BI_RGB;

    unsigned char* screenData = new unsigned char[width * height * 4]; 
    GetDIBits(hdcMem, hBitmap, 0, height, screenData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);

    DeleteObject(hBitmap);
    DeleteDC(hdcMem);
    ReleaseDC(hwnd, hdcWindow);

    return screenData;
}

void Colorbot::scanScreenForColor(const char* data, int width, int height) {
    int centerX = width / 2;
    int centerY = height / 2;
    int fovRadius = settings.fov;  

    int highestX = -1;
    int highestY = -1;
    int minY = height;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int dx = x - centerX;
            int dy = y - centerY;
            float distance = sqrt(dx * dx + dy * dy);

            if (distance <= fovRadius) {
                int index = (y * width + x) * 4; 

                unsigned char r = data[index];
                unsigned char g = data[index + 1];
                unsigned char b = data[index + 2];
                unsigned char a = data[index + 3];

                if (isColorClose(r, g, b, settings.targetColor, settings.colorTolerance) && a == 255) {
                    if (y < minY) {  
                        minY = y;
                        highestX = x;
                        highestY = y;
                    }
                }
            }
        }
    }
    if (highestY != -1 && isKeyPressed(VK_RBUTTON)) { // mouse key to activate it
        int targetX = highestX + 30;   // a lil offset becausse its detecting health/name tag first
        int targetY = highestY + 20; 

        moveMouseToTarget(targetX, targetY);
    }
}

void Colorbot::moveMouseToTarget(int targetX, int targetY) {
    POINT currentPos;
    GetCursorPos(&currentPos);

    int xmove = targetX - currentPos.x;
    int ymove = targetY - currentPos.y;

    float mulx = 1.0f;  
    float muly = 1.0f; 
    float sensitivity = settings.gameSens;  

    int adjustedXmove = static_cast<int>(xmove * mulx / (sensitivity / 2.5f));
    int adjustedYmove = static_cast<int>(ymove * muly / (sensitivity / 2.5f));

    float smoothingFactor = settings.smoothing; 
    int smoothedXmove = static_cast<int>(adjustedXmove * smoothingFactor);
    int smoothedYmove = static_cast<int>(adjustedYmove * smoothingFactor);

    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    input.mi.dx = smoothedXmove; 
    input.mi.dy = smoothedYmove;  

    if (settings.enabled) {
        SendInput(1, &input, sizeof(INPUT));
    }
}

bool Colorbot::isKeyPressed(int vkCode) {
    return (GetAsyncKeyState(vkCode) & 0x8000) != 0;
}