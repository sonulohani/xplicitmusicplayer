#include "XMPVolumeSlider.h"

namespace xmp {
	namespace ui {
		XMPVolumeSlider::XMPVolumeSlider(QWidget *parent) :
			QSlider(parent)
		{
			setWindowFlags(Qt::FramelessWindowHint);
			setMinimum(0);
			setMaximum(100);
			setOrientation(Qt::Horizontal);
			setFixedSize(150, 20);
			hide();
		}


		XMPVolumeSlider::~XMPVolumeSlider()
		{
		}

		void XMPVolumeSlider::focusOutEvent(QFocusEvent * event)
		{
			this->hide();
		}
	}
}

