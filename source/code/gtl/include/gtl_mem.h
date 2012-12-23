/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_mem.h, 21/03/2003						*
\***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
namespace gtl {

#ifdef _DEBUG
	#define FREE(pMem)												\
	if (pMem)														\
	{																\
		free (pMem);												\
		(pMem) = NULL;												\
		printf ("GTL MEM INFO : Memory free\n");					\
	}																\
	else															\
	{																\
		printf ("GTL MEM WARNING : Memory allready free\n");		\
	}
#else // RELEASE
	#define FREE(pMem)												\
	if (pMem)														\
	{																\
		free (pMem);												\
		(pMem) = NULL;												\
	}
#endif // _DEBUG

#ifdef _DEBUG
	#define DELETE(pMem)											\
	if (pMem)														\
	{																\
		delete (pMem);												\
		(pMem) = NULL;												\
		printf ("GTL MEM INFO : Memory free\n");					\
	}																\
	else															\
	{																\
		printf ("GTL MEM WARNING : Memory allready free\n");		\
	}
#else // RELEASE
	#define DELETE(pMem)											\
	if (pMem)														\
	{																\
		delete (pMem);												\
		(pMem) = NULL;												\
	}
#endif // _DEBUG

};
