#include "Layer.h"

int Layer::count = 0;

Layer::Layer(QGraphicsItem* parent): QGraphicsItemGroup(parent){
    name = "Layer" + QString::number(count++);
}
