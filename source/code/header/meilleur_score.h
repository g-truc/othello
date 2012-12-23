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
*	meilleur_score.h, 12/03/2003						*
*	par MatRem, matrem@codegba.fr.st					*
\*******************************************************/

#ifndef MEILLEUR_SCORE_H
#define MEILLEUR_SCORE_H

#define FIC_SCR "./data/scores.txt"

#include "resultat.h"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class CMeilleurScore
{
private:
	
	vector<CResultat> ListResultat;
	
	void Charger (void);
	void Sauver (void);
	
	//MatRem 13/02/2003 Ajoute le résultat dans le tableau à la bonne position
	void Ajouter (const CResultat & Resultat);

	short nbr;

public:

    //MatRem 13/02/2003 Pour la visualisation
	CMeilleurScore () {nbr = 0; Charger ();}
	
	//MatRem 13/02/2003 En fin de partie
	CMeilleurScore (const CResultat & Resultat) {nbr = 0; Charger (); Ajouter (Resultat);}
	
	~CMeilleurScore () {Sauver ();}

	const CResultat & operator[] (const short iPosition) const {return ListResultat[iPosition];}

	short GetNbr() const {return nbr;}
};

#endif //MEILLEUR_SCORE_H
