/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_image.cpp, 21/03/2003					*
\***********************************************/

#include "../include/gtl_image.h"
#include <stdio.h>
#include <stdlib.h>

using namespace gtl;

void CImage::Error (const error_image_t iError)
{
	switch (iError)
	{
	default:
	case ERROR_IMAGE_NULL:
		break;
	case ERROR_IMAGE_FILE_NOT_FOUND:
		printf ("File not found\n");
		break;
	case ERROR_IMAGE_MEM_ALLOC:
		printf ("Not readable image\n");
		break;
	case ERROR_IMAGE_SIZE:
		printf ("Incorrect size\n");
		break;
	case ERROR_IMAGE_PIXEL_BITS:
		printf ("Incorrect color\n");
		break;
	}
	exit (0);
}

void CImage::ReadDataRGBA (FILE *File, const unsigned int iOffsetData)
{
	if (!(pImageData = (unsigned char *) malloc (iSize * 4)))
	{
		Error (ERROR_IMAGE_MEM_ALLOC);
		return;
	}

	fseek (File, iOffsetData, SEEK_SET);
	unsigned int iCheckSize = fread (pImageData, sizeof (unsigned char), iSize * 4, File); 

	if (iCheckSize != iSize * 4)
	{
		Error (ERROR_IMAGE_BAD_DATA);
		free (pImageData);
		return;
	}

	// Groove - 17/02/2003 - Change BGRA color format to RGBA color format
	if (Format == COLOR_FORMAT_BGRA32)
	{
		BGRtoRGB ();
		Format = COLOR_FORMAT_RGBA32;
	}
}

void CImage::ReadDataRGB (FILE *File, const unsigned int iOffsetData)
{
	
	pImageData = (unsigned char *) malloc (iSize * 3); 

	if (pImageData == NULL)
	{
		Error (ERROR_IMAGE_MEM_ALLOC);
		return;
	}

	fseek (File, iOffsetData, SEEK_SET);
	unsigned int iCheckSize = fread (pImageData, sizeof (unsigned char), iSize * 3, File);

	if (iCheckSize != iSize * 3)
	{
		free (pImageData);
		Error (ERROR_IMAGE_BAD_DATA);
		return;
	}

	// Groove - 17/02/2003 - Change BGR color format to RGB color format
	if (Format == COLOR_FORMAT_BGR24)
	{
		BGRtoRGB ();
		Format = COLOR_FORMAT_RGB24;
	}
}

void CImage::ReadDataAlpha (FILE *File, const unsigned int iOffsetData)
{
	pImageData = (unsigned char *) malloc (iSize);

	if (pImageData == NULL)
	{
		Error (ERROR_IMAGE_MEM_ALLOC);
		return;
	}

	fseek (File, iOffsetData, SEEK_SET);
	unsigned int iCheckSize = fread (pImageData, sizeof (unsigned char), iSize, File);

	if (iCheckSize != iSize)
	{
		free (pImageData);
		Error (ERROR_IMAGE_BAD_DATA);
		return;
	}

	Format = COLOR_FORMAT_GRAY08;
}

void CImage::BGRtoRGB ()
{
	unsigned int iMax = 0;

	switch (iPixelSize)
	{
	case 24:
		iMax = 3;
		break;
	case 32:
		iMax = 4;
		break;
	}

	unsigned char Temp;
	for (unsigned int i=0; i<iSize*iMax; i+=iMax)
	{
		Temp = pImageData[i];
		pImageData[i] = pImageData[i+2];
		pImageData[i+2] = Temp;
	}
}
