#include "Menu.h"

Menu::Menu(QWidget *parent) : QMenuBar(parent) {
    addAction("&File");
    addAction("&Edit");
    addAction("&View");
    addAction("&Help");
}
