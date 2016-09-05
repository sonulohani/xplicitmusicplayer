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
