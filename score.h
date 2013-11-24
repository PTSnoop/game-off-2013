#pragma once

class Score
{
public:
	Score();
	Score(Score&);
	float reds;
	float greens;
	float blues;
	float teals;
	float blacks;
	float total();
	Score copy();
	void print();
};
