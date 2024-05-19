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
    void itemAdded(QGraphicsItem* item);
    void onLayerAdd();
    void onLayerRemove();
    void onLayerSwap();
signals:
    void layerRemove(size_t index);
};

class LayerWidgetItem: public QListWidgetItem{
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
