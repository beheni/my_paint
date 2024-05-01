#include "Canvas.h"
#include <QGraphicsPathItem>
#include <QStyleOptionGraphicsItem>

Canvas::Canvas(QWidget* parent): QGraphicsView(parent){
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);
    drawing = false;
    setMouseTracking(true);
    show();
}

void Canvas::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    scene()->setSceneRect(sceneRect());
}

void Canvas::paintEvent(QPaintEvent *event) {
    QGraphicsView::paintEvent(event);
    qDebug() << "draw";
    QPainter painter(viewport());
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(path);
    QGraphicsPathItem *item = new QGraphicsPathItem(path);
    scene()->addItem(item);


}


void Canvas::mousePressEvent(QMouseEvent *event) {
    path.clear();
    qDebug() << "Pressed";
    if (event->button() == Qt::LeftButton) {
        drawing = true;
    }
}
void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        path.lineTo(event->pos());
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && drawing) {
        path.lineTo(event->pos());
        drawing = false;
        qDebug() << "Released";
        update();
    }
}
