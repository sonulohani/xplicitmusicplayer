#include "xmpmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XMPMainWindow w;
    w.show();

    return a.exec();
}
