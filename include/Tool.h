#ifndef MY_PAINT_TOOL_H
#define MY_PAINT_TOOL_H

#include <QSet>
#include <QWidget>
#include <QColor>
#include <QMouseEvent>
#include <QPainterPath>
#include <QGraphicsItem>

class Canvas;
class Layer;

class Tool: public QWidget{
    Q_OBJECT
protected:
    QColor color_;
    int thickness_;
public:
    explicit Tool();
    void setToolColor(const QColor& color);
    void setToolThickness(int thickness);
    void mousePressCallback(QMouseEvent *event, Canvas* drawer);
    void mouseMoveCallback(QMouseEvent *event,  Canvas* drawer);
    void mouseReleaseCallback(QMouseEvent *event, Canvas* drawer);
    void keyPressCallback(QKeyEvent *event);
    void paint(QPaintEvent *event, Canvas* drawer);
    QGraphicsItem* newItem();
protected:
    virtual void mousePress(QMouseEvent *event, Canvas* drawer) = 0;
    virtual void mouseMove(QMouseEvent *event, Canvas* drawer) = 0;
    virtual void mouseRelease(QMouseEvent *event, Canvas* drawer) = 0;
    virtual void painter(QPaintEvent *event, Canvas* drawer) = 0;
    virtual void keyPress(QKeyEvent *event) = 0;
    virtual QGraphicsItem* createItem() = 0;
};

class SelectionTool: public Tool{
    Q_OBJECT
    QPointF start;
    QPointF end;
    QSet<QGraphicsItem*> selectedItems;
    Layer* currentLayer;
    QGraphicsItem* lastSelectionBoundary;
    QPointF moveStart;
protected:
    void mousePress(QMouseEvent *event, Canvas* drawer) override;
    void mouseMove(QMouseEvent *event, Canvas* drawer) override;
    void mouseRelease(QMouseEvent *event, Canvas* drawer) override;
    void painter(QPaintEvent *event, Canvas* drawer) override;
    void keyPress(QKeyEvent *event) override;

    QGraphicsItem* createItem() override;
};

class DrawerTool: public Tool{
    Q_OBJECT
    QPainterPath path;
protected:
    void mousePress(QMouseEvent *event, Canvas* drawer) override;
    void mouseMove(QMouseEvent *event, Canvas* drawer) override;
    void mouseRelease(QMouseEvent *event, Canvas* drawer) override;
    void painter(QPaintEvent *event, Canvas* drawer) override;
    void keyPress(QKeyEvent *event) override;

    QGraphicsItem* createItem() override;
};

class RectTool: public Tool{
    Q_OBJECT
    QRectF rect;
protected:
    void mousePress(QMouseEvent *event, Canvas* drawer) override;
    void mouseMove(QMouseEvent *event, Canvas* drawer) override;
    void mouseRelease(QMouseEvent *event, Canvas* drawer) override;
    void painter(QPaintEvent *event, Canvas* drawer) override;
    void keyPress(QKeyEvent *event) override;

    QGraphicsItem* createItem() override;
};

class EllipseTool: public Tool{
    Q_OBJECT
    QRectF rect;
protected:
    void mousePress(QMouseEvent *event, Canvas* drawer) override;
    void mouseMove(QMouseEvent *event, Canvas* drawer) override;
    void mouseRelease(QMouseEvent *event, Canvas* drawer) override;
    void painter(QPaintEvent *event, Canvas* drawer) override;
    void keyPress(QKeyEvent *event) override;
    QGraphicsItem* createItem() override;
};

class LineTool: public Tool{
    Q_OBJECT
    QLineF line;
protected:
    void mousePress(QMouseEvent *event, Canvas* drawer) override;
    void mouseMove(QMouseEvent *event, Canvas* drawer) override;
    void mouseRelease(QMouseEvent *event, Canvas* drawer) override;
    void painter(QPaintEvent *event, Canvas* drawer) override;
    void keyPress(QKeyEvent *event) override;
    QGraphicsItem* createItem() override;
};

class TriangleTool: public Tool{
    Q_OBJECT
    QRectF boundingRect;
protected:
    void mousePress(QMouseEvent *event, Canvas* drawer) override;
    void mouseMove(QMouseEvent *event, Canvas* drawer) override;
    void mouseRelease(QMouseEvent *event, Canvas* drawer) override;
    void painter(QPaintEvent *event, Canvas* drawer) override;
    void keyPress(QKeyEvent *event) override;
    QGraphicsItem* createItem() override;
};

class PolyTool: public Tool{
    Q_OBJECT
    QPolygonF poly;
    bool finished = false;
    QPointF firstPoint;
    QPointF lastPoint;
protected:
    void mousePress(QMouseEvent *event, Canvas* drawer) override;
    void mouseMove(QMouseEvent *event, Canvas* drawer) override;
    void mouseRelease(QMouseEvent *event, Canvas* drawer) override;
    void painter(QPaintEvent *event, Canvas* drawer) override;
    void keyPress(QKeyEvent *event) override;
    QGraphicsItem* createItem() override;
};


class TextTool: public Tool{
    Q_OBJECT
    QString text;
    QPointF textCursor;
protected:
    void mousePress(QMouseEvent *event, Canvas* drawer) override;
    void mouseMove(QMouseEvent *event, Canvas* drawer) override;
    void mouseRelease(QMouseEvent *event, Canvas* drawer) override;
    void keyPress(QKeyEvent *event) override;
    void painter(QPaintEvent *event, Canvas* drawer) override;
    QGraphicsItem* createItem() override;
};
//fill

#endif //MY_PAINT_TOOL_H
