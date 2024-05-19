#include "Layer.h"

int Layer::count = 0;

Layer::Layer(QGraphicsItem* parent): QGraphicsItemGroup(parent){
    name = "Layer" + QString::number(count++);
}

void Layer::addBatch(QList<QGraphicsItem*> items){
    for (auto item: items){
        addToGroup(item);
    }
}

void Layer::removeBatch(QList<QGraphicsItem*> items){
    for (auto item: items){
        removeFromGroup(item);
    }
}
