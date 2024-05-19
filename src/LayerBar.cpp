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
    thicknessSlider_->setRange(1, 40);
    thicknessSlider_->setOrientation(Qt::Horizontal);
    thicknessSlider_->setSliderPosition(2);
    thicknessSlider_->setSingleStep(1);

    QGroupBox* sliderGroup = new QGroupBox("Tool Thickness", this);
    QHBoxLayout* layoutSlider = new QHBoxLayout(sliderGroup);
    layoutSlider->addWidget(thicknessSlider_);
    thicknessSlider_->setTickPosition(QSlider::TicksBothSides);
    thicknessSlider_->setTickInterval(1);


    QGroupBox* layerGroup = new QGroupBox("Layers", this);
    QHBoxLayout* layout = new QHBoxLayout(layerGroup);

    QPushButton* addLayer = new QPushButton("Add Layer", this);
    QPushButton* removeLayer = new QPushButton("Remove Layer", this);
    QPushButton* upLayer = new QPushButton("Up Layer", this);
    QPushButton* downLayer = new QPushButton("Down Layer", this);

    layout->addWidget(addLayer);
    layout->addWidget(removeLayer);
    layout->addWidget(upLayer);
    layout->addWidget(downLayer);
    layerGroup->setLayout(layout);

    layerWidget_ = new LayerWidget(this);

    addWidget(colorPicker_);
    addWidget(sliderGroup);
    // addWidget(thicknessSlider_);
    addWidget(layerGroup);
    addWidget(layerWidget_);

}

LayerWidget* LayerBar::layerWidget(){
    return layerWidget_;
}

QColorDialog* LayerBar::colorPicker(){
    return colorPicker_;
}

QSlider* LayerBar::thicknessSlider() {
    return thicknessSlider_;
}
