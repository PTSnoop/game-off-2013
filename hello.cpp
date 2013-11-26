#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
#include <Wt/WSlider>
#include <Wt/WTimer>

#include <boost/thread.hpp>

#include "world.h"
#include "circle.h"
#include "score.h"

using namespace std;
using namespace Wt;

class HelloApplication : public WApplication
{
public:
	HelloApplication(const WEnvironment& env);
	~HelloApplication();

	void Slider1Slid(int slider);
	void Slider2Slid(int slider);
	void Slider3Slid(int slider);
	void Slider4Slid(int slider);
	void Slider5Slid(int slider);
	void SlidersSlid(float,float,float,float,float);
	void labelSliders();

	Score currentScore;
	Score potentialScore;

	float cost1;
	float cost2;
	float cost3;
	float cost4;
	float cost5;

	float totalWorth();
	float totalPotentialWorth();

	void Reset();
	void Trade();

	World* g_World;

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

	Wt::WSlider *slider1;
	Wt::WSlider *slider2;
	Wt::WSlider *slider3;
	Wt::WSlider *slider4;
	Wt::WSlider *slider5;

	Wt::WText* slider1label;
	Wt::WText* slider2label;
	Wt::WText* slider3label;
	Wt::WText* slider4label;
	Wt::WText* slider5label;

	Wt::WTimer *timer;

	boost::thread m_UpdateThread;
	boost::mutex m_UpdateMutex;
	bool m_ThreadRunning;
	void Update(int);
	void UpdateEvent();
};

float HelloApplication::totalWorth()
{
	return (currentScore.reds*cost1) + (currentScore.greens*cost2) + (currentScore.blues*cost3) + (currentScore.teals*cost4) + (currentScore.blacks*cost5);
}


float HelloApplication::totalPotentialWorth()
{
	return (potentialScore.reds*cost1) + (potentialScore.greens*cost2) + (potentialScore.blues*cost3) + (potentialScore.teals*cost4) + (potentialScore.blacks*cost5);
}

HelloApplication::HelloApplication(const WEnvironment& env)
: WApplication(env)
, currentScore()
, potentialScore()
{
	g_World = new World();
	g_World->init();

	currentScore.blacks = 500.0;

	potentialScore = currentScore.copy();

	setTitle("Graphs Go Up And Down");
	useStyleSheet("main.css");
	setCssTheme("things2");

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
	bigmoneybox = new Wt::WContainerWidget();
	Wt::WVBoxLayout* bigmoneyboxlayout = new Wt::WVBoxLayout();
	bigmoneyboxlayout->setContentsMargins(0, 0, 0, 0);
	bigmoneybox->setLayout(bigmoneyboxlayout);
	bigmoneyboxlayout->addWidget(bigmoney,1,AlignCenter);
	numberboxboxlayout->addWidget(bigmoneybox);

	numberboxboxlayout->addWidget(numberbox,2);

	circ1box = new Wt::WContainerWidget();
	circ1 = new SmallCircle(circ1box);
	circ1->color = WColor(0xcb,0x2e,0x2e,255);
	numberboxlayout->addWidget(circ1box,0,0,AlignCenter | AlignMiddle);
	line1current = new Wt::WText(L"0.0");
	numberboxlayout->addWidget(line1current,0,1,AlignRight | AlignMiddle);
	line1value = new Wt::WText(L"0.0");
	numberboxlayout->addWidget(line1value,0,2,AlignRight | AlignMiddle);

	circ2box = new Wt::WContainerWidget();
	circ2 = new SmallCircle(circ2box);
	circ2->color = WColor(0x2f, 0xcb, 0x2e,255);
	numberboxlayout->addWidget(circ2box,1,0,AlignCenter | AlignMiddle);
	line2current = new Wt::WText(L"0.0");
	numberboxlayout->addWidget(line2current,1,1,AlignRight | AlignMiddle);
	line2value = new Wt::WText(L"0.0");
	numberboxlayout->addWidget(line2value,1,2,AlignRight | AlignMiddle);

	circ3box = new Wt::WContainerWidget();
	circ3 = new SmallCircle(circ3box);
	circ3->color = WColor(0x00, 0x45, 0x86,255);
	numberboxlayout->addWidget(circ3box,2,0,AlignCenter | AlignMiddle);
	line3current = new Wt::WText(L"0.0");
	numberboxlayout->addWidget(line3current,2,1,AlignRight | AlignMiddle);
	line3value = new Wt::WText(L"0.0");
	numberboxlayout->addWidget(line3value,2,2,AlignRight | AlignMiddle);

	circ4box = new Wt::WContainerWidget();
	circ4 = new SmallCircle(circ4box);
	circ4->color = WColor(0x2e, 0xc8, 0xce,255);
	numberboxlayout->addWidget(circ4box,3,0,AlignCenter | AlignMiddle);
	line4current = new Wt::WText(L"0.0");
	numberboxlayout->addWidget(line4current,3,1,AlignRight | AlignMiddle);
	line4value = new Wt::WText(L"0.0");
	numberboxlayout->addWidget(line4value,3,2,AlignRight | AlignMiddle);

	circ5box = new Wt::WContainerWidget();
	circ5 = new SmallCircle(circ5box);
	circ5->color = WColor(0x88,0x88,0x88,255);
	numberboxlayout->addWidget(circ5box,4,0,AlignCenter | AlignMiddle);
	line5current = new Wt::WText(L"1.0");
	numberboxlayout->addWidget(line5current,4,1,AlignRight | AlignMiddle);
	line5value = new Wt::WText(L"500.0");
	numberboxlayout->addWidget(line5value,4,2,AlignRight | AlignMiddle);
	
	vspace = new Wt::WContainerWidget();
	sidebarlayout->addWidget(vspace,1);

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

	controlsbox = new Wt::WContainerWidget();
	controlsbox->setStyleClass("whitebox");
	sidebarlayout->addWidget(controlsbox);

	Wt::WVBoxLayout* controlsboxlayout = new Wt::WVBoxLayout();
	controlsbox->setLayout(controlsboxlayout);
	controlsboxlayout->setContentsMargins(20, 0, 20, 20);

	Wt::WContainerWidget* controlsboxgridbox = new Wt::WContainerWidget();
	controlsboxlayout->addWidget(controlsboxgridbox,1);
	Wt::WGridLayout* controlsboxgrid = new Wt::WGridLayout();
	controlsboxgridbox->setLayout(controlsboxgrid);

	SmallCircle* ccirc1 = new SmallCircle(controlsbox);
	ccirc1->color = WColor(0xcb,0x2e,0x2e,255);
	controlsboxgrid->addWidget(ccirc1,0,0,AlignCenter | AlignMiddle);
	SmallCircle* ccirc2 = new SmallCircle(controlsbox);
	ccirc2->color = WColor(0x2f, 0xcb, 0x2e,255);
	controlsboxgrid->addWidget(ccirc2,1,0,AlignCenter | AlignMiddle);
	SmallCircle* ccirc3 = new SmallCircle(controlsbox);
	ccirc3->color = WColor(0x00, 0x45, 0x86,255);
	controlsboxgrid->addWidget(ccirc3,2,0,AlignCenter | AlignMiddle);
	SmallCircle* ccirc4 = new SmallCircle(controlsbox);
	ccirc4->color = WColor(0x2e, 0xc8, 0xce,255);
	controlsboxgrid->addWidget(ccirc4,3,0,AlignCenter | AlignMiddle);
	SmallCircle* ccirc5 = new SmallCircle(controlsbox);
	ccirc5->color = WColor(0x88,0x88,0x88,255);
	controlsboxgrid->addWidget(ccirc5,4,0,AlignCenter | AlignMiddle);

	slider1 = new Wt::WSlider();
	slider1->resize(150, 50);
	slider1->setMinimum(0);
	slider1->setMaximum(100);
	slider1->setValue(0);
	slider1->sliderMoved().connect(this,&HelloApplication::Slider1Slid);
	controlsboxgrid->addWidget(slider1,0,1,AlignCenter | AlignMiddle);

	slider2 = new Wt::WSlider();
	slider2->resize(150, 50);
	slider2->setMinimum(0);
	slider2->setMaximum(100);
	slider2->setValue(0);
	slider2->sliderMoved().connect(this,&HelloApplication::Slider2Slid);
	controlsboxgrid->addWidget(slider2,1,1,AlignCenter | AlignMiddle);

	slider3 = new Wt::WSlider();
	slider3->resize(150, 50);
	slider3->setMinimum(0);
	slider3->setMaximum(100);
	slider3->setValue(0);
	slider3->sliderMoved().connect(this,&HelloApplication::Slider3Slid);
	controlsboxgrid->addWidget(slider3,2,1,AlignCenter | AlignMiddle);

	slider4 = new Wt::WSlider();
	slider4->resize(150, 50);
	slider4->setMinimum(0);
	slider4->setMaximum(100);
	slider4->setValue(0);
	slider4->sliderMoved().connect(this,&HelloApplication::Slider4Slid);
	controlsboxgrid->addWidget(slider4,3,1,AlignCenter | AlignMiddle);

	slider5 = new Wt::WSlider();
	slider5->resize(150, 50);
	slider5->setMinimum(0);
	slider5->setMaximum(100);
	slider5->setValue(100);
	slider5->sliderMoved().connect(this,&HelloApplication::Slider5Slid);
	controlsboxgrid->addWidget(slider5,4,1,AlignCenter | AlignMiddle);

	slider1label = new Wt::WText(L"   ");
	controlsboxgrid->addWidget(slider1label,0,2,AlignRight | AlignMiddle);
	slider2label = new Wt::WText(L"   ");
	controlsboxgrid->addWidget(slider2label,1,2,AlignRight | AlignMiddle);
	slider3label = new Wt::WText(L"   ");
	controlsboxgrid->addWidget(slider3label,2,2,AlignRight | AlignMiddle);
	slider4label = new Wt::WText(L"   ");
	controlsboxgrid->addWidget(slider4label,3,2,AlignRight | AlignMiddle);
	slider5label = new Wt::WText(L"   ");
	controlsboxgrid->addWidget(slider5label,4,2,AlignRight | AlignMiddle);

	Wt::WPushButton *resetbutton = new Wt::WPushButton("Reset");
	resetbutton->setStyleClass("button");
	resetbutton->clicked().connect(this,&HelloApplication::Reset);
	Wt::WPushButton *buybutton = new Wt::WPushButton("Trade");
	buybutton->setStyleClass("button");
	buybutton->clicked().connect(this,&HelloApplication::Trade);
	controlsboxlayout->addWidget(resetbutton);
	controlsboxlayout->addWidget(buybutton);

	UpdateEvent();
	timer = new Wt::WTimer();
	timer->setInterval(1000);
	timer->timeout().connect(this, &HelloApplication::UpdateEvent);
	timer->start();

	//m_UpdateEvent = new EventSignal<>("EventSignal",this);
	//m_UpdateEvent->connect(this, &HelloApplication::UpdateEvent);

	//m_ThreadRunning = true;
	//m_UpdateThread = boost::thread(boost::bind(&HelloApplication::Update, this, 1000));
}

void HelloApplication::Reset()
{
	potentialScore = currentScore.copy();
	float hundred = 100; // This made sense in context, honest
	float s1 = hundred * (potentialScore.reds	*cost1/totalPotentialWorth());
	float s2 = (hundred * (potentialScore.greens	*cost2/totalPotentialWorth()));
	float s3 = (hundred * (potentialScore.blues	*cost3/totalPotentialWorth()));
	float s4 = (hundred * (potentialScore.teals	*cost4/totalPotentialWorth()));
	float s5 = (hundred * (potentialScore.blacks	*cost5/totalPotentialWorth()));
	slider1->setValue(s1);
	slider2->setValue(s2);
	slider3->setValue(s3);
	slider4->setValue(s4);
	slider5->setValue(s5);
	SlidersSlid(s1,s2,s3,s4,s5);

	//slider1label->setText("   ");
	//slider2label->setText("   ");
	//slider3label->setText("   ");
	//slider4label->setText("   ");
	//slider5label->setText("   ");
}

void HelloApplication::Trade()
{
	currentScore = potentialScore.copy();
	SlidersSlid(slider1->value(),slider2->value(),slider3->value(),slider4->value(),slider5->value());
	//slider1label->setText("   ");
	//slider2label->setText("   ");
	//slider3label->setText("   ");
	//slider4label->setText("   ");
	//slider5label->setText("   ");
}

void HelloApplication::Slider1Slid(int s1)
{
	float s2 = slider2->value();
	float s3 = slider3->value();
	float s4 = slider4->value();
	float s5 = slider5->value();

	float totalPerc = s1+s2+s3+s4+s5;

	while (totalPerc <= 99.0)
	{
		s5 += 0.1;
		totalPerc = s1+s2+s3+s4+s5;
	}

	while (totalPerc > 101.0)
	{
		s2 *= 0.99;
		s3 *= 0.99;
		s4 *= 0.99;
		s5 *= 0.99;
		totalPerc = s1+s2+s3+s4+s5;
	}
	slider2->setValue(s2);
	slider3->setValue(s3);
	slider4->setValue(s4);
	slider5->setValue(s5);
	SlidersSlid(s1,s2,s3,s4,s5);
}
void HelloApplication::Slider2Slid(int s2)
{
	float s1 = slider1->value();
	float s3 = slider3->value();
	float s4 = slider4->value();
	float s5 = slider5->value();

	float totalPerc = s1+s2+s3+s4+s5;

	while (totalPerc <= 99.0)
	{
		s5 += 0.1;
		totalPerc = s1+s2+s3+s4+s5;
	}

	while (totalPerc > 101.0)
	{
		s1 *= 0.99;
		s3 *= 0.99;
		s4 *= 0.99;
		s5 *= 0.99;
		totalPerc = s1+s2+s3+s4+s5;
	}
	slider1->setValue(s1);
	slider3->setValue(s3);
	slider4->setValue(s4);
	slider5->setValue(s5);
	SlidersSlid(s1,s2,s3,s4,s5);
}
void HelloApplication::Slider3Slid(int s3)
{
	float s2 = slider2->value();
	float s1 = slider1->value();
	float s4 = slider4->value();
	float s5 = slider5->value();

	float totalPerc = s1+s2+s3+s4+s5;

	while (totalPerc <= 99.0)
	{
		s5 += 0.1;
		totalPerc = s1+s2+s3+s4+s5;
	}

	while (totalPerc > 101.0)
	{
		s1 *= 0.99;
		s2 *= 0.99;
		s4 *= 0.99;
		s5 *= 0.99;
		totalPerc = s1+s2+s3+s4+s5;
	}
	slider2->setValue(s2);
	slider1->setValue(s1);
	slider4->setValue(s4);
	slider5->setValue(s5);
	SlidersSlid(s1,s2,s3,s4,s5);
}
void HelloApplication::Slider4Slid(int s4)
{
	float s2 = slider2->value();
	float s3 = slider3->value();
	float s1 = slider1->value();
	float s5 = slider5->value();

	float totalPerc = s1+s2+s3+s4+s5;

	while (totalPerc <= 99.0)
	{
		s5 += 0.1;
		totalPerc = s1+s2+s3+s4+s5;
	}

	while (totalPerc > 101.0)
	{
		s2 *= 0.99;
		s3 *= 0.99;
		s1 *= 0.99;
		s5 *= 0.99;
		totalPerc = s1+s2+s3+s4+s5;
	}
	slider2->setValue(s2);
	slider3->setValue(s3);
	slider1->setValue(s1);
	slider5->setValue(s5);
	SlidersSlid(s1,s2,s3,s4,s5);
}
void HelloApplication::Slider5Slid(int s5)
{
	float s2 = slider2->value();
	float s3 = slider3->value();
	float s4 = slider4->value();
	float s1 = slider1->value();

	float totalPerc = s1+s2+s3+s4+s5;

	while (totalPerc <= 99.0)
	{
		s2 += 0.1;
		s3 += 0.1;
		s4 += 0.1;
		s1 += 0.1;
		totalPerc = s1+s2+s3+s4+s5;
	}

	while (totalPerc > 101.0)
	{
		s2 *= 0.99;
		s3 *= 0.99;
		s4 *= 0.99;
		s1 *= 0.99;
		totalPerc = s1+s2+s3+s4+s5;
	}
	slider2->setValue(s2);
	slider3->setValue(s3);
	slider4->setValue(s4);
	slider1->setValue(s1);
	SlidersSlid(s1,s2,s3,s4,s5);
}

void HelloApplication::SlidersSlid(float s1, float s2, float s3, float s4, float s5)
{
	float hundred = s1+s2+s3+s4+s5;
	potentialScore.reds =   (s1/hundred) * totalWorth() / cost1;
	potentialScore.greens = (s2/hundred) * totalWorth() / cost2;
	potentialScore.blues =  (s3/hundred) * totalWorth() / cost3;
	potentialScore.teals =  (s4/hundred) * totalWorth() / cost4;
	potentialScore.blacks = (s5/hundred) * totalWorth() / cost5;
	
	labelSliders();
}

void HelloApplication::labelSliders()
{
	char buffer [64];

	float gain1 = (potentialScore.reds - currentScore.reds)*cost1;
	if (gain1 > 0.1 || gain1 < -0.1)
	{
		sprintf(buffer,"%+0.01f",gain1);
		slider1label->setText(buffer);
	}
	else
	{
		slider1label->setText("   ");
	}

	float gain2 = (potentialScore.greens - currentScore.greens)*cost2;
	if (gain2 > 0.1 || gain2 < -0.1)
	{
		sprintf(buffer,"%+0.01f",gain2);
		slider2label->setText(buffer);
	}
	else
	{
		slider2label->setText("   ");
	}

	float gain3 = (potentialScore.blues - currentScore.blues)*cost3;
	if (gain3 > 0.1 || gain3 < -0.1)
	{
		sprintf(buffer,"%+0.01f",gain3);
		slider3label->setText(buffer);
	}
	else
	{
		slider3label->setText("   ");
	}

	float gain4 = (potentialScore.teals - currentScore.teals)*cost4;
	if (gain4 > 0.1 || gain4 < -0.1)
	{
		sprintf(buffer,"%+0.01f",gain4);
		slider4label->setText(buffer);
	}
	else
	{
		slider4label->setText("   ");
	}

	float gain5 = (potentialScore.blacks - currentScore.blacks)*cost5;
	if (gain5 > 0.1 || gain5 < -0.1)
	{
		sprintf(buffer,"%+0.01f",gain5);
		slider5label->setText(buffer);
	}
	else
	{
		slider5label->setText("   ");
	}

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

float GetValueFromModelItem(Wt::WStandardItem* item)
{
	std::string data1 = item->text().toUTF8();
	return atof(data1.c_str());
}

void HelloApplication::UpdateEvent()
{
	g_World->Get(model);

	cost1 = GetValueFromModelItem(model->item(99,1));
	cost2 = GetValueFromModelItem(model->item(99,2));
	cost3 = GetValueFromModelItem(model->item(99,3));
	cost4 = GetValueFromModelItem(model->item(99,4));
	cost5 = 1.0;

	char buffer [64];

	sprintf(buffer,"%0.01f",cost1);
	line1current->setText(buffer);
	sprintf(buffer,"%0.01f",cost2);
	line2current->setText(buffer);
	sprintf(buffer,"%0.01f",cost3);
	line3current->setText(buffer);
	sprintf(buffer,"%0.01f",cost4);
	line4current->setText(buffer);
	sprintf(buffer,"%0.01f",cost5);
	line5current->setText(buffer);

	sprintf(buffer,"%0.01f",currentScore.reds*cost1);
	line1value->setText(buffer);
	sprintf(buffer,"%0.01f",currentScore.greens*cost2);
	line2value->setText(buffer);
	sprintf(buffer,"%0.01f",currentScore.blues*cost3);
	line3value->setText(buffer);
	sprintf(buffer,"%0.01f",currentScore.teals*cost4);
	line4value->setText(buffer);
	sprintf(buffer,"%0.01f",currentScore.blacks*cost5);
	line5value->setText(buffer);

	sprintf(buffer,"%0.01f",totalWorth());
	bigmoney->setText(buffer);

	SlidersSlid(slider1->value(),slider2->value(),slider3->value(),slider4->value(),slider5->value());

	//float hundred = slider1->value() + slider2->value() + slider3->value() + slider4->value() + slider5->value();
	//slider1->setValue(hundred * (potentialScore.reds	*cost1/totalPotentialWorth()));
	//slider2->setValue(hundred * (potentialScore.greens	*cost2/totalPotentialWorth()));
	//slider3->setValue(hundred * (potentialScore.blues	*cost3/totalPotentialWorth()));
	//slider4->setValue(hundred * (potentialScore.teals	*cost4/totalPotentialWorth()));
	//slider5->setValue(hundred * (potentialScore.blacks	*cost5/totalPotentialWorth()));

	labelSliders();
}

HelloApplication::~HelloApplication()
{
	m_ThreadRunning = false;
	m_UpdateThread.join();

	delete g_World;
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
	srand(time(NULL));
	return WRun(argc, argv, &createApplication);
}


