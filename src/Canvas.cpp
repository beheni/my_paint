#include "Canvas.h"
#include <QGraphicsPathItem>
#include <QDebug>
#include <QStyleOptionGraphicsItem>

Canvas::Canvas(QWidget* parent): QGraphicsView(parent){
    tool_ = nullptr;

    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    drawing = false;
    setMouseTracking(true);

    undoStack = new QUndoStack(this);
    show();

}

void Canvas::paintEvent(QPaintEvent *event) {
    QGraphicsView::paintEvent(event);
    if (tool_) tool_->paint(event, this);
    qDebug() << scene()->items().size();
}


void Canvas::mousePressEvent(QMouseEvent *event) {
    path.moveTo(event->pos());
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        if (tool_) tool_->mousePressCallback(event, this);
    }
}
void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        if (tool_) tool_->mouseMoveCallback(event, this);
        scene()->update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
        if (tool_) tool_->mouseReleaseCallback(event, this);
        if (tool_) {
            auto newItem = tool_->newItem();
            if (newItem){
                currentLayer_->addToGroup(newItem);
                emit objectAdded(newItem);
            }
            else
                scene()->update();
            // scene()->addItem(tool_->newItem());
        }
    }
}

void Canvas::onToolChange(Tool* tool) {
    tool_ = tool;
    tool_->setToolColor(lastSelectedColor);
    tool_->setToolThickness(lastSelectedThickness);

}

void Canvas::onColorChange(const QColor& color) {
    qDebug() << color.name();
    lastSelectedColor = color;
    if (tool_) {
        tool_->setToolColor(lastSelectedColor);
    }
}

void Canvas::onLayerAdd() {
    Layer* newLayer = new Layer();
    layers_.insert(0, newLayer);
    layerItems_[newLayer] = QList<QGraphicsItem*>();
    scene()->addItem(newLayer);
    currentLayer_ = newLayer;
}

void Canvas::onLayerRemove(size_t index){
    Layer* layer = layers_[index];
    layers_.removeAt(index);
    scene()->removeItem(layer);
    layerItems_.remove(layer);
    qDebug() << layers_.size();
    delete layer;
}

void Canvas::onLayerSwap(Layer* layer1, Layer* layer2){
    int index1 = layers_.indexOf(layer1);
    int index2 = layers_.indexOf(layer2);
    layers_[index1] = layer2;
    layers_[index2] = layer1;
}

void Canvas::onLayerChange(int currentRow){
    qDebug() << "ROW" << currentRow;
    currentLayer_ = layers_[currentRow];
}

Layer* Canvas::currentLayer(){
    return currentLayer_;
}

QList<Layer*>& Canvas::layers(){
    return layers_;
}

QMap<Layer*, QList<QGraphicsItem*>>& Canvas::layerItems(){
    return layerItems_;
}

void Canvas::setCurrentLayer(Layer* layer){
    currentLayer_ = layer;
}

void Canvas::onThicknessChange(int thickness) {
    lastSelectedThickness = thickness;
    if (tool_) {
        tool_->setToolThickness(thickness);
    }
}
