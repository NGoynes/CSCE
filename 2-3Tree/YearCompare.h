#ifndef YEAR_COMPARE_H
#define YEAR_COMPARE_H

/* Declaration of the comparison functor for use with the Year index */

#include <string>
#include "Song.h"

struct YearCompare
{
	/*
	 * Return whether or not song a's year is
	 * numerically less than song b's year
	 */
	bool operator()(const Song *a, const Song *b);

	/*
	 * Return whether or not the song's year is
	 * numerically less than the given year
	 */
	bool operator()(const Song *song, const unsigned long &year);

	/*
	 * Return whether or not the given year is
	 * numerically less than the song's year
	 */
	bool operator()(const unsigned long &year, const Song *song);
};

#endif