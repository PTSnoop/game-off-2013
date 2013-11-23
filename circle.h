#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WPaintedWidget>
#include <Wt/WPainterPath>
#include <Wt/WPainter>

using namespace Wt;

class SmallCircle : public Wt::WPaintedWidget
{
public:

  SmallCircle(Wt::WContainerWidget* parent);
  void paintEvent(WPaintDevice *paintDevice);
  WColor color;
};
