#ifndef XMPMAINWINDOW_H
#define XMPMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class XMPMainWindow;
}

class XMPMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit XMPMainWindow(QWidget *parent = 0);
    ~XMPMainWindow();

private:
    Ui::XMPMainWindow *ui;
};

#endif // XMPMAINWINDOW_H
