#ifndef RENDERING_H 
#define RENDERING_H 

//Error codes.
#define VIEWSTACK_OVERFLOW 5
#define NON_EXISTING_VIEW 4

//Constants.
#define BACKGROUND_COLOR (Color){15, 15, 15, 255}

#define VIEWSTACK_SIZE 10

#define MAIN_BTNS_AMNT 6
#define ARRAY_BTNS_AMNT 2
#define ARRAY_SORT_LIST_BTNS_AMNT 9
#define ARRAY_SORTING_BTNS_AMNT 2

#define CONVERSION_ENTRY_AMNT 28 

typedef enum{
    TITLE,
    MAIN_MENU,
    ARRAY,
    ARRAY_OVERVIEW,
    ARRAY_SORTING,
    ARRAY_SORTING_BUBBLE,
    ARRAY_SORTING_SHAKER,
    ARRAY_SORTING_SELECTION,
    ARRAY_SORTING_INSERTION,
    ARRAY_SORTING_QUICK,
    ARRAY_SORTING_MERGE,
    ARRAY_SORTING_HEAP,
    ARRAY_SORTING_SHELL,
    ARRAY_SORTING_COMB,
    ARRAY_SORTING_BUBBLE_OVERVIEW,
    ARRAY_SORTING_SHAKER_OVERVIEW,
    ARRAY_SORTING_SELECTION_OVERVIEW,
    ARRAY_SORTING_INSERTION_OVERVIEW,
    ARRAY_SORTING_QUICK_OVERVIEW,
    ARRAY_SORTING_MERGE_OVERVIEW,
    ARRAY_SORTING_HEAP_OVERVIEW,
    ARRAY_SORTING_SHELL_OVERVIEW,
    ARRAY_SORTING_COMB_OVERVIEW,
    STACK,
    QUEUE,
    LINKED_LIST,
    TREES,
    GRAPHS,
} View;

typedef struct{
    View view;
    const char* str_view;
} Converter;

typedef struct Button{
    const char **title;
    bool isActive;
    Rectangle body;
} Button;

typedef struct ViewContext{
    View viewStack[VIEWSTACK_SIZE];
    size_t viewStackPointer;

    //Text to display with DrawTextBox()
    const char *textBoxContent;

    //Array sorting sound
    Sound sqrWave;

    //Data structures examples
    int array[100];
    int arraySize;
    size_t arrayPointer;
} ViewContext;

//Text for buttons
extern const char *MAIN_BTNS[MAIN_BTNS_AMNT];
extern const char *ARRAY_BTNS[ARRAY_BTNS_AMNT];
extern const char *ARRAY_SORT_LIST_BTNS[ARRAY_SORT_LIST_BTNS_AMNT];
extern const char *ARRAY_SORTING_BTNS[ARRAY_SORTING_BTNS_AMNT];

//Used when convert button text into view enum
extern const Converter conversion[CONVERSION_ENTRY_AMNT];


void DrawReturnButton(ViewContext *viewContext);
void DrawCloseButton(bool *mainLoopCon);
void DrawNavigationButtons(ViewContext *viewContext, Vector2 pos);
void DrawArraySortingButtons(ViewContext *viewContext, void (*sortFuncPtr)(ViewContext*));

void DrawViewTitle(const char* viewTitle);

void DrawTextBox(ViewContext *viewContext);

void DrawView(ViewContext *viewContext);

const char *ViewStrConvert(View view);
void SwitchViewTo(ViewContext *viewContext, const char* newView);

void DrawArray(ViewContext *viewContext, int size);
void VisualizeArraySorting(ViewContext *viewContext);
void VerifyArrayAfterSort(ViewContext *viewContext);
#endif
