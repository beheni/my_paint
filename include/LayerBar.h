#ifndef LAYERBAR_H
#define LAYERBAR_H

#include <QToolBar>
#include <QSlider>
#include <LayerWidget.h>
#include <QColorDialog>
#include <QGroupBox>
#include <QPushButton>
#include <QHBoxLayout>


class LayerBar: public QToolBar{
    Q_OBJECT
    LayerWidget* layerWidget_;
    QColorDialog* colorPicker_;
    QSlider* thicknessSlider_;
    QPushButton* addLayer_;
    QPushButton* removeLayer_;
    QPushButton* upLayer_;
    QPushButton* downLayer_;

public:
    LayerBar(QWidget *parent = nullptr);
    ~LayerBar() override = default;
    LayerWidget* layerWidget();
    QColorDialog* colorPicker();
    QPushButton* addLayer();
    QPushButton* removeLayer();
    QPushButton* upLayer();
    QPushButton* downLayer();
};

#endif // LAYERBAR_H
