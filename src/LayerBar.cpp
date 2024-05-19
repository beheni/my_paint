#include "LayerBar.h"
#include <QColorDialog>
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
    colorPicker_->setCurrentColor(QColor(0, 0, 0));

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

    addLayer_ = new QPushButton("Add Layer", this);
    removeLayer_ = new QPushButton("Remove Layer", this);
    upLayer_ = new QPushButton("Up Layer", this);
    downLayer_ = new QPushButton("Down Layer", this);

    layout->addWidget(addLayer_);
    layout->addWidget(removeLayer_);
    layout->addWidget(upLayer_);
    layout->addWidget(downLayer_);
    layerGroup->setLayout(layout);

    layerWidget_ = new LayerWidget(this);

    addWidget(colorPicker_);
    addWidget(sliderGroup);
    addWidget(layerGroup);
    addWidget(layerWidget_);

}

LayerWidget* LayerBar::layerWidget(){
    return layerWidget_;
}

QColorDialog* LayerBar::colorPicker(){
    return colorPicker_;
}

QPushButton* LayerBar::addLayer(){
    return addLayer_;
}

QPushButton* LayerBar::removeLayer(){
    return removeLayer_;
}

QPushButton* LayerBar::upLayer(){
    return upLayer_;
}

QPushButton* LayerBar::downLayer(){
    return downLayer_;
}
QSlider* LayerBar::thicknessSlider() {
    return thicknessSlider_;
}
