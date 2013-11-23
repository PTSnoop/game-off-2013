#include "world.h"

#include <Wt/WDateTime>

World::World()
{
}

World::~World()
{
	m_ThreadRunning = false;
	m_WorldUpdate.join();
}

void World::init()
{
	printf("INIT\n");

	long int currentEpoch;
	time(&currentEpoch);
	//currentEpoch -= 100;

	int iLine0 = 1;
	int iLine1 = 300;
	int iLine2 = 300;
	int iLine3 = 300;
	int iLine4 = 300;

	for (int i=0; i<100; ++i)
	{
		m_Times.push_back(currentEpoch);
		m_Line0.push_back(iLine0);
		m_Line1.push_back(iLine1);
		m_Line2.push_back(iLine2);
		m_Line3.push_back(iLine3);
		m_Line4.push_back(iLine4);

		currentEpoch += 1;

		iLine0 += 1;
		iLine1 += (rand()%20) - 10;
		iLine2 += (rand()%20) - 10;
		iLine3 += (rand()%20) - 10;
		iLine4 += (rand()%20) - 10;
		
	}
	m_ThreadRunning = true;
	m_WorldUpdate = boost::thread(boost::bind(&World::Update, this, 1000));
}

/*
	std::vector<int> m_Line1;
	std::vector<int> m_Line2;
	std::vector<int> m_Line3;
	std::vector<int> m_Line4;


	boost::thread m_WorldUpdate;
	boost::mutex m_UpdateMutex;

*/

void World::Update(int frequency)
{
	printf("BEGIN\n");
	m_ThreadRunning= true;

	while (m_ThreadRunning)
	{
		if (m_ThreadRunning)
		{
			printf("Update\n");
			boost::mutex::scoped_lock lock(m_UpdateMutex);

			m_Times.pop_front();
			m_Line1.pop_front();
			m_Line2.pop_front();
			m_Line3.pop_front();
			m_Line4.pop_front();

			time_t currentEpoch;
			time(&currentEpoch);
			m_Times.push_back(currentEpoch);
			m_Line0.push_back( m_Line0.back() + 1);
			m_Line1.push_back( m_Line1.back() + (rand()%20) - 10 );
			m_Line2.push_back( m_Line2.back() + (rand()%20) - 10 );
			m_Line3.push_back( m_Line3.back() + (rand()%20) - 10 );
			m_Line4.push_back( m_Line4.back() + (rand()%20) - 10 );
		}

		boost::this_thread::sleep(boost::posix_time::milliseconds(frequency));
	} 
}

void World::Get(Wt::WStandardItemModel* model)
{
	boost::mutex::scoped_lock lock(m_UpdateMutex);

    //WStandardItemModel *model = new WStandardItemModel(100, 5, 0);
	// I could do with some asserts in here. Ah well.

    for (unsigned i = 0; i < 100; ++i) {
		model->setData(i, 0, m_Line0[i]);
		model->setData(i, 1, m_Line1[i]);
		model->setData(i, 2, m_Line2[i]);
		model->setData(i, 3, m_Line3[i]);
		model->setData(i, 4, m_Line4[i]);
    }
}
