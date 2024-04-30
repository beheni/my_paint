#include "ToolBar.h"
#include "Button.h"
#include <QMessageBox>

ToolBar::ToolBar(QWidget *parent) : QToolBar(parent) {
    setOrientation(Qt::Vertical);
    setMovable(false);
    setFloatable(false);
    // toolbar->setAllowedAreas(Qt::LeftToolBarArea);
    Button *selection = new Button(this);
    connect(selection, &Button::clicked, this, &ToolBar::onSelection);
    Button *bezier = new Button(this);
    connect(bezier, &Button::clicked, this, &ToolBar::onBezier);
    Button *aand = new Button(this);
    Button *other = new Button(this);
    Button *BUTTons = new Button(this);

    // QVBoxLayout *layout = new QVBoxLayout(this);
    addWidget(selection);
    addWidget(bezier);
    addWidget(aand);
    addWidget(other);
    addWidget(BUTTons);
    // toolbar->show();
}

void ToolBar::onSelection(){
    QMessageBox* popup = new QMessageBox(this);
    popup->setText("Selection");
    popup->show();
}

void ToolBar::onBezier(){
    QMessageBox* popup = new QMessageBox(this);
    popup->setText("Bezier");
    popup->show();

}
