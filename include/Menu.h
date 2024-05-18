#ifndef MY_PAINT_MENU_H
#define MY_PAINT_MENU_H
#include <QMenu>
#include <QMenuBar>
#include "Canvas.h"

class MenuBar : public QMenuBar {
    Q_OBJECT
    Canvas *canvas;

public slots:
    void onSave();
    void onOpen();
public:
    explicit MenuBar(QWidget *parent = nullptr);
    void setCanvas(Canvas *canvas);
};

class Menu : public QMenu{
    Q_OBJECT

public:
    explicit Menu(const QString &title, QWidget *parent = nullptr);
    ~Menu() override = default;
};


#endif //MY_PAINT_MENU_H
