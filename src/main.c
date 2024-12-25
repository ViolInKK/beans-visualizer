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
        return WINDOW_INIT_FAIL; 
    }
    SetTargetFPS(fps);

    InitAudioDevice();
    if (!IsAudioDeviceReady()){
        return AUDIO_INIT_FAIL;
    }
    ChangeDirectory(GetApplicationDirectory());
    SetMasterVolume(0.03);

    return SUCCESS;
}

void InitViewContext(ViewContext *viewContext){
    viewContext->textBoxContent = "If you see this, something went wrong. Oops.";

    //Set audio
    Wave wavSqrWave = LoadWave("../asine.wav");
    Sound sqrWave = LoadSoundFromWave(wavSqrWave);
    UnloadWave(wavSqrWave);
    viewContext->sqrWave = sqrWave;

    //Set view stack
    viewContext->viewStackPointer = 0;
    memset(&viewContext->viewStack, 0, sizeof(viewContext->viewStack));
    viewContext->viewStack[viewContext->viewStackPointer] = TITLE;

    //Set array
    viewContext->arraySize = 100;
    int array[viewContext->arraySize];
    viewContext->arrayPointer = 0;
    FillArrayRandom(array, viewContext->arraySize);
    memcpy(&viewContext->array, &array[0], sizeof(viewContext->array));

    return;
}

int main(){
    // INITIALIZATION
    int init_status = InitRaylib();
    if (init_status != SUCCESS){
        fprintf(stderr, "ERROR: Couldn't initialize raylib.\n");
        return init_status;
    }
    ViewContext *viewContext = malloc(sizeof(ViewContext));
    if (viewContext == NULL){
        fprintf(stderr, "ERROR: Couldn't initialize viewcontext.\n");
        CloseWindow();
        CloseAudioDevice();
        return VIEWCONTEXT_INIT_FAIL;
    }
    //TODO: Error checking.
    InitViewContext(viewContext);

    // MAIN LOOP
    bool isRunning = true;
    while (!WindowShouldClose() && isRunning){
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        DrawCloseButton(&isRunning);
        DrawView(viewContext);
        EndDrawing();
    }
    UnloadSound(viewContext->sqrWave);
    CloseAudioDevice();
    CloseWindow();
    free(viewContext);
    return SUCCESS;
}
