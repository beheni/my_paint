#ifndef MY_PAINT_MENU_H
#define MY_PAINT_MENU_H
#include <QMenu>
#include <QMenuBar>
#include <QAction>

class Menu;

class MenuBar : public QMenuBar {
    Q_OBJECT
    QAction *openAction_;
    QAction *saveAction_;
    QAction *newAction_;
    QAction *exitAction_;
    QAction *undoAction_;
    QAction *redoAction_;
    QAction *cutAction_;
    QAction *copyAction_;
    QAction *pasteAction_;
    QAction *zoomInAction_;
    QAction *zoomOutAction_;
    QAction *zoomResetAction_;
    QAction *helpAction_;

    Menu* file;
    Menu* edit;
    Menu* view;
    Menu* help;

public:
    explicit MenuBar(QWidget *parent = nullptr);
    QAction *openAction();
    QAction *saveAction();
    QAction *newAction();
    QAction *exitAction();
    QAction *helpAction();

    Menu* getFileMenu();
    Menu* getEditMenu();
    Menu* getViewMenu();
    Menu* getHelpMenu();
};

class Menu : public QMenu{
    Q_OBJECT

public:
    explicit Menu(const QString &title, QWidget *parent = nullptr);
    ~Menu() override = default;
};


#endif //MY_PAINT_MENU_H
