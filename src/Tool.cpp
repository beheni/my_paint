#include "Tool.h"
#include <QPainter>

Tool::Tool(): QWidget() {
}

QGraphicsItem* Tool::newItem() {
    return createItem();
}

void Tool::mousePressEvent(QMouseEvent *event) {
    mousePress(event);
}

void Tool::mouseMoveEvent(QMouseEvent *event) {
    mouseMove(event);
}

void Tool::mouseReleaseEvent(QMouseEvent *event) {
    mouseRelease(event);
}

void Tool::paint(QPaintEvent *event, QWidget *drawer) {
    QWidget::paintEvent(event);
    painter(event, drawer);
}

void DrawerTool::mousePress(QMouseEvent *event) {
    path.moveTo(event->pos());
}

void DrawerTool::mouseMove(QMouseEvent *event) {
    path.lineTo(event->pos());
}

void DrawerTool::mouseRelease(QMouseEvent *event) {
    path.lineTo(event->pos());
}

void DrawerTool::painter(QPaintEvent *event, QWidget *drawer) {
    QPainter painter(drawer);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(path);
}

QGraphicsItem* DrawerTool::createItem() {
    QGraphicsPathItem *item = new QGraphicsPathItem(path);
    path.clear();
    return item;
}
