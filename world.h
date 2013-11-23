#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <deque>

#include <Wt/WStandardItemModel>

#include <boost/thread.hpp>

class World
{
public:
	World();
	~World();
	void init();
	void Get(Wt::WStandardItemModel* model);

private:
	std::deque<std::time_t> m_Times;
	std::deque<int> m_Line0;
	std::deque<int> m_Line1;
	std::deque<int> m_Line2;
	std::deque<int> m_Line3;
	std::deque<int> m_Line4;

	boost::thread m_WorldUpdate;
	boost::mutex m_UpdateMutex;
	bool m_ThreadRunning;
	void Update(int);

};
