#ifndef LAYERBAR_H
#define LAYERBAR_H

#include <QToolBar>
#include <QSlider>
#include <LayerWidget.h>
#include <QColorDialog>

class LayerBar: public QToolBar{
    Q_OBJECT
    LayerWidget* layerWidget_;
    QColorDialog* colorPicker_;
    QSlider* thicknessSlider_;
public:
    LayerBar(QWidget *parent = nullptr);
    ~LayerBar() override = default;
    LayerWidget* layerWidget();
    QColorDialog* colorPicker();

};

#endif // LAYERBAR_H
