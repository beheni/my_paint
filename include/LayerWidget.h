#ifndef LAYERWIDGET_H
#define LAYERWIDGET_H

#include <QListWidget>
#include <QGraphicsScene>
#include <QListWidgetItem>
#include <QSize>

class LayerWidget : public QListWidget{
    Q_OBJECT
    QSize iconSize;
public:
    LayerWidget(QWidget *parent = nullptr);
    ~LayerWidget() override = default;
public slots:
    void itemAdded(QGraphicsItem* item);
};

class LayerWidgetItem: public QListWidgetItem{
    QGraphicsItem* item;
    QString name;
public:
    LayerWidgetItem(QListWidget* parent=nullptr);
    ~LayerWidgetItem() override = default;
    QGraphicsItem* getItem();
    QString getName();
    void setItem(QGraphicsItem* item);
    void setName(QString name);
};
#endif // LAYERWIDGET_H
