/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_color.h, 21/02/2003						*
\***********************************************/

#ifndef GTL_COLOR_H
#define GTL_COLOR_H

namespace gtl {

#ifdef __GL_H__
	typedef GLfloat color_t;
#else
	typedef float color_t;
#endif //__GL_H__

typedef color_t			color3_t[3];
typedef color_t			color4_t[4];

extern const color3_t fColorWhite;
extern const color3_t fColorGray;
extern const color3_t fColorBlack;

extern const color3_t fColorRed;
extern const color3_t fColorOrange;
extern const color3_t fColorYellow;
extern const color3_t fColorYellowGreen;
extern const color3_t fColorGreen;
extern const color3_t fColorGreenSkyBlue;
extern const color3_t fColorSkyBlue;
extern const color3_t fColorSkyBlueBlue;
extern const color3_t fColorBlue;
extern const color3_t fColorBluePurple;
extern const color3_t fColorPurple;
extern const color3_t fColorPurpleRed;

typedef unsigned char color8_t;
typedef unsigned int color_rgb_t;
typedef unsigned int color_rgba_t;

// Groove - 18/03/2003 - Stokage d'une couleur RGBA comme donnée
inline color_rgba_t GetRGBA (color8_t r, color8_t g, color8_t b, color8_t a)
{
	return r << 24 | g << 16 | b << 8 | a;
}

// Groove - 18/03/2003 - Récupération des couleurs qui compose une couleur RGBA
inline color8_t GetRedRGBA (color_rgba_t rgba)
{
	return ((rgba & 0xff000000) >> 24);
}

inline color8_t GetGreenRGBA (color_rgba_t rgba)
{
	return ((rgba & 0xff0000) >> 16);
}

inline color8_t GetBlueRGBA (color_rgba_t rgba)
{
	return ((rgba & 0xff00) >> 8);
}

inline color8_t GetAlphaRGBA (color_rgba_t rgba)
{
	return (rgba & 0xff);
}

// Groove - 18/03/2003 - Stokage d'une couleur RGB comme donnée
inline color_rgb_t GetRGB (color8_t r, color8_t g, color8_t b)
{
	return r << 16 | g << 8 | b;
}

// Groove - 18/03/2003 - Récupération des couleurs qui compose une couleur RGB
inline color8_t GetRedRGB (color_rgb_t rgb)
{
	return ((rgb & 0xff0000) >> 16);
}

inline color8_t GetGreenRGB (color_rgb_t rgb)
{
	return ((rgb & 0xff00) >> 8);
}

inline color8_t GetBlueRGB (color_rgb_t rgb)
{
	return (rgb & 0xff);
}

}; // namespace gtl

#endif //GTL_COLOR_H
