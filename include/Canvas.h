#ifndef MY_PAINT_CANVAS_H
#define MY_PAINT_CANVAS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QEvent>
#include <QMouseEvent>
#include <QPainterPath>
#include <QColor>
#include "Tool.h"

class Canvas: public QGraphicsView{
    Q_OBJECT
    bool drawing;
    Tool* tool_;
    QColor lastSelectedColor = QColor(0, 0, 0);
    int lastSelectedThickness = 1;
    QPainterPath path;

public:
    Canvas(QWidget *parent = nullptr);
    ~Canvas() override = default;

    // void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;    
public slots:
    void onToolChange(Tool* tool);
    void onColorChange(const QColor& color);
    void onThicknessChange(int thickness);
signals:
    void objectAdded(QGraphicsItem* item);
};
#endif
