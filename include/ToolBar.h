#ifndef MY_PAINT_TOOLBAR_H
#define MY_PAINT_TOOLBAR_H

#include <QToolBar>
class ToolBar: public QToolBar{
    Q_OBJECT
public:
    ToolBar(QWidget *parent = nullptr);
    ~ToolBar() override = default;

private slots:
    void onSelection();
    void onBezier();
};
#endif //MY_PAINT_TOOLBAR_H
