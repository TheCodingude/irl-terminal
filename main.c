#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <time.h>

void renderDate(){
    // TODO: figure out how to scale the size of the rect to the size of the text 
    DrawRectangleLines(50, 50, 180, 60, WHITE);

    time_t now;
    struct tm *timeinfo;

    time(&now);
    timeinfo = localtime(&now);

    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);

    DrawText(buffer, 60, 60, 30, WHITE);
}

// if i would've called it `24hour-clock` if i could
void renderTime(bool militaryformat){

    time_t now;
    struct tm *timeinfo;

    time(&now);
    timeinfo = localtime(&now);

    if(!militaryformat){
        timeinfo->tm_hour = timeinfo->tm_hour % 12;
    }
    
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);

    
    DrawRectangleLines(50, 50, 130, 50, WHITE);
    DrawText(buffer, 55, 55, 30, WHITE);

}




int main()
{
    InitWindow(1000, 500, "raygui - controls test suite");
    SetTargetFPS(60);

    int monitorCount = GetMonitorCount();
    // Example: Get info for the second monitor (index 1)
    int targetMonitor = 0; 
    if (targetMonitor < monitorCount)
    {
        Vector2 monitorPos = GetMonitorPosition(targetMonitor);
        int monitorWidth = GetMonitorWidth(targetMonitor);
        int monitorHeight = GetMonitorHeight(targetMonitor);
        int windowWidth = 800; 
        int windowHeight = 600; 
        int posX = monitorPos.x + (monitorWidth - windowWidth) / 2;
        int posY = monitorPos.y + (monitorHeight - windowHeight) / 2;
        SetWindowPosition(posX, posY);
    }
    bool remoteDesktop = false;

    while (!WindowShouldClose())
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);

            renderTime(false);
            
            

        EndDrawing();
    }

    CloseWindow();
    return 0;
}