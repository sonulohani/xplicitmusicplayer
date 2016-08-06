#include "xmpmainwindow.h"
#include "ui_xmpmainwindow.h"
#include <xmphelperclass.h>

XMPMainWindow::XMPMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::XMPMainWindow)
{
	ui->setupUi(this);
    xmp::helper::XMPHelperClass::setStandardControlButtonSettings( ui->previousPushButton );
    xmp::helper::XMPHelperClass::setStandardControlButtonSettings( ui->playPushButton );
    xmp::helper::XMPHelperClass::setStandardControlButtonSettings( ui->nextPushButton );
    xmp::helper::XMPHelperClass::setStandardControlButtonSettings( ui->volumePushButton );
    xmp::helper::XMPHelperClass::setStandardControlButtonSettings( ui->shufflePushButton );
    xmp::helper::XMPHelperClass::setStandardControlButtonSettings( ui->repeatPushButton );
}

XMPMainWindow::~XMPMainWindow()
{
	delete ui;
}

