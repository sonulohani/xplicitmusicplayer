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
