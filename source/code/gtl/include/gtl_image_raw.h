/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_image_raw.h, 21/03/2003					*
\***********************************************/

#ifndef GTL_IMAGE_RAW_H
#define GTL_IMAGE_RAW_H

#include "gtl_image.h"
#include "gtl_mem.h"

namespace gtl {

class CImageRAW : public CImage
{
private:

public:
	CImageRAW () {pImageData = NULL;}
	CImageRAW (const char* szFilename, const unsigned short iWitdh, const unsigned short iHeight, const color_format_t Format = COLOR_FORMAT_DEFAULT) {pImageData = NULL; Load (szFilename); Init (iWitdh, iHeight);}
	~CImageRAW ();
	
	void Init (const unsigned short iWitdh, const unsigned short iHeight);
	virtual bool Load (const char* szFilename, const color_format_t ColorFormat = COLOR_FORMAT_DEFAULT);
};

}; //namespace gtl

#endif //GTL_IMAGE_RAW_H
