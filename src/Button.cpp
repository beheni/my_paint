#include "Button.h"

Button::Button(QWidget *parent) : QToolButton(parent) {
    setIconSize(QSize(50, 50));
    setAutoRaise(true);
    setCheckable(true);
    setAutoExclusive(true);
}

Tool* Button::tool(){
    return tool_;
}

void Button::setTool(Tool *tool){
    tool_ = tool;
}
