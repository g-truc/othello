/***********************************************\
*	GTL (G-Truc Library)						*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	test_vector.h, 17/02/2003					*
\***********************************************/

//#include <iostream>
#include "../../include/gtl_vector3.h"

using namespace gtl;
using namespace std;

//typedef CAngle3 <float> Angle;
typedef CVector3 <float> Vector;

int main (void)
{
	Vector v1 = Vector (2,2,2);
	Vector v2 = Vector (4,5,6);
	Vector v3 = v1 ^ v2;

//	v1.SetAngleX (Angle (1, 1, 2));

	cout << "Valeur du vecteur 1 :\n" << v1 << endl;
	cout << "Valeur du vecteur 2 :\n" << v2 << endl;
	cout << "Valeur du vecteur 3 :\n" << v3 << endl;
	cout << "Valeur des vecteurs 1 + 2 :\n" << v1 + v2 << endl;
	cout << "Valeur du vecteur 1 * 2 :\n" << v1 * 2 << endl;
	
	cout << "Le vecteur 1 est t'il plus petit que le vecteur 2 ? :\n" << (v1 < v2) << endl;
	return 0;
}
