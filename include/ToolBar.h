#ifndef MY_PAINT_TOOLBAR_H
#define MY_PAINT_TOOLBAR_H

#include "Canvas.h"

#include <QToolBar>
class ToolBar: public QToolBar{
    Q_OBJECT
    Canvas* canvas;
public:
    void setCanvas(Canvas* canvas_) { canvas = canvas_; }
    explicit ToolBar(QWidget *parent = nullptr);
    ~ToolBar() override = default;
    void setup();
};
#endif //MY_PAINT_TOOLBAR_H
