#include "ArtistCompare.h"

bool ArtistCompare::operator()(const Song *a, const Song *b)
{
	/* Your comparison logic here... */
	return (a->artist < b->artist);

}

bool ArtistCompare::operator()(const Song *song, const std::string &artist)
{
	/* Your comparison logic here... */
	return (song->artist < artist);
}


bool ArtistCompare::operator()(const std::string &artist, const Song *song)
{
	/* Your comparison logic here... */
	return (artist < song->artist);
}
