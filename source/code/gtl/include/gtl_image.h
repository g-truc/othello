/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_image.h, 21/03/2003						*
\***********************************************/

#ifndef GTL_IMAGE_H
#define GTL_IMAGE_H

#include <stdio.h>

namespace gtl {

typedef enum
{
	COLOR_FORMAT_NULL = 0,
	COLOR_FORMAT_DEFAULT,
	COLOR_FORMAT_RGBA32,
	COLOR_FORMAT_RGB24,
	COLOR_FORMAT_BGRA32,
	COLOR_FORMAT_BGR24,
	COLOR_FORMAT_ARGB16,
	COLOR_FORMAT_GRAY08
} color_format_t;

typedef enum
{
	ERROR_IMAGE_NULL = 0,
	ERROR_IMAGE_FILE_NOT_FOUND,
	ERROR_IMAGE_MEM_ALLOC,
	ERROR_IMAGE_SIZE,
	ERROR_IMAGE_PIXEL_BITS,
	ERROR_IMAGE_BAD_DATA,
	ERROR_IMAGE_TYPE,
} error_image_t;

class CImage
{
protected:
	unsigned int iSize;

	color_format_t Format;
	unsigned char iPixelSize;
	unsigned short iHeight;
	unsigned short iWidth;
	unsigned char *pImageData;
	
	void Error (const error_image_t iError);
	void BGRtoRGB ();

	void ReadDataAlpha (FILE* File, const unsigned int iOffsetData);
	void ReadDataRGB (FILE* File, const unsigned int iOffsetData);
	void ReadDataRGBA (FILE* File, const unsigned int iOffsetData);

public:
	CImage () {}
	virtual ~CImage () {};
	
	virtual bool Load (const char* szFilename, const color_format_t ColorFormat = COLOR_FORMAT_DEFAULT) = 0;
	
	unsigned char* GetData () const {return pImageData;}
	unsigned short GetValue (unsigned short x, unsigned short y) const {return pImageData[y*iWidth+x];}
	color_format_t GetFormat () const {return Format;}
	unsigned short GetHeight () const {return iHeight;}
	unsigned short GetWidth () const {return iWidth;}
};

}; // namespace gtl

#endif //GTL_IMAGE_H

