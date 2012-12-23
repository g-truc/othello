/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_image_raw.cpp, 21/03/2003				*
\***********************************************/

#include "../include/gtl_image_raw.h"
#include <stdio.h>
#include <stdlib.h>

using namespace gtl;

CImageRAW::~CImageRAW ()
{
	FREE (pImageData);
}

void CImageRAW::Init (const unsigned short _iWitdh, const unsigned short _iHeight)
{
	iHeight = _iHeight;
	iWidth = _iWitdh;
	iSize = iHeight * iWidth;
}

bool CImageRAW::Load (const char* szFilename, const color_format_t ColorFormat)
{
	FILE *File;

	if (!(File = fopen (szFilename, "r+b")))
	{
		Error (ERROR_IMAGE_FILE_NOT_FOUND);
		return false;
	}

	// Groove - 05/03/2003 - On va a la fin du fichier
	fseek (File, 0, SEEK_END);
	// Groove - 05/03/2003 - On récupère la taille du fichier en nombre d'octets
	long iFileLenght = ftell (File);

	#ifdef _DEBUG
		printf ("iFileLenght = %d\n", iFileLenght);
	#endif //_DEBUG

	pImageData = (unsigned char *) malloc (iFileLenght * sizeof (unsigned char));

	fseek (File, 0, SEEK_SET);
	fread (pImageData, sizeof (unsigned char), iFileLenght, File);
	fclose (File);

	if (pImageData == NULL)
	{
		Error (ERROR_IMAGE_BAD_DATA);
		return false;
	}

	return true;
}
