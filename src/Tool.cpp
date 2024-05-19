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

void Tool::keyPressCallback(QKeyEvent *event) {
    keyPressEvent(event);
}

void Tool::keyPressEvent(QKeyEvent *event) {
    return;
}

void Tool::paint(QPaintEvent *event, QGraphicsView* drawer) {
    QWidget::paintEvent(event);
    painter(event, drawer);
}

void Tool::setToolColor(const QColor &color = QColor(0, 0, 0)) {
    color_ = color;
}

void Tool::setToolThickness(int thickness) {
    thickness_ = thickness;
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
    }

}

void SelectionTool::mouseRelease(QMouseEvent *event, QGraphicsView* drawer) {
    if (selectedItems.size() == 0) end = start;
    else end = event->pos();
}

void SelectionTool::painter(QPaintEvent *event, QGraphicsView *drawer) {
    QPainter painter(drawer->viewport());

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::gray, 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Qt::NoBrush);
    // auto itemsInArea = drawer->items(QRect(start.toPoint(), end.toPoint()));
    // for (auto item: itemsInArea) {
    //     item->setSelected(true);
    //     selectedItems.insert(item);
    // }
    // for (auto item: selectedItems) {
    //     item->moveBy((end.x())-start.x(), end.y()-start.y());
    // }
    if (!lastSelectionBoundary) {
        painter.drawRect(QRect(start.toPoint(), end.toPoint()));
    }

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

void SelectionTool::keyPressEvent(QKeyEvent *event) {
    // if (event->key() == Qt::Key_Delete) {
    //     for (auto item: selectedItems) {
    //         item->scene()->removeItem(item);
    //     }
    //     selectedItems.clear();
    // }
}

void DrawerTool::keyPressEvent(QKeyEvent *event) {
    /*qDebug() << "Key pressed";
    if (event->key() == Qt::Key_Backspace) {
        path = QPainterPath();
    }*/
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
    painter.setPen(QPen(color_, thickness_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(path);
}

QGraphicsItem* DrawerTool::createItem() {
    QGraphicsPathItem *item = new QGraphicsPathItem(path);
    item->setPen(QPen(color_, thickness_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
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
    painter.setPen(QPen(color_, thickness_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(rect);
}

QGraphicsItem* RectTool::createItem() {
    QGraphicsRectItem *item = new QGraphicsRectItem(rect);
    item->setPen(QPen(color_, thickness_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    return item;
}

void RectTool::keyPressEvent(QKeyEvent *event) {
    /*qDebug() << "Key pressed";
    if (event->key() == Qt::Key_Backspace) {
        rect = QRectF();
    }*/
}

void EllipseTool::keyPressEvent(QKeyEvent *event) {
    /*qDebug() << "Key pressed";
    if (event->key() == Qt::Key_Backspace) {
        rect = QRectF();
    }*/
}

void EllipseTool::mousePress(QMouseEvent *event, QGraphicsView* drawer) {
    rect.setTopLeft(event->pos());
    rect.setBottomRight(event->pos());
}

void EllipseTool::mouseMove(QMouseEvent *event, QGraphicsView* drawer) {
    rect.setBottomRight(event->pos());
}

void EllipseTool::mouseRelease(QMouseEvent *event, QGraphicsView* drawer) {
    rect.setBottomRight(event->pos());
}

void EllipseTool::painter(QPaintEvent *event, QGraphicsView* drawer) {
    QPainter painter(drawer->viewport());
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(color_, thickness_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(rect);
    // painter.fillRect(rect, Qt::blue);
}

QGraphicsItem* EllipseTool::createItem() {
    QGraphicsEllipseItem *item = new QGraphicsEllipseItem(rect);
    item->setPen(QPen(color_, thickness_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    return item;
}


void LineTool::mousePress(QMouseEvent *event, QGraphicsView* drawer) {
    line.setP1(event->pos());
    line.setP2(event->pos());
}

void LineTool::mouseMove(QMouseEvent *event, QGraphicsView* drawer) {
    line.setP2(event->pos());
}

void LineTool::mouseRelease(QMouseEvent *event, QGraphicsView* drawer) {
    line.setP2(event->pos());
}

void LineTool::painter(QPaintEvent *event, QGraphicsView* drawer) {
    QPainter painter(drawer->viewport());
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(color_, thickness_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Qt::NoBrush);
    painter.drawLine(line);
}

QGraphicsItem* LineTool::createItem() {
    QGraphicsLineItem *item = new QGraphicsLineItem(line);
    item->setPen(QPen(color_, thickness_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    return item;
}

void LineTool::keyPressEvent(QKeyEvent *event) {
    /*qDebug() << "Key pressed";
    if (event->key() == Qt::Key_Backspace) {
        rect = QRectF();
    }*/
}

void TriangleTool::keyPressEvent(QKeyEvent *event) {
    /*qDebug() << "Key pressed";
    if (event->key() == Qt::Key_Backspace) {
        rect = QRectF();
    }*/
}

void TriangleTool::mousePress(QMouseEvent *event, QGraphicsView* drawer) {
    boundingRect.setTopLeft(event->pos());
    boundingRect.setBottomRight(event->pos());
}

void TriangleTool::mouseMove(QMouseEvent *event, QGraphicsView* drawer) {
    boundingRect.setBottomRight(event->pos());
}

void TriangleTool::mouseRelease(QMouseEvent *event, QGraphicsView* drawer) {
    boundingRect.setBottomRight(event->pos());
}

void TriangleTool::painter(QPaintEvent *event, QGraphicsView* drawer) {
    QPainter painter(drawer->viewport());
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(color_, thickness_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Qt::NoBrush);
    painter.drawPolygon(QPolygonF() << (boundingRect.topLeft() + boundingRect.topRight())/2 <<boundingRect.bottomRight() << boundingRect.bottomLeft());
}

QGraphicsItem* TriangleTool::createItem() {
    QGraphicsPolygonItem *item = new QGraphicsPolygonItem(QPolygonF() << (boundingRect.topLeft() + boundingRect.topRight())/2 <<boundingRect.bottomRight() << boundingRect.bottomLeft());
    item->setPen(QPen(color_, thickness_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    return item;
}

void PolyTool::mousePress(QMouseEvent *event, QGraphicsView* drawer) {
    if (event->button()==Qt::RightButton) {
        finished = true;
    }
    poly << event->pos();
}

void PolyTool::mouseMove(QMouseEvent *event, QGraphicsView* drawer) {
    return;
}

void PolyTool::mouseRelease(QMouseEvent *event, QGraphicsView* drawer) {
    return;
}

void PolyTool::painter(QPaintEvent *event, QGraphicsView* drawer) {
    if (finished) {
        QPainter painter(drawer->viewport());
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(color_, thickness_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.setBrush(Qt::NoBrush);
        painter.drawPolygon(poly);
        poly.clear();
    }

}

QGraphicsItem* PolyTool::createItem() {
    if (finished) {
        QGraphicsPolygonItem *item = new QGraphicsPolygonItem(poly);
        item->setPen(QPen(color_, thickness_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        return item;
    }
    return nullptr;
}

void PolyTool::keyPressEvent(QKeyEvent *event) {
    // if (event->key() == Qt::Key_Backspace) {
    //     poly.clear();
    //     finished = false;
    // }
}

void TextTool::mousePress(QMouseEvent *event, QGraphicsView* drawer) {
    text = "";
    textCursor = event->pos();
}

void TextTool::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Key pressed";
    if (event->key() == Qt::Key_Backspace) {
        text = text.left(text.size()-1);
    }
    else {
        text += event->text();
        repaint();
    }
    qDebug() << text;
    repaint();
}

void TextTool::mouseMove(QMouseEvent *event, QGraphicsView* drawer) {
    return;
}

void TextTool::mouseRelease(QMouseEvent *event, QGraphicsView* drawer) {
    return;
}

void TextTool::painter(QPaintEvent *event, QGraphicsView* drawer) {
    QPainter painter(drawer->viewport());
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(color_, thickness_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Qt::NoBrush);
    painter.drawText(textCursor, text);
    qDebug()<<"from painter " << text;
}

QGraphicsItem* TextTool::createItem() {
    QGraphicsTextItem *item = new QGraphicsTextItem();
    item->setPos(textCursor);
    qDebug() << "From create item "<<text;
    item->setPlainText(text);
    item->setDefaultTextColor(color_);
    item->setFont(QFont("Arial", thickness_));
    return item;
}










