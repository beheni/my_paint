#include "Canvas.h"
#include <iostream>
#include <QDebug>
Canvas::Canvas(QWidget *parent) : QWidget(parent) {
    setMouseTracking(true);
    resize(parent->size());
    addLayer();

}

void Canvas::addLayer() {
    Layer *layer = new Layer(this);
    layers.push_back(layer);
    activeLayer = layers.back();
    activeLayer->resize(size());
    qDebug() << size()<< "\n";
    qDebug() << activeLayer->size()<< "\n";
}

void Canvas::removeLayer() {
    if (layers.size() > 1) {
        layers.pop_back();
        activeLayer = layers.back();
    }
}

void Canvas::setActiveLayer(int index) {
    activeLayer = layers[index];
}


void Canvas::paintEvent(QPaintEvent *event) {
    activeLayer->update();
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    activeLayer->mousePressEvent(event);
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    activeLayer->mouseMoveEvent(event);
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    activeLayer->mouseReleaseEvent(event);
}
