#include "xmphelperclass.h"

namespace {
    const int CONTROL_PUSHBUTTON_WIDTH = 48;
    const int CONTROL_PUSHBUTTON_HEIGHT = 48;
}

namespace xmp {

    namespace helper {

        XMPHelperClass::XMPHelperClass()
        {
        }

        void XMPHelperClass::XMPHelperClass::setStandardControlButtonSettings(QPointer<QPushButton> pushButton)
        {
            pushButton->setFlat( true );
            pushButton->setFixedSize( CONTROL_PUSHBUTTON_WIDTH, CONTROL_PUSHBUTTON_HEIGHT );
        }

    }
}
