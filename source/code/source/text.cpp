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
*	text.cpp, 12/03/2003								*
*	par Groove, groove@g-truc.fr.st						*
\*******************************************************/

#include "../header/common.h"
#include "../header/text.h"
#include <fstream>
#include <iostream>

using namespace std;

bool CText::Load (const char* szFileName)
{
	ifstream in (STRCAT (REP_DATA, szFileName));
	if (!in.good ())
	{
		cerr << "Erreur lors de l'ouverture du fichier " << szFileName << endl;
		return false;
	}

	getline (in, szJoueur1);
	getline (in, szJoueur2);
	getline (in, szJoueurType);
	getline (in, szJoueurNiveau);
	getline (in, szJoueurNom);
	getline (in, szJoueurHumain);
	getline (in, szJoueurIA);
	getline (in, szPartieCommencer);
	getline (in, szPartieContinuer);
	getline (in, szMeilleurScores);
	getline (in, szQuitter);
	getline (in, szMsgJouer);
	getline (in, szMsgGagnant);

	return true;
}
