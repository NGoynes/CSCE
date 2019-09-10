#include "GenreCompare.h"

bool GenreCompare::operator()(const Song *a, const Song *b)
{
	/* Your comparison logic here... */
	return (a->genre < b->genre);

}

bool GenreCompare::operator()(const Song *song, const std::string &genre)
{
	/* Your comparison logic here... */
	return (song->genre < genre);
}


bool GenreCompare::operator()(const std::string &genre, const Song *song)
{
	/* Your comparison logic here... */
	return (genre < song->genre);
}
