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

#include "XMPPlaylist.h"
#include <macros.h>
#include <XMPPlaylistModel.h>

#include <QTableWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFileInfo>
#include <QHeaderView>
#include <QList>
#include <QMediaPlaylist>
#include <QListView>

using QTableWidgetItemList = QList<QTableWidgetItem*>;

namespace {
	const QString audioExtensionFilters = "Media ( *.mp3 *.aac )";
	const int COLUMN = 0;
}

namespace xmp {
	namespace ui {
		XMPPlaylist::XMPPlaylist(QWidget *parent) : QDialog(parent)
		{
			initUI();
			XMP_VALIDATE(connect(m_pAddToPlaylistButton, SIGNAL(clicked()), SLOT(onAddToPlaylistButtonClicked())));
			XMP_VALIDATE(connect(m_pRemoveFromPlaylistButton, SIGNAL(clicked()), SLOT(onRemoveFromPlaylistButtonClicked())));
			XMP_VALIDATE(connect(m_pClearPlaylistPushButton, SIGNAL(clicked()), SLOT(onClearPlaylistButtonClicked())));
		}

		void XMPPlaylist::initUI()
		{
			m_pMediaPlaylist = new QMediaPlaylist(this);
			m_pPlaylistModel = new model::XMPPlaylistModel(this);

			m_pListView = new QListView(this);
			m_pListView->setModel(m_pPlaylistModel);

			m_pPlaylistModel->setPlaylist(m_pMediaPlaylist);

			m_pAddToPlaylistButton = new QPushButton(this);
			m_pAddToPlaylistButton->setText(tr("+"));

			m_pRemoveFromPlaylistButton = new QPushButton(this);
			m_pRemoveFromPlaylistButton->setText("-");

			m_pClearPlaylistPushButton = new QPushButton(this);
			m_pClearPlaylistPushButton->setText("Clear");

			QHBoxLayout *pHorizontalButtonLayout = new QHBoxLayout;
			pHorizontalButtonLayout->addWidget(m_pAddToPlaylistButton);
			pHorizontalButtonLayout->addWidget(m_pRemoveFromPlaylistButton);
			pHorizontalButtonLayout->addWidget(m_pClearPlaylistPushButton);

			QVBoxLayout *pParentLayout = new QVBoxLayout(this);
			pParentLayout->addWidget(m_pListView);
			pParentLayout->addLayout(pHorizontalButtonLayout);

			setLayout(pParentLayout);

			m_pListView->setCurrentIndex(m_pPlaylistModel->index(m_pMediaPlaylist->currentIndex(), 0));
		}

		QMediaPlaylist * XMPPlaylist::playlist() const
		{
			return m_pMediaPlaylist;
		}

		void XMPPlaylist::addFilesToPlaylist(QStringList fileList)
		{
			if (!fileList.isEmpty())
			{
				Q_FOREACH(QString file, fileList)
				{
					m_pMediaPlaylist->addMedia(QUrl(file));
				}
			}
		}

		void XMPPlaylist::onAddToPlaylistButtonClicked()
		{
			QStringList mediaFiles = QFileDialog::getOpenFileNames(this, "Open Media Files", QDir::home().dirName(), audioExtensionFilters);
			if (!mediaFiles.isEmpty())
			{
				addFilesToPlaylist(mediaFiles);
			}
		}

		void XMPPlaylist::onRemoveFromPlaylistButtonClicked()
		{
			QModelIndexList selectedItemList = m_pListView->selectionModel()->selectedIndexes();
			Q_FOREACH(const QModelIndex &index, selectedItemList)
			{
				m_pMediaPlaylist->removeMedia(index.row());
			}
		}

		void xmp::ui::XMPPlaylist::onClearPlaylistButtonClicked()
		{
			m_pMediaPlaylist->clear();
		}
	}
}