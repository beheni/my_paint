#ifndef MY_PAINT_LAYER_H
#define MY_PAINT_LAYER_H
#include <vector>
#include <optional>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>
#include "Curve.h"

class Layer: public QWidget{
    Q_OBJECT
public:
    explicit Layer(QWidget *parent = nullptr);
    std::vector<Curve> curves;
    std::optional<Curve> activeCurve;

public:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    // void resizeEvent(QResizeEvent *event) override;
    // void update();
private:
    bool drawing;
    QPainterPath path;
};
#endif //MY_PAINT_LAYER_H
