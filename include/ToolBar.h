#ifndef MY_PAINT_TOOLBAR_H
#define MY_PAINT_TOOLBAR_H

#include <QToolBar>
class ToolBar: public QToolBar{
    Q_OBJECT    
public:
    explicit ToolBar(QWidget *parent = nullptr);
    ~ToolBar() override = default;

private slots:
    void onSelection();
    // void onSelectionArea();
    void onLine();
    void onRect();
    void onTriangle();
    void onEllipse();
    void onPoly();
    void onText();
    // void onBezier(); //for later
};
#endif //MY_PAINT_TOOLBAR_H
