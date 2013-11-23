#include <stdio.h>
#include <stdlib.h>

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>


#include <Wt/WStandardItem>
#include <Wt/WStandardItemModel>
#include <Wt/WAbstractItemModel>
#include <Wt/WAbstractItemView>
#include <Wt/WItemDelegate>
#include <Wt/WShadow>
#include <Wt/Chart/WCartesianChart>

#include <Wt/WPaintedWidget>
#include <Wt/WPaintDevice>
#include <Wt/WPainter>
#include <Wt/WHBoxLayout>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WTimer>

#include <boost/thread.hpp>

#include "world.h"
#include "circle.h"

using namespace std;
using namespace Wt;

World* g_World;

class HelloApplication : public WApplication
{
public:
	HelloApplication(const WEnvironment& env);
	~HelloApplication();

private:


	Wt::WHBoxLayout *rootlayout;
	Wt::WContainerWidget* graphsbox;
	Wt::WGridLayout *graphslayout;

	Wt::WContainerWidget* graph1;
	Wt::WContainerWidget* graph2;
	Wt::WContainerWidget* graph3;
	Wt::WContainerWidget* graph4;
	Wt::WContainerWidget* graph5;

	Wt::WContainerWidget* sidebar;
	Wt::WVBoxLayout *sidebarlayout;
	Wt::WContainerWidget* numberbox;
	Wt::WGridLayout *numberboxlayout;

	Wt::WText* bigmoney;

	Wt::WContainerWidget* vspace;

	Wt::WContainerWidget* controlsbox;

	WStandardItemModel * model;

	Wt::Chart::WCartesianChart *chart1;
	Wt::Chart::WCartesianChart *chart2;
	Wt::Chart::WCartesianChart *chart3;
	Wt::Chart::WCartesianChart *chart4;

	Wt::WVBoxLayout* graph1layout;
	Wt::WVBoxLayout* graph2layout;
	Wt::WVBoxLayout* graph3layout;
	Wt::WVBoxLayout* graph4layout;

	Wt::EventSignal<>* m_UpdateEvent;

	Wt::WContainerWidget* numberboxbox;
	Wt::WVBoxLayout* numberboxboxlayout;
	Wt::WContainerWidget* bigmoneybox;

	Wt::WContainerWidget* circ1box;
	SmallCircle* circ1;
	Wt::WText* line1current;
	Wt::WText* line1value;

	Wt::WContainerWidget* circ2box;
	SmallCircle* circ2;
	Wt::WText* line2current;
	Wt::WText* line2value;

	Wt::WContainerWidget* circ3box;
	SmallCircle* circ3;
	Wt::WText* line3current;
	Wt::WText* line3value;

	Wt::WContainerWidget* circ4box;
	SmallCircle* circ4;
	Wt::WText* line4current;
	Wt::WText* line4value;

	Wt::WContainerWidget* circ5box;
	SmallCircle* circ5;
	Wt::WText* line5current;
	Wt::WText* line5value;

	Wt::WTimer *timer;

	boost::thread m_UpdateThread;
	boost::mutex m_UpdateMutex;
	bool m_ThreadRunning;
	void Update(int);
	void UpdateEvent();
	void ScrollGraphs();
};

HelloApplication::HelloApplication(const WEnvironment& env)
: WApplication(env)
{
	setTitle("Graphs Go Up And Down");
	useStyleSheet("main.css");

	rootlayout = new Wt::WHBoxLayout();
	rootlayout->setContentsMargins(10, 10, 10, 10);
	root()->setLayout(rootlayout);

	graphsbox = new Wt::WContainerWidget();
	rootlayout->addWidget(graphsbox,1);
	graphslayout = new Wt::WGridLayout();
	graphslayout->setContentsMargins(10, 10, 10, 10);
	graphsbox->setLayout(graphslayout);

	graph1 = new Wt::WContainerWidget();
	graph1->setStyleClass("whitebox");
	graphslayout->addWidget(graph1,0,0);
	graph2 = new Wt::WContainerWidget();
	graph2->setStyleClass("whitebox");
	graphslayout->addWidget(graph2,1,0);
	graph3 = new Wt::WContainerWidget();
	graph3->setStyleClass("whitebox");
	graphslayout->addWidget(graph3,0,1);
	graph4 = new Wt::WContainerWidget();
	graph4->setStyleClass("whitebox");
	graphslayout->addWidget(graph4,1,1);
	//graph5 = new Wt::WContainerWidget();
	//graph5->setStyleClass("whitebox");
	//graphslayout->addWidget(graph5,2,0,0,2);

	graphslayout->setHorizontalSpacing(20);
	graphslayout->setVerticalSpacing(20);

	sidebar = new Wt::WContainerWidget();
	rootlayout->addWidget(sidebar);
	sidebarlayout = new Wt::WVBoxLayout();
	sidebarlayout->setContentsMargins(10, 10, 10, 10);
	sidebar->setLayout(sidebarlayout);

	numberboxbox = new Wt::WContainerWidget();
	numberboxbox->setStyleClass("whitebox");
	sidebarlayout->addWidget(numberboxbox);

	numberboxboxlayout = new Wt::WVBoxLayout();
	numberboxboxlayout->setContentsMargins(10, 10, 10, 10);
	numberboxbox->setLayout(numberboxboxlayout);
	
	numberbox = new Wt::WContainerWidget();
	numberboxlayout = new Wt::WGridLayout();
	numberboxlayout->setContentsMargins(10, 10, 10, 10);
	numberbox->setLayout(numberboxlayout);

	bigmoney = new Wt::WText(L"265.9");
	bigmoney->setStyleClass("bigmoney");
	//bigmoneybox = new Wt::WContainerWidget();
	//bigmoneybox->addWidget(bigmoney);
	numberboxboxlayout->addWidget(bigmoney);//box);

	numberboxboxlayout->addWidget(numberbox,1);

	circ1box = new Wt::WContainerWidget();
	circ1 = new SmallCircle(circ1box);
	circ1->color = WColor(0xcb,0x2e,0x2e,255);
	numberboxlayout->addWidget(circ1box,1,0,AlignCenter);
	line1current = new Wt::WText(L"0.0");
	numberboxlayout->addWidget(line1current,1,1,AlignCenter);
	line1value = new Wt::WText(L"0.0");
	numberboxlayout->addWidget(line1value,1,2,AlignCenter);

	circ2box = new Wt::WContainerWidget();
	circ2 = new SmallCircle(circ2box);
	circ2->color = WColor(0x2f, 0xcb, 0x2e,255);
	numberboxlayout->addWidget(circ2box,2,0,AlignCenter);
	line2current = new Wt::WText(L"0.0");
	numberboxlayout->addWidget(line2current,2,1,AlignCenter);
	line2value = new Wt::WText(L"0.0");
	numberboxlayout->addWidget(line2value,2,2,AlignCenter);

	circ3box = new Wt::WContainerWidget();
	circ3 = new SmallCircle(circ3box);
	circ3->color = WColor(0x00, 0x45, 0x86,255);
	numberboxlayout->addWidget(circ3box,3,0,AlignCenter);
	line3current = new Wt::WText(L"0.0");
	numberboxlayout->addWidget(line3current,3,1,AlignCenter);
	line3value = new Wt::WText(L"0.0");
	numberboxlayout->addWidget(line3value,3,2,AlignCenter);

	circ4box = new Wt::WContainerWidget();
	circ4 = new SmallCircle(circ4box);
	circ4->color = WColor(0x2e, 0xc8, 0xce,255);
	numberboxlayout->addWidget(circ4box,4,0,AlignCenter);
	line4current = new Wt::WText(L"0.0");
	numberboxlayout->addWidget(line4current,4,1,AlignCenter);
	line4value = new Wt::WText(L"0.0");
	numberboxlayout->addWidget(line4value,4,2,AlignCenter);

	circ5box = new Wt::WContainerWidget();
	circ5 = new SmallCircle(circ5box);
	circ5->color = WColor(0x88,0x88,0x88,255);
	numberboxlayout->addWidget(circ5box,5,0,AlignCenter);
	line5current = new Wt::WText(L"1.0");
	numberboxlayout->addWidget(line5current,5,1,AlignCenter);
	line5value = new Wt::WText(L"500.0");
	numberboxlayout->addWidget(line5value,5,2,AlignCenter);
	
	vspace = new Wt::WContainerWidget();
	sidebarlayout->addWidget(vspace);

	controlsbox = new Wt::WContainerWidget();
	controlsbox->setStyleClass("whitebox");
	sidebarlayout->addWidget(controlsbox);

	model = new WStandardItemModel(100, 5, 0);
	g_World->Get(model);

	Wt::WPen pen;
	pen.setWidth(2);
	pen.setColor(WColor(0,0,0,255));

	pen.setColor(WColor(0xcb,0x2e,0x2e,255));
	chart1 = new Wt::Chart::WCartesianChart();
	chart1->setModel(model); 
	chart1->setXSeriesColumn(0);
	chart1->axis(Wt::Chart::XAxis).setVisible(false);
	chart1->setType(Wt::Chart::ScatterPlot);
	chart1->setPlotAreaPadding(5);
	chart1->setPlotAreaPadding(40, Left);
	Wt::Chart::WDataSeries s1(1, Wt::Chart::LineSeries);
	s1.setPen(WPen(pen));
	chart1->addSeries(s1);

	graph1layout = new Wt::WVBoxLayout();
	graph1layout->setContentsMargins(0, 0, 0, 0);
	graph1->setLayout(graph1layout);
	graph1layout->addWidget(chart1,1);
	pen.setColor(WColor(0x2f, 0xcb, 0x2e,255));
	chart2 = new Wt::Chart::WCartesianChart();
	chart2->setModel(model); 
	chart2->setXSeriesColumn(0);
	chart2->axis(Wt::Chart::XAxis).setVisible(false);
	chart2->setType(Wt::Chart::ScatterPlot);
	chart2->setPlotAreaPadding(5);
	chart2->setPlotAreaPadding(40, Left);
	Wt::Chart::WDataSeries s2(2, Wt::Chart::LineSeries);
	s2.setPen(WPen(pen));
	chart2->addSeries(s2);

	graph2layout = new Wt::WVBoxLayout();
	graph2layout->setContentsMargins(0, 0, 0, 0);
	graph2->setLayout(graph2layout);
	graph2layout->addWidget(chart2,1);
	pen.setColor(WColor(0x00, 0x45, 0x86,255));

	chart3 = new Wt::Chart::WCartesianChart();
	chart3->setModel(model); 
	chart3->setXSeriesColumn(0);
	chart3->axis(Wt::Chart::XAxis).setVisible(false);
	chart3->setType(Wt::Chart::ScatterPlot);
	chart3->setPlotAreaPadding(5);
	chart3->setPlotAreaPadding(40, Left);
	Wt::Chart::WDataSeries s3(3, Wt::Chart::LineSeries);
	s3.setPen(WPen(pen));
	chart3->addSeries(s3);

	graph3layout = new Wt::WVBoxLayout();
	graph3layout->setContentsMargins(0, 0, 0, 0);
	graph3->setLayout(graph3layout);
	graph3layout->addWidget(chart3,1);

	pen.setColor(WColor(0x2e, 0xc8, 0xce,255));
	chart4 = new Wt::Chart::WCartesianChart();
	chart4->setModel(model); 
	chart4->setXSeriesColumn(0);
	chart4->axis(Wt::Chart::XAxis).setVisible(false);
	chart4->setType(Wt::Chart::ScatterPlot);
	chart4->setPlotAreaPadding(5);
	chart4->setPlotAreaPadding(40, Left);
	Wt::Chart::WDataSeries s4(4, Wt::Chart::LineSeries);
	s4.setPen(WPen(pen));
	chart4->addSeries(s4);

	graph4layout = new Wt::WVBoxLayout();
	graph4layout->setContentsMargins(0, 0, 0, 0);
	graph4->setLayout(graph4layout);
	graph4layout->addWidget(chart4,1);

	timer = new Wt::WTimer();
	timer->setInterval(1000);
	timer->timeout().connect(this, &HelloApplication::UpdateEvent);
	timer->start();

	//m_UpdateEvent = new EventSignal<>("EventSignal",this);
	//m_UpdateEvent->connect(this, &HelloApplication::UpdateEvent);

	//m_ThreadRunning = true;
	//m_UpdateThread = boost::thread(boost::bind(&HelloApplication::Update, this, 1000));
}

void HelloApplication::Update(int frequency)
{
	m_ThreadRunning= true;

	Wt::WApplication* app = Wt::WApplication::instance();

	while (m_ThreadRunning)
	{
		if (m_ThreadRunning)
		{
			boost::mutex::scoped_lock lock(m_UpdateMutex);
			Wt::WApplication::UpdateLock uiLock(this);
			if (uiLock)
			{
				m_UpdateEvent->emit();
				enableUpdates(true);
			}
		}
		boost::this_thread::sleep(boost::posix_time::milliseconds(frequency));
	} 
}

void HelloApplication::UpdateEvent()
{
	ScrollGraphs();

}

void SetStandardItemLabel(Wt::WText* label, Wt::WStandardItem* item)
{
	std::string data1 = item->text().toUTF8();
	float float1 = atof(data1.c_str());

	char buffer [16];
	sprintf(buffer,"%0.01f",float1);
	label->setText(buffer);

	
}

void HelloApplication::ScrollGraphs()
{
	g_World->Get(model);

	SetStandardItemLabel(line1current,model->item(99,1));
	SetStandardItemLabel(line2current,model->item(99,2));
	SetStandardItemLabel(line3current,model->item(99,3));
	SetStandardItemLabel(line4current,model->item(99,4));
	
	//chart1->setModel(model);
	//chart2->setModel(model);
	//chart3->setModel(model);
	//chart4->setModel(model);
}

HelloApplication::~HelloApplication()
{
	m_ThreadRunning = false;
	m_UpdateThread.join();
/*
	delete controlsbox;

	delete vspace;

	delete bigmoney;

	delete numberboxlayout;
	delete numberbox;
	delete sidebarlayout;
	delete sidebar;

	delete graph5;
	delete graph4;
	delete graph3;
	delete graph2;
	delete graph1;

	delete graphslayout;
	delete graphsbox;
	delete rootlayout;
*/
}


WApplication *createApplication(const WEnvironment& env)
{
	return new HelloApplication(env);
}

int main(int argc, char **argv)
{
	g_World = new World();
	g_World->init();
	return WRun(argc, argv, &createApplication);
}


