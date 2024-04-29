#include "Canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent) {
    setMouseTracking(true);
    setStyleSheet("background-color: white;");
}

void Canvas::addLayer() {
    Layer *layer = new Layer(this);
    layers.push_back(layer);
    activeLayer = layers.back();
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
