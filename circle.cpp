#include "circle.h"

SmallCircle::SmallCircle(Wt::WContainerWidget* parent)
    : WPaintedWidget(parent)
  {
    resize(25, 25);
  }

void SmallCircle::paintEvent(WPaintDevice *paintDevice)
{
	WPainter painter(paintDevice);
	Wt::WPen pen (color);
	Wt::WBrush brush (color);
	painter.setPen(pen);
	painter.setBrush(brush);
	painter.setShadow(WShadow(2, 2, WColor(0, 0, 0, 0x20), 2));
	painter.setRenderHint(WPainter::Antialiasing);
	painter.drawEllipse(WRectF(3, 3, 20, 20));
}

