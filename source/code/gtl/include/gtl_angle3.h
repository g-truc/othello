/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_angle3.h, 21/03/2003					*
\***********************************************/

#ifndef GTL_ANGLE_3_H
#define GTL_ANGLE_3_H

namespace gtl {

template <typename T> class CAngle3
{
private:
	// Members
	T value[3];

	T Length () const							{return static_cast<T>(sqrt (value[0] * value[0] + value[1] * value[1] + value[2] * value[2]));}
	CAngle3<T> Normalize () const
	{
		T VecLen = Length ();
		if (VecLen == 0) 
			return CAngle3<T> (0,0,0);
		return CAngle3<T> (value[0] / VecLen, value[1] / VecLen, value[2] / VecLen);
	}

public:
	CAngle3 ()									{}
	CAngle3 (const T x, const T y, const T z)	{value[0] = x; value[1] = y; value[2] = z; *this = Normalize ();}
	CAngle3 (const T angles[3])					{value[0] = angles[0]; value[1] = angles[1]; value[2] = angles[2]; *this = Normalize ();}
	CAngle3 (const CAngle3& angles)				{value[0] = angles[0]; value[1] = angles[1]; value[2] = angles[2]; *this = Normalize ();}

	CAngle3 operator- () const					{return CAngle3<T> (-value[0], -value[1], -value[2]);}
	T& operator[] (unsigned char i)				{if (i > 2) i = 2; return value[i];}
};

}; // namespace gtl

#endif //GTL_ANGLE_3_H
