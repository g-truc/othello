/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_angle2.h, 21/03/2003					*
\***********************************************/

#ifndef GTL_ANGLE_2_H
#define GTL_ANGLE_2_H

namespace gtl {

template <typename T> class CAngle2
{
private:
	// Members
	T value[2];

	T Length () const					{return static_cast<T>(sqrt (value[0] * value[0] + value[1] * value[1]));}
	CAngle2<T> Normalize () const
	{
		T VecLen = Length ();
		if (VecLen == 0) 
			return CAngle2<T> (0,0);
		return CAngle2<T> (value[0] / VecLen, value[1] / VecLen);
	}

public:
	CAngle2 ()							{}
	CAngle2 (const T x, const T y)		{value[0] = x; value[1] = y; *this = Normalize ();}
	CAngle2 (const T angles[2])			{value[0] = angles[0]; value[1] = angles[1]; *this = Normalize ();}
	CAngle2 (const CAngle2& angles)		{value[0] = angles[0]; value[1] = angles[1]; *this = Normalize ();}

	CAngle2 operator- () const			{return CAngle2<T> (-value[0], -value[1]);}
	T& operator[] (unsigned char i)		{i > 1 ? i = 1, return value[i] : return value[i];}
};

}; // namespace gtl

#endif //GTL_ANGLE_2_H
