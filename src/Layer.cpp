#include "Layer.h"

Layer::Layer(QWidget *parent) : QWidget(parent) {
    drawing = false;
    setMouseTracking(true);
}

void Layer::paintEvent(QPaintEvent *event) {

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(path);
}

void Layer::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        path.moveTo(event->pos());
        drawing = true;
    }
}

void Layer::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        path.lineTo(event->pos());
        update();
    }
}

void Layer::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && drawing) {
        path.lineTo(event->pos());
        drawing = false;
        update();
    }
}

