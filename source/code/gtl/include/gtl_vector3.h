/***********************************************\
*	GTL (G-Truc Library) : Alpha 3.00			*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	gtl_vector3.h, 21/03/2003					*
\***********************************************/

#ifndef GTL_VECTOR_3_H
#define GTL_VECTOR_3_H

#include "gtl_angle3.h"
#include <math.h>
#include <iostream>

namespace gtl {

template <typename T> class CVector3
{
private:
	// Members
	T value[3];

public:
	// Construction/destruction
	CVector3 ()														{for (unsigned char i=0; i<3; i++) value[i]=0;}
	CVector3 (T x, T y, T z)										{value[0] = x;			value[1] = y;			value[2] = z;}
	CVector3 (const CVector3& v)									{value[0] = v.value[0];	value[1] = v.value[1];	value[2] = v.value[2];} 
	CVector3 (T Array[3])											{value[0] = Array[0];	value[1] = Array[1];	value[2] = Array[2];}

	// Operateurs de comaparaisons
	bool operator== (const CVector3& v) const						{return (value[0] == v.value[0] &&			value[1] == v.value[1] &&	value[2] == v.value[2]);}
	bool operator== (const T Array[3]) const						{return (value[0] == Array[0] &&			value[1] == Array[1] &&		value[2] == Array[2]);}
	bool operator!= (const CVector3& v) const						{return !(*this==v);}
	bool operator!= (const T Array[3]) const						{return (value[0] != Array[0] ||			value[1] != Array[1] ||		value[2] != Array[2]);}
	bool operator> (const CVector3& v) const						{return (Length () > v.Length ());}
	bool operator< (const CVector3& v) const						{return (Length () < v.Length ());}
	bool operator>= (const CVector3& v) const						{return (Length () >= v.Length ());}
	bool operator<= (const CVector3& v) const						{return (Length () <= v.Length ());}

	void SetAngleX (CAngle3<T> Angle) 
	{ 
		value[0] = -sin (Angle[2]) * sin (Angle[0]) * cos (Angle[1]) + cos (Angle[2]) * sin (Angle[1]); 
		value[1] = -sin (Angle[2]) * sin (Angle[0]) * sin (Angle[1]) - cos (Angle[2]) * cos (Angle[1]); 
		value[2] = -sin (Angle[2]) * cos (Angle[0]); 
	} 

	void SetAngleY (CAngle3<T> Angle) 
	{ 
		value[0] = cos (Angle[0]) * cos (Angle[1]); 
		value[1] = cos (Angle[0]) * sin (Angle[1]); 
		value[2] = -sin (Angle[0]); 
	} 

	void SetAngleZ (CAngle3<T> Angle) 
	{ 
		value[0] = cos (Angle[2]) * sin (Angle[0]) * cos (Angle[1]) + sin (Angle[2]) * sin (Angle[1]); 
		value[1] = cos (Angle[2]) * sin (Angle[0]) * sin (Angle[1]) - sin (Angle[2]) * cos (Angle[1]); 
		value[2] = cos (Angle[2]) * cos (Angle[0]); 
	}

	// Operateurs de modifications
	CVector3 operator- () const										{return CVector3<T> (-value[0],				-value[1],					-value[2]);}
	CVector3 operator= (const CVector3& v)							{return CVector3<T> (value[0] = v.value[0],	value[1] = v.value[1],		value[2] = v.value[2]);}
	CVector3 operator= (const T Array[3])							{return CVector3<T> (value[0] = Array[0],		value[1] = Array[1],		value[2] = Array[2]);}
	CVector3 operator+ (const CVector3& v) const					{return CVector3<T> (value[0] + v.value[0],	value[1] + v.value[1],		value[2] + v.value[2]);}
	CVector3 operator+= (const CVector3& v)							{value[0] += v.value[0];					value[1] += v.value[1];		value[2] += v.value[2];		return *this;}
	CVector3 operator+ (const T Array[3]) const						{return CVector3<T> (value[0] + Array[0],		value[1] + Array[1],		value[2] + Array[2]);}
	CVector3 operator+= (const T Array[3])							{value[0] += Array[0];						value[1] += Array[1];		value[2] += Array[2];		return *this;}
	CVector3 operator- (const CVector3& v) const					{return CVector3<T> (value[0] - v.value[0],	value[1] - v.value[1],		value[2] - v.value[2]);}
	CVector3 operator-= (const CVector3& v)							{value[0] -= v.value[0];					value[1] -= v.value[1];		value[2] -= v.value[2];		return *this;}
	CVector3 operator- (const T Array[3]) const						{return CVector3<T> (value[0] - Array[0],		value[1] - Array[1],		value[2] - Array[2]);}
	CVector3 operator-= (const T Array[3])							{value[0] -= Array[0];						value[1] -= Array[1];		value[2] -= Array[2];		return *this;}
	CVector3 operator* (const T Nb) const							{return CVector3<T> (value[0] * Nb,			value[1] * Nb,				value[2] * Nb);}
	CVector3 operator*= (const T Nb)								{value[0] *= Nb;							value[1] *= Nb;				value[2] *= Nb;				return *this;}
	// Groove - 21/11/2002 - Produit scalaire
	T operator* (const CVector3& v) const							{return (value[0] * v.value[0] +			value[1] * v.value[1] +		value[2] * v.value[2]);}
	T operator* (const T Array[3]) const							{return (value[0] * Array[0] +				value[1] * Array[1] +		value[2] * Array[2]);}
	CVector3 operator/ (const T Nb) const							{return CVector3<T> (value[0] / Nb,			value[1] / Nb,				value[2] / Nb);}
	CVector3 operator/= (const T Nb)								{value[0] /= Nb;							value[1] /= Nb;				value[2] /= Nb;				return *this;}
	// Groove - 21/11/2002 - Produit vectoriel
	CVector3 operator^ (const CVector3& v) const					{return CVector3<T> (value[1] * v.value[2] -	value[2]*v.value[1], value[2] * v.value[0] - value[0] * v.value[2], value[0] * v.value[1] - value[1] * v.value[0]);}
	CVector3 operator^= (const CVector3& v)							{value[0] = value[1] * v.value[2] - value[2] * v.value[1];		value[1] = value[2] * v.value[0] - value[0] * v.value[2];		value[2] = value[0] * v.value[1] - value[1] * v.value[0];		return *this;}

	T* operator>> (T Array[3]) const								{Array[0] = value[0]; Array[1] = value[1]; Array[2] = value[2]; return Array;}
	T* operator<< (T Array[3])										{value[0] = Array[0]; value[1] = Array[1]; value[2] = Array[2]; return Array;}

	friend std::ostream& operator<< (std::ostream & out, const CVector3<T>& v)		{out << v.value[0] << '\n' << v.value[1] << '\n' << v.value[2] << '\n' << endl;	return out;}
	friend std::istream& operator>> (std::istream & in, CVector3<T>& v)				{in >> v.value[0]; in >> v.value[1]; in >> v.value[2]; return in;}

	T& operator[] (unsigned char i)
	{
		if (i > 2)
			i = 2;

		return value[i];
	}

	operator T* ()													{return value;} // Groove - 23/11/2002 - Retourne CVector3 sous forme de tableau de T
	operator const T* () const										{return value;} // Groove - 23/11/2002 - Retourne CVector3 sous forme de tableau de T
	
	// Methodes
	T Length () const												{return static_cast<T>(sqrt (value[0] * value[0] + value[1] * value[1] + value[2] * value[2]));}
	CVector3<T> Normalize () const
	{
		T VecLen = Length ();
		if (VecLen == 0) 
			return CVector3<T> (0,0,0);
		return CVector3<T> (value[0] / VecLen, value[1] / VecLen, value[2] / VecLen);
	}
};

template <typename T> CVector3<T> operator* (const T nb, const CVector3<T>& v)	{return v * nb;}

}; // namespace gtl

#endif //GTL_VECTOR_3_H
