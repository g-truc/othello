/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_vector2.h, 21/03/2003					*
\***********************************************/

#ifndef GTL_VECTOR_2_H
#define GTL_VECTOR_2_H

#include "gtl_angle2.h"
#include <math.h>
#include <iostream>

namespace gtl {

template <typename T> class CVector2
{
private:
	// Members
	T value[2];

public:
	// Construction/destruction
	CVector2 ()														{for (unsigned char i=0; i<2; i++) value[i]=0;}
	CVector2 (T x, T y)												{value[0] = x;			value[1] = y;}
	CVector2 (const CVector2& v)									{value[0] = v.value[0];	value[1] = v.value[1];} 
	CVector2 (T Array[2])											{value[0] = Array[0];	value[1] = Array[1];}

	// Operateurs de comaparaisons
	bool operator== (const CVector2& v) const						{return (value[0] == v.value[0] &&			value[1] == v.value[1]);}
	bool operator== (const T Array[2]) const						{return (value[0] == Array[0] &&			value[1] == Array[1]);}
	bool operator!= (const CVector2& v) const						{return !(*this==v);}
	bool operator!= (const T Array[2]) const						{return (value[0] != Array[0] ||			value[1] != Array[1]);}
	bool operator> (const CVector2& v) const						{return (Length () > v.Length ());}
	bool operator< (const CVector2& v) const						{return (Length () < v.Length ());}
	bool operator>= (const CVector2& v) const						{return (Length () >= v.Length ());}
	bool operator<= (const CVector2& v) const						{return (Length () <= v.Length ());}

	// Operateurs de modifications
	CVector2 operator- (void) const									{return CVector2<T> (-value[0],				-value[1]);}
	CVector2 operator= (const CVector2& v)							{return CVector2<T> (value[0] = v.value[0],	value[1] = v.value[1]);}
	CVector2 operator= (const T Array[2])							{return CVector2<T> (value[0] = Array[0],		value[1] = Array[1]);}
	CVector2 operator= (const CAngle2& Angle) 						{Length (); value[0] = Angle[0] * VecLen; value[1] = Angle[1] * VecLen;}

	CVector2 operator+ (const CVector2& v) const					{return CVector2<T> (value[0] + v.value[0],	value[1] + v.value[1]);}
	CVector2 operator+= (const CVector2& v)							{value[0] += v.value[0];					value[1] += v.value[1];		return *this;}
	CVector2 operator+ (const T Array[2]) const						{return CVector2<T> (value[0] + Array[0],		value[1] + Array[1],);}
	CVector2 operator+= (const T Array[2])							{value[0] += Array[0];						value[1] += Array[1];		return *this;}
	CVector2 operator- (const CVector2& v) const					{return CVector2<T> (value[0] - v.value[0],	value[1] - v.value[1]);}
	CVector2 operator-= (const CVector2& v)							{value[0] -= v.value[0];					value[1] -= v.value[1];		return *this;}
	CVector2 operator- (const T Array[2]) const						{return CVector2<T> (value[0] - Array[0],		value[1] - Array[1]);}
	CVector2 operator-= (const T Array[2])							{value[0] -= Array[0];						value[1] -= Array[1];		return *this;}
	CVector2 operator* (const T Nb) const							{return CVector2<T> (value[0] * Nb,			value[1] * Nb);}
	CVector2 operator*= (const T Nb)								{value[0] *= Nb;							value[1] *= Nb;				return *this;}
	// Groove - 21/11/2002 - Produit scalaire
	T operator* (const CVector2& v) const							{return (value[0] * v.value[0] +			value[1] * v.value[1]);}
	T operator* (const T Array[2]) const							{return (value[0] * Array[0] +				value[1] * Array[1]);}
	CVector2 operator/ (const T Nb) const							{return CVector2<T> (value[0] / Nb,			value[1] / Nb);}
	CVector2 operator/= (const T Nb)								{value[0] /= Nb;							value[1] /= Nb;				return *this;}
	T* operator>> (T Array[2]) const								{Array[0] = value[0]; Array[1] = value[1];								return Array;}
	T* operator<< (T Array[2])										{value[0] = Array[0]; value[1] = Array[1];								return Array;}

	friend std::ostream& operator<< (std::ostream & out, const CVector2<T>& v)		{out << v.value[0] << '\n' << v.value[1] << '\n' << endl; return out;}
	friend std::istream& operator>> (std::istream & in, CVector2<T>& v)				{in >> v.value[0]; in >> v.value[1]; return in;}

	T& operator[] (unsigned char i)
	{
		if (i > 1)
			i = 1;
		return value[i];
	}

	operator T* ()													{return value;} // Groove - 23/11/2002 - Retourne CVector2 sous forme de tableau de T
	operator const T* () const										{return value;} // Groove - 23/11/2002 - Retourne CVector2 sous forme de tableau de T
	
	// Methodes
	T Length () const												{return static_cast<T>(sqrt (value[0] * value[0] + value[1] * value[1]));}
	CVector2<T> Normalize () const
	{
		T VecLen = Length ();
		if (VecLen == 0) 
			return CVector2<T> (0,0);
		return CVector2<T> (value[0] / VecLen, value[1] / VecLen);
	}
};

template <typename T> CVector2<T> operator* (const T nb, const CVector2<T>& v)	{return v * nb;}

}; // namespace gtl

#endif //GTL_VECTOR_2_H