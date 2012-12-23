/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_image_bmp.h, 21/03/2003					*
\***********************************************/

#ifndef GTL_IMAGE_BMP_H
#define GTL_IMAGE_BMP_H

#include "gtl_image.h"
#include "gtl_mem.h"

namespace gtl {

class CImageBMP : public CImage
{
private:

public:
	CImageBMP () {pImageData = NULL;}
	CImageBMP (const char* szFilename, const color_format_t ColorFormat = COLOR_FORMAT_DEFAULT) {pImageData = NULL; Load (szFilename, ColorFormat);}
	virtual ~CImageBMP ();

	virtual bool Load (const char* szFilename, const color_format_t ColorFormat = COLOR_FORMAT_DEFAULT);
};

}; //namespace gtl

#endif //GTL_IMAGE_TGA_H
