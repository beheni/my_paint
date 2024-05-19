#ifndef LAYERBAR_H
#define LAYERBAR_H

#include <QToolBar>
#include <LayerWidget.h>

class LayerBar: public QToolBar{
    Q_OBJECT
    LayerWidget* layerWidget_;
public:
    LayerBar(QWidget *parent = nullptr);
    ~LayerBar() override = default;
    LayerWidget* layerWidget();

};

#endif // LAYERBAR_H
