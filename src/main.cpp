// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <QApplication>
#include <QPushButton>
#include "MainWindow.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    MainWindow w;
    w.showMaximized();

    return QApplication::exec();
}
