/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_image_tga.h, 21/03/2003					*
\***********************************************/

#ifndef GTL_IMAGE_TGA_H
#define GTL_IMAGE_TGA_H

#include <stdio.h>
#include <stdlib.h>
#include "gtl_image.h"
#include "gtl_mem.h"

namespace gtl {

class CImageTGA : public CImage
{
private:
	// Groove - 05/03/2003 - Champs d'identification comportant au plus 255 charactères
	char *szIdenticationField;
	// Groove - 05/03/2003 - Données de la palette de couleurs
	unsigned char *pColorMapData;
	// Groove - 10/03/2003 - Tampon fichier
	unsigned char *piFileBuffer;

	void FreeAll ();
	bool CheckSize (long iSize);

public:
	CImageTGA ();
	CImageTGA (const char* szFilename, const color_format_t ColorFormat = COLOR_FORMAT_DEFAULT);
	virtual ~CImageTGA ();

	// Groove - 09/03/2003 - Chargement d'une image.
	virtual bool Load (const char* szFilename, const color_format_t ColorFormat = COLOR_FORMAT_DEFAULT);
	// Groove - 09/03/2003 - Fonction pemetant de récupérer le champ d'identification
	char* GetIdentificationField () const {return szIdenticationField;}
};

}; //namespace gtl

#endif //GTL_IMAGE_TGA_H
