#include "xmpmainwindow.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// Mainly for shuffle functionality
	qsrand(QTime::currentTime().msec());

	xmp::ui::XMPMainWindow w;
	w.show();

	return a.exec();
}