#ifndef MY_PAINT_TOOL_H
#define MY_PAINT_TOOL_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainterPath>
#include <QGraphicsItem>


class Tool: public QWidget{
    Q_OBJECT
public:
    explicit Tool();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paint(QPaintEvent *event, QWidget* drawer);
    QGraphicsItem* newItem();
protected:
    virtual void mousePress(QMouseEvent *event) = 0;
    virtual void mouseMove(QMouseEvent *event) = 0;
    virtual void mouseRelease(QMouseEvent *event) = 0;
    virtual void painter(QPaintEvent *event, QWidget* drawer) = 0;
    virtual QGraphicsItem* createItem() = 0;
};

class DrawerTool: public Tool{
    Q_OBJECT
    QPainterPath path;
protected:
    void mousePress(QMouseEvent *event) override;
    void mouseMove(QMouseEvent *event) override;
    void mouseRelease(QMouseEvent *event) override;
    void painter(QPaintEvent *event, QWidget* drawer) override;
    QGraphicsItem* createItem() override;
};
#endif //MY_PAINT_TOOL_H
