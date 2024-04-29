#ifndef MY_PAINT_MENU_H
#define MY_PAINT_MENU_H
#include <QMenuBar>

class Menu : public QMenuBar {
    Q_OBJECT
public:
    Menu(QWidget *parent = nullptr);
};
#endif //MY_PAINT_MENU_H
