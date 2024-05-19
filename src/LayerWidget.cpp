#include "LayerWidget.h"

LayerWidget::LayerWidget(QWidget *parent): QListWidget(parent){
    setWindowTitle("LayerWidget");
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setDefaultDropAction(Qt::MoveAction);
}

void LayerWidget::itemAdded(QGraphicsItem* item){
    LayerWidgetItem* layerItem = new LayerWidgetItem(this);
    layerItem->setItem(item);
    layerItem->setText(layerItem->getName());
    addItem(layerItem);
}

void LayerWidgetItem::setItem(QGraphicsItem* item){
    item = item;
}

QGraphicsItem* LayerWidgetItem::getItem(){
    return item;
}

void LayerWidgetItem::setName(QString name){
    name = name;
}

QString LayerWidgetItem::getName(){
    return name;
}

LayerWidgetItem::LayerWidgetItem(QListWidget* parent): QListWidgetItem(parent){
    item = nullptr;
    name = "Layer";
}
