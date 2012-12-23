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
*	joueur_humain.h, 20/02/2003							*
*	par Groove, groove@g-truc.fr.st						*
\*******************************************************/

#ifndef JOUEUR_HUMAIN_H
#define JOUEUR_HUMAIN_H

#include "joueur.h"
#include "interface.h"
#include <iostream>

using namespace std;

class CJoueurHumain : public CJoueur
{
private:
	CInterface *pInterface;

public:
	CJoueurHumain (CInterface *_pInterface, const string & szNom, joueur_index_t _Index);
	virtual ~CJoueurHumain () {};

	virtual position_t DemanderPositionPion (CReglesJeu & Regles) {return pInterface->DemanderPositionPion (Index);}
	virtual void EstLeGagnant () {Index == 1 ? pInterface->AfficherMsg (MSG_GAGNE_1) : pInterface->AfficherMsg (MSG_GAGNE_2);}
};

#endif //PLAYER_HUMAN_H
