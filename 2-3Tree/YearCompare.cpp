#include "YearCompare.h"

bool YearCompare::operator()(const Song *a, const Song *b)
{
	/* Your comparison logic here... */
	return (a->year < b->year);

}

bool YearCompare::operator()(const Song *song, const unsigned long &year)
{
	/* Your comparison logic here... */
	return (song->year < year);
}


bool YearCompare::operator()(const unsigned long &year, const Song *song)
{
	/* Your comparison logic here... */
	return (year < song->year);
}
