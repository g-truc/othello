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
*	joueur_ia.h, 20/02/2003								*
*	par Groove, groove@g-truc.fr.st						*
\*******************************************************/

#ifndef JOUEUR_IA_H
#define JOUEUR_IA_H

#include "interface.h"
#include "joueur.h"
#include <set>

using namespace std;

#define TEMPS_PR_JOUER		1

class CJoueurIA : public CJoueur
{
protected:
	typedef set<int> cases_t;
	typedef set<int>::const_iterator cases_cit;

	time_t TimeStart;
	CInterface *pInterface;

	// Groove - 03/02/2003 - Niveau est un short pour pouvoir l'incrémenter et le décrémenter facilement au niveau de l'affichage.
	short NiveauIA;
	// Groove - 12/02/2003 - Grille de points du plateau pour l'IA actuel.
	unsigned char iModelIA[64];

	void LoadModelIA (const char* szNameFile);

public:
	CJoueurIA () {}
	CJoueurIA (const char* szFileName, CInterface *_pInterface, joueur_index_t Index);
	virtual ~CJoueurIA () {};

	virtual position_t DemanderPositionPion (CReglesJeu & Regles);
	virtual void EstLeGagnant () {Index == JOUEUR_1 ? pInterface->AfficherMsg (MSG_GAGNE_1) : pInterface->AfficherMsg (MSG_GAGNE_2);}
};

#endif //JOUEUR_IA_H
