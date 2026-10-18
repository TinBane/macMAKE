typedef unsigned short Boolean;
typedef unsigned short EventKind;
typedef unsigned short EventMask;
typedef unsigned short EventModifiers;
typedef unsigned long UInt32;
typedef short SInt16;
typedef struct WindowRecord *WindowPtr;
typedef struct MenuRecord *MenuHandle;

typedef struct Point {
    short v;
    short h;
} Point;

typedef struct Rect {
    short top;
    short left;
    short bottom;
    short right;
} Rect;

typedef struct EventRecord {
    EventKind what;
    UInt32 message;
    UInt32 when;
    Point where;
    EventModifiers modifiers;
} EventRecord;

enum {
    kFileMenuID = 128,
    kQuitItem = 1,
    kEveryEvent = 0xffff,
    kMouseDown = 1,
    kKeyDown = 3,
    kUpdateEvt = 6,
    kCommandKey = 0x0100,
    kInMenuBar = 1,
    kInSysWindow = 2,
    kInContent = 3,
    kInDrag = 4,
    kInGoAway = 6,
    kDocumentProc = 0
};

void MacMakeM68KInitGraf(void);
void MacMakeM68KInitFonts(void);
void MacMakeM68KInitWindows(void);
void MacMakeM68KInitMenus(void);
void MacMakeM68KInitDialogs(void *ignored);
void MacMakeM68KInitCursor(void);
MenuHandle MacMakeM68KNewMenu(short menuID, const unsigned char *title);
void MacMakeM68KAppendMenu(MenuHandle menu, const unsigned char *items);
void MacMakeM68KInsertMenu(MenuHandle menu, short beforeID);
void MacMakeM68KDrawMenuBar(void);
void MacMakeM68KSetRect(Rect *rect, short left, short top, short right, short bottom);
WindowPtr MacMakeM68KNewWindow(void *storage, const Rect *bounds,
    const unsigned char *title, Boolean visible, short procID,
    WindowPtr behind, Boolean goAway, UInt32 refCon);
void MacMakeM68KSetPort(WindowPtr window);
void MacMakeM68KMoveTo(short h, short v);
void MacMakeM68KDrawString(const unsigned char *text);
Boolean MacMakeM68KGetNextEvent(EventMask mask, EventRecord *event);
void MacMakeM68KSystemTask(void);
void MacMakeM68KBeginUpdate(WindowPtr window);
void MacMakeM68KEndUpdate(WindowPtr window);
short MacMakeM68KFindWindow(const Point *point, WindowPtr *window);
UInt32 MacMakeM68KMenuSelect(const Point *point);
UInt32 MacMakeM68KMenuKey(short key);
void MacMakeM68KHiliteMenu(short menuID);
Boolean MacMakeM68KTrackGoAway(WindowPtr window, const Point *point);
void MacMakeM68KSelectWindow(WindowPtr window);
void MacMakeM68KDragWindow(WindowPtr window, const Point *startPoint,
    const Rect *bounds);
void MacMakeM68KSystemClick(const EventRecord *event, WindowPtr window);
void MacMakeM68KDisposeWindow(WindowPtr window);

static Boolean IsQuitChoice(UInt32 choice)
{
    return (Boolean)(((choice >> 16) == kFileMenuID)
        && ((choice & 0xffffUL) == kQuitItem));
}

static void DrawHello(WindowPtr window, const unsigned char *message)
{
    MacMakeM68KSetPort(window);
    MacMakeM68KMoveTo(16, 32);
    MacMakeM68KDrawString(message);
}

int main(void)
{
    Rect bounds;
    Rect dragBounds;
    WindowPtr window;
    MenuHandle fileMenu;
    EventRecord event;
    UInt32 menuChoice;
    Boolean done;
    unsigned char menuTitle[] = {4, 'F', 'i', 'l', 'e'};
    unsigned char quitItem[] = {6, 'Q', 'u', 'i', 't', '/', 'Q'};
    unsigned char windowTitle[] = {
        14, 'H', 'e', 'l', 'l', 'o', 'W', 'i', 'n', 'd', 'o', 'w', '6', '8', 'K'
    };
    unsigned char helloText[] = {
        23, 'H', 'e', 'l', 'l', 'o', ' ', 'f', 'r', 'o', 'm', ' ', 'm', 'a', 'c',
        'M', 'A', 'K', 'E', ' ', '6', '8', 'K', '!'
    };

    MacMakeM68KInitGraf();
    MacMakeM68KInitFonts();
    MacMakeM68KInitWindows();
    MacMakeM68KInitMenus();
    MacMakeM68KInitDialogs((void *)0);
    MacMakeM68KInitCursor();

    fileMenu = MacMakeM68KNewMenu(kFileMenuID, menuTitle);
    if (fileMenu == (MenuHandle)0) {
        return 1;
    }
    MacMakeM68KAppendMenu(fileMenu, quitItem);
    MacMakeM68KInsertMenu(fileMenu, 0);
    MacMakeM68KDrawMenuBar();

    MacMakeM68KSetRect(&bounds, 40, 60, 440, 260);
    /* Allow dragging anywhere on a classic desktop, including multi-screen
     * desktops, without depending on a specific monitor size. */
    MacMakeM68KSetRect(&dragBounds, -32767, -32767, 32767, 32767);
    window = MacMakeM68KNewWindow((void *)0, &bounds, windowTitle, 1,
        kDocumentProc, (WindowPtr)-1, 1, 0);
    if (window == (WindowPtr)0) {
        return 1;
    }
    DrawHello(window, helloText);

    done = 0;
    while (!done) {
        MacMakeM68KSystemTask();
        if (MacMakeM68KGetNextEvent(kEveryEvent, &event)) {
            if (event.what == kUpdateEvt) {
                WindowPtr updateWindow = (WindowPtr)event.message;
                MacMakeM68KBeginUpdate(updateWindow);
                DrawHello(updateWindow, helloText);
                MacMakeM68KEndUpdate(updateWindow);
            } else if (event.what == kMouseDown) {
                WindowPtr clickedWindow;
                short part = MacMakeM68KFindWindow(&event.where, &clickedWindow);
                if (part == kInMenuBar) {
                    menuChoice = MacMakeM68KMenuSelect(&event.where);
                    if (IsQuitChoice(menuChoice)) {
                        done = 1;
                    }
                    MacMakeM68KHiliteMenu(0);
                } else if (part == kInGoAway) {
                    if (MacMakeM68KTrackGoAway(clickedWindow, &event.where)) {
                        done = 1;
                    }
                } else if (part == kInDrag) {
                    MacMakeM68KDragWindow(clickedWindow, &event.where,
                        &dragBounds);
                } else if (part == kInContent) {
                    MacMakeM68KSelectWindow(clickedWindow);
                } else if (part == kInSysWindow) {
                    MacMakeM68KSystemClick(&event, clickedWindow);
                }
            } else if (event.what == kKeyDown
                && (event.modifiers & kCommandKey) != 0) {
                menuChoice = MacMakeM68KMenuKey((short)(event.message & 0xff));
                if (IsQuitChoice(menuChoice)) {
                    done = 1;
                }
                MacMakeM68KHiliteMenu(0);
            }
        }
    }

    MacMakeM68KDisposeWindow(window);
    return 0;
}
