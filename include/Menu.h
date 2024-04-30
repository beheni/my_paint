#ifndef MY_PAINT_MENU_H
#define MY_PAINT_MENU_H
#include <QMenuBar>

class MenuBar : public QMenuBar {
    Q_OBJECT
public:
    MenuBar(QWidget *parent = nullptr);
};

class Menu : public QMenu{
    Q_OBJECT
public:

    explicit Menu(const QString &title, QWidget *parent = nullptr);
    ~Menu() override = default;
};


#endif //MY_PAINT_MENU_H
