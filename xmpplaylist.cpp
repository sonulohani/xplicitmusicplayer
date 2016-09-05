#include "XMPPlaylist.h"
#include <macros.h>

#include <QTableWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFileInfo>
#include <QHeaderView>
#include <QList>
#include <QMediaPlaylist>

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
			updateUIState();
			XMP_VALIDATE(connect(m_pAddToPlaylistButton, SIGNAL(clicked()), SLOT(onAddToPlaylistButtonClicked())));
			XMP_VALIDATE(connect(m_pRemoveFromPlaylistButton, SIGNAL(clicked()), SLOT(onRemoveFromPlaylistButtonClicked())));
			XMP_VALIDATE(connect(m_pClearPlaylistPushButton, SIGNAL(clicked()), SLOT(onClearPlaylistButtonClicked())));
			XMP_VALIDATE(connect(m_pTableWidget, SIGNAL(itemSelectionChanged()), SLOT(updateUIState())));
		}

		void XMPPlaylist::initUI()
		{
			m_pTableWidget = new QTableWidget(this);
			m_pTableWidget->horizontalHeader()->setStretchLastSection(true);
			m_pTableWidget->horizontalHeader()->hide();
			m_pTableWidget->setColumnCount(1);

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
			pParentLayout->addWidget(m_pTableWidget);
			pParentLayout->addLayout(pHorizontalButtonLayout);

			setLayout(pParentLayout);

			m_pMediaPlaylist = new QMediaPlaylist(this);
		}

		QMediaPlaylist * XMPPlaylist::playlist() const
		{
			return m_pMediaPlaylist;
		}

		void XMPPlaylist::updateTableContent()
		{
			// Clearing all the items from the table and reinserting it from beginning
			m_pTableWidget->setRowCount(0);
			m_pTableWidget->setRowCount(m_pMediaPlaylist->mediaCount());
			for (int i = 0; i < m_pMediaPlaylist->mediaCount(); i++)
			{
				QTableWidgetItem *pItem = new QTableWidgetItem();
				pItem->setText(QFileInfo(m_pMediaPlaylist->media(i).canonicalUrl().toString()).fileName());
				m_pTableWidget->setItem(i, COLUMN, pItem);
			}
		}

		void XMPPlaylist::addFilesToPlaylist(QStringList fileList)
		{
			if (!fileList.isEmpty())
			{
				Q_FOREACH(QString file, fileList)
				{
					m_pMediaPlaylist->addMedia(QUrl(file));
				}
				updateTableContent();
			}
		}

		void XMPPlaylist::onAddToPlaylistButtonClicked()
		{
			QStringList mediaFiles = QFileDialog::getOpenFileNames(this, "Open Media Files", QDir::home().dirName(), audioExtensionFilters);
			if (!mediaFiles.isEmpty())
			{
				addFilesToPlaylist(mediaFiles);
				updateUIState();
				emit mediaFilesChanged(true);
			}
		}

		void XMPPlaylist::onRemoveFromPlaylistButtonClicked()
		{
			QTableWidgetItemList tableWidgetItemList = m_pTableWidget->selectedItems();

			for (int i = 0; i < tableWidgetItemList.count(); i++)
			{
				int row = tableWidgetItemList[i]->row();
				m_pTableWidget->removeRow(row);
				m_pMediaPlaylist->removeMedia(row);
			}
			emit mediaFilesChanged(m_pTableWidget->rowCount());
			updateUIState();
		}
		void XMPPlaylist::onItemSelectionChanged()
		{
			m_pRemoveFromPlaylistButton->setEnabled(!m_pTableWidget->selectedItems().isEmpty());
		}

		void xmp::ui::XMPPlaylist::onClearPlaylistButtonClicked()
		{
			// Setting rowCount to 0 will delete the QTableWidgetItems automatically, by calling removeRows as you can see in QTableWidget internal model code
			m_pTableWidget->setRowCount(0);
			m_pMediaPlaylist->clear();
			emit mediaFilesChanged(false);
		}

		void XMPPlaylist::updateUIState()
		{
			onItemSelectionChanged();
		}
	}
}