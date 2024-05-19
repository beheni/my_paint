#include "Menu.h"
#include <QSize>
#include <QAction>
#include <QDebug>
#include <QMessageBox>
#include <QSvgGenerator>
#include <QFileDialog>
#include <QGraphicsPixmapItem>

MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent) {
    Menu *file = new Menu("&File");
    newAction_ = file->addAction("New");
    newAction_->setShortcut(QKeySequence::New);

    openAction_ = file->addAction("Open");
    openAction_->setShortcut(QKeySequence::Open);

    saveAction_ = file->addAction("Save");
    saveAction_->setShortcut(QKeySequence::Save);

    file->addSeparator();
    exitAction_ = file->addAction("Exit");
    exitAction_->setShortcut(QKeySequence::Quit);

    Menu *edit = new Menu("&Edit");
    undoAction_ = edit->addAction("Undo");
    undoAction_->setShortcut(QKeySequence::Undo);

    redoAction_ = edit->addAction("Redo");
    redoAction_->setShortcut(QKeySequence::Redo);
    edit->addSeparator();

    cutAction_ = edit->addAction("Cut");
    cutAction_->setShortcut(QKeySequence::Cut);

    copyAction_ = edit->addAction("Copy");
    copyAction_->setShortcut(QKeySequence::Copy);

    pasteAction_ = edit->addAction("Paste");
    pasteAction_->setShortcut(QKeySequence::Paste);

    Menu *view = new Menu("&View");
    zoomInAction_ = view->addAction("Zoom In");
    zoomInAction_->setShortcut(QKeySequence::ZoomIn);
    zoomOutAction_ = view->addAction("Zoom Out");
    zoomOutAction_->setShortcut(QKeySequence::ZoomOut);
    zoomResetAction_ = view->addAction("Zoom Reset");

    Menu *help = new Menu("&Help");
    helpAction_ = help->addAction("About");

    addMenu(file);
    addMenu(edit);
    addMenu(view);
    addMenu(help);

}
Menu::Menu(const QString &title, QWidget *parent) : QMenu(title, parent) {}


QAction *MenuBar::exitAction() {
    return exitAction_;
}

QAction *MenuBar::openAction() {
    return openAction_;
}

QAction *MenuBar::saveAction() {
    return saveAction_;
}

QAction *MenuBar::newAction() {
    return newAction_;
}

QAction *MenuBar::helpAction() {
    return helpAction_;
}




