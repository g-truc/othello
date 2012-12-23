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
*	grille.cpp, 13/02/2003								*
*	par MatRem, matrem@codegba.fr.st					*
\*******************************************************/

#include "../header/grille.h"

void CGrille::Initialiser()
{
	TableauPions.resize(GRID_SIZE*GRID_SIZE,pion_t());
	for(int a=0; a<GRID_SIZE; a++)
		for(int b=0; b<GRID_SIZE; b++)
		{
			TableauPions[a+b*GRID_SIZE]=PION_NULL;
			if((a==3 && b==4) || (a==4 && b==3)) TableauPions[a+b*GRID_SIZE]=PION_BLANC;
			if((a==3 && b==3) || (a==4 && b==4)) TableauPions[a+b*GRID_SIZE]=PION_NOIR;
		}
}
