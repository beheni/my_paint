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
    QAction* exitAction = file->addAction("Exit");
    connect(exitAction, &QAction::triggered, this, &MenuBar::onExit);
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
    QSvgGenerator generator;
    generator.setFileName("canvas.svg");

    generator.setSize(canvas->size());
    generator.setViewBox(canvas->scene()->sceneRect()); //size to be changed
    QPainter painter;
    painter.begin(&generator);
    canvas->render(&painter);
    painter.end();
}

void MenuBar::onExit() {
    QMessageBox::StandardButton exit = QMessageBox::question(this, "Exit",
                                                               tr("Are you sure want to exit?\n"),
                                                               QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                               QMessageBox::Yes);
    if (exit==QMessageBox::Yes) {
        QApplication::quit();
    }
}
