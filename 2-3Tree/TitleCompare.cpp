#include "TitleCompare.h"

bool TitleCompare::operator()(const Song *a, const Song *b)
{
    /* Your comparison logic here... */
	return (a->title < b->title);

}

bool TitleCompare::operator()(const Song *song, const std::string &title)
{
	/* Your comparison logic here... */
	return (song->title < title);
}
    

bool TitleCompare::operator()(const std::string &title, const Song *song)
{
    /* Your comparison logic here... */
	return (title < song->title);
}
