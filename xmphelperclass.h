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

            static void setStandardControlButtonSettings( QPointer<QPushButton> pushButton );
        };
    }
}

#endif // XMPHELPERCLASS_H
