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

#ifndef XMPMAINWINDOW_H
#define XMPMAINWINDOW_H

#include <QMainWindow>
#include <QStringList>

class QFocusEvent;

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
			enum class STATE
			{
				PLAY,
				PAUSE,
				STOP
			};
		public:
			//! Ctor
			explicit XMPMainWindow(QWidget *parent = 0);

			//! Dtor
			~XMPMainWindow();

			//! This function would be called at the starting of the application.
			//! Generally initializes the mainwindow ui elements
			void initUI();
			void initComponent();

		private slots:
			void openMediaFiles();
			void openPlaylist();
			void onPlayButtonClicked();
			void onNextButtonClicked();
			void onPrevButtonClicked();
			void onVolumeButtonClicked();
			void changeVolume(int value);

		public slots:
			void updateUIState(bool isEnabled);

		private:
			Ui::XMPMainWindow *ui;
			XMPPlaylist *m_pPlaylistWindow;
			multimedia::XMPMediaPlayer *m_pMediaPlayer;
			STATE m_state;
			XMPVolumeSlider *m_pVolumeSlider;
		};
	}
}

#endif // XMPMAINWINDOW_H
