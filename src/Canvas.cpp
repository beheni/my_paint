#include "Canvas.h"
#include <QGraphicsPathItem>
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

void Canvas::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    scene()->setSceneRect(0,0, width(), height());
    qDebug() << "Scene size: " << scene()->sceneRect() << "View size" << size();
    fitInView(sceneRect(), Qt::KeepAspectRatioByExpanding);
}

void Canvas::paintEvent(QPaintEvent *event) {
    QGraphicsView::paintEvent(event);
    if (tool_) tool_->paint(event, viewport());
    qDebug() << scene()->items().size();
}


void Canvas::mousePressEvent(QMouseEvent *event) {
    path.moveTo(event->pos());
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        if (tool_) tool_->mousePressEvent(event);
    }
}
void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        if (tool_) tool_->mouseMoveEvent(event);
        scene()->update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && drawing) {
        if (tool_) tool_->mouseReleaseEvent(event);
        drawing = false;
        if (tool_) scene()->addItem(tool_->newItem());
    }
}

void Canvas::onToolChange(Tool* tool) {
    tool_ = tool;
    qDebug() << "ok lol";
}

