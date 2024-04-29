#ifndef MY_PAINT_CANVAS_H
#define MY_PAINT_CANVAS_H

#include <vector>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>

class Canvas: public QWidget {
    Q_OBJECT
public:
    Canvas(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    bool drawing;
    QPainterPath path;
};
#endif //MY_PAINT_CANVAS_H
