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

}

void LayerWidget::itemAdded(QGraphicsItem* item){
    qDebug() << item->boundingRect().size().toSize();
    QPixmap pixmap(item->boundingRect().size().toSize());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);

    QStyleOptionGraphicsItem opt;
    item->paint(&painter, &opt);
    auto pix = pixmap.scaled(iconSize);
    qDebug() << pix.size();

    LayerWidgetItem* layerItem = new LayerWidgetItem(this);
    QIcon icon(pixmap);
    layerItem->setIcon(icon);
    layerItem->setText(layerItem->getName());
    qDebug() << "Item added";
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
