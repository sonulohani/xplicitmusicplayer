#include "xmpplaylist.h"
#include <macros.h>

#include <QTableWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFileInfo>
#include <QHeaderView>
#include <QList>

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

			QHBoxLayout *pHorizontalButtonLayout = new QHBoxLayout;
			pHorizontalButtonLayout->addWidget(m_pAddToPlaylistButton);
			pHorizontalButtonLayout->addWidget(m_pRemoveFromPlaylistButton);

			QVBoxLayout *pParentLayout = new QVBoxLayout(this);
			pParentLayout->addWidget(m_pTableWidget);
			pParentLayout->addLayout(pHorizontalButtonLayout);

			setLayout(pParentLayout);
		}

		void XMPPlaylist::addFilesToPlaylist(QStringList fileList)
		{
			if (!fileList.isEmpty())
			{
				int noOfRows = fileList.count() + m_pTableWidget->rowCount();
				m_pTableWidget->setRowCount(noOfRows);
				int index = 0;
				for (int i = m_pTableWidget->rowCount() - fileList.count(); i < m_pTableWidget->rowCount(); i++)
				{
					QTableWidgetItem *pItem = new QTableWidgetItem();
					pItem->setText(QFileInfo(fileList[index]).fileName());
					m_pTableWidget->setItem(i, COLUMN, pItem);
					index++;
				}
			}
		}

		void XMPPlaylist::onAddToPlaylistButtonClicked()
		{
			m_mediaFiles = QFileDialog::getOpenFileNames(this, "Open Media Files", QDir::home().dirName(), audioExtensionFilters);
			addFilesToPlaylist(m_mediaFiles);
			updateUIState();
		}

		void XMPPlaylist::onRemoveFromPlaylistButtonClicked()
		{
			QTableWidgetItemList tableWidgetItemList = m_pTableWidget->selectedItems();

			for (int i = 0; i < tableWidgetItemList.count(); i++)
			{
				int row = tableWidgetItemList[i]->row();
				m_pTableWidget->removeRow(row);
			}
			updateUIState();
		}
		void XMPPlaylist::onItemSelectionChanged()
		{
			m_pRemoveFromPlaylistButton->setEnabled(!m_pTableWidget->selectedItems().isEmpty());
		}

		void XMPPlaylist::updateUIState()
		{
			onItemSelectionChanged();
		}
	}
}