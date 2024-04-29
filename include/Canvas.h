#ifndef MY_PAINT_CANVAS_H
#define MY_PAINT_CANVAS_H

#include <QWidget>

class Canvas: public QWidget {
    Q_OBJECT
public:
    Canvas(QWidget *parent = nullptr);
};
#endif //MY_PAINT_CANVAS_H
