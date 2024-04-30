#ifndef MY_PAINT_LAYER_H
#define MY_PAINT_LAYER_H
#include <vector>
#include <optional>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>
#include "Curve.h"
class Layer: QWidget{
    Q_OBJECT
public:
    Layer(QWidget *parent = nullptr);
    std::vector<Curve> curves;
    std::optional<Curve> activeCurve;
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    bool drawing;
    QPainterPath path;
};
#endif //MY_PAINT_LAYER_H
