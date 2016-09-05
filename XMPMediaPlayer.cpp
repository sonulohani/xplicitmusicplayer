/*\
|*|  Copyright 2016-2017 Sonu Lohani <sonulohani@gmail.com>
|*|
|*|  This file is part of the XMPMusicPlayer program.
|*|
|*|  AvCaster is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU Lesser General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  AvCaster is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU Lesser General Public License for more details.
|*|
|*|  You should have received a copy of the GNU Lesser General Public License
|*|  along with AvCaster.  If not, see <http://www.gnu.org/licenses/>.
\*/

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