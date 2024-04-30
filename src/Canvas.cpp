#include "Canvas.h"
#include <QGraphicsPathItem>
#include <QStyleOptionGraphicsItem>

Canvas::Canvas(QWidget* parent): QGraphicsView(parent){
    QGraphicsScene* scene = new QGraphicsScene(this);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);
    drawing = false;
    setMouseTracking(true);
    setSceneRect(QRect(QPoint(0,0), parent->size()));

}

void Canvas::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    scene()->setSceneRect(sceneRect());
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
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && drawing) {
        path.lineTo(event->pos());
        drawing = false;
        qDebug() << "Released";
        update();
        scene()->update();
    }
}
void Canvas::paintEvent(QPaintEvent *event) {
    qDebug() << "Paint";
    QStyleOptionGraphicsItem style{};
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Qt::NoBrush);
    scene()->addPath(path, painter.pen(), painter.brush());
    for (auto* item: scene()->items()){
        item->update();
    }
}
