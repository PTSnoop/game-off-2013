#include <Wt/WPaintedWidget>
#include <Wt/WPaintDevice>
#include <Wt/WPainter>
#include <Wt/WHBoxLayout>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>

#include <boost/thread.hpp>

//#include "WtGraphApp.h" 

using namespace std;
using namespace Wt;


class ResizingGraph : public Wt::Chart::WCartesianChart
{
    public:
        ResizingGraph(void) :
            Wt::Chart::WCartesianChart(),
            m_app(Wt::WApplication::instance()),
            m_threadRunning(false)
        {
            setLayoutSizeAware(true);

            m_app->enableUpdates(true);

            m_thread= boost::thread(boost::bind(&ResizingGraph::updateThread, this, 1000));
        }

        ~ResizingGraph()
        {
            m_threadRunning= false;
            m_thread.join();
        }

    private:

        Wt::WApplication* m_app;
        bool m_threadRunning;
        boost::thread m_thread;

        void updateThread(int frequency)
        {
            m_threadRunning= true;

            while (m_threadRunning)
            {
              {
                Wt::WApplication::UpdateLock uiLock(m_app);
                if (uiLock)
                {
                    update(PaintUpdate);
                    m_app->triggerUpdate();
                }
              }
				boost::this_thread::sleep(boost::posix_time::milliseconds(frequency));
                
            }
        }

        virtual void layoutSizeChanged(int width, int height)
        {
            cout << "SIZE CHANGED " << width << " " << height << endl;
            WPaintedWidget::layoutSizeChanged(width, height);
			resize(width,height);
        }

        virtual void paintEvent(Wt::WPaintDevice *paintDevice)
        {
            WPainter painter(paintDevice);

            int widgetWidth= paintDevice->width().toPixels();
            int widgetHeight= paintDevice->height().toPixels();

            ((WBrush&)painter.brush()).setStyle(SolidPattern);
            ((WPen&)painter.pen()).setColor(WColor(0, 0, 0, 255));
            painter.drawRect(0, 0, widgetWidth, widgetHeight);

            painter.setPen(WColor(0, 255, 0, 255));
            ((WPen&)painter.pen()).setWidth(WLength(2, WLength::Pixel));
            painter.drawLine(0, 0, widgetWidth, widgetHeight);
        }
};

