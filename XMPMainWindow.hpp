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

#ifndef XMPMAINWINDOW_H
#define XMPMAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QMediaPlayer>
#include <QPixmap>

class QFocusEvent;
class QResizeEvent;

namespace TagLib {
	namespace ID3v2 {
		class Tag;
	}
}

namespace Ui {
	class XMPMainWindow;
}

namespace xmp {
	namespace multimedia {
		class XMPMediaPlayer;
	}
	namespace ui {
		class XMPPlaylist;
		class XMPVolumeSlider;

		class XMPMainWindow : public QMainWindow
		{
			Q_OBJECT
		public:
			//! Ctor
			explicit XMPMainWindow(QWidget *parent = 0);

			//! Dtor
			~XMPMainWindow();

			//! This function would be called at the starting of the application.
			//! Generally initializes the mainwindow ui elements
			void initUI();
			void initComponent();
			void updateMetadataInformation();
			void setAlbumArtToLabel(TagLib::ID3v2::Tag *pTag = nullptr);

			private slots:
			void openMediaFiles();
			void openPlaylist();
			void onPlayButtonClicked();
			void onNextButtonClicked();
			void onPrevButtonClicked();
			void onVolumeButtonClicked();
			void changeVolume(int value);
			void onStopButtonClicked();
			void onStateChanged(QMediaPlayer::State state);
			void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
			void onSliderMoved(int pos);
			void onDurationChanged(qint64 duration);
			void onSelectionChanged(const QModelIndex & index);

		protected:
			void resizeEvent(QResizeEvent *pEvent);

		private:
			void stopPlayingMusic();
			QPixmap getAlbumArt(TagLib::ID3v2::Tag *pTag) const;
			void updateSlider();

			Ui::XMPMainWindow *ui;
			XMPPlaylist *m_pPlaylistWindow;
			multimedia::XMPMediaPlayer *m_pMediaPlayer;
			XMPVolumeSlider *m_pVolumeSlider;
		};
	}
}

#endif // XMPMAINWINDOW_H