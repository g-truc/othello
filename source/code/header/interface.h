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
*	interface.h, 20/02/2003								*
*	par Groove, groove@g-truc.fr.st						*
\*******************************************************/

#ifndef INTERFACE_H
#define INTERFACE_H

#include "common.h"
#include "grille.h"
#include "menu.h"
#include "affichage_plateau.h"
#include "interface.h"
#include <time.h>

#define WINDOW_NAME				"Othello GL Beta 3.00"
#define RESOLUTION_COULEUR		32
#define RESOLUTION_FREQUENCE	75

class CInterface
{
private:
	CMenu Menu;
	CAffichagePlateau AffichagePlateau;
	resolution_t Resolution;

	short iFps, iFpsBuffer;
	time_t FpsTimeStart;

	void CompteFPS ();
	void AfficherEn2D () const;
	void AfficherEn3D () const;
	void CreerFenetre (int argc, char **argv);

public:
	CInterface (int argc, char **argv);

	// Groove - 02/02/2003 - Call back function pour GLUT
	void Afficher ();
	void Clavier (unsigned char key);
	void ClavierSP (int key);
	void Idle ();

	void DeplacerCurseur (const position_t & Position) {AffichagePlateau.DeplacerCurseur(Position);}
	void InitialiserPlateau (CGrille *pGrille) {AffichagePlateau.Initialiser (pGrille);}
	
	// Groove - 03/02/2003 - Fonction utiliser par les joueurs (acteur) pour informer des actions demandées par le programme.
	void AfficherMsg (const msg_id_t MsgID) {Menu.SetMsgHUD (MsgID);}
	position_t DemanderPositionPion (const short iIndex) {iIndex == 1 ? Menu.SetMsgHUD (MSG_JOUER_1) : Menu.SetMsgHUD (MSG_JOUER_2); return AffichagePlateau.GetPosition();}
};

#endif //INTERFACE_H
