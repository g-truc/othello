/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_font.cpp, 21/03/2003					*
\***********************************************/

#include "../include/gtl_font.h"
#include "../include/gtl_image_tga.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

using namespace gtl;

CFont::~CFont ()
{
	glDeleteLists (iFontID, 128);
}

void CFont::LoadTexture (const char *szFilename)
{
	CImageTGA Image (szFilename);

	glGenTextures (1, &iTextureID);

	glBindTexture (GL_TEXTURE_2D, iTextureID);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, Image.GetWidth (), Image.GetHeight (), 0, GL_RGB, GL_UNSIGNED_BYTE, Image.GetData ());

	fFontWidth = Image.GetWidth () / 16;
	fFontHeight = Image.GetHeight () / 16;
}

void CFont::BuildFont ()
{
	iFontID = glGenLists (128);
	glBindTexture (GL_TEXTURE_2D, iTextureID);
	for (int i=0; i<128; i++)
	{
		float x=i%16/fFontWidth;
		float y=i/16/fFontHeight;

		glNewList (iFontID+i,GL_COMPILE);
			glBegin (GL_QUADS);
				glTexCoord2f (x, 1.0f-y-0.13f);
				glVertex2f (0, fFontHeight);
				glTexCoord2f (x+0.0625f,1.0f-y-0.13f);
				glVertex2f (fFontWidth, fFontHeight);
				glTexCoord2f (x+0.0625f,1.0f-y);
				glVertex2f (fFontWidth,0);
				glTexCoord2f (x,1.0f-y);
				glVertex2f (0,0);
			glEnd ();
			glTranslated (fFontWidth,0,0);
		glEndList ();
	}
}

/*
void CFont::BuildFont ()
{
	iFontID = glGenLists (128);
	glBindTexture (GL_TEXTURE_2D, iTextureID);
	for (int i=0; i<128; i++)
	{
		float x=i%16/fFontWidth;
		float y=i/16/fFontHeight;

		glNewList (iFontID+i,GL_COMPILE);
			glBegin (GL_QUADS);
				glTexCoord2f (x,1.0f-y-0.0625f);
				glVertex2d (0, fFontHeight);
				glTexCoord2f (x+0.0625f,1.0f-y-0.0625f);
				glVertex2i (fFontWidth, fFontHeight);
				glTexCoord2f (x+0.0625f,1.0f-y-0.001f);
				glVertex2i (fFontWidth,0);
				glTexCoord2f (x,1.0f-y-0.001f);
				glVertex2i (0,0);
			glEnd ();
			glTranslated (fFontWidth,0,0);
		glEndList ();
	}
}
*/

void CFont::Load (const char *szFilename)
{
	LoadTexture (szFilename);
	BuildFont ();
}

void CFont::Print (short x, short y, const char *szMsg, ...)
{
	char text[1024];
	va_list ap;

	if (szMsg == NULL)
		return;

	va_start (ap, szMsg);
	    vsprintf (text, szMsg, ap);
	va_end (ap);

	glEnable (GL_BLEND);

	glBlendFunc (GL_SRC_ALPHA, GL_ONE);
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
	glBindTexture (GL_TEXTURE_2D,iTextureID);

	glEnable (GL_TEXTURE_2D);
	glLoadIdentity ();
	glTranslated (x,y,0);
	glListBase (iFontID-32);

	glScalef ((iSize/fFontHeight)*fRatio, iSize/fFontHeight, (iSize/fFontHeight)*fRatio);

	glCallLists (strlen(text), GL_UNSIGNED_BYTE, text);
	glDisable (GL_TEXTURE_2D);
	glDisable (GL_BLEND);
}
