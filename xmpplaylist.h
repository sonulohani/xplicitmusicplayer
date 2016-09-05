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

#ifndef XMPPLAYLIST_H
#define XMPPLAYLIST_H

#include <QDialog>
#include <QStringList>

class QTableWidget;
class QPushButton;
class QMediaPlaylist;

namespace xmp {
	namespace ui {
		class XMPPlaylist : public QDialog
		{
			Q_OBJECT
		public:
			explicit XMPPlaylist(QWidget *parent = 0);
			void initUI();
			QMediaPlaylist *playlist() const;
			void addFilesToPlaylist(QStringList fileList);
			void updateTableContent();

		signals:
			void mediaFilesChanged(bool isAdded);

		public slots :
			void onAddToPlaylistButtonClicked();
			void onRemoveFromPlaylistButtonClicked();
			void onItemSelectionChanged();

		private slots:
			void updateUIState();
			void onClearPlaylistButtonClicked();

		private:
			QTableWidget *m_pTableWidget;
			QPushButton *m_pAddToPlaylistButton;
			QPushButton *m_pRemoveFromPlaylistButton;
			QPushButton *m_pClearPlaylistPushButton;
			QMediaPlaylist *m_pMediaPlaylist;
		};
	}
}

#endif // XMPPLAYLIST_H
