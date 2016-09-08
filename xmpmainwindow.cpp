/*\
|*|  Copyright 2016-2017 Sonu Lohani <sonulohani@gmail.com>
|*|
|*|  This file is part of the XMPMusicPlayer program.
|*|
|*|  XplicitMusicPlayer is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU Lesser General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  XplicitMusicPlayer is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU Lesser General Public License for more details.
|*|
|*|  You should have received a copy of the GNU Lesser General Public License
|*|  along with XplicitMusicPlayer.  If not, see <http://www.gnu.org/licenses/>.
\*/

#include "XMPMainWindow.hpp"
#include "ui_xmpmainwindow.h"
#include <XMPHelperClass.hpp>
#include <macros.hpp>
#include <XMPPlaylist.hpp>
#include <XMPMediaPlayer.hpp>
#include <XMPVolumeSlider.hpp>

// Taglib includes
#include <id3v2tag.h>
#include <mpegfile.h>
#include <attachedpictureframe.h>
#include <id3v2frame.h>
#include <tlist.h>

// Qt includes
#include <QFileDialog>
#include <QDir>
#include <QFocusEvent>
#include <qdebug.h>
#include <QPoint>
#include <QGridLayout>
#include <QMediaPlaylist>
#include <QMediaMetaData>
#include <QVariant>
#include <QMessageBox>
#include <QByteArray>
#include <QResizeEvent>

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
	const QString stopPushButtoniconFilePath = ":/controls/resources/icons/stop_icon_small.png";
	const QString albumArtFilePath = ":/controls/resources/icons/dummy_album_art.jpg";
}

namespace xmp {
	namespace ui {
		XMPMainWindow::XMPMainWindow(QWidget *parent) :
			QMainWindow(parent),
			ui(new Ui::XMPMainWindow),
			m_pPlaylistWindow(nullptr) {
			ui->setupUi(this);
			initUI();
			initComponent();

			XMP_VALIDATE(connect(ui->actionExit, SIGNAL(triggered()), SLOT(close())));
			XMP_VALIDATE(connect(ui->actionOpen_media, SIGNAL(triggered(bool)), SLOT(openMediaFiles())));
			XMP_VALIDATE(connect(ui->actionPlaylist, SIGNAL(triggered(bool)), SLOT(openPlaylist())));
			XMP_VALIDATE(connect(ui->openMediaButton, SIGNAL(clicked()), SLOT(openMediaFiles())));
			XMP_VALIDATE(connect(ui->playPushButton, SIGNAL(clicked()), SLOT(onPlayButtonClicked())));
			XMP_VALIDATE(connect(ui->actionStop, SIGNAL(triggered()), SLOT(onStopButtonClicked())));
			XMP_VALIDATE(connect(ui->stopPushButton, SIGNAL(clicked()), SLOT(onStopButtonClicked())));
			XMP_VALIDATE(connect(ui->actionPlay, SIGNAL(triggered()), SLOT(onPlayButtonClicked())));
			XMP_VALIDATE(connect(ui->nextPushButton, SIGNAL(clicked()), SLOT(onNextButtonClicked())));
			XMP_VALIDATE(connect(ui->previousPushButton, SIGNAL(clicked()), SLOT(onPrevButtonClicked())));
			XMP_VALIDATE(connect(ui->volumePushButton, SIGNAL(clicked()), SLOT(onVolumeButtonClicked())));
			XMP_VALIDATE(connect(m_pVolumeSlider, SIGNAL(valueChanged(int)), SLOT(changeVolume(int))));
			XMP_VALIDATE(connect(m_pMediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), SLOT(onStateChanged(QMediaPlayer::State))));
			XMP_VALIDATE(connect(m_pMediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus))));
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
			xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->stopPushButton, stopPushButtonIconFilePath);
			xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->nextPushButton, nextPushButtonIconFilePath);
			xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->volumePushButton, volumePushButtonIconFilePath);
			xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->shufflePushButton, shufflePushButtonIconFilePath);
			xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->repeatPushButton, repeatPushButtonIconFilePath);

			ui->songNameLabel->setText("<b>Song :- </b>");
			ui->artistLabel->setText("<b>Artist :- </b>");
			ui->albumLabel->setText("<b>Album :- </b>");
			m_pVolumeSlider = new XMPVolumeSlider;
		}

		void XMPMainWindow::initComponent()
		{
			m_pPlaylistWindow = new XMPPlaylist(this);
			m_pMediaPlayer = new multimedia::XMPMediaPlayer(this);
			QGridLayout *pGridLayout = new QGridLayout(ui->playListWidget);
			pGridLayout->addWidget(m_pPlaylistWindow, 0, 0, 1, 1);
			m_pMediaPlayer->setPlaylist(m_pPlaylistWindow->playlist());
		}

		void XMPMainWindow::updateMetadataInformation()
		{
			TagLib::MPEG::File f(m_pMediaPlayer->currentMedia().canonicalUrl().toString().toStdString().c_str());
			TagLib::ID3v2::Tag *id3v2tag = f.ID3v2Tag();
			if (id3v2tag)
			{
				ui->songNameLabel->setText( "<b>Song :- </b>" + QString( id3v2tag->title().toCString() ));
				ui->artistLabel->setText( "<b>Artist :- </b>" + QString( id3v2tag->artist().toCString() ));
				ui->albumLabel->setText( "<b>Album :- </b>" + QString( id3v2tag->album().toCString() ));
				
				setAlbumArtToLabel(id3v2tag);
			}
		}

		void XMPMainWindow::openMediaFiles()
		{
			QStringList mediaFiles = QFileDialog::getOpenFileNames(this, "Open Media Files", QDir::home().dirName(), audioExtensionFilters);
			if (!mediaFiles.isEmpty())
			{
				m_pPlaylistWindow->addFilesToPlaylist(mediaFiles);
			}
		}

		void XMPMainWindow::openPlaylist()
		{
			m_pPlaylistWindow->show();
		}

		void XMPMainWindow::onPlayButtonClicked()
		{
			if (m_pPlaylistWindow->playlist()->isEmpty())
			{
				return;
			}
			QMediaPlayer::State playState = m_pMediaPlayer->state();
			if ((playState == QMediaPlayer::PausedState) || (playState == QMediaPlayer::StoppedState))
			{
				m_pMediaPlayer->play();
			}
			else
			{
				m_pMediaPlayer->pause();
			}
		}
		void XMPMainWindow::onNextButtonClicked()
		{
			if (m_pPlaylistWindow->playlist()->isEmpty())
			{
				return;
			}
			stopPlayingMusic();
			QMediaPlaylist *pPlaylist = m_pPlaylistWindow->playlist();
			pPlaylist->next();
			onPlayButtonClicked();
		}
		void XMPMainWindow::onPrevButtonClicked()
		{
			if (m_pPlaylistWindow->playlist()->isEmpty())
			{
				return;
			}
			stopPlayingMusic();
			QMediaPlaylist *pPlaylist = m_pPlaylistWindow->playlist();
			pPlaylist->previous();
			onPlayButtonClicked();
		}
		void XMPMainWindow::onVolumeButtonClicked()
		{
			m_pVolumeSlider->setValue(m_pMediaPlayer->volume());
			m_pVolumeSlider->move(mapToParent(QPoint(ui->volumePushButton->x() - 50, ui->volumePushButton->y() + 70)));
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
		void XMPMainWindow::onStopButtonClicked()
		{
			m_pMediaPlayer->stop();
		}
		void XMPMainWindow::onStateChanged(QMediaPlayer::State state)
		{
			if (state == QMediaPlayer::PlayingState)
			{
				ui->playPushButton->setIcon(QIcon(pausePushButtonIconFilePath));
			}
			else if (state == QMediaPlayer::PausedState)
			{
				ui->playPushButton->setIcon(QIcon(playPushButtonIconFilePath));
			}
			else
			{
				ui->playPushButton->setIcon(QIcon(playPushButtonIconFilePath));
			}
		}
		void XMPMainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
		{
			switch(status)
			{
			case QMediaPlayer::UnknownMediaStatus:
				ui->statusBar->showMessage("Unknown Media Status");
				break;
			case QMediaPlayer::NoMedia:
				ui->statusBar->showMessage("No Media");
				break;
			case QMediaPlayer::LoadingMedia:
				ui->statusBar->showMessage("Loading Media");
				break;
			case QMediaPlayer::LoadedMedia:
				ui->statusBar->showMessage("Media Loaded");
				break;
			case QMediaPlayer::StalledMedia:
				ui->statusBar->showMessage("Stalled Media");
				break;
			case QMediaPlayer::BufferingMedia:
				ui->statusBar->showMessage("Buffering Media");
				break;
			case QMediaPlayer::BufferedMedia:
				updateMetadataInformation();
				ui->statusBar->showMessage("Buffered Media");
				break;
			case QMediaPlayer::EndOfMedia:
				ui->statusBar->showMessage("End of Media");
				break;
			case QMediaPlayer::InvalidMedia:
				ui->statusBar->showMessage("Invalid Media");
			}
		}
		void XMPMainWindow::resizeEvent(QResizeEvent * pEvent)
		{
			TagLib::MPEG::File f(m_pMediaPlayer->currentMedia().canonicalUrl().toString().toStdString().c_str());
			TagLib::ID3v2::Tag *id3v2tag = f.ID3v2Tag();
			setAlbumArtToLabel(id3v2tag);
			QMainWindow::resizeEvent(pEvent);
		}
		void XMPMainWindow::stopPlayingMusic()
		{
			if ( (m_pMediaPlayer->state() == QMediaPlayer::PlayingState) || 
				(m_pMediaPlayer->state() == QMediaPlayer::PausedState) )
			{
				m_pMediaPlayer->stop();
			}
		}
		QPixmap XMPMainWindow::getAlbumArt(TagLib::ID3v2::Tag *pTag) const
		{
			QPixmap pix;
			if (pTag)
			{
				TagLib::ID3v2::FrameList frameList = pTag->frameListMap()["APIC"];
				TagLib::ID3v2::AttachedPictureFrame *picFrame = nullptr;
				if (!frameList.isEmpty())
				{
					for (TagLib::ID3v2::FrameList::ConstIterator it = frameList.begin(); it != frameList.end(); ++it)
					{
						unsigned long size;
						picFrame = (TagLib::ID3v2::AttachedPictureFrame *)(*it);
						size = picFrame->picture().size();
						QByteArray byteArray(picFrame->picture().data(), size);
						pix.loadFromData(byteArray);
						return pix;
					}
				}
			}
			pix.load(albumArtFilePath);
			return pix;
		}
		void XMPMainWindow::setAlbumArtToLabel(TagLib::ID3v2::Tag * pTag)
		{
			QPixmap pix = getAlbumArt(pTag);
			pix = pix.scaled(ui->albumArtLabel->width(), ui->albumArtLabel->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			ui->albumArtLabel->setPixmap(pix);
		}
	}
}