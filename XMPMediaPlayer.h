#pragma once

#include <QMediaPlayer>

namespace xmp
{
	namespace multimedia {
		class XMPMediaPlayer :
			public QMediaPlayer
		{
		public:
			XMPMediaPlayer(QObject *parent = Q_NULLPTR, Flags flags = Flags());
			~XMPMediaPlayer();

			void setFileToPlay(const QString &fileName);
		};
	} //multimedia
} // xmp
