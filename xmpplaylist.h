#ifndef XMPPLAYLIST_H
#define XMPPLAYLIST_H

#include <QDialog>
#include <QStringList>

class QTableWidget;
class QPushButton;

namespace xmp {
	namespace ui {
		class XMPPlaylist : public QDialog
		{
			Q_OBJECT
		public:
			explicit XMPPlaylist(QWidget *parent = 0);
			void initUI();
			void addFilesToPlaylist(QStringList fileList);

		public slots :
			void onAddToPlaylistButtonClicked();
			void onRemoveFromPlaylistButtonClicked();
			void onItemSelectionChanged();

		private slots:
			void updateUIState();

		private:
			QTableWidget *m_pTableWidget;
			QPushButton *m_pAddToPlaylistButton;
			QPushButton *m_pRemoveFromPlaylistButton;
			QStringList m_mediaFiles;
		};
	}
}

#endif // XMPPLAYLIST_H
