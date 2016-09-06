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

#include "XMPPlaylistModel.hpp"

#include <QFileInfo>
#include <QUrl>
#include <QMediaPlaylist>

namespace xmp {
	namespace model {
		XMPPlaylistModel::XMPPlaylistModel(QObject *parent)
			: QAbstractItemModel(parent)
			, m_playlist(0)
		{
		}

		int XMPPlaylistModel::rowCount(const QModelIndex &parent) const
		{
			return m_playlist && !parent.isValid() ? m_playlist->mediaCount() : 0;
		}

		int XMPPlaylistModel::columnCount(const QModelIndex &parent) const
		{
			return !parent.isValid() ? ColumnCount : 0;
		}

		QModelIndex XMPPlaylistModel::index(int row, int column, const QModelIndex &parent) const
		{
			return m_playlist && !parent.isValid()
				&& row >= 0 && row < m_playlist->mediaCount()
				&& column >= 0 && column < ColumnCount
				? createIndex(row, column)
				: QModelIndex();
		}

		QModelIndex XMPPlaylistModel::parent(const QModelIndex &child) const
		{
			Q_UNUSED(child);

			return QModelIndex();
		}

		QVariant XMPPlaylistModel::data(const QModelIndex &index, int role) const
		{
			if (index.isValid() && role == Qt::DisplayRole) {
				QVariant value = m_data[index];
				if (!value.isValid() && index.column() == Title) {
					QUrl location = m_playlist->media(index.row()).canonicalUrl();
					return QFileInfo(location.path()).fileName();
				}

				return value;
			}
			return QVariant();
		}

		QMediaPlaylist *XMPPlaylistModel::playlist() const
		{
			return m_playlist;
		}

		void XMPPlaylistModel::setPlaylist(QMediaPlaylist *playlist)
		{
			if (m_playlist) {
				disconnect(m_playlist, SIGNAL(mediaAboutToBeInserted(int, int)), this, SLOT(beginInsertItems(int, int)));
				disconnect(m_playlist, SIGNAL(mediaInserted(int, int)), this, SLOT(endInsertItems()));
				disconnect(m_playlist, SIGNAL(mediaAboutToBeRemoved(int, int)), this, SLOT(beginRemoveItems(int, int)));
				disconnect(m_playlist, SIGNAL(mediaRemoved(int, int)), this, SLOT(endRemoveItems()));
				disconnect(m_playlist, SIGNAL(mediaChanged(int, int)), this, SLOT(changeItems(int, int)));
			}

			beginResetModel();
			m_playlist = playlist;

			if (m_playlist) {
				connect(m_playlist, SIGNAL(mediaAboutToBeInserted(int, int)), this, SLOT(beginInsertItems(int, int)));
				connect(m_playlist, SIGNAL(mediaInserted(int, int)), this, SLOT(endInsertItems()));
				connect(m_playlist, SIGNAL(mediaAboutToBeRemoved(int, int)), this, SLOT(beginRemoveItems(int, int)));
				connect(m_playlist, SIGNAL(mediaRemoved(int, int)), this, SLOT(endRemoveItems()));
				connect(m_playlist, SIGNAL(mediaChanged(int, int)), this, SLOT(changeItems(int, int)));
			}

			endResetModel();
		}

		bool XMPPlaylistModel::setData(const QModelIndex &index, const QVariant &value, int role)
		{
			Q_UNUSED(role);
			m_data[index] = value;
			emit dataChanged(index, index);
			return true;
		}

		void XMPPlaylistModel::beginInsertItems(int start, int end)
		{
			m_data.clear();
			beginInsertRows(QModelIndex(), start, end);
		}

		void XMPPlaylistModel::endInsertItems()
		{
			endInsertRows();
		}

		void XMPPlaylistModel::beginRemoveItems(int start, int end)
		{
			m_data.clear();
			beginRemoveRows(QModelIndex(), start, end);
		}

		void XMPPlaylistModel::endRemoveItems()
		{
			endInsertRows();
		}

		void XMPPlaylistModel::changeItems(int start, int end)
		{
			m_data.clear();
			emit dataChanged(index(start, 0), index(end, ColumnCount));
		}
	}
}