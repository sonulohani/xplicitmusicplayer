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

#ifndef XMPPLAYLIST_H
#define XMPPLAYLIST_H

#include <QDialog>
#include <QStringList>

class QListView;
class QPushButton;
class QMediaPlaylist;

namespace xmp {
	namespace model {
		class XMPPlaylistModel;
	}
	namespace ui {
		class XMPPlaylist : public QDialog
		{
			Q_OBJECT
		public:
			explicit XMPPlaylist(QWidget *parent = 0);
			void initUI();
			QMediaPlaylist *playlist() const;
			void addFilesToPlaylist(QStringList fileList);

		signals:
			void mediaFilesChanged(bool isAdded);

			public slots :
			void onAddToPlaylistButtonClicked();

			private slots:
			void onClearPlaylistButtonClicked();
			void onRemoveFromPlaylistButtonClicked();

		private:
			QListView *m_pListView;
			QPushButton *m_pAddToPlaylistButton;
			QPushButton *m_pRemoveFromPlaylistButton;
			QPushButton *m_pClearPlaylistPushButton;
			QMediaPlaylist *m_pMediaPlaylist;
			model::XMPPlaylistModel *m_pPlaylistModel;
		};
	}
}

#endif // XMPPLAYLIST_H
