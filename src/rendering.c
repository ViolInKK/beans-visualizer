#include<raylib.h>

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"rendering.h"
#include"helpers.h"
#include"content.h"
#include"array_sorts.h"


const char *MAIN_BTNS[MAIN_BTNS_AMNT] = {
    "ARRAY",
    "STACK",
    "QUEUE",
    "LINKED LIST",
    "TREES",
    "GRAPHS",
};

const char *ARRAY_BTNS[ARRAY_BTNS_AMNT] = {
    "ARRAY OVERVIEW",
    "ARRAY SORTING ALGORITHMS",
};

const char *ARRAY_SORT_LIST_BTNS[ARRAY_SORT_LIST_BTNS_AMNT] = {
    "BUBBLE",
    "SHAKER",
    "SELECTION",
    "INSERTION",
    "QUICK",
    "MERGE",
    "HEAP",
    "SHELL",
    "COMB",
};

const char *ARRAY_SORTING_BTNS[ARRAY_SORTING_BTNS_AMNT] = {
    "SORT ARRAY",
    "SHUFFLE ARRAY",
};

const Converter conversion[CONVERSION_ENTRY_AMNT] = {
    {TITLE, "TITLE"},
    {MAIN_MENU, "MAIN MENU"},
    {ARRAY, "ARRAY"},
    {ARRAY_OVERVIEW, "ARRAY OVERVIEW"},
    {ARRAY_SORTING, "ARRAY SORTING ALGORITHMS"},
    {ARRAY_SORTING_BUBBLE, "BUBBLE"},
    {ARRAY_SORTING_SHAKER, "SHAKER"},
    {ARRAY_SORTING_SELECTION, "SELECTION"},
    {ARRAY_SORTING_INSERTION, "INSERTION"},
    {ARRAY_SORTING_QUICK, "QUICK"},
    {ARRAY_SORTING_MERGE, "MERGE"},
    {ARRAY_SORTING_HEAP, "HEAP"},
    {ARRAY_SORTING_SHELL, "SHELL"},
    {ARRAY_SORTING_COMB, "COMB"},
    {ARRAY_SORTING_BUBBLE_OVERVIEW, "BUBBLE OVERVIEW"},
    {ARRAY_SORTING_SHAKER_OVERVIEW, "SHAKER OVERVIEW"},
    {ARRAY_SORTING_SELECTION_OVERVIEW, "SELECTION OVERVIEW"},
    {ARRAY_SORTING_INSERTION_OVERVIEW, "INSERTION OVERVIEW"},
    {ARRAY_SORTING_QUICK_OVERVIEW, "QUICK OVERVIEW"},
    {ARRAY_SORTING_MERGE_OVERVIEW, "MERGE OVERVIEW"},
    {ARRAY_SORTING_HEAP_OVERVIEW, "HEAP OVERVIEW"},
    {ARRAY_SORTING_SHELL_OVERVIEW, "SHELL OVERVIEW"},
    {ARRAY_SORTING_COMB_OVERVIEW, "COMB OVERVIEW"},
    {STACK, "STACK"},
    {QUEUE, "QUEUE"},
    {TREES, "TREES"},
    {GRAPHS, "GRAPHS"},
    {LINKED_LIST, "LINKED LIST"},
};

void DrawReturnButton(ViewContext *viewContext){
    if (viewContext->viewStackPointer == 0) {
        return;
    }
    int fontSize = 50; 
    int titleXPos = GetScreenWidth()*0.05;
    int titleYPos = GetScreenHeight() - GetScreenHeight() * 0.99;
    int textSize = MeasureText("<-", fontSize);
    DrawText("<-",titleXPos,titleYPos,fontSize,WHITE);
    Rectangle inputRec = (Rectangle){titleXPos, titleYPos, textSize+50, 50.0};
    DrawRectangleRec(inputRec,BLANK);

    if (CheckCollisionPointRec(GetMousePosition(), inputRec) 
            && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        if (viewContext->viewStackPointer < 1){
            return;
        }
        else {
            viewContext->viewStack[viewContext->viewStackPointer] = 0;
            viewContext->viewStackPointer--;
        }
    }
}

void DrawCloseButton(bool *mainLoopCon){
    int fontSize = 50; 
    int titleXPos = GetScreenWidth()*0.95;
    int titleYPos = GetScreenHeight() - GetScreenHeight() * 0.99;
    int textSize = MeasureText("x", fontSize);
    DrawText("x",titleXPos,titleYPos,fontSize,RED);
    Rectangle inputRec = (Rectangle){titleXPos, titleYPos, textSize+50, 50.0};
    DrawRectangleRec(inputRec,BLANK);
    if (CheckCollisionPointRec(GetMousePosition(), inputRec) 
            && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        *mainLoopCon = false;
    }
}

const char *ViewStrConvert(View view){
    for (size_t i = 0; i < CONVERSION_ENTRY_AMNT; i++){
        if (view == conversion[i].view){
            return conversion[i].str_view;
        }
    }
    return "Placeholder Title";
}

void SwitchViewTo(ViewContext *viewContext, const char* newView){
    for (size_t i = 0; i < CONVERSION_ENTRY_AMNT; i++){
        if (!strcmp(newView, conversion[i].str_view)){
            viewContext->viewStackPointer++;
            if (viewContext->viewStackPointer > VIEWSTACK_SIZE){
                fprintf(stderr, "ERROR: Viewstack overflow\n");
                exit(VIEWSTACK_OVERFLOW);
            }
            viewContext->viewStack[viewContext->viewStackPointer] = conversion[i].view;
            return;
        }
    }
    //Reset stack and return to main menu if switching to non existing view.
    viewContext->viewStackPointer = 1;
    memset(&viewContext->viewStack, 0, sizeof(viewContext->viewStack));
    viewContext->viewStack[viewContext->viewStackPointer] = MAIN_MENU;
}

void DrawNavigationButtons(ViewContext *viewContext, Vector2 pos){
    size_t buttons_amnt;
    Button buttons[20];
    const char **map;
    switch (viewContext->viewStack[viewContext->viewStackPointer]){
        case MAIN_MENU:
            buttons_amnt = MAIN_BTNS_AMNT;
            map = MAIN_BTNS;
            break;
        case ARRAY:
            buttons_amnt = ARRAY_BTNS_AMNT;
            map = ARRAY_BTNS;
            break;
        case ARRAY_SORTING:
            buttons_amnt = ARRAY_SORT_LIST_BTNS_AMNT;
            map = ARRAY_SORT_LIST_BTNS;
            break;
        default:
            return;
            break;
    }

    float buttonWidth = 400.0, 
          buttonHeight = 50.0,
          buttonBotMargin = 70.0;
    bool overflows = false;


    //Check if last button overflows screen, to split buttons in two columns
    if (buttonBotMargin * buttons_amnt > GetScreenHeight()){
        overflows = true;
    }

    for (size_t i = 0; i < buttons_amnt; i++){
        Rectangle body = (Rectangle){
            (GetScreenWidth()*0.50) - buttonWidth/2, 
            (buttonBotMargin * i) + 50, 
            buttonWidth, 
            buttonHeight};

        if (overflows){
            if (i < buttons_amnt/2){
                body = (Rectangle){
                    (GetScreenWidth()*0.25) - buttonWidth/2, 
                    (buttonBotMargin * i) + 50, 
                    buttonWidth, 
                    buttonHeight};
            }
            else {
                body = (Rectangle){
                    (GetScreenWidth()*0.75) - buttonWidth/2, 
                    (buttonBotMargin * (i%(buttons_amnt - buttons_amnt/2))) + 50, 
                    buttonWidth, 
                    buttonHeight};
            }
        }
        buttons[i].title = &map[i];
        buttons[i].body = body;
        buttons[i].isActive = false;
    }
    //Draw buttons
    for (size_t i = 0; i < buttons_amnt; i++){
        int fontSize = 30;
        if (CheckCollisionPointRec(GetMousePosition(), buttons[i].body)){
            buttons[i].isActive = true;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                SwitchViewTo(viewContext, *buttons[i].title);
            }
        }
        int textSize = MeasureText(*buttons[i].title, fontSize);
        if (textSize > buttons[i].body.width){
            fontSize = 20;
            textSize = MeasureText(*buttons[i].title, fontSize);
        }
        DrawRectangleRec(buttons[i].body, buttons[i].isActive ? SKYBLUE : WHITE);
        DrawRectangleLinesEx(buttons[i].body, 3, buttons[i].isActive ? BLUE : LIGHTGRAY);
        DrawText(
                *buttons[i].title, 
                buttons[i].body.width/2 + buttons[i].body.x - textSize/2, 
                buttons[i].body.y+10, 
                fontSize, 
                buttons[i].isActive ? BLUE : DARKGRAY);
    }
}

void DrawArraySortingButtons(ViewContext *viewContext, void (*sortFuncPtr)(ViewContext*)){
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float buttonWidth = screenWidth * 0.30, 
          buttonHeight = 50.0;
    int fontSize = 30; 
    
    //Buttons
    char *sortArrayTitle = "SORT ARRAY";
    Rectangle sortArray = (Rectangle){
        screenWidth - screenWidth * 0.95, 
        screenHeight - screenHeight * 0.90, 
        buttonWidth, 
        buttonHeight};
    int sortArrayTitleSize = MeasureText(sortArrayTitle, fontSize);
    bool isSortArrayHover = false;

    char *sortOverviewTitle = "SORT OVERVIEW";
    Rectangle sortOverview = (Rectangle){
        screenWidth - screenWidth * 0.95 + buttonWidth, 
        screenHeight - screenHeight * 0.90, 
        buttonWidth, 
        buttonHeight};
    int sortOverviewTitleSize = MeasureText(sortOverviewTitle, fontSize);
    bool isSortOverviewHover = false;

    char *shuffleArrayTitle = "SHUFFLE ARRAY";
    Rectangle shuffleArray = (Rectangle){
        screenWidth - screenWidth * 0.05 - buttonWidth, 
        screenHeight - screenHeight * 0.90, 
        buttonWidth, 
        buttonHeight};
    int shuffleArrayTitleSize = MeasureText(shuffleArrayTitle, fontSize);
    bool isShuffleArrayHover = false;

    //Drawing Buttons
    isSortArrayHover = CheckCollisionPointRec(GetMousePosition(), sortArray);
    DrawRectangleRec(sortArray,isSortArrayHover ? SKYBLUE : WHITE);
    DrawRectangleLinesEx(sortArray, 3, isSortArrayHover ? BLUE : LIGHTGRAY);
    DrawText(sortArrayTitle, sortArray.width/2 + sortArray.x - sortArrayTitleSize/2, sortArray.y+10, fontSize, isSortArrayHover ? BLUE : DARKGRAY);
    if (isSortArrayHover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        EndDrawing();
        (*sortFuncPtr)(viewContext);
        VerifyArrayAfterSort(viewContext);
        StopSound(viewContext->sqrWave);
    }

    isSortOverviewHover = CheckCollisionPointRec(GetMousePosition(), sortOverview);
    DrawRectangleRec(sortOverview,isSortOverviewHover ? SKYBLUE : WHITE);
    DrawRectangleLinesEx(sortOverview, 3, isSortOverviewHover ? BLUE : LIGHTGRAY);
    DrawText(sortOverviewTitle, sortOverview.width/2 + sortOverview.x - sortOverviewTitleSize/2, sortOverview.y+10, fontSize, isSortOverviewHover ? BLUE : DARKGRAY);
    if (isSortOverviewHover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        SwitchViewTo(viewContext, ViewStrConvert(viewContext->viewStack[viewContext->viewStackPointer] + 9));
    }

    isShuffleArrayHover = CheckCollisionPointRec(GetMousePosition(), shuffleArray);
    DrawRectangleRec(shuffleArray, isShuffleArrayHover ? SKYBLUE : WHITE);
    DrawRectangleLinesEx(shuffleArray, 3, isShuffleArrayHover ? BLUE : LIGHTGRAY); 
    DrawText(shuffleArrayTitle, shuffleArray.width/2 + shuffleArray.x - shuffleArrayTitleSize/2, shuffleArray.y+10, fontSize, isShuffleArrayHover ? BLUE : DARKGRAY);
    if (isShuffleArrayHover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        ShuffleArray(viewContext->array, viewContext->arraySize);
    }
}

void DrawViewTitle(const char* viewTitle){
    int fontSize = 40; 
    int textSize = MeasureText(viewTitle, fontSize);
    int titleXPos = (GetScreenWidth()/2)-(textSize/2);
    int titleYPos = GetScreenHeight() - GetScreenHeight() * 0.99;
    DrawText(viewTitle,titleXPos,titleYPos,fontSize,WHITE);
}

void DrawTextBox(ViewContext *viewContext){
    /*
        REF: https://github.com/raysan5/raylib/blob/master/examples/text/text_rectangle_bounds.c
    */
    const char *content = viewContext->textBoxContent;

    float textOffsetY = 60;
    float textOffsetX = 0.0f;

    Rectangle screenBorder = (Rectangle){50,0,GetScreenWidth() - 100, GetScreenHeight()};

    Font font = GetFontDefault();
    int fontSize = 40; 
    const float spacing = 2.0f;
    float scaleFactor = fontSize/(float)font.baseSize;
    int length = TextLength(content);

    int startLine = -1;
    int endLine = -1;
    int lastk = -1;

    int selectStart = 0;
    int selectLength = 0;

    enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
    int state = MEASURE_STATE;
    bool wordWrap = true;
    for (int i = 0, k = 0; i < length; i++, k++){
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&content[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        if (codepoint == 0x3f) codepointByteCount = 1;
        i += (codepointByteCount - 1);

        float glyphWidth = 0;
        if (codepoint != '\n'){
            glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;

            if (i + 1 < length) glyphWidth = glyphWidth + spacing;
        }

        if (state == MEASURE_STATE){
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) endLine = i;

            if ((textOffsetX + glyphWidth) > screenBorder.width){
                endLine = (endLine < 1)? i : endLine;
                if (i == endLine) endLine -= codepointByteCount;
                if ((startLine + codepointByteCount) == endLine) endLine = (i - codepointByteCount);

                state = !state;
            }
            else if ((i + 1) == length){
                endLine = i;
                state = !state;
            }
            else if (codepoint == '\n') state = !state;

            if (state == DRAW_STATE){
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                int tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        }
        else{
            if (codepoint == '\n'){
                if (!wordWrap){
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }
            }
            else{
                if (!wordWrap && ((textOffsetX + glyphWidth) > screenBorder.width)){
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }

                if ((textOffsetY + font.baseSize*scaleFactor) > screenBorder.height) break;

                if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength))){
                    DrawRectangleRec((Rectangle){ screenBorder.x + textOffsetX - 1, screenBorder.y + textOffsetY, glyphWidth, (float)font.baseSize*scaleFactor }, RED);
                }

                if ((codepoint != ' ') && (codepoint != '\t')){
                    DrawTextCodepoint(font, codepoint, (Vector2){ screenBorder.x + textOffsetX, screenBorder.y + textOffsetY }, fontSize, WHITE);
                }
            }

            if (wordWrap && (i == endLine)){
                textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                selectStart += lastk - k;
                k = lastk;

                state = !state;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' ')) textOffsetX += glyphWidth;  // avoid leading spaces
    }
}

void DrawView(ViewContext *viewContext){
    View view = viewContext->viewStack[viewContext->viewStackPointer];
    DrawViewTitle(ViewStrConvert(viewContext->viewStack[viewContext->viewStackPointer]));
    DrawNavigationButtons(viewContext, (Vector2){0.0, 0.0});
    DrawReturnButton(viewContext);

    void (*sortFuncPtr)(ViewContext*);

    switch (view){
        case TITLE:
            if (IsKeyPressed(KEY_ENTER)){
                SwitchViewTo(viewContext, "MAIN MENU");
            }
            break;
        case ARRAY_OVERVIEW:
            viewContext->textBoxContent = ARRAY_OVERVIEW_CONTENT;
            DrawTextBox(viewContext);
            break;
        case MAIN_MENU:
        case ARRAY:
        case ARRAY_SORTING_BUBBLE_OVERVIEW:
        case ARRAY_SORTING_SHAKER_OVERVIEW:
        case ARRAY_SORTING_SELECTION_OVERVIEW:
        case ARRAY_SORTING_INSERTION_OVERVIEW:
        case ARRAY_SORTING_QUICK_OVERVIEW:
        case ARRAY_SORTING_MERGE_OVERVIEW:
        case ARRAY_SORTING_HEAP_OVERVIEW:
        case ARRAY_SORTING_SHELL_OVERVIEW:
        case ARRAY_SORTING_COMB_OVERVIEW:
        case ARRAY_SORTING:
            break;
        case ARRAY_SORTING_BUBBLE:
            viewContext->textBoxContent = BUBBLESORT_OVERVIEW_CONTENT;
            sortFuncPtr = &BubbleSort;
            break;
        case ARRAY_SORTING_SHAKER:
            viewContext->textBoxContent = SHAKERSORT_OVERVIEW_CONTENT;
            sortFuncPtr = &ShakerSort;
            break;
        case ARRAY_SORTING_SELECTION:
            viewContext->textBoxContent = SELECTIONSORT_OVERVIEW_CONTENT;
            sortFuncPtr = &SelectionSort;
            break;
        case ARRAY_SORTING_INSERTION:
            viewContext->textBoxContent = INSERTIONSORT_OVERVIEW_CONTENT;
            sortFuncPtr = &InsertionSort;
            break;
        case ARRAY_SORTING_QUICK:
            viewContext->textBoxContent = QUICKSORT_OVERVIEW_CONTENT;
            sortFuncPtr = &QuickSortInterface;
            break;
        case ARRAY_SORTING_MERGE:
            viewContext->textBoxContent = MERGESORT_OVERVIEW_CONTENT;
            sortFuncPtr = &MergeSortInterface;
            break;
        case ARRAY_SORTING_HEAP:
            viewContext->textBoxContent = HEAPSORT_OVERVIEW_CONTENT;
            sortFuncPtr = &HeapSort;
            break;
        case ARRAY_SORTING_SHELL:
            viewContext->textBoxContent = SHELLSORT_OVERVIEW_CONTENT;
            sortFuncPtr = &ShellSort;
            break;
        case ARRAY_SORTING_COMB:
            viewContext->textBoxContent = COMBSORT_OVERVIEW_CONTENT;
            sortFuncPtr = &CombSort;
            break;
        case STACK:
            viewContext->textBoxContent = STACK_OVERVIEW_CONTENT;
            DrawTextBox(viewContext);
            break;
        case QUEUE:
            viewContext->textBoxContent = QUEUE_OVERVIEW_CONTENT;
            DrawTextBox(viewContext);
            break;
        case LINKED_LIST:
            viewContext->textBoxContent = LINKED_LIST_OVERVIEW_CONTENT;
            DrawTextBox(viewContext);
            break;
        case TREES:
            viewContext->textBoxContent = TREES_OVERVIEW_CONTENT;
            DrawTextBox(viewContext);
            break;
        case GRAPHS:
            viewContext->textBoxContent = GRAPHS_OVERVIEW_CONTENT;
            DrawTextBox(viewContext);
            break;
        default:
            fprintf(stderr, "ERROR: Tried to render non existing view\n");
            exit(NON_EXISTING_VIEW);
    }

    //If view is one of array sorting examples.
    if (view > 4 && view <= 13){
        DrawArray(viewContext, viewContext->arraySize);
        DrawArraySortingButtons(viewContext, sortFuncPtr);
    }
    //If view is one of array sorting overviews.
    if (view > 13 && view <= 24){
        DrawTextBox(viewContext);
    }
}

void DrawArray(ViewContext *viewContext, int size){
    float screenWidth = (float)GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Color color;
    for (size_t i = 0; i<size; i++){
        color = WHITE;
        if (viewContext->arrayPointer == i){
            color = RED;
        }
        DrawRectangle(
            (screenWidth/size)*i, 
            (float)screenHeight-((screenHeight/size)*viewContext->array[i]),
            screenWidth/size, 
            ((screenHeight/size)*viewContext->array[i]), color);
        DrawRectangleLines(
            (screenWidth/size)*i, 
            (float)screenHeight-((screenHeight/size)*viewContext->array[i]),
            screenWidth/size, 
            ((screenHeight/size)*viewContext->array[i]),BLACK);
    }
}

void VisualizeArraySorting(ViewContext *viewContext){
    SetSoundPitch(viewContext->sqrWave, 1.0 + viewContext->array[viewContext->arrayPointer] * 0.015);
    if(!IsSoundPlaying(viewContext->sqrWave)){
        PlaySound(viewContext->sqrWave);
    }
    BeginDrawing();
    ClearBackground(BACKGROUND_COLOR);
    DrawViewTitle(ViewStrConvert(viewContext->viewStack[viewContext->viewStackPointer]));
    DrawArray(viewContext, viewContext->arraySize);
    EndDrawing();
}

void VerifyArrayAfterSort(ViewContext *viewContext){
    int size = viewContext->arraySize;

    for (int j = 0; j<size; j++){
        viewContext->arrayPointer = j;
        SetSoundPitch(viewContext->sqrWave, 1.0 + viewContext->array[j] * 0.015);
        if(!IsSoundPlaying(viewContext->sqrWave)){
            PlaySound(viewContext->sqrWave);
        }
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        DrawViewTitle(ViewStrConvert(viewContext->viewStack[viewContext->viewStackPointer]));
        DrawArray(viewContext, viewContext->arraySize);
        EndDrawing();
    }

    for (int j = size; j>0; j--){
        viewContext->arrayPointer = j;
        SetSoundPitch(viewContext->sqrWave, 1.0 + viewContext->array[j] * 0.015);
        if(!IsSoundPlaying(viewContext->sqrWave)){
            PlaySound(viewContext->sqrWave);
        }
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        DrawViewTitle(ViewStrConvert(viewContext->viewStack[viewContext->viewStackPointer]));
        DrawArray(viewContext, viewContext->arraySize);
        EndDrawing();
    }
}
