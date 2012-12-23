/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_dll.h, 21/03/2003						*
\***********************************************/

#ifndef GTL_DLL_H
#define GTL_DLL_H

namespace gtl {

//#ifdef _WIN32
#define EXPORT __declspec (dllexport);
#define IMPORT __declspec (dllimport);
//#endif //_WIN32

}; // namespace gtl

#endif//GTL_DLL_H