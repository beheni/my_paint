#ifndef MY_PAINT_CANVAS_H
#define MY_PAINT_CANVAS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QEvent>
#include <QMouseEvent>
#include <QPainterPath>
#include <QColor>
#include "Tool.h"
#include "Layer.h"
#include <QList>

class Canvas: public QGraphicsView{
    Q_OBJECT
    bool drawing;
    Tool* tool_;
    QColor lastSelectedColor = QColor(0, 0, 0);
    int lastSelectedThickness = 1;
    void setZValues();
    QPainterPath path;
    Layer* currentLayer_;
    QList<Layer*> layers_;
    QMap<Layer*, QList<QGraphicsItem*>> layerItems_;

public:
    Canvas(QWidget *parent = nullptr);
    ~Canvas() override = default;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    Layer* currentLayer();
    QList<Layer*>& layers();
    QMap<Layer*, QList<QGraphicsItem*>>& layerItems();
    void setCurrentLayer(Layer* layer);

public slots:
    void onToolChange(Tool* tool);
    void onColorChange(const QColor& color);
    void onLayerChange(int index);
    void onLayerAdd();
    void onLayerRemove(size_t index);
    void onLayerSwap(size_t index1, size_t index2);
    void onThicknessChange(int thickness);
signals:
    void objectAdded(QGraphicsItem* item);
};
#endif
