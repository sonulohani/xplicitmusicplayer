#pragma once

#include <QSlider>

class QFocusEvent;
namespace xmp {
	namespace ui {

		class XMPVolumeSlider :
			public QSlider
		{
		public:
			XMPVolumeSlider(QWidget *parent = nullptr);
			~XMPVolumeSlider();

		protected:
			virtual void focusOutEvent(QFocusEvent *event) override;
		};
	}
}