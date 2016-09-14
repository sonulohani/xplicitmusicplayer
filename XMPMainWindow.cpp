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
#include <XMPPlaylist.hpp>
#include <XMPMediaPlayer.hpp>
#include <XMPVolumeSlider.hpp>

// Taglib includes
#include <id3v2tag.h>
#include <mpegfile.h>
#include <attachedpictureframe.h>
#include <id3v2frame.h>
#include <tlist.h>

//cpp includes
#include <assert.h>

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
#include <QTime>

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
	const QString appIconFilePath = ":/controls/resources/icons/music_player_icon.png";
}

namespace xmp {
	namespace ui {
		XMPMainWindow::XMPMainWindow(QWidget *parent) :
			QMainWindow(parent),
			ui(new Ui::XMPMainWindow),
			m_pPlaylistWindow(nullptr),
			m_pTrayIcon(nullptr)
		{
			ui->setupUi(this);
			initUI();
			initComponent();
			setWindowIcon(QIcon(appIconFilePath));

			assert(connect(ui->actionExit, SIGNAL(triggered()), SLOT(close())));
			assert(connect(ui->actionOpen_media, SIGNAL(triggered(bool)), SLOT(openMediaFiles())));
			assert(connect(ui->actionPlaylist, SIGNAL(triggered(bool)), SLOT(openPlaylist())));
			assert(connect(ui->openMediaButton, SIGNAL(clicked()), SLOT(openMediaFiles())));
			assert(connect(ui->playPushButton, SIGNAL(clicked()), SLOT(onPlayButtonClicked())));
			assert(connect(ui->actionStop, SIGNAL(triggered()), SLOT(onStopButtonClicked())));
			assert(connect(ui->stopPushButton, SIGNAL(clicked()), SLOT(onStopButtonClicked())));
			assert(connect(ui->actionPlay, SIGNAL(triggered()), SLOT(onPlayButtonClicked())));
			assert(connect(ui->nextPushButton, SIGNAL(clicked()), SLOT(onNextButtonClicked())));
			assert(connect(ui->previousPushButton, SIGNAL(clicked()), SLOT(onPrevButtonClicked())));
			assert(connect(ui->actionPrevious, SIGNAL(triggered()), SLOT(onPrevButtonClicked())));
			assert(connect(ui->actionNext, SIGNAL(triggered()), SLOT(onNextButtonClicked())));
			assert(connect(ui->volumePushButton, SIGNAL(clicked()), SLOT(onVolumeButtonClicked())));
			assert(connect(m_pVolumeSlider, SIGNAL(valueChanged(int)), SLOT(changeVolume(int))));
			assert(connect(m_pMediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), SLOT(onStateChanged(QMediaPlayer::State))));
			assert(connect(m_pMediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus))));
			assert(connect(ui->playerSlider, SIGNAL(sliderMoved(int)), SLOT(onSliderMoved(int))));
			// TODO
			//assert(connect(ui->playerSlider, SIGNAL(valueChanged(int)), SLOT(onSliderMoved(int))));
			assert(connect(m_pMediaPlayer, SIGNAL(positionChanged(qint64)), SLOT(onDurationChanged(qint64))));
			assert(connect(m_pPlaylistWindow, SIGNAL(selectionChanged(const QModelIndex &)), SLOT(onSelectionChanged(const QModelIndex &))));
			assert(connect(ui->shufflePushButton, SIGNAL(clicked()), SLOT(onShuffleButtonClicked())));
			assert(connect(ui->actionAbout_XMP, SIGNAL(triggered()), SLOT(onAboutXMPTriggerred())));
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
			//xmp::helper::XMPHelperClass::setStandardControlButtonSettings(ui->repeatPushButton, repeatPushButtonIconFilePath);

			ui->songNameLabel->setText("<b>Song :- </b>");
			ui->artistLabel->setText("<b>Artist :- </b>");
			ui->albumLabel->setText("<b>Album :- </b>");
			m_pVolumeSlider = new XMPVolumeSlider;

			ui->playPushButton->setShortcut(Qt::Key_Space);
			ui->stopPushButton->setShortcut(Qt::Key_S);
			ui->previousPushButton->setShortcut(Qt::Key_P);
			ui->nextPushButton->setShortcut(Qt::Key_N);
			ui->shufflePushButton->setShortcut(Qt::Key_H);
		}

		void XMPMainWindow::initComponent()
		{
			m_pPlaylistWindow = new XMPPlaylist(this);
			m_pMediaPlayer = new multimedia::XMPMediaPlayer(this);
			QGridLayout *pGridLayout = new QGridLayout(ui->playListWidget);
			pGridLayout->addWidget(m_pPlaylistWindow, 0, 0, 1, 1);
			m_pMediaPlayer->setPlaylist(m_pPlaylistWindow->playlist());

			ui->playerSlider->setRange(0, m_pMediaPlayer->duration() / 1000);
		}

		void XMPMainWindow::updateMetadataInformation()
		{
			TagLib::MPEG::File f(m_pMediaPlayer->currentMedia().canonicalUrl().toString().toStdString().c_str());
			TagLib::ID3v2::Tag *id3v2tag = f.ID3v2Tag();
			if (id3v2tag)
			{
				ui->songNameLabel->setText("<b>Song :- </b>" + QString(id3v2tag->title().toCString()));
				ui->artistLabel->setText("<b>Artist :- </b>" + QString(id3v2tag->artist().toCString()));
				ui->albumLabel->setText("<b>Album :- </b>" + QString(id3v2tag->album().toCString()));

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
				showSystemTrayMessage(tr("Playing"), QFileInfo(m_pMediaPlayer->playlist()->currentMedia().canonicalUrl().path()).fileName());
			}
			else
			{
				m_pMediaPlayer->pause();
				showSystemTrayMessage(tr("Paused"), QFileInfo(m_pMediaPlayer->playlist()->currentMedia().canonicalUrl().path()).fileName());
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
			m_pVolumeSlider->move(mapToParent(QPoint(ui->volumePushButton->x() - 50, ui->volumePushButton->y() + 50)));
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
			if (m_pPlaylistWindow->playlist()->isEmpty())
			{
				return;
			}
			m_pMediaPlayer->stop();

			showSystemTrayMessage(tr("Stopped"), QFileInfo(m_pMediaPlayer->playlist()->currentMedia().canonicalUrl().path()).fileName());
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
			switch (status)
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
				updateSlider();
				updateMetadataInformation();
				m_pPlaylistWindow->selectCurrentPlaying(m_pMediaPlayer->playlist()->currentIndex());
				showSystemTrayMessage(tr("Playing"), QFileInfo(m_pMediaPlayer->playlist()->currentMedia().canonicalUrl().path()).fileName());
				ui->statusBar->showMessage("Buffered Media");
				break;
			case QMediaPlayer::EndOfMedia:
				ui->statusBar->showMessage("End of Media");
				break;
			case QMediaPlayer::InvalidMedia:
				ui->statusBar->showMessage("Invalid Media");
			}
		}
		void XMPMainWindow::onSliderMoved(int pos)
		{
			m_pMediaPlayer->setPosition(pos * 1000);
		}
		void XMPMainWindow::onDurationChanged(qint64 duration)
		{
			ui->playerSlider->setValue(duration / 1000);
			ui->startTimeLabel->setText(QTime(0, 0).addMSecs(duration).toString("mm:ss"));
		}
		void XMPMainWindow::onSelectionChanged(const QModelIndex & index)
		{
			m_pMediaPlayer->playlist()->setCurrentIndex(index.row());
			m_pMediaPlayer->play();
		}
		void XMPMainWindow::onShow(QSystemTrayIcon::ActivationReason reason)
		{
			if (reason != QSystemTrayIcon::DoubleClick)
				return;

			showNormal();

			delete m_pTrayIcon;
			m_pTrayIcon = nullptr;
		}
		void XMPMainWindow::onShuffleButtonClicked()
		{
			m_pMediaPlayer->playlist()->shuffle();
		}
		void XMPMainWindow::onAboutXMPTriggerred()
		{
			helper::XMPHelperClass::showMessageDialog(tr("About Xplicit Media Player"), tr("<b>Music player that never sucks.</b>\nCopyright 2016-2017 Sonu Lohani <sonulohani@gmail.com>"), QMessageBox::Information);
		}
		void XMPMainWindow::resizeEvent(QResizeEvent * pEvent)
		{
			TagLib::MPEG::File f(m_pMediaPlayer->currentMedia().canonicalUrl().toString().toStdString().c_str());
			TagLib::ID3v2::Tag *id3v2tag = f.ID3v2Tag();
			setAlbumArtToLabel(id3v2tag);
			QMainWindow::resizeEvent(pEvent);
		}
		void XMPMainWindow::changeEvent(QEvent * pEvent)
		{
			if (pEvent->type() == QEvent::WindowStateChange)
			{
				if (windowState() & Qt::WindowMinimized)
				{
					this->hide();
					createTrayIcon();
					return;
				}
			}
			QMainWindow::changeEvent(pEvent);
		}
		void XMPMainWindow::stopPlayingMusic()
		{
			if ((m_pMediaPlayer->state() == QMediaPlayer::PlayingState) ||
				(m_pMediaPlayer->state() == QMediaPlayer::PausedState))
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
		void XMPMainWindow::updateSlider()
		{
			qint64 mediaDuration = m_pMediaPlayer->duration();
			ui->playerSlider->setMaximum(mediaDuration / 1000);
			ui->finishTimeLabel->setText(QTime(0, 0).addMSecs(mediaDuration).toString("mm:ss"));
		}
		void XMPMainWindow::setAlbumArtToLabel(TagLib::ID3v2::Tag * pTag)
		{
			QPixmap pix = getAlbumArt(pTag);
			pix = pix.scaled(ui->albumArtLabel->width(), ui->albumArtLabel->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			ui->albumArtLabel->setPixmap(pix);
		}
		void XMPMainWindow::createTrayIcon()
		{
			m_pTrayIcon = new QSystemTrayIcon(QIcon(appIconFilePath), this);

			assert(connect(m_pTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onShow(QSystemTrayIcon::ActivationReason))));

			QAction *pPlayAction = new QAction("Play/Pause", m_pTrayIcon);
			assert(connect(pPlayAction, SIGNAL(triggered()), this, SLOT(onPlayButtonClicked())));

			QAction *pStopAction = new QAction("Stop", m_pTrayIcon);
			assert(connect(pStopAction, SIGNAL(triggered()), this, SLOT(onStopButtonClicked())));

			QAction *pNextAction = new QAction("Next", m_pTrayIcon);
			assert(connect(pNextAction, SIGNAL(triggered()), this, SLOT(onNextButtonClicked())));

			QAction *pPreviousAction = new QAction("Previous", m_pTrayIcon);
			assert(connect(pPreviousAction, SIGNAL(triggered()), this, SLOT(onPrevButtonClicked())));

			QAction *pExitAction = new QAction("Exit", m_pTrayIcon);
			assert(connect(pExitAction, SIGNAL(triggered()), this, SLOT(close())));

			QMenu *pTrayIconMenu = new QMenu;
			pTrayIconMenu->addAction(pPlayAction);
			pTrayIconMenu->addAction(pNextAction);
			pTrayIconMenu->addAction(pPreviousAction);
			pTrayIconMenu->addAction(pStopAction);
			pTrayIconMenu->addAction(pExitAction);

			m_pTrayIcon->setContextMenu(pTrayIconMenu);

			m_pTrayIcon->show();
		}
		void XMPMainWindow::showSystemTrayMessage(const QString &title, const QString &msg)
		{
			if (m_pTrayIcon)
			{
				m_pTrayIcon->showMessage(title, msg);
			}
		}
	}
}