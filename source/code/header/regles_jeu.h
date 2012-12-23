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
*	regles_jeu.h, 13/02/2003							*
*	par MatRem, matrem@codegba.fr.st					*
\*******************************************************/

#ifndef REGLES_JEU_H
#define REGLES_JEU_H

#include "grille.h"

class CReglesJeu
{
private:
	CGrille Grille;
	
	//MatRem renvoi le pion inverse de celui donné en paramètre 
	pion_t PionInverse (const pion_t Pion) const;
	
	//MatRem 13/02/2003 Retourne la valeur du pion
	pion_t GetPion (const short x, const short y);
	
	//MatRem 13/02/2003 Pose du pion
	void SetPion (const short x, const short y, const pion_t Pion) {Grille[y * GRID_SIZE + x] = Pion;}

public:
	
	CGrille* GetGrilleAdr () {return &Grille;}
	
	//MatRem 13/02/2003 idem get pion sauf  privé et paramètre 
	pion_t GetValeurGrille (const short iCase) {return Grille[iCase];}
	
	//MatRem 13/02/2003 donne le nombre de pion de cette couleur
	short CompterPion (const pion_t Pion);

	//MatRem 13/02/2003 verifie la validité et renvoi le nombre de pion que ce placement permet de retourner
	short VerifierPose (const short x, const short y, const pion_t Pion);
	
	//MatRem 13/02/2003 verifie pose et retourne
	short EssayerPose (const short x, const short y, const pion_t Pion);
	
	//MatRem 13/02/2003 Regarde si le joueur peut jouer
	bool VerifierJoueurPeutJouer (const pion_t Pion);

	bool VerifierFinPartie () const;
	
	void Initialiser() {Grille.Initialiser();}
};

#endif //REGLES_JEU_H
