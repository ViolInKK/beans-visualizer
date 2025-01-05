#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#include<raylib.h>

#include"rendering.h"
#include"helpers.h"

//Error codes
#define SUCCESS 0
#define WINDOW_INIT_FAIL 1
#define AUDIO_INIT_FAIL 2
#define VIEWCONTEXT_INIT_FAIL 3

int InitRaylib() {
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const char *title = "databeans";
    const int fps = 60;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, title);
    if (!IsWindowReady()){
        fprintf(stderr, "ERROR: Couldn't initialize raylib window.\n");
        exit(WINDOW_INIT_FAIL); 
    }
    SetTargetFPS(fps);

    InitAudioDevice();
    if (!IsAudioDeviceReady()){
        fprintf(stderr, "ERROR: Couldn't initialize raylib audio.\n");
        CloseWindow();
        exit(AUDIO_INIT_FAIL);
    }
    //NOTE(ViolinKK): We do this to make use of relatives paths easier when loading files.
    ChangeDirectory(GetApplicationDirectory());

    SetMasterVolume(0.03);

    return SUCCESS;
}

ViewContext *InitViewContext(){
    //Allocate memory
    ViewContext *viewContext;
    viewContext = malloc(sizeof(*viewContext));
    if (viewContext == NULL){
        fprintf(stderr, "ERROR: Couldn't allocate viewcontext memory.\n");
        CloseWindow();
        CloseAudioDevice();
        exit(VIEWCONTEXT_INIT_FAIL);
    }
    viewContext->textBoxContent = "If you see this, something went wrong. Oops.";

    //Set audio
    Wave wavSqrWave = LoadWave("../asine.wav");
    Sound sqrWave = LoadSoundFromWave(wavSqrWave);
    UnloadWave(wavSqrWave);
    viewContext->sqrWave = sqrWave;

    //Set view stack
    viewContext->viewStackPointer = 0;
    viewContext->viewStack[viewContext->viewStackPointer] = TITLE;

    //Set array
    viewContext->arraySize = 100;
    viewContext->arrayPointer = 0;
    FillArrayRandom(viewContext->array, viewContext->arraySize);

    return viewContext;
}

/*|------------------------------|
  |             MAIN             |
  |------------------------------|
*/
int main(){
    // INITIALIZATION
    InitRaylib();
    ViewContext *viewContext = InitViewContext();

    // ---- MAIN LOOP ----
    bool isRunning = true;
    while (!WindowShouldClose() && isRunning){
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        DrawCloseButton(&isRunning);
        DrawView(viewContext);
        EndDrawing();
    }

    // DEINITIALIZATION
    UnloadSound(viewContext->sqrWave);
    CloseAudioDevice();
    CloseWindow();

    free(viewContext);

    return SUCCESS;
}
