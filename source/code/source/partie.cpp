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
*	partie.cpp, 12/03/2003								*
*	par MatRem, matrem@codegba.fr.st					*
\*******************************************************/

#include "../header/partie.h"
#include "../header/interface.h"
#include "../header/joueur_humain.h"
#include "../header/joueur_ia.h"
#include "../header/meilleur_score.h"

CReglesJeu CPartie::ReglesJeu;

CJoueur* CPartie::GetJoueurAdr (const joueur_index_t Index) const
{
	if (Index == JOUEUR_1)
		return pJoueur1; 
	else if (Index == JOUEUR_2)
		return pJoueur2;
	else 
		return NULL;
}

void CPartie::Commencer (CInterface & Interface, player_info_t Joueur1Information, player_info_t Joueur2Information)
{
//MatRem 14/02/2003

	// Groove - 29/03/2003 - Inicialisation du plateau
	Interface.InitialiserPlateau (ReglesJeu.GetGrilleAdr ());
	
	//Initialisation du joueur 1

	//Joueur Humain
	if(Joueur1Information.Type==JOUEUR_HUMAIN)
		pJoueur1 = new CJoueurHumain (&Interface, Joueur1Information.szNom,JOUEUR_1);
	
	//Joueur Ia
	if(Joueur1Information.Type==JOUEUR_IA)
	{

		//On initialise le fichier à charger par rapport au niveau de l'ia
		char * s;
		switch(Joueur1Information.Niveau)
		{
		case	NIVEAU_IA_1:	s="ia1.dat"; break;
		case	NIVEAU_IA_2:	s="ia2.dat"; break;
		case	NIVEAU_IA_3:	s="ia3.dat"; break;
		case	NIVEAU_IA_4:	s="ia4.dat"; break;
		case	NIVEAU_IA_5:	s="ia5.dat"; break;
		default:				s="ia5.dat"; break;
		}

		//On crée le joueur1 dynamiquement
		pJoueur1 = new CJoueurIA(s,&Interface,JOUEUR_1);
	}

	
	//Initialisation du joueur 2
	
	//Joueur Humain
	if(Joueur2Information.Type==JOUEUR_HUMAIN)
		pJoueur2 = new CJoueurHumain(&Interface, Joueur2Information.szNom,JOUEUR_2);
	
	//Joueur Ia
	if(Joueur2Information.Type==JOUEUR_IA)
	{
		char * s;
		switch(Joueur2Information.Niveau)
		{
		case	NIVEAU_IA_1:	s="ia1.dat"; break;
		case	NIVEAU_IA_2:	s="ia2.dat"; break;
		case	NIVEAU_IA_3:	s="ia3.dat"; break;
		case	NIVEAU_IA_4:	s="ia4.dat"; break;
		case	NIVEAU_IA_5:	s="ia5.dat"; break;
		default:				s="ia1.dat"; break;
		}

		pJoueur2 = new CJoueurIA(s,&Interface,JOUEUR_2);
	}
	
	//Initialisation des scores
	pJoueur1->SetScore(2);
	pJoueur2->SetScore(2);
	
	//Initialisation des régles du jeu donc de la grille
	ReglesJeu.Initialiser();
	
	//initialisation du drapeau de fin de partie et du tour 
	bEstPartieFini=false;
	TourJoueur=TOUR_JOUEUR_1;
}


void CPartie::Continuer()
{
	position_t pos;
	pos.x=-1;
	
	//On vérifie si les joueurs peuvent jouer sinon la partie est finie
	if(ReglesJeu.VerifierJoueurPeutJouer(PION_BLANC) || ReglesJeu.VerifierJoueurPeutJouer(PION_NOIR))
	{
		//Si c'est le tour su joueur 1
		if(TourJoueur==TOUR_JOUEUR_1)
		{
			//Si il peut jouer sinon c'est le tour du joueur 2
			if(ReglesJeu.VerifierJoueurPeutJouer(PION_BLANC))
			{
				//On importe la position demandée par le joueur
				pos=pJoueur1->DemanderPositionPion(ReglesJeu);
				//Si l'abscisse =-1 c'est que la position n'est pas donnée
				if(pos.x!=-1)
				{
					//On véridie si la pose à cette position est bonne pour ce joueur
					if(int a=ReglesJeu.EssayerPose(pos.x,pos.y,PION_BLANC))
					{
						//On  passe au joueur suivant
						TourJoueur = TOUR_JOUEUR_2;
						//On modifie les scores
						pJoueur1->SetScore(pJoueur1->GetScore()+a+1);
						pJoueur2->SetScore(ReglesJeu.CompterPion(PION_NOIR));
					}
				}
			} 
			else TourJoueur=TOUR_JOUEUR_2;
			
			//On quitte la fonction pour laisser la main à l'affichage
			return;
		}	

		//Si c'est le tour du joueur 2
		if(TourJoueur==TOUR_JOUEUR_2)
		{
			if(ReglesJeu.VerifierJoueurPeutJouer(PION_NOIR))
			{
				pos=pJoueur2->DemanderPositionPion(ReglesJeu);
				if(pos.x!=-1)
				{
					if(int a=ReglesJeu.EssayerPose(pos.x,pos.y,PION_NOIR))
					{
						TourJoueur = TOUR_JOUEUR_1;
						pJoueur2->SetScore(pJoueur2->GetScore()+a+1);
						pJoueur1->SetScore(ReglesJeu.CompterPion(PION_BLANC));
					}
				}
			}
			else TourJoueur = TOUR_JOUEUR_1;
			return;
		}
	}

	//La partie est finie
	else
	{
		//Si elle n'est pas déjà finie
		if(!bEstPartieFini)
		{
			//On met le drapeau de fin à 1
			bEstPartieFini=true;

			//Ce n'est plus à aucun joueur de jouer
			TourJoueur=TOUR_JOUEUR_NULL;
	
			//On crée un résultat en fonction des scores
			short ScrGgn, ScrPrd;
			string NomGgn, NomPrd;
	
			if(pJoueur1->GetScore()>=pJoueur2->GetScore())
			{
				pJoueur1->EstLeGagnant();
				ScrGgn = pJoueur1->GetScore();
				ScrPrd = pJoueur2->GetScore();
				NomGgn = pJoueur1->GetNom();
				NomPrd = pJoueur2->GetNom();
			}
			else
			{
				pJoueur2->EstLeGagnant();
				ScrGgn = pJoueur2->GetScore();
				ScrPrd = pJoueur1->GetScore();
				NomGgn = pJoueur2->GetNom();
				NomPrd = pJoueur1->GetNom();
			}
			
#ifdef _DEBUG
			cout<<"SCRGGN: "<<ScrGgn<<endl;
			cout<<"SCRPRD: "<<ScrPrd<<endl;
			cout<<"NOMGGN: "<<NomGgn<<endl;
			cout<<"NOMPRD: "<<NomPrd<<endl;
#endif
			CResultat ResultatPartie(NomGgn,ScrGgn,NomPrd,ScrPrd);

#ifdef _DEBUG
			ResultatPartie.Afficher();
#endif

			//On intègre le résultat au meilleur score
			CMeilleurScore MeilleurScores (ResultatPartie);
		}
	}
}

CPartie::~CPartie()
{
	//Si les joueurs ont été créés, on les efface
	if (pJoueur1) delete pJoueur1;
	if (pJoueur2) delete pJoueur2;
}
