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
*	joueur.h, 20/02/2003								*
*	par Groove, groove@g-truc.fr.st						*
\*******************************************************/

#ifndef JOUEUR_H
#define JOUEUR_H

#include "common.h"
#include "regles_jeu.h"
#include <string>

using namespace std;

typedef enum
{
	NIVEAU_IA_1 = 0,
	NIVEAU_IA_2,
	NIVEAU_IA_3,
	NIVEAU_IA_4,
	NIVEAU_IA_5,
} niveau_ia_t;

typedef enum
{
	JOUEUR_NULL = 0,
	JOUEUR_HUMAIN,
	JOUEUR_IA,
} joueur_type_t;

typedef enum
{
	JOUEUR_0 = 0,
	JOUEUR_1,
	JOUEUR_2
} joueur_index_t;

typedef struct
{
	string szNom;
	joueur_type_t Type;
	/*niveau_ia_t*/short Niveau;
	short iScore;
} player_info_t;

class CJoueur
{
protected:
	string szNom;
	short iPionNb;
	joueur_index_t Index;

public:
	virtual ~CJoueur () {};

	string GetNom () const {return szNom;}
	void SetNom (const string _szNom) {szNom = _szNom;}
	short GetScore () const {return iPionNb;}
	void SetScore (const short iScore) {iPionNb = iScore;}
	joueur_index_t GetIndex () const {return Index;}
	void SetIndex (const joueur_index_t _Index) {Index = _Index;}

	// Groove - 31/01/2003 - Communication avec la partie.
	virtual position_t DemanderPositionPion (CReglesJeu & Regles) = 0;
	// Groove - 03/02/2003 - Pour indiquer que ce joueur est le gagnant au niveau de l'affichage.
	virtual void EstLeGagnant () = 0;
};

#endif //JOUEUR_H
