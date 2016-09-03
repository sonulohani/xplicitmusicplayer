#ifndef XMPMAINWINDOW_H
#define XMPMAINWINDOW_H

#include <QMainWindow>
#include <QStringList>

namespace Ui {
	class XMPMainWindow;
}

namespace xmp {
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
			void init();
			void initComponent();

			private slots:
			void openMediaFiles();
			void openPlaylist();

		private:
			Ui::XMPMainWindow *ui;
			QStringList m_mediaFiles;
			XMPPlaylist *m_pPlaylistWindow;
		};
	}
}

#endif // XMPMAINWINDOW_H
