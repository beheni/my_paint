#ifndef MY_PAINT_LAYER_H
#define MY_PAINT_LAYER_H
#include <QGraphicsItemGroup>

class Layer: public QGraphicsItemGroup{
    QString name;
public:
    Layer(QGraphicsItem* parent = nullptr);
    ~Layer() override = default;

    QString getName();
    void setName(const QString& name);

    void addBatch(QList<QGraphicsItem*> items);
    void removeBatch(QList<QGraphicsItem*> items);
public slots:
    void onCreate();
};

#endif //MY_PAINT_LAYER_H
