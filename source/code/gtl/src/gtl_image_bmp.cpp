/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_image_bmp.cpp, 21/03/2003				*
\***********************************************/

#include "../include/gtl_image_bmp.h"
#include <stdio.h>
#include <stdlib.h>

using namespace gtl;

#define	BITMAP_ID			('B' + ('M'<<8))

CImageBMP::~CImageBMP () 
{
	FREE (pImageData);
}

bool CImageBMP::Load (const char *szFilename, const color_format_t ColorFormat)
{
	FILE *File;
	unsigned short iType;
	unsigned int iOffsetData;
	int piSize[2];
	
	if (!(File = fopen (szFilename, "r+b")))
	{
		Error (ERROR_IMAGE_FILE_NOT_FOUND);
		return false;
	}

	fread (&iType, sizeof (unsigned short), 1, File);
	if (iType != BITMAP_ID)
	{
		Error (ERROR_IMAGE_TYPE);
		return false;
	}

	// Groove - 17/02/2003 - Lecture de l'adresse ou commence les données
	fseek (File, 10, SEEK_SET);
	fread (&iOffsetData, sizeof (unsigned int), 1, File);
	fseek (File, 18, SEEK_SET);

	// Groove - 17/02/2003 - Lecture de dimension de l'image
	fread (&piSize, sizeof (int), 2, File);
	iHeight = piSize[1];
	iWidth = piSize[0];
	iSize = iHeight * iWidth;

	// Groove - 17/02/2003 - Lecture du nombre de bit par pixel
	fseek (File, 28, SEEK_SET);
	fread (&iPixelSize, sizeof (unsigned short), 1, File);

	switch (ColorFormat)
	{
	default:
		break;
	case COLOR_FORMAT_DEFAULT:
	case COLOR_FORMAT_BGR24:
		if (iPixelSize == 24)
		{
			ReadDataRGB (File, iOffsetData);
		}
		break;
	case COLOR_FORMAT_RGB24:
		if (iPixelSize == 24)
		{
			ReadDataRGB (File, iOffsetData);
			BGRtoRGB ();
		}
		break;
	}

	fclose (File);

	if (pImageData == NULL)
	{
		Error (ERROR_IMAGE_BAD_DATA);
		return false;
	}

	return true;
}
