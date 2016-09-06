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

#ifndef XMPPLAYLISTMODEL_H
#define XMPPLAYLISTMODEL_H

#include <QAbstractItemModel>

QT_BEGIN_NAMESPACE
class QMediaPlaylist;
QT_END_NAMESPACE

namespace xmp {
	namespace model {

		class XMPPlaylistModel : public QAbstractItemModel
		{
			Q_OBJECT

		public:
			enum Column
			{
				Title = 0,
				ColumnCount
			};

			XMPPlaylistModel(QObject *parent = 0);

			int rowCount(const QModelIndex &parent = QModelIndex()) const;
			int columnCount(const QModelIndex &parent = QModelIndex()) const;

			QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
			QModelIndex parent(const QModelIndex &child) const;

			QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

			QMediaPlaylist *playlist() const;
			void setPlaylist(QMediaPlaylist *playlist);

			bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);

			private slots:
			void beginInsertItems(int start, int end);
			void endInsertItems();
			void beginRemoveItems(int start, int end);
			void endRemoveItems();
			void changeItems(int start, int end);

		private:
			QMediaPlaylist *m_playlist;
			QMap<QModelIndex, QVariant> m_data;
		};
	}
}

#endif // XMPPLAYLISTMODEL_H
