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
    VIEW_COUNT,
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

    const char *textBoxContent;

    //Array sorting sound
    Sound sqrWave;

    //Data structure examples
    int array[100];
    int arraySize;
    size_t arrayPointer;
} ViewContext;

// ---- Text for buttons at specific views ----

//Button titles at main menu view
extern const char *MAIN_BTNS[MAIN_BTNS_AMNT];
//Button titles at array view
extern const char *ARRAY_BTNS[ARRAY_BTNS_AMNT];
//Button titles at view with all array sorting algorithms
extern const char *ARRAY_SORT_LIST_BTNS[ARRAY_SORT_LIST_BTNS_AMNT];
//Button titles at array sorting view 
extern const char *ARRAY_SORTING_BTNS[ARRAY_SORTING_BTNS_AMNT];

//NOTE(ViolinKK): When button is pressed we lookup to what view switch to based on button text. 
//                This conversion table converts view title(string) to view enum type.
extern const Converter conversion[VIEW_COUNT];

// ---- Rendering functions ----

void DrawReturnButton(ViewContext *viewContext);
void DrawCloseButton(bool *mainLoopCon);
void DrawNavigationButtons(ViewContext *viewContext, Vector2 pos);
void DrawArraySortingButtons(ViewContext *viewContext, void (*p_sortingFunc)(ViewContext*));

void DrawViewTitle(const char* viewTitle);

//TODO(ViolinKK): Add scroll functionality and scroll bar.
void DrawTextBox(ViewContext *viewContext); //Used for rendering long text with word wrapping and scroll.

void DrawView(ViewContext *viewContext);

const char *ViewStrConvert(View view); //Used to convert current view from viewstack(or any view) into its string to render view title.
void SwitchViewTo(ViewContext *viewContext, const char* newView); //Called when navigation button is pressed and takes that button title as argument.

void DrawArray(ViewContext *viewContext, int size);
void VisualizeArraySorting(ViewContext *viewContext);
//TODO(ViolinKK): Mark correctly placed elements in array with green color.
void VerifyArrayAfterSort(ViewContext *viewContext);
#endif
