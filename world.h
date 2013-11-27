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
	void Update();

private:
	std::deque<std::time_t> m_Times;
	std::deque<float> m_Line0;
	std::deque<float> m_Line1;
	std::deque<float> m_Line2;
	std::deque<float> m_Line3;
	std::deque<float> m_Line4;

	boost::mutex m_UpdateMutex;
	bool m_ThreadRunning;

};
