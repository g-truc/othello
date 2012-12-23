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
*	text.h, 12/03/2003									*
*	par Groove, groove@g-truc.fr.st						*
\*******************************************************/

#ifndef TEXT_H
#define TEXT_H

#include <string>

using namespace std;

class CText
{
private:
	string szJoueur1;
	string szJoueur2;
	string szJoueurType;
	string szJoueurNiveau;
	string szJoueurNom;
	string szJoueurHumain;
	string szJoueurIA;
	string szPartieCommencer;
	string szPartieContinuer;
	string szMeilleurScores;
	string szQuitter;
	string szMsgJouer;
	string szMsgGagnant;
	
public:
	bool Load (const char* szFileName);

	const char* GetJoueur1 () const {return szJoueur1.c_str ();}
	const char* GetJoueur2 () const {return szJoueur2.c_str ();}
	const char* GetJoueurType () const {return szJoueurType.c_str ();}
	const char* GetJoueurNiveau () const {return szJoueurNiveau.c_str ();}
	const char* GetJoueurNom () const {return szJoueurNom.c_str ();}
	const char* GetJoueurHumain () const {return szJoueurHumain.c_str ();}
	const char* GetJoueurIA () const {return szJoueurIA.c_str ();}
	const char* GetPartieCommencer () const {return szPartieCommencer.c_str ();}
	const char* GetPartieContinuer () const {return szPartieContinuer.c_str ();}
	const char* GetMeilleurScores () const {return szMeilleurScores.c_str ();}
	const char* GetQuitter () const {return szQuitter.c_str ();}
	const char* GetMsgJouer () const {return szMsgJouer.c_str ();}
	const char* GetMsgGagnant () const {return szMsgGagnant.c_str ();}
};

#endif //TEXT_H
