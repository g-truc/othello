/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_math.h, 21/03/2003						*
\***********************************************/

#ifndef GTL_MATH_H
#define GTL_MATH_H

namespace gtl {

#define M_PI				3.14159265358979323846
#define RACINE_DE_3_SUR_2	0.8660254038
#define RACINE_DE_2			0.7071067812

extern const short g_iCos[360];
extern const short g_iSin[360];

inline float cos (unsigned short iAngle)
{
	if (iAngle > 360)
		iAngle = 360;
	return static_cast<float> (g_iCos[iAngle]) / 1024;
}

inline float sin (unsigned short iAngle)
{
	if (iAngle > 360)
		iAngle = 360;
	return static_cast<float> (g_iSin[iAngle]) / 1024;
}

template <typename T> T BitInversion (const T iNb)
{
	T iNbBuffer = 0;
	for (short i = 0; i < sizeof(T); i++)
		if (iNb & (1<<i))
			iNbBuffer |= (1<<(31-i));
	return iNbBuffer;
}

template <typename T> T max (const T nb1, const T nb2) {return nb1 > nb2 ? nb1 : nb2;}
template <typename T> T min (const T nb1, const T nb2) {return nb1 < nb2 ? nb1 : nb2;}
template <typename T> T rad2deg (const T AngleRad) {return AngleRad * static_cast<T>(180.0f / M_PI);}
template <typename T> T deg2rad (const T AngleDeg) {return AngleDeg * static_cast<T>(M_PI / 180.0f);}
template <typename T> T pow (const T Nb) {return (Nb*Nb);}
template <typename T> T pow (const T Nb, int iCoef) {T Buffer = Nb; for (int i = 1; i < iCoef; i++, Buffer *= Buffer); return Buffer;}

}; // namespace gtl

#endif //GTL_MATH_H
