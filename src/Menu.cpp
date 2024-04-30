#include "Menu.h"

MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent) {
    Menu *file = new Menu("&File");
    file->addAction("New");
    file->addAction("Open");
    file->addAction("Save");
    file->addAction("Save As");
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


Menu::Menu(const QString &title, QWidget *parent) : QMenu(title, parent) {

}
