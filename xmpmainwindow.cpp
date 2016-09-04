#include "XMPMainWindow.h"
#include "ui_xmpmainwindow.h"
#include <XMPHelperClass.h>
#include <macros.h>
#include <XMPPlaylist.h>
#include <XMPMediaPlayer.h>

// Qt includes
#include <QFileDialog>
#include <QDir>

// Private namespace
namespace {
	const QString audioExtensionFilters = "Media ( *.mp3 *.aac )";
	const QString previousPushButtonIconFilePath = ":/controls/resources/icons/previous_icon_small.png";
	const QString playPushButtonIconFilePath = ":/controls/resources/icons/play_icon_small.png";
	const QString nextPushButtonIconFilePath = ":/controls/resources/icons/next_icon_small.png";
	const QString volumePushButtonIconFilePath = ":/controls/resources/icons/fullVolume_icon_small.png";
	const QString shufflePushButtonIconFilePath = ":/controls/resources/icons/shuffle_icon_small.png";
	const QString repeatPushButtonIconFilePath = ":/controls/resources/icons/repeat_icon_small.png";
}

namespace xmp {
	namespace ui {
		XMPMainWindow::XMPMainWindow(QWidget *parent) :
			QMainWindow(parent),
			ui(new Ui::XMPMainWindow),
			m_pPlaylistWindow(nullptr)
		{
			ui->setupUi(this);
			initUI();
			initComponent();

			XMP_VALIDATE(connect(ui->actionExit, SIGNAL(triggered()), SLOT(close())));
			XMP_VALIDATE(connect(ui->actionOpen_media, SIGNAL(triggered(bool)), SLOT(openMediaFiles())));
			XMP_VALIDATE(connect(ui->actionPlaylist, SIGNAL(triggered(bool)), SLOT(openPlaylist())));
			XMP_VALIDATE(connect(m_pPlaylistWindow, SIGNAL(mediaFilesChanged(bool)), SLOT(updateUIState(bool))));
			XMP_VALIDATE(connect(ui->openMediaButton, SIGNAL(clicked()), SLOT(openMediaFiles())));
		}

		XMPMainWindow::~XMPMainWindow()
		{
			delete ui;
		}

		void XMPMainWindow::initUI()
		{
			xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->previousPushButton, previousPushButtonIconFilePath);
			xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->playPushButton, playPushButtonIconFilePath);
			xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->nextPushButton, nextPushButtonIconFilePath);
			xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->volumePushButton, volumePushButtonIconFilePath, true);
			xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->shufflePushButton, shufflePushButtonIconFilePath);
			xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->repeatPushButton, repeatPushButtonIconFilePath);

			ui->albumLabel->hide();
			ui->artistLabel->hide();
			ui->songNameLabel->hide();
			ui->bitrateLabel->hide();
		}

		void XMPMainWindow::initComponent()
		{
			m_pPlaylistWindow = new XMPPlaylist(this);
			m_pMediaPlayer = new multimedia::XMPMediaPlayer(this);
		}

		void XMPMainWindow::updateUIState(bool isEnabled)
		{
			ui->previousPushButton->setEnabled(isEnabled);
			ui->playPushButton->setEnabled(isEnabled);
			ui->nextPushButton->setEnabled(isEnabled);
			ui->shufflePushButton->setEnabled(isEnabled);
			ui->repeatPushButton->setEnabled(isEnabled);
		}

		void XMPMainWindow::openMediaFiles()
		{
			m_mediaFiles = QFileDialog::getOpenFileNames(this, "Open Media Files", QDir::home().dirName(), audioExtensionFilters);
			if (!m_mediaFiles.isEmpty())
			{
				m_pPlaylistWindow->addFilesToPlaylist(m_mediaFiles);
				updateUIState(true);
			}
			// Dummy statement. Remove it after test
			m_pMediaPlayer->setFileToPlay(m_mediaFiles[0]);
			m_pMediaPlayer->play();
		}

		void XMPMainWindow::openPlaylist()
		{
			m_pPlaylistWindow->show();
		}
	}
}