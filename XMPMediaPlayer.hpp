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

#ifndef XMPMEDIAPLAYER_H
#define XMPMEDIAPLAYER_H

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

#endif // XMPMEDIAPLAYER_H