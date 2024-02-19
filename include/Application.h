#ifndef MY_PAINT_APPLICATION_H
#define MY_PAINT_APPLICATION_H
#include "Canvas.h"
#include "Menu.h"
#include "ContextMenu.h"
#include "Tool.h"
class Application
{
    Canvas canvas;
    Menu menu;
    ContextMenu context;
    Tool currentTool;
public:
    int run();
};

#endif //MY_PAINT_APPLICATION_H
