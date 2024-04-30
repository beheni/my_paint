#ifndef MY_PAINT_CANVAS_H
#define MY_PAINT_CANVAS_H

#include <vector>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>

#include "Layer.h"

class Canvas: public QWidget {
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    void addLayer();
    void removeLayer();
    void setActiveLayer(int index);
    std::vector<Layer*> layers;
    Layer* activeLayer;
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};
#endif //MY_PAINT_CANVAS_H
