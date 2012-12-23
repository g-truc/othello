/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_def.h, 21/03/2003						*
\***********************************************/

#ifndef GTL_DEF_H
#define GTL_DEF_H

namespace gtl {

#define GTL_ALPHA_3_00

typedef signed char int08;
typedef unsigned char uint08;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed long int32;
typedef unsigned long uint32;
#ifdef _WIN32
typedef signed __int64 int64;
typedef unsigned __int64 uint64;
#else //__linux__
typedef signed long long int64;
typedef unsigned long long uint64;
#endif 

}; // namespace gtl

#endif //GTL_DEF_H
