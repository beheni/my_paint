#include "Tool.h"
#include <QDebug>
#include <QPainter>

Tool::Tool(): QWidget() {
}

QGraphicsItem* Tool::newItem() {
    return createItem();
}

void Tool::mousePressCallback(QMouseEvent *event, QGraphicsView* drawer) {
    mousePress(event, drawer);
}

void Tool::mouseMoveCallback(QMouseEvent *event, QGraphicsView* drawer) {
    mouseMove(event, drawer);
}

void Tool::mouseReleaseCallback(QMouseEvent *event, QGraphicsView* drawer) {
    mouseRelease(event, drawer);
}

void Tool::paint(QPaintEvent *event, QGraphicsView* drawer) {
    QWidget::paintEvent(event);
    painter(event, drawer);
}

void SelectionTool::mousePress(QMouseEvent *event, QGraphicsView* drawer) {
    auto clickCoord = event->pos();
    if (lastSelectionBoundary && !lastSelectionBoundary->contains(clickCoord)) {
        drawer->scene()->removeItem(lastSelectionBoundary);
        lastSelectionBoundary = nullptr;
        selectedItems.clear();
    }
    // drawer->scene()->removeItem(lastSelectionBoundary);
    if (QGraphicsItem *item = drawer->itemAt(clickCoord)) {
        selectedItems.insert(item);
        qDebug() << "You clicked on item" << item;
    }
    else {
        qDebug() << "You clicked on nothing";
    }
    start = event->pos();
    if (lastSelectionBoundary  && lastSelectionBoundary->contains(clickCoord)) {
            moveStart = event->pos();
        }

}

void SelectionTool::mouseMove(QMouseEvent *event, QGraphicsView* drawer) {
    if (lastSelectionBoundary && lastSelectionBoundary->contains(event->pos())) {
        // lastSelectionBoundary->moveBy(event->pos().x()-moveStart.x(), event->pos().y()-moveStart.y());
        for (auto item: selectedItems) {
            item->moveBy(event->pos().x()-moveStart.x(), event->pos().y()-moveStart.y());
        }
        moveStart = event->pos();
    }
    else {
        end = event->pos();
        if (QGraphicsItem *item = drawer->itemAt(event->pos())) {
            selectedItems.insert(item);
            qDebug() << "You clicked on item" << item;
        }
        qDebug() << "selected items count"<< selectedItems.size();
    }
}

void SelectionTool::mouseRelease(QMouseEvent *event, QGraphicsView* drawer) {
    end = event->pos();
}

void SelectionTool::painter(QPaintEvent *event, QGraphicsView *drawer) {
    QPainter painter(drawer->viewport());

    // painter.setRenderHint(QPainter::Antialiasing);
    // painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    // painter.setBrush(Qt::NoBrush);
    // auto itemsInArea = drawer->items(QRect(start.toPoint(), end.toPoint()));
    // for (auto item: itemsInArea) {
    //     item->setSelected(true);
    //     selectedItems.insert(item);
    // }
    // for (auto item: selectedItems) {
    //     item->moveBy((end.x())-start.x(), end.y()-start.y());
    // }

    // painter.drawRect(QRect(start.toPoint(), end.toPoint()));
}

QGraphicsItem* SelectionTool::createItem() {
    if (selectedItems.size() == 0) return nullptr;
    if (lastSelectionBoundary) {
        return nullptr;
    }
    QGraphicsRectItem *item = new QGraphicsRectItem(QRect(start.toPoint(), end.toPoint()));
    lastSelectionBoundary = item;
    return lastSelectionBoundary;
    // return item;
}



void DrawerTool::mousePress(QMouseEvent *event, QGraphicsView* drawer) {
    path.moveTo(event->pos());
}

void DrawerTool::mouseMove(QMouseEvent *event, QGraphicsView* drawer) {
    path.lineTo(event->pos());
}

void DrawerTool::mouseRelease(QMouseEvent *event, QGraphicsView* drawer) {
    path.lineTo(event->pos());
}

void DrawerTool::painter(QPaintEvent *event, QGraphicsView* drawer) {
    QPainter painter(drawer->viewport());
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

void RectTool::mousePress(QMouseEvent *event, QGraphicsView* drawer) {
    rect.setTopLeft(event->pos());
    rect.setBottomRight(event->pos());
}

void RectTool::mouseMove(QMouseEvent *event, QGraphicsView* drawer) {
    rect.setBottomRight(event->pos());
}

void RectTool::mouseRelease(QMouseEvent *event, QGraphicsView* drawer) {
    rect.setBottomRight(event->pos());
}

void RectTool::painter(QPaintEvent *event, QGraphicsView* drawer) {
    QPainter painter(drawer->viewport());
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(rect);
}

QGraphicsItem* RectTool::createItem() {
    QGraphicsRectItem *item = new QGraphicsRectItem(rect);
    return item;
}
