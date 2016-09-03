#ifndef XMPMAINWINDOW_H
#define XMPMAINWINDOW_H

#include <QMainWindow>
#include <QStringList>

namespace Ui {
	class XMPMainWindow;
}

namespace xmp {
    namespace ui {

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

        private slots:
            void openMediaFiles();

        private:
            Ui::XMPMainWindow *ui;
            QStringList m_mediaFiles;
        };
    }
}

#endif // XMPMAINWINDOW_H
