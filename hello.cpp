/*
* Copyright (C) 2008 Emweb bvba, Heverlee, Belgium.
*
* See the LICENSE file for terms of use.
*/

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


#include <Wt/WStandardItemModel>
#include <Wt/WAbstractItemModel>
#include <Wt/WAbstractItemView>
#include <Wt/WItemDelegate>
#include <Wt/WShadow>
#include <Wt/Chart/WCartesianChart>

// c++0x only, for std::bind
// #include <functional>

#include <Wt/WPaintedWidget>
#include <Wt/WPaintDevice>
#include <Wt/WPainter>
#include <Wt/WHBoxLayout>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>

//#include <Windows.h>

#include <boost/thread.hpp>

#include "world.h"

using namespace std;
using namespace Wt;

World* g_World;

class HelloApplication : public WApplication
{
public:
	HelloApplication(const WEnvironment& env);

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
/////

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
	graphslayout->addWidget(graph2,0,1);
	graph3 = new Wt::WContainerWidget();
	graph3->setStyleClass("whitebox");
	graphslayout->addWidget(graph3,1,0);
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

	numberbox = new Wt::WContainerWidget();
	numberbox->setStyleClass("whitebox");
	sidebarlayout->addWidget(numberbox);

	numberboxlayout = new Wt::WGridLayout();
	numberboxlayout->setContentsMargins(10, 10, 10, 10);
	numberbox->setLayout(numberboxlayout);

	bigmoney = new Wt::WText(L"265.9");
	numberboxlayout->addWidget(bigmoney,0,0);
	
	vspace = new Wt::WContainerWidget();
	sidebarlayout->addWidget(vspace);

	controlsbox = new Wt::WContainerWidget();
	controlsbox->setStyleClass("whitebox");
	sidebarlayout->addWidget(controlsbox);


  WStandardItemModel *model = new WStandardItemModel(40, 2, this);
  model->setHeaderData(0, WString("X"));
  model->setHeaderData(1, WString("Y = sin(X)"));

  int j = 200;

  for (unsigned i = 0; i < 40; ++i) {
    
    model->setData(i, 0, i);
    model->setData(i, 1, j );
    j = j - 10 + (rand()%20);
  }

	Wt::Chart::WCartesianChart *chart = new Wt::Chart::WCartesianChart();
	chart->setModel(model); 
	chart->setXSeriesColumn(0); 


	chart->setType(Wt::Chart::ScatterPlot);

	chart->setPlotAreaPadding(5);
	chart->setPlotAreaPadding(30, Bottom);
	chart->setPlotAreaPadding(50, Left);

	Wt::Chart::WDataSeries s(1, Wt::Chart::LineSeries);
	//s.setShadow(WShadow(3, 3, WColor(0, 0, 0, 127), 3));
	chart->addSeries(s);

	//chart->setMargin(10, Top | Bottom);
	//chart->setMargin(WLength::Auto, Left | Right);

	Wt::WVBoxLayout* graph1layout = new Wt::WVBoxLayout();
	graph1layout->setContentsMargins(0, 0, 0, 0);
	graph1->setLayout(graph1layout);
	graph1layout->addWidget(chart,1);
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


