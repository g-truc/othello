/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_rand.h, 21/03/2003						*
\***********************************************/

#ifndef GTL_RAND_H
#define GTL_RAND_H

#include <stdlib.h>
#include <time.h>

namespace gtl {

inline void RandInit (long iStart = clock ())	{srand (iStart);}
inline float RandFloat ()						{return rand () / ((float)RAND_MAX);}
inline long RandFloat (long iMax)				{return (long) (RandFloat () * iMax);}
inline float RandFloat (float fMin, float fMax)	{return ((RandFloat () * (fMax - fMin)) + fMin);}
inline long RandInt (long iMin, long iMax)		{return (long) (((float)rand () / RAND_MAX * (iMax - iMin )) + iMin);}

}; // namespace gtl

#endif//GTL_RAND_H
