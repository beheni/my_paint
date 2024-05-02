#include "Menu.h"
#include <QSize>
#include <QAction>
#include <QDebug>
#include <QMessageBox>
#include <QSvgGenerator>

MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent) {
    Menu *file = new Menu("&File");
    file->addAction("New");
    file->addAction("Open");

    QAction* saveAction = file->addAction("Save");
    connect(saveAction, &QAction::triggered, this, &MenuBar::onSave);

    file->addSeparator();
    file->addAction("Exit");
    Menu *edit = new Menu("&Edit");
    Menu *view = new Menu("&View");
    Menu *help = new Menu("&Help");

    addMenu(file);
    addMenu(edit);
    addMenu(view);
    addMenu(help);

}

void MenuBar::setCanvas(Canvas *canvas_) {
    canvas = canvas_;
}


Menu::Menu(const QString &title, QWidget *parent) : QMenu(title, parent) {}

void MenuBar::onSave() {
    // QMessageBox* popup = new QMessageBox(this);
    // popup->setText("Save");
    // popup->show();
    QSvgGenerator generator;
    generator.setFileName("canvas.svg");
    qDebug() << canvas->sceneRect();
    qDebug() << canvas->height() << " " << canvas->width();

    generator.setSize(QSize(800, 600));
    generator.setViewBox(QRect(0, 0, 800, 600)); //size to be changed
    QPainter painter;
    painter.begin(&generator);
    canvas->render(&painter);
    painter.end();
}
