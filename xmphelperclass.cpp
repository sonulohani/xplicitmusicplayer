#include "XMPHelperClass.h"

#include <QIcon>
#include <QPixmap>

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