#include "ToolBar.h"
#include "Button.h"
#include <QIcon>
#include <QMessageBox>
#include "Canvas.h"

void ToolBar::setup(){
    Button *selection = new Button(this);
    selection->setTool(new SelectionTool());
    connect(selection, &Button::clicked, canvas, [this, selection](){canvas->onToolChange(selection->tool());});
    selection->setIcon(QIcon(":/select.png"));

    Button *brush = new Button(this);
    brush->setTool(new DrawerTool());
    connect(brush, &Button::clicked, canvas, [this, brush](){canvas->onToolChange(brush->tool());});
    brush->setIcon(QIcon(":/brush.png"));

    Button *line = new Button(this);
    line->setTool(new DrawerTool());
    connect(line, &Button::clicked, canvas, [this, line](){canvas->onToolChange(line->tool());});
    line->setIcon(QIcon(":/line.png"));

    Button *rect = new Button(this);
    rect->setTool(new RectTool());
    connect(rect, &Button::clicked, canvas, [this, rect](){canvas->onToolChange(rect->tool());});
    rect->setIcon(QIcon(":/rect.png"));

    Button *triangle = new Button(this);
    triangle->setTool(new DrawerTool());
    connect(triangle, &Button::clicked, canvas,  [this, triangle](){canvas->onToolChange(triangle->tool());});
    triangle->setIcon(QIcon(":/triangle.png"));

    Button *ellipse = new Button(this);
    ellipse->setTool(new DrawerTool());
    connect(ellipse, &Button::clicked, canvas,  [this, ellipse](){canvas->onToolChange(ellipse->tool());});
    ellipse->setIcon(QIcon(":/ellipse.png"));

    Button *poly = new Button(this);
    poly->setTool(new DrawerTool());
    connect(poly, &Button::clicked, canvas,  [this, poly](){canvas->onToolChange(poly->tool());});
    poly->setIcon(QIcon(":/poly.png"));

    Button *text = new Button(this);
    text->setTool(new DrawerTool());
    connect(text, &Button::clicked, canvas,  [this, text](){canvas->onToolChange(text->tool());});
    text->setIcon(QIcon(":/text.png"));

    // QVBoxLayout *layout = new QVBoxLayout(this);
    addWidget(selection);
    addWidget(brush);
    addWidget(line);
    addWidget(rect);
    addWidget(triangle);
    addWidget(ellipse);
    addWidget(poly);
    addWidget(text);
}

ToolBar::ToolBar(QWidget *parent) : QToolBar(parent) {
    setOrientation(Qt::Vertical);
    setMovable(false);
    setFloatable(false);


}
