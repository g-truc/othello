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
*	meilleur_score.cpp, 12/03/2003						*
*	par MatRem, matrem@codegba.fr.st					*
\*******************************************************/

#include "../header/meilleur_score.h"

void CMeilleurScore::Charger ()
{
	int nbScr;
	ifstream Fichier(FIC_SCR);
	Fichier>>nbScr;
	Fichier.ignore();
	if(!(nbScr<=10)) nbScr=0;
	ListResultat.resize(nbScr,CResultat());
	for(int a=0; a<nbScr;a++)
	{
		short sg, sp;
		string ng, np;

		getline(Fichier,ng);
		Fichier>>sg;
		Fichier.ignore();
		getline(Fichier,np);
		Fichier>>sp;
		Fichier.ignore();

		ListResultat[a]=CResultat(ng,sg,np,sp);

#ifdef DEBUG
		ListResultat[a].Afficher();
#endif

	}
	nbr=nbScr;
	Fichier.close();
}

void CMeilleurScore::Sauver ()
{
	ofstream Fichier(FIC_SCR);
	int nbScr=ListResultat.size();
	Fichier<<nbScr<<"\n";
	for(int a=0;a<nbScr;a++)
	{
		string ng = ListResultat[a].GetNomGagnant();
		short sg = ListResultat[a].GetScoreGagnant();
		string np =ListResultat[a].GetNomPerdant();
		short sp = ListResultat[a].GetScorePerdant();
		Fichier<<ng<<endl;
		Fichier<<sg<<endl;
		Fichier<<np<<endl;
		Fichier<<sp<<endl;
	}
	Fichier.close();
}
	

void CMeilleurScore::Ajouter (const CResultat & Resultat)
{

#ifdef DEBUG
	Resultat.Afficher();
#endif
	int a;
	int nbScr = ListResultat.size();
	int indiceSc=11;
	
	for(a=0;a<nbScr;a++)
	{
		if(Resultat>ListResultat[a])
		{
			indiceSc=a;
			break;
		}
	}

	if(indiceSc==11 && nbScr!=10)
	{
		ListResultat.push_back(CResultat());
		ListResultat[nbScr]=Resultat;
	}
	if(indiceSc<11)
	{
		if(nbScr!=10)
		{
			ListResultat.push_back(CResultat());
			for(a=nbScr;a>indiceSc;a--)
			{
				ListResultat[a]=ListResultat[a-1];
			}
			ListResultat[indiceSc]=Resultat;
		}
		else
		{
			for(a=9;a>indiceSc;a--)
			{
				ListResultat[a]=ListResultat[a-1];
			}
			ListResultat[indiceSc]=Resultat;
		}
		
	}
}
