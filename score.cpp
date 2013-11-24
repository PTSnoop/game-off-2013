#include "score.h"
#include <stdio.h>

Score::Score()
{
	reds = 0;
	greens = 0;
	blues = 0;
	teals = 0;
	blacks = 500;
}

Score::Score(Score& sc)
{
	reds = sc.reds;
	greens = sc.greens;
	blues = sc.blues;
	teals = sc.teals;
	blacks = sc.blacks;
}

float Score::total()
{
	return reds+greens+blues+teals+blacks;
}

Score Score::copy()
{
	Score newscore;
	newscore.reds = reds;
	newscore.greens = greens;
	newscore.blues = blues;
	newscore.teals = teals;
	newscore.blacks = blacks;
	return newscore;
}

void Score::print()
{
	printf("REDS: %f\n",reds);
	printf("GREENS: %f\n",greens);
	printf("BLUES: %f\n",blues);
	printf("TEALS: %f\n",teals);
	printf("BLACKS: %f\n",blacks);
}
