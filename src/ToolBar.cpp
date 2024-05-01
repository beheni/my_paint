#include "ToolBar.h"
#include "Button.h"
#include <QIcon>
#include <QMessageBox>

ToolBar::ToolBar(QWidget *parent) : QToolBar(parent) {
    setOrientation(Qt::Vertical);
    setMovable(false);
    setFloatable(false);

    Button *selection = new Button(this);
    connect(selection, &Button::clicked, this, &ToolBar::onSelection);
    selection->setIcon(QIcon("../my_paint/icons/select.png"));

    Button *line = new Button(this);
    connect(line, &Button::clicked, this, &ToolBar::onLine);
    line->setIcon(QIcon("../my_paint/icons/line.png"));

    Button *rect = new Button(this);
    connect(rect, &Button::clicked, this, &ToolBar::onRect);
    rect->setIcon(QIcon("../my_paint/icons/rect.png"));

    Button *triangle = new Button(this);
    connect(triangle, &Button::clicked, this, &ToolBar::onTriangle);
    triangle->setIcon(QIcon("../my_paint/icons/triangle.png"));

    Button *ellipse = new Button(this);
    connect(ellipse, &Button::clicked, this, &ToolBar::onEllipse);
    ellipse->setIcon(QIcon("../my_paint/icons/ellipse.png"));

    Button *poly = new Button(this);
    connect(poly, &Button::clicked, this, &ToolBar::onPoly);
    poly->setIcon(QIcon("../my_paint/icons/poly.png"));

    Button *text = new Button(this);
    connect(text, &Button::clicked, this, &ToolBar::onText);
    text->setIcon(QIcon("../my_paint/icons/text.png"));

    // QVBoxLayout *layout = new QVBoxLayout(this);
    addWidget(selection);
    addWidget(line);
    addWidget(rect);
    addWidget(triangle);
    addWidget(ellipse);
    addWidget(poly);
    addWidget(text);
}

void ToolBar::onSelection(){
    QMessageBox* popup = new QMessageBox(this);
    popup->setText("Selection");
    popup->show();
}

void ToolBar::onLine(){
    QMessageBox* popup = new QMessageBox(this);
    popup->setText("Line");
    popup->show();
}

void ToolBar::onRect(){
    QMessageBox* popup = new QMessageBox(this);
    popup->setText("Rectangle");
    popup->show();
}

void ToolBar::onTriangle(){
    QMessageBox* popup = new QMessageBox(this);
    popup->setText("Triangle");
    popup->show();
}

void ToolBar::onEllipse(){
    QMessageBox* popup = new QMessageBox(this);
    popup->setText("Ellipse");
    popup->show();
}

void ToolBar::onPoly(){
    QMessageBox* popup = new QMessageBox(this);
    popup->setText("Polygon");
    popup->show();
}

void ToolBar::onText(){
    QMessageBox* popup = new QMessageBox(this);
    popup->setText("Text");
    popup->show();
}


// void ToolBar::onBezier(){
//     QMessageBox* popup = new QMessageBox(this);
//     popup->setText("Bezier");
//     popup->show();

// }
