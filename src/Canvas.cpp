#include "Canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent) {
    setStyleSheet("background-color: black;");
    setMinimumSize(400, 400);
}
