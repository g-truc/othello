/*******************************************************\
*	Othello-GL : b3.00									*
*	Copyright (c) 2003, G-Truc Creation, Code GBA.		*
*********************************************************
*	G-Truc Creation, www.g-truc.fr.st					*
*	Code GBA, www.codegba.fr.st							*
*********************************************************
*	Ce programme est un programme libre, vous			*
*	pouvez	le distribuer et/ou le modifier suivant		*
*	les termes de la GNU General Public Licence.		*
*********************************************************
*	grille.h, 13/02/2003								*
*	par MatRem, matrem@codegba.fr.st					*
\*******************************************************/

#ifndef GRILLE_H
#define GRILLE_H

#include <vector>

using namespace std;

#define GRID_SIZE	8

typedef enum
{
	PION_INVALID = 0,
	PION_NULL,
	PION_BLANC,
	PION_NOIR
} pion_t;

class CGrille
{
private:
	//MatRem 13/02/2003 tableau a une seule colonne 
	vector<pion_t> TableauPions;

public:
	CGrille () {Initialiser ();}
	
	//MatRem 13/02/2003 Initialisation de la grille
	void Initialiser ();

	//MatRem 13/02/2003 permet d'accéder au pion à ce numéro
	pion_t& operator[] (const short iposition) {return TableauPions[iposition];}
};

#endif //GRILLE_H
