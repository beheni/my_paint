#ifndef MY_PAINT_CANVAS_H
#define MY_PAINT_CANVAS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QEvent>
#include <QMouseEvent>
#include <QPainterPath>

class Canvas: public QGraphicsView{
    Q_OBJECT
    bool drawing;
    QPainterPath path;
public:
    Canvas(QWidget *parent = nullptr);
    ~Canvas() override = default;

    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    // void update();

};
#endif
