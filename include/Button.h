#ifndef MY_PAINT_BUTTON_H
#define MY_PAINT_BUTTON_H

#include <QToolButton>
#include "Tool.h"

class Button: public QToolButton{
    Q_OBJECT
    Tool* tool_;
public:
    explicit Button(QWidget* parent = nullptr);
    ~Button() override = default;
    void setTool(Tool* tool);
    Tool* tool();
signals:
    void buttonChanged(Tool* tool);
};
#endif //MY_PAINT_BUTTON_H
