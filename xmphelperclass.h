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

#ifndef XMPHELPERCLASS_H
#define XMPHELPERCLASS_H

#include <QPushButton>
#include <QString>
#include <QPointer>

namespace xmp
{
	namespace helper
	{
		class XMPHelperClass
		{
		public:
			XMPHelperClass();

			static void setStandardControlButtonSettings(QPushButton *pushButton, const QString &iconName, bool isEnabled = false);
		};
	}
}

#endif // XMPHELPERCLASS_H
