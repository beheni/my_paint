#ifndef MY_PAINT_BUTTON_H
#define MY_PAINT_BUTTON_H

#include <QToolButton>

class Button: public QToolButton{
    Q_OBJECT
public:
    explicit Button(QWidget* parent = nullptr);
    ~Button() override = default;
};
#endif //MY_PAINT_BUTTON_H
