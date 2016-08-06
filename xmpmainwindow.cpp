#include "xmpmainwindow.h"
#include "ui_xmpmainwindow.h"

XMPMainWindow::XMPMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::XMPMainWindow)
{
    ui->setupUi(this);
}

XMPMainWindow::~XMPMainWindow()
{
    delete ui;
}
