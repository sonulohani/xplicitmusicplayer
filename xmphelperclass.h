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
