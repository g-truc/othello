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
*	resultat.h, 12/03/2003								*
*	par MatRem, matrem@code-gba.fr.st					*
\*******************************************************/

#ifndef RESULTAT_H
#define RESULTAT_H

#include "joueur.h"

class CResultat
{
private:
	short iScoreGagnant;
	short iScorePerdant;
	string szNomGagnant;
	string szNomPerdant;

public:
	
	//MatRem 13/02/2003 Constructeur vide pour la création d'une instance pour les meilleurs scores
	CResultat () {}
	
	//MatRem 13/02/2003 Création du résultat en fin de partie
	CResultat (string szNomGagnant, short iScoreGagnant, string szNomPerdant, short iScorePerdant);
	
	//MatRem 13/02/2003 Test si un résultat est meilleur q'un autre
	friend bool operator > (const CResultat & Resultat1, const CResultat & Resultat2);

	short GetScoreGagnant () const {return iScoreGagnant;}
	short GetScorePerdant () const {return iScorePerdant;}
	string GetNomGagnant () const {return szNomGagnant;}
	string GetNomPerdant () const {return szNomPerdant;}

#ifdef _DEBUG
	void Afficher() const;
#endif //_DEBUG
};

#endif //RESULTAT_H
