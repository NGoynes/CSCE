#ifndef ALBUM_COMPARE_H
#define ALBUM_COMPARE_H

/* Declaration of the comparison functor for use with the Album index */

#include <string>
#include "Song.h"

struct AlbumCompare
{
	/*
	 * Return whether or not song a's album is
	 * lexicographically less than song b's album
	 */
	bool operator()(const Song *a, const Song *b);

	/*
	 * Return whether or not the song's album is
	 * lexicographically less than the given album
	 */
	bool operator()(const Song *song, const std::string &album);

	/*
	 * Return whether or not the given album is
	 * lexicographically less than the song's album
	 */
	bool operator()(const std::string &album, const Song *song);
};

#endif