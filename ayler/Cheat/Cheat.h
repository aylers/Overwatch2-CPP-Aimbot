#include <iostream>
#include <Windows.h>

#include "../Game/Aim/Colorbot.h"
#include "../Game/Config/Config.h"

Config cfg;
Settings settings;

int cheat() {


    settings.gameSens = 1.5f;
    settings.targetColor = { 255, 4, 252 };  
    settings.colorTolerance = 50;
    settings.updateInterval = 1; 
    settings.enabled = true; 
    settings.aimSpeed = 0.2f;  
    settings.fov = 90;  
    settings.smoothing = 0.1f; 


    Colorbot colorbot(settings);
    colorbot.run();

    return 0;
}