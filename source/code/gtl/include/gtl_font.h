/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_font.h, 21/03/2003						*
\***********************************************/

#ifndef GTL_FONT_H
#define GTL_FONT_H

namespace gtl {

class CFont
{
private:
	unsigned int iFontID;
	unsigned int iTextureID;
	float fFontHeight;
	float fFontWidth;
	float fRatio;
	unsigned char iSize;
	
	void BuildFont ();
	void LoadTexture (const char *szFilename);

public:
	CFont () {iSize = 12; fRatio = 0.5;}
	CFont (const char *szFilename) {iSize = 12; fRatio = 0.5; Load (szFilename);}
	~CFont ();

	void Load (const char *szFilename);
	void Print (short x, short y, const char *szMsg, ...);

	unsigned char GetSize () const {return iSize;}
	void SetSize (const unsigned char _iSize) {iSize = _iSize;}
	float GetRadio () const {return fRatio;}
	void SetRadio (const float _fRatio) {fRatio = _fRatio;}
};

}; // namespace gtl

#endif //GTL_FONT_H
