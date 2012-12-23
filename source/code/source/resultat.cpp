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
*	resultat.cpp, 12/03/2003							*
*	par MatRem, matrem@codegba.fr.st					*
\*******************************************************/

#include <iostream>
#include "../header/resultat.h"

using namespace std;

CResultat::CResultat (string szNomGagnant, short iScoreGagnant, string szNomPerdant, short iScorePerdant)
:iScoreGagnant(iScoreGagnant), iScorePerdant(iScorePerdant), szNomGagnant(szNomGagnant), szNomPerdant(szNomPerdant)
{
}

bool operator > (const CResultat & Resultat1, const CResultat & Resultat2)
{
	short total1 ,total2;
	total1 = Resultat1.GetScorePerdant()+Resultat1.GetScoreGagnant();
	total2 = Resultat2.GetScorePerdant()+Resultat2.GetScoreGagnant();

	if(total1<64)
	{
		if(total2<64)
		{
			if(total1<=total2) return true;
			else return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if(total2<64) return false;
		else
		{
			if(Resultat1.GetScoreGagnant()>=Resultat2.GetScoreGagnant()) return true;
			else return false;
		}
	}

}

#ifdef _DEBUG
void CResultat::Afficher() const
{
	cout<<"Score gagnant: "<<iScoreGagnant<<endl;
	cout<<"Score perdant: "<<iScorePerdant<<endl;
	cout<<"Nom gagnant: "<<szNomGagnant<<endl;
	cout<<"Nom perdant: "<<szNomPerdant<<endl;

}
#endif //_DEBUG
