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
*	joueur_humain.cpp, 20/02/2003						*
*	par Groove, groove@g-truc.fr.st						*
\*******************************************************/

#include "../header/joueur_humain.h"

CJoueurHumain::CJoueurHumain (CInterface *_pInterface, const string & _szNom, joueur_index_t _Index)
{
	pInterface = _pInterface;
	szNom = _szNom;
	iPionNb = 2;
	Index = _Index;
}
