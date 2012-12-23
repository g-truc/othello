/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_image_tga.cpp, 21/03/2003				*
\***********************************************/

#include "../include/gtl_image_tga.h"
#include <stdio.h>

using namespace gtl;

CImageTGA::CImageTGA ()
{
	pImageData = NULL;
	pColorMapData = NULL;
	szIdenticationField = 0;
}

CImageTGA::CImageTGA (const char* szFilename, const color_format_t ColorFormat)
{
	pImageData = NULL;
	pColorMapData = NULL;
	szIdenticationField = 0;

	Load (szFilename, ColorFormat);
}

CImageTGA::~CImageTGA ()
{
 	FREE (szIdenticationField);
	FREE (pColorMapData);
	FREE (pImageData);
}

bool CImageTGA::Load (const char* szFilename, const color_format_t ColorFormat)
{
	// Groove - 05/03/2003 - Nombre de bits dans le champs d'identification
	unsigned char iNbByteInIdField;
	// Groove - 05/03/2003 - L'image utilise telle une palette de couleurs
	bool bUseColorMap;
	// Groove - 05/03/2003 - Type de l'image
	unsigned char iImageType;
	// Groove - 05/03/2003 - Offset de la première couleur de la palette 
	unsigned short iColorMapOrigin = 0;
	// Groove - 05/03/2003 - Nombre de couleurs dans la palette.
	unsigned short iColorMapLength = 0;
	// Groove - 05/03/2003 - Nombre de bits par couleur dans la palette.
	unsigned char iColorMapSize = 0;
	// Groove - 05/03/2003 - Origine de l'image en X de la texture
	short iOriginX;
	// Groove - 05/03/2003 - Origine de l'image en Y de la texture
	short iOriginY;
	// Groove - 05/03/2003 - Octet indiquant quelques information sur l'image suivant la position des bits
	// Bit 0-3, nombre de bit réservé pour la couche alpha
	// Bit 4, Reservé, doit etre égale à 0
	// Bit 5, sens de l'image. Si Bit5 == 1 l'origine de l'image est en haut a gauche de l'ecran sinon en bas à gauche
	// Bit 6,7 Drapeau de stokage de données intercalées
	// 00 -> Pas de données intercalés
	// 01 -> ???
	// 10 -> ???
	// 11 -> reserved
	unsigned char iImageDescriptorByte;

///////////////////////////////////////////////////////

	FILE *File;

	if (!(File = fopen (szFilename, "r+b")))
	{
		Error (ERROR_IMAGE_FILE_NOT_FOUND);
		return false;
	}

	// Groove - 05/03/2003 - On va a la fin du fichier
	fseek (File, 0, SEEK_END);
	// Groove - 05/03/2003 - On récupère la taille du fichier en nombre d'octets
	long iSize = ftell (File);

	#ifdef _DEBUG
		printf ("iSize = %d\n", iSize);
	#endif //_DEBUG

	// Groove - 05/03/2003 - On aloue de la mémoire dynamique de la taille du fichier
	unsigned char *piFileBuffer = (unsigned char *) malloc (iSize);
	// Groove - 05/03/2003 - On se positionne au debut du fichier
	fseek (File, 0, SEEK_SET);
	// Groove - 05/03/2003 - On lit la totalité du fichier.
	fread (piFileBuffer, sizeof (unsigned char), iSize, File);

	// Groove - 05/03/2003 - Fermeture du fichier
	fclose (File);

	// Groove - 05/03/2003 - Lecture du header
	iNbByteInIdField = piFileBuffer[0];
	bUseColorMap = piFileBuffer[1] == 1;
	iImageType = piFileBuffer[2];

	#ifdef _DEBUG
		printf ("iNbByteInIdField = %d\n", iNbByteInIdField);
		printf ("bUseColorMap = %d\n", bUseColorMap);
		printf ("iImageType = %d\n", iImageType);
	#endif //_DEBUG

	if (bUseColorMap)
	{
		iColorMapOrigin = iNbByteInIdField + 18;
		//iColorMapOrigin = piFileBuffer[3] | (piFileBuffer[4] << 8);
		iColorMapLength = piFileBuffer[5] | (piFileBuffer[6] << 8);
		iColorMapSize = piFileBuffer[7];
		#ifdef _DEBUG
			printf ("iColorMapOrigin = %d\n", iColorMapOrigin);
			printf ("iColorMapLength = %d\n", iColorMapLength);
			printf ("iColorMapSize = %d\n", iColorMapSize);
		#endif //_DEBUG

		if (!(pColorMapData = (unsigned char *) malloc (sizeof (unsigned char) * iColorMapLength * iColorMapSize / 8)))
		{
			FREE (piFileBuffer);
			Error (ERROR_IMAGE_MEM_ALLOC);
			return false;
		}
		for (unsigned short i=0; i<(iColorMapLength * iColorMapSize / 8); i++)
			pColorMapData[i] = piFileBuffer [iColorMapOrigin+i];
	}

	iOriginX = piFileBuffer[8] | (piFileBuffer[9] << 8);
	iOriginY = piFileBuffer[10] | (piFileBuffer[11] << 8);
	iWidth = piFileBuffer[12] | (piFileBuffer[13] << 8);
	iHeight = piFileBuffer[14] | (piFileBuffer[15] << 8);
	iPixelSize = piFileBuffer[16];
	iImageDescriptorByte = piFileBuffer[17];

	if (!CheckSize (iWidth) || !CheckSize (iHeight))
	{
		FREE (pColorMapData);
		FREE (piFileBuffer);
		Error (ERROR_IMAGE_SIZE);
		return false;
	}

	#ifdef _DEBUG
		printf ("iOriginX = %d\n", iOriginX);
		printf ("iOriginY = %d\n", iOriginY);
		printf ("iWidth = %d\n", iWidth);
		printf ("iHeight = %d\n", iHeight);
		printf ("iPixelSize = %d\n", iPixelSize);
		printf ("iImageDescriptorByte = %d\n", iImageDescriptorByte);
	#endif //_DEBUG	

	// Groove - 05/03/2003 - Lecture du champ d'information (titre de l'image)
	if (iNbByteInIdField > 0)
	{
		if (!(szIdenticationField =  (char *) malloc (sizeof (char) * iNbByteInIdField)))
		{
			FREE (pColorMapData);
			FREE (piFileBuffer);
			Error (ERROR_IMAGE_MEM_ALLOC);
			return false;
		}
		for (short j=0; j<iNbByteInIdField; j++)
			szIdenticationField[j] = piFileBuffer [18+j];
	}

	// Groove - 09/03/2003 - Allocation de la mémoire nécéssaire pour récupérer les données de l'image.
	if (!(pImageData = (unsigned char *) malloc (sizeof (unsigned char) * iPixelSize * iWidth * iHeight)))
	{
		FreeAll ();
		Error (ERROR_IMAGE_MEM_ALLOC);
		return false;
	}

	long iDataOrigin, k;

	switch (iImageType)
	{
	default:
		FreeAll ();
		Error (ERROR_IMAGE_BAD_DATA);
		break;
	case 1:
		iDataOrigin = iColorMapOrigin + iColorMapLength * iColorMapSize / 8;

		// Groove - 10/03/2003 - Palette -> BGR24
		if (ColorFormat == COLOR_FORMAT_BGR24 || ColorFormat == COLOR_FORMAT_DEFAULT)
		{
			for (k = 0; k < (iWidth * iHeight); k++)
			{
				pImageData[k*3+0] = pColorMapData[piFileBuffer[iDataOrigin + k]*3+0];
				pImageData[k*3+1] = pColorMapData[piFileBuffer[iDataOrigin + k]*3+1];
				pImageData[k*3+2] = pColorMapData[piFileBuffer[iDataOrigin + k]*3+2];
			}
			Format = COLOR_FORMAT_BGR24;
		}
		// Groove - 10/03/2003 - Palette -> RGB24
		else if (ColorFormat == COLOR_FORMAT_RGB24)
		{
			for (k = 0; k < (iWidth * iHeight); k++)
			{
				pImageData[k*3+0] = pColorMapData[piFileBuffer[iDataOrigin + k]*3+2];
				pImageData[k*3+1] = pColorMapData[piFileBuffer[iDataOrigin + k]*3+1];
				pImageData[k*3+2] = pColorMapData[piFileBuffer[iDataOrigin + k]*3+0];
			}
			Format = COLOR_FORMAT_RGB24;
		}
		break;
	case 2:
		iDataOrigin = 18 + iNbByteInIdField;

		if (iPixelSize == 16)
		{
			// Groove - 10/03/2003 - Image ARGB16 -> ARGB16
			if (ColorFormat == COLOR_FORMAT_ARGB16 || ColorFormat == COLOR_FORMAT_DEFAULT)
			{
				for (k = 0; k < (iWidth * iHeight * 2); k+=2)
				{
					pImageData[k+0] = piFileBuffer[iDataOrigin + k+0];
					pImageData[k+1] = piFileBuffer[iDataOrigin + k+1];
				}
				Format = COLOR_FORMAT_ARGB16;
			}
		}

		if (iPixelSize == 24)
		{
			// Groove - 10/03/2003 - Image BGR24 -> BGR24
			if (ColorFormat == COLOR_FORMAT_BGR24 || ColorFormat == COLOR_FORMAT_DEFAULT)
			{
				for (k = 0; k < (iWidth * iHeight * 3); k+=3)
				{
					pImageData[k+0] = piFileBuffer[iDataOrigin + k+0];
					pImageData[k+1] = piFileBuffer[iDataOrigin + k+1];
					pImageData[k+2] = piFileBuffer[iDataOrigin + k+2];
				}
				Format = COLOR_FORMAT_BGR24;
			}
			// Groove - 10/03/2003 - Image BGR24 -> RGB24
			else if (ColorFormat == COLOR_FORMAT_RGB24)
			{
				for (k = 0; k < (iWidth * iHeight * 3); k+=3)
				{
					pImageData[k+0] = piFileBuffer[iDataOrigin + k+2];
					pImageData[k+1] = piFileBuffer[iDataOrigin + k+1];
					pImageData[k+2] = piFileBuffer[iDataOrigin + k+0];
				}
				Format = COLOR_FORMAT_RGB24;
			}
		}

		else if (iPixelSize == 32)
		{
			// Groove - 10/03/2003 - Image BGRA32 -> BGRA32
			if (ColorFormat == COLOR_FORMAT_BGRA32 || ColorFormat == COLOR_FORMAT_DEFAULT)
			{
				for (k = 0; k < (iWidth * iHeight * 4); k+=4)
				{
					pImageData[k+0] = piFileBuffer[iDataOrigin + k+0];
					pImageData[k+1] = piFileBuffer[iDataOrigin + k+1];
					pImageData[k+2] = piFileBuffer[iDataOrigin + k+2];
					pImageData[k+3] = piFileBuffer[iDataOrigin + k+3];
				}
				Format = COLOR_FORMAT_BGRA32;
			}
			// Groove - 10/03/2003 - Image BGRA32 -> RGBA32
			else if (ColorFormat == COLOR_FORMAT_RGBA32)
			{
				for (k = 0; k < (iWidth * iHeight * 4); k+=4)
				{
					pImageData[k+0] = piFileBuffer[iDataOrigin + k+2];
					pImageData[k+1] = piFileBuffer[iDataOrigin + k+1];
					pImageData[k+2] = piFileBuffer[iDataOrigin + k+0];
					pImageData[k+3] = piFileBuffer[iDataOrigin + k+3];
				}
				Format = COLOR_FORMAT_RGBA32;
			}
		}

		break;
	}

//	FreeAll ();
	return true;
}

bool CImageTGA::CheckSize (long iSize)
{
    return (iSize == 2		|| iSize == 4		|| 
			iSize == 8		|| iSize == 16		|| 
			iSize == 32		|| iSize == 64		||
			iSize == 128	|| iSize == 256		|| 
			iSize == 512	|| iSize == 1024	||
			iSize == 2048	|| iSize == 4096	||
			iSize == 8192	|| iSize == 16384);
}

void CImageTGA::FreeAll ()
{
	FREE (szIdenticationField);
	FREE (pColorMapData);
	FREE (piFileBuffer);
}
