#include "xmpmainwindow.h"
#include "ui_xmpmainwindow.h"
#include <xmphelperclass.h>
#include <macros.h>

// Qt includes
#include <QFileDialog>
#include <QDir>

// Private namespace
namespace {
    const QString audioExtensionFilters = "Media ( *.mp3 *.aac )";
}

namespace xmp {
    namespace ui {

        XMPMainWindow::XMPMainWindow(QWidget *parent) :
            QMainWindow(parent),
            ui(new Ui::XMPMainWindow)
        {
            ui->setupUi(this);
            init();

            xmp::helper::XMPHelperClass::setStandardControlButtonSettings( ui->previousPushButton );
            xmp::helper::XMPHelperClass::setStandardControlButtonSettings( ui->playPushButton );
            xmp::helper::XMPHelperClass::setStandardControlButtonSettings( ui->nextPushButton );
            xmp::helper::XMPHelperClass::setStandardControlButtonSettings( ui->volumePushButton );
            xmp::helper::XMPHelperClass::setStandardControlButtonSettings( ui->shufflePushButton );
            xmp::helper::XMPHelperClass::setStandardControlButtonSettings( ui->repeatPushButton );

            XMP_VALIDATE( connect( ui->actionExit, SIGNAL( triggered() ), SLOT( close() ) ) );
            XMP_VALIDATE( connect( ui->actionOpen_media, SIGNAL( triggered(bool)), SLOT( openMediaFiles() ) ) );
        }

        XMPMainWindow::~XMPMainWindow()
        {
            delete ui;
        }

        void XMPMainWindow::init()
        {
            ui->albumLabel->hide();
            ui->artistLabel->hide();
            ui->songNameLabel->hide();
            ui->bitrateLabel->hide();
        }

        void XMPMainWindow::openMediaFiles()
        {
            m_mediaFiles = QFileDialog::getOpenFileNames( this, "Open Media Files", QDir::home().dirName(), audioExtensionFilters );
        }
    }
}

