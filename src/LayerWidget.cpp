#include "LayerWidget.h"
#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsItem>

LayerWidget::LayerWidget(QWidget *parent): QListWidget(parent){
    setWindowTitle("LayerWidget");
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setDefaultDropAction(Qt::MoveAction);
    iconSize = QSize(50, 50);
    setIconSize(iconSize);
    LayerWidgetItem* layerItem = new LayerWidgetItem(this);
    layerItem->setText(layerItem->getName());
    addItem(layerItem);
    setCurrentRow(0);

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

int LayerWidgetItem::count = 0;

LayerWidgetItem::LayerWidgetItem(QListWidget* parent): QListWidgetItem(parent){
    item = nullptr;
    name = "Layer" + QString::number(count++);
}


void LayerWidget::onLayerAdd(){
    LayerWidgetItem* layerItem = new LayerWidgetItem(this);
    layerItem->setText(layerItem->getName());
    addItem(layerItem);
    setCurrentItem(layerItem);
}

void LayerWidget::onLayerRemove(){
    auto selected = currentItem();
    int row = currentRow();
    if (selected){
        emit layerRemove(row);
        delete selected;
    }
    int size = count();
    setCurrentRow(std::min(row, size-1));
}

void LayerWidget::onLayerUp(){
    int row = currentRow();
    if (row != 0 ){
        auto item = takeItem(row);
        insertItem(row-1, item);
        setCurrentRow(row-1);
        emit layerSwap(row, row-1);
    }
}

void LayerWidget::onLayerDown(){
    int row = currentRow();
    if (row != count()-1){
        auto item = takeItem(row);
        insertItem(row+1, item);
        setCurrentRow(row+1);
        emit layerSwap(row, row+1);
    }
}
