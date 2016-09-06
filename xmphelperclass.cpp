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

#include "XMPHelperClass.h"

#include <QIcon>
#include <QPixmap>
#include <QLabel>

namespace {
	const int CONTROL_PUSHBUTTON_WIDTH = 29;
	const int CONTROL_PUSHBUTTON_HEIGHT = 29;
}

namespace xmp {
	namespace helper {
		XMPHelperClass::XMPHelperClass()
		{
		}

		void XMPHelperClass::XMPHelperClass::setStandardControlButtonSettings(QPushButton *pushButton,
			const QString &iconName, bool isEnabled)
		{
			if (pushButton)
			{
				QPixmap iconPixmap(iconName);
				QIcon icon(iconPixmap);
				pushButton->setFlat(true);
				pushButton->setIcon(icon);
				pushButton->setIconSize(iconPixmap.rect().size());
				pushButton->setEnabled(isEnabled);
				pushButton->setFixedSize(CONTROL_PUSHBUTTON_WIDTH, CONTROL_PUSHBUTTON_HEIGHT);
			}
		}
	}
}