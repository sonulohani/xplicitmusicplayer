#ifndef XMPMAINWINDOW_H
#define XMPMAINWINDOW_H

#include <QMainWindow>
#include <QStringList>

namespace Ui {
	class XMPMainWindow;
}

namespace xmp {
	namespace multimedia {
		class XMPMediaPlayer;
	}
	namespace ui {
		class XMPPlaylist;

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

			private slots:
			void openMediaFiles();
			void openPlaylist();

			public slots:
			void updateUIState(bool isEnabled);

		private:
			Ui::XMPMainWindow *ui;
			QStringList m_mediaFiles;
			XMPPlaylist *m_pPlaylistWindow;
			multimedia::XMPMediaPlayer *m_pMediaPlayer;
		};
	}
}

#endif // XMPMAINWINDOW_H
