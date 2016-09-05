/*\
|*|  Copyright 2016-2017 Sonu Lohani <sonulohani@gmail.com>
|*|
|*|  This file is part of the XMPMusicPlayer program.
|*|
|*|  AvCaster is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU Lesser General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  AvCaster is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU Lesser General Public License for more details.
|*|
|*|  You should have received a copy of the GNU Lesser General Public License
|*|  along with AvCaster.  If not, see <http://www.gnu.org/licenses/>.
\*/

#include "XMPMainWindow.h"
#include "ui_xmpmainwindow.h"
#include <XMPHelperClass.h>
#include <macros.h>
#include <XMPPlaylist.h>
#include <XMPMediaPlayer.h>
#include <XMPVolumeSlider.h>

// Qt includes
#include <QFileDialog>
#include <QDir>
#include <QFocusEvent>
#include <qdebug.h>
#include <QPoint>
#include <QMediaPlaylist>

// Private namespace
namespace {
	const QString audioExtensionFilters = "Media ( *.mp3 *.aac )";
	const QString previousPushButtonIconFilePath = ":/controls/resources/icons/previous_icon_small.png";
	const QString playPushButtonIconFilePath = ":/controls/resources/icons/play_icon_small.png";
	const QString stopPushButtonIconFilePath = ":/controls/resources/icons/stop_icon_small.png";
	const QString pausePushButtonIconFilePath = ":/controls/resources/icons/pause_icon_small.png";
	const QString nextPushButtonIconFilePath = ":/controls/resources/icons/next_icon_small.png";
	const QString volumePushButtonIconFilePath = ":/controls/resources/icons/fullVolume_icon_small.png";
	const QString shufflePushButtonIconFilePath = ":/controls/resources/icons/shuffle_icon_small.png";
	const QString repeatPushButtonIconFilePath = ":/controls/resources/icons/repeat_icon_small.png";
	const QString mediumVolumePushButtonIconFilePath = ":/controls/resources/icons/mediumVolume_icon_small.png";
	const QString muteVolumePushButtonIconFilePath = ":/controls/resources/icons/mute_icon_small.png";
}

namespace xmp {
	namespace ui {
		XMPMainWindow::XMPMainWindow(QWidget *parent) :
			QMainWindow(parent),
			ui(new Ui::XMPMainWindow),
			m_pPlaylistWindow(nullptr),
			m_state(STATE::STOP)
		{
			ui->setupUi(this);
			initUI();
			initComponent();

			XMP_VALIDATE(connect(ui->actionExit, SIGNAL(triggered()), SLOT(close())));
			XMP_VALIDATE(connect(ui->actionOpen_media, SIGNAL(triggered(bool)), SLOT(openMediaFiles())));
			XMP_VALIDATE(connect(ui->actionPlaylist, SIGNAL(triggered(bool)), SLOT(openPlaylist())));
			XMP_VALIDATE(connect(m_pPlaylistWindow, SIGNAL(mediaFilesChanged(bool)), SLOT(updateUIState(bool))));
			XMP_VALIDATE(connect(ui->openMediaButton, SIGNAL(clicked()), SLOT(openMediaFiles())));
			XMP_VALIDATE(connect(ui->playPushButton, SIGNAL(clicked()), SLOT(onPlayButtonClicked())));
			XMP_VALIDATE(connect(ui->actionPlay, SIGNAL(triggered()), SLOT(onPlayButtonClicked())));
			XMP_VALIDATE(connect(ui->nextPushButton, SIGNAL(clicked()), SLOT(onNextButtonClicked())));
			XMP_VALIDATE(connect(ui->previousPushButton, SIGNAL(clicked()), SLOT(onPrevButtonClicked())));
			XMP_VALIDATE(connect(ui->volumePushButton, SIGNAL(clicked()), SLOT(onVolumeButtonClicked())));
			XMP_VALIDATE(connect(m_pVolumeSlider, SIGNAL(valueChanged(int)), this, SLOT(changeVolume(int))));
		}

		XMPMainWindow::~XMPMainWindow()
		{
			m_pVolumeSlider->deleteLater();
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

			m_pVolumeSlider = new XMPVolumeSlider;
		}

		void XMPMainWindow::initComponent()
		{
			m_pPlaylistWindow = new XMPPlaylist(this);
			m_pMediaPlayer = new multimedia::XMPMediaPlayer(this);
		}

		void XMPMainWindow::updateUIState(bool isEnabled)
		{
			m_state = STATE::STOP;
			ui->previousPushButton->setEnabled(isEnabled);
			ui->playPushButton->setEnabled(isEnabled);
			ui->nextPushButton->setEnabled(isEnabled);
			ui->shufflePushButton->setEnabled(isEnabled);
			ui->repeatPushButton->setEnabled(isEnabled);
		}

		void XMPMainWindow::openMediaFiles()
		{
			QStringList mediaFiles = QFileDialog::getOpenFileNames(this, "Open Media Files", QDir::home().dirName(), audioExtensionFilters);
			if (!mediaFiles.isEmpty())
			{
				m_pPlaylistWindow->addFilesToPlaylist(mediaFiles);
				updateUIState(true);
			}
		}

		void XMPMainWindow::openPlaylist()
		{
			m_pPlaylistWindow->show();
		}

		void XMPMainWindow::onPlayButtonClicked()
		{
			if ((m_state == STATE::PAUSE) || (m_state == STATE::STOP))
			{
				if (m_state != STATE::PAUSE) {
					QMediaPlaylist *pPlaylist = m_pPlaylistWindow->playlist();
					if (pPlaylist->currentIndex() == -1)
					{
						pPlaylist->setCurrentIndex(0);
					}
					m_pMediaPlayer->setMedia(pPlaylist->media(pPlaylist->currentIndex()));
					ui->finishTimeLabel->setText(QString::number(m_pMediaPlayer->duration()));
				}
				m_pMediaPlayer->play();
				ui->playPushButton->setIcon(QIcon(pausePushButtonIconFilePath));
				m_state = STATE::PLAY;
			}
			else
			{
				ui->playPushButton->setIcon(QIcon(playPushButtonIconFilePath));
				m_pMediaPlayer->pause();
				m_state = STATE::PAUSE;
			}
		}
		void XMPMainWindow::onNextButtonClicked()
		{
			m_state = STATE::STOP;
			QMediaPlaylist *pPlaylist = m_pPlaylistWindow->playlist();
			pPlaylist->next();
			onPlayButtonClicked();
		}
		void XMPMainWindow::onPrevButtonClicked()
		{
			m_state = STATE::STOP;
			QMediaPlaylist *pPlaylist = m_pPlaylistWindow->playlist();
			pPlaylist->previous();
			onPlayButtonClicked();
		}
		void XMPMainWindow::onVolumeButtonClicked()
		{
			m_pVolumeSlider->setValue(m_pMediaPlayer->volume());
			m_pVolumeSlider->move(mapToParent( QPoint( ui->volumePushButton->x() - 50, ui->volumePushButton->y() + 15 )));
			m_pVolumeSlider->show();
			m_pVolumeSlider->setFocus();
		}
		void XMPMainWindow::changeVolume(int value)
		{
			m_pMediaPlayer->setVolume(value);

			if (value == 0)
			{
				ui->volumePushButton->setIcon(QIcon(muteVolumePushButtonIconFilePath));
			}
			else if (value < 60)
			{
				ui->volumePushButton->setIcon(QIcon(mediumVolumePushButtonIconFilePath));
			}
			else
			{
				ui->volumePushButton->setIcon(QIcon(volumePushButtonIconFilePath));
			}
		}
	}
}