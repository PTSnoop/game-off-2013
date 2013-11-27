#include "world.h"
#include "math.h"

#include <Wt/WDateTime>

World::World()
{
}

World::~World()
{
	//m_ThreadRunning = false;
	//m_WorldUpdate.join();
}

void World::init()
{
	long int currentEpoch;
	time(&currentEpoch);
	//currentEpoch -= 100;

	float iLine0 = 1;
	float iLine1 = 30;
	float iLine2 = 30;
	float iLine3 = 30;
	float iLine4 = 30;

	for (int i=0; i<100; ++i)
	{
		//m_Times.push_back(currentEpoch);
		m_Line0.push_back(iLine0);
		m_Line1.push_back(iLine1);
		m_Line2.push_back(iLine2);
		m_Line3.push_back(iLine3);
		m_Line4.push_back(iLine4);

		currentEpoch += 1;

		float logline1 = log(iLine1);
		float logline2 = log(iLine2);
		float logline3 = log(iLine3);
		float logline4 = log(iLine4);

		logline1 += ((rand()%20) - 9.0)/1000.0;
		logline2 += ((rand()%20) - 9.0)/1000.0;
		logline3 += ((rand()%20) - 9.0)/1000.0;
		logline4 += ((rand()%20) - 9.0)/1000.0;

		iLine0 += 1;
		iLine1 = exp(logline1);
		iLine2 = exp(logline2);
		iLine3 = exp(logline3);
		iLine4 = exp(logline4);
		
		//iLine1 += (rand()%20) - 9;
		//iLine2 += (rand()%20) - 9;
		//iLine3 += (rand()%20) - 9;
		//iLine4 += (rand()%20) - 9;
		
	}
	m_ThreadRunning = true;
	//m_WorldUpdate = boost::thread(boost::bind(&World::Update, this, 1000));
}

/*
	std::vector<int> m_Line1;
	std::vector<int> m_Line2;
	std::vector<int> m_Line3;
	std::vector<int> m_Line4;


	boost::thread m_WorldUpdate;
	boost::mutex m_UpdateMutex;

*/

void World::Update()
{
	//while (m_ThreadRunning)
	//{
	//	if (m_ThreadRunning)
	//	{
			//boost::mutex::scoped_lock lock(m_UpdateMutex);

			//m_Times.pop_front();
			//m_Line0.pop_front();
			m_Line1.pop_front();
			m_Line2.pop_front();
			m_Line3.pop_front();
			m_Line4.pop_front();

			//time_t currentEpoch;
			//time(&currentEpoch);
			//m_Times.push_back(currentEpoch);
			//m_Line0.push_back( m_Line0.back() + 1);

			float logline1 = log(m_Line1.back());
			float logline2 = log(m_Line2.back());
			float logline3 = log(m_Line3.back());
			float logline4 = log(m_Line4.back());

                	logline1 += ((rand()%20) - 9.0)/1000.0;
                	logline2 += ((rand()%20) - 9.0)/1000.0;
                	logline3 += ((rand()%20) - 9.0)/1000.0;
                	logline4 += ((rand()%20) - 9.0)/1000.0;

	                m_Line1.push_back(exp(logline1));
	                m_Line2.push_back(exp(logline2));
	                m_Line3.push_back(exp(logline3));
	                m_Line4.push_back(exp(logline4));

			//m_Line1.push_back( m_Line1.back() + (rand()%20) - 10 );
			//m_Line2.push_back( m_Line2.back() + (rand()%20) - 10 );
			//m_Line3.push_back( m_Line3.back() + (rand()%20) - 10 );
			//m_Line4.push_back( m_Line4.back() + (rand()%20) - 10 );
//		}
//
//		boost::this_thread::sleep(boost::posix_time::milliseconds(frequency));
//	} 
}

void World::Get(Wt::WStandardItemModel* model)
{
//boost::mutex::scoped_lock lock(m_UpdateMutex);

    //WStandardItemModel *model = new WStandardItemModel(100, 5, 0);
	// I could do with some asserts in here. Ah well.

    for (unsigned i = 0; i < 100; ++i) {
		model->setData(i, 0, m_Line0[i]);//10.0f);
		model->setData(i, 1, m_Line1[i]);//10.0f);
		model->setData(i, 2, m_Line2[i]);//10.0f);
		model->setData(i, 3, m_Line3[i]);//10.0f);
		model->setData(i, 4, m_Line4[i]);//10.0f);
    }
}
