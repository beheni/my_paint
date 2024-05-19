#include "LayerBar.h"
#include <QColorDialog>
#include <QButtonGroup>
#include <QGroupBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <LayerWidget.h>

LayerBar::LayerBar(QWidget *parent): QToolBar(parent){
    setWindowTitle("LayerBar");
    setMovable(false);
    setFloatable(false);
    setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);
    setOrientation(Qt::Vertical);

    colorPicker_ = new QColorDialog(this);
    colorPicker_->setOption(QColorDialog::NoButtons);

    thicknessSlider_ = new QSlider();
    thicknessSlider_->setFocusPolicy(Qt::StrongFocus);

    QGroupBox* group = new QGroupBox("Layers", this);
    QHBoxLayout* layout = new QHBoxLayout(group);

    QPushButton* addLayer = new QPushButton("Add Layer", this);
    QPushButton* removeLayer = new QPushButton("Remove Layer", this);
    QPushButton* upLayer = new QPushButton("Up Layer", this);
    QPushButton* downLayer = new QPushButton("Down Layer", this);

    layout->addWidget(addLayer);
    layout->addWidget(removeLayer);
    layout->addWidget(upLayer);
    layout->addWidget(downLayer);
    group->setLayout(layout);

    layerWidget_ = new LayerWidget(this);

    addWidget(colorPicker_);
    addWidget(thicknessSlider_);
    addWidget(group);
    addWidget(layerWidget_);

}

LayerWidget* LayerBar::layerWidget(){
    return layerWidget_;
}

QColorDialog* LayerBar::colorPicker(){
    return colorPicker_;
}
