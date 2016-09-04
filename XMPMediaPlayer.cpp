#include "XMPMediaPlayer.h"
#include <QMediaContent>

namespace xmp
{
	namespace multimedia {
		XMPMediaPlayer::XMPMediaPlayer(QObject * parent, Flags flags) :
			QMediaPlayer(parent, flags)
		{
		}

		XMPMediaPlayer::~XMPMediaPlayer()
		{
		}
		void XMPMediaPlayer::setFileToPlay(const QString & fileName)
		{
			QMediaContent mediaContent(fileName);
			setMedia(mediaContent);
		}
	}
}