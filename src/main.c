#include<stdio.h>
#include<stdlib.h>
#include<raylib.h>

#define SUCCESS 0
#define WINDOW_INIT_FAIL 1
#define AUDIO_INIT_FAIL 2

int main() {
    const int screenWidth = 1024;
    const int screenHeight = 768;
    const char *title = "databeans";


    InitWindow(screenWidth, screenHeight, title);
    if (!IsWindowReady()) {
        return WINDOW_INIT_FAIL; 
    }
    SetTargetFPS(60);
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitAudioDevice();
    if (!IsAudioDeviceReady()) {
        return AUDIO_INIT_FAIL;
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();
    return SUCCESS;
}
