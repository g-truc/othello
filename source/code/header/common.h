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
*	common.h, 20/02/2003								*
*	par Groove, groove@g-truc.fr.st						*
\*******************************************************/

#ifndef COMMON_H
#define COMMON_H

// Groove - 06/02/2003 - Non util pour Visual C++ 6 et 7 (.net), 
// choisir le mode de compilation debug.
// #define _DEBUG

#define STRCAT(rep,file)	((string (rep) + string (file)).c_str ())
#define REP_DATA			"./data/"

typedef struct
{
	short iLargeur;
	short iHauteur;
	short iCouleur;
	short iFrequence;
} resolution_t;

typedef struct
{
	short x;
	short y;
} position_t;

#endif // COMMON_H
