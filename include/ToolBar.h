#ifndef MY_PAINT_TOOLBAR_H
#define MY_PAINT_TOOLBAR_H

#include <QToolBar>
class ToolBar: public QToolBar{
    Q_OBJECT
public:
    ToolBar(QWidget *parent = nullptr);
};
#endif //MY_PAINT_TOOLBAR_H
