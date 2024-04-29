#include <QPushButton>
#include "ToolBar.h"

ToolBar::ToolBar(QWidget *parent) : QToolBar(parent) {
    setOrientation(Qt::Vertical);
    setMovable(false);
    setFloatable(false);
    // toolbar->setAllowedAreas(Qt::LeftToolBarArea);
    QPushButton *button1 = new QPushButton("Button1");
    QPushButton *button2 = new QPushButton("Button2");
    QPushButton *button3 = new QPushButton("Button3");
    QPushButton *button4 = new QPushButton("Button4");
    QPushButton *button5 = new QPushButton("Button5");

    // QVBoxLayout *layout = new QVBoxLayout(this);
    addWidget(button1);
    addWidget(button2);
    addWidget(button3);
    addWidget(button4);
    addWidget(button5);
    // toolbar->show();
}
