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
*	partie.h, 12/03/2003								*
*	par MatRem, matrem@codegba.fr.st					*
\*******************************************************/

#ifndef PARTIE_H
#define PARTIE_H

#include "regles_jeu.h"
#include "joueur.h"
#include <stddef.h>

typedef enum
{
	TOUR_JOUEUR_NULL = 0,
	TOUR_JOUEUR_1,
	TOUR_JOUEUR_2,
} tour_joueur_t;

class CInterface;

class CPartie
{
private:
	CJoueur *pJoueur1;
	CJoueur *pJoueur2;
	static CReglesJeu ReglesJeu;
	bool bEstPartieFini;
	tour_joueur_t TourJoueur;

	//MatRem 13/02/2003 -> Création des joueurs, Initialisations des attributs
	void Commencer (CInterface & Interface, player_info_t Joueur1Information, player_info_t Joueur2Information);

public:
	// Groove - 12/03/2003 - Création d'une partie
	CPartie (CInterface & Interface, player_info_t Joueur1Information, player_info_t Joueur2Information) {bEstPartieFini = false; pJoueur1 = NULL; pJoueur2 = NULL;	Commencer (Interface, Joueur1Information, Joueur2Information);}
	// Groove - 12/03/2003 - Controle la fin de partie pour sa destruction
	bool GetEstPartieFini () const {return bEstPartieFini;}
	CJoueur *GetJoueurAdr (const joueur_index_t Index) const;
	//MatRem 13/02/2003 -> Demandes au joueurs (tour, controles (validité, fin de partie))
	//et création du résultat en fin de partie
	void Continuer ();

	~CPartie ();
};

#endif // PARTIE_H
