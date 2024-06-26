#ifndef LAYERWIDGET_H
#define LAYERWIDGET_H

#include <QListWidget>
#include <QGraphicsScene>
#include <QListWidgetItem>
#include <QSize>
#include "Layer.h"

class LayerWidget : public QListWidget{
    Q_OBJECT
    QSize iconSize;
    Layer* currentLayer;
public:
    LayerWidget(QWidget *parent = nullptr);
    ~LayerWidget() override = default;
public slots:
    void onLayerAdd();
    void onLayerRemove();
    void onLayerUp();
    void onLayerDown();
signals:
    void layerRemove(size_t index);
    void layerSwap(size_t index1, size_t index2);
};

class LayerWidgetItem: public QListWidgetItem{
    static int count;
    QGraphicsItem* item;
    QString name;
public:
    LayerWidgetItem(QListWidget* parent=nullptr);
    ~LayerWidgetItem() override = default;
    QGraphicsItem* getItem();
    QString getName();
    void setItem(QGraphicsItem* item);
    void setName(QString name);

};
#endif // LAYERWIDGET_H
