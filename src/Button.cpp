#include "Button.h"

Button::Button(QWidget *parent) : QToolButton(parent) {
    setIconSize(QSize(50, 50));
    setAutoRaise(true);
    setCheckable(true);
    setAutoExclusive(true);
}
