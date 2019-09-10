#include "AlbumCompare.h"

bool AlbumCompare::operator()(const Song *a, const Song *b)
{
	/* Your comparison logic here... */
	return (a->album < b->album);

}

bool AlbumCompare::operator()(const Song *song, const std::string &album)
{
	/* Your comparison logic here... */
	return (song->album < album);
}


bool AlbumCompare::operator()(const std::string &album, const Song *song)
{
	/* Your comparison logic here... */
	return (album < song->album);
}
