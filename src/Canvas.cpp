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
                scene()->addItem(newItem);
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
    tool_->setToolThickness(2);

}

void Canvas::onColorChange(const QColor& color) {
    qDebug() << color.name();
    lastSelectedColor = color;
    if (tool_) {
        tool_->setToolColor(lastSelectedColor);
    }
}


void Canvas::onThicknessChange(int thickness) {
    if (tool_) {
        tool_->setToolThickness(thickness);
    }
}
