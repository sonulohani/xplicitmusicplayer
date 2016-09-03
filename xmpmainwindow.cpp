#include "xmpmainwindow.h"
#include "ui_xmpmainwindow.h"
#include <xmphelperclass.h>
#include <macros.h>
#include <xmpplaylist.h>

// Qt includes
#include <QFileDialog>
#include <QDir>

// Private namespace
namespace {
	const QString audioExtensionFilters = "Media ( *.mp3 *.aac )";
}

namespace xmp {
	namespace ui {
		XMPMainWindow::XMPMainWindow(QWidget *parent) :
			QMainWindow(parent),
			ui(new Ui::XMPMainWindow),
			m_pPlaylistWindow(nullptr)
		{
			ui->setupUi(this);
			init();
			initComponent();

			xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->previousPushButton);
			xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->playPushButton);
			xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->nextPushButton);
			xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->volumePushButton);
			xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->shufflePushButton);
			xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->repeatPushButton);

			XMP_VALIDATE(connect(ui->actionExit, SIGNAL(triggered()), SLOT(close())));
			XMP_VALIDATE(connect(ui->actionOpen_media, SIGNAL(triggered(bool)), SLOT(openMediaFiles())));
			XMP_VALIDATE(connect(ui->actionPlaylist, SIGNAL(triggered(bool)), SLOT(openPlaylist())));
			XMP_VALIDATE(connect(ui->openMediaButton, SIGNAL(clicked()), SLOT(openMediaFiles())));
		}

		XMPMainWindow::~XMPMainWindow()
		{
			delete ui;
		}

		void XMPMainWindow::init()
		{
			ui->albumLabel->hide();
			ui->artistLabel->hide();
			ui->songNameLabel->hide();
			ui->bitrateLabel->hide();
		}

		void XMPMainWindow::initComponent()
		{
			m_pPlaylistWindow = new XMPPlaylist(this);
		}

		void XMPMainWindow::openMediaFiles()
		{
			m_mediaFiles = QFileDialog::getOpenFileNames(this, "Open Media Files", QDir::home().dirName(), audioExtensionFilters);
			m_pPlaylistWindow->addFilesToPlaylist(m_mediaFiles);
		}

		void XMPMainWindow::openPlaylist()
		{
			m_pPlaylistWindow->show();
		}
	}
}