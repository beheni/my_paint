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
    // qDebug() << scene()->items().size();
}


void Canvas::mousePressEvent(QMouseEvent *event) {
    path.moveTo(event->pos());
    // if (event->button() == Qt::LeftButton) {
    drawing = true;
    if (tool_) tool_->mousePressCallback(event, this);
    // }
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

void Canvas::keyPressEvent(QKeyEvent *event) {
    if (tool_) tool_->keyPressCallback(event);
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
    qDebug() << "Layer added " << layers_.size();
    Layer* newLayer = new Layer();
    layers_.push_back(newLayer);
    layerItems_[newLayer] = QList<QGraphicsItem*>();
    scene()->addItem(newLayer);
    setZValues();
    currentLayer_ = newLayer;

}

void Canvas::onLayerRemove(size_t index){
    Layer* layer = layers_[index];
    layers_.removeAt(index);
    scene()->removeItem(layer);
    layerItems_.remove(layer);
    qDebug() << "Layer removed " << index << " new size " << layers_.size();
    setZValues();
    delete layer;
    size_t size = layers_.size();
    currentLayer_ = layers_[std::min(index, size-1)];
}

void Canvas::onLayerSwap(size_t index1, size_t index2){
    qDebug() << "Layer swapped " << index1 << " " << index2;
    layers_.swapItemsAt(index1, index2);
    setZValues();
}

void Canvas::onLayerChange(int currentRow){
    if (currentRow < 0 || currentRow >= layers_.size()){
        return;
    }
    qDebug() << "chose layer " << currentRow;
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

void Canvas::setZValues(){
    for(size_t i = 0; i<layers_.size(); ++i){
        qDebug() << layers_[i]->parentWidget();
        layers_[i]->setZValue(i);
    }
    scene()->update();
}
