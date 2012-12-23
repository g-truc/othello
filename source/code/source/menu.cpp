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
*	affichage_menu.cpp, 29/03/2003						*
*	par Groove, groove@g-truc.fr.st						*
\*******************************************************/

#include "../header/affichage_plateau.h"
#include "../header/meilleur_score.h"
#include "../header/menu.h"
#include "../header/text.h"
#include <GL/glut.h>
#include <iostream>
#include <string>

using namespace std;

void CMenu::Executer ()
{
	if (ActionChoix == ACTION_CONTINUER_PARTIE)
	{
		if (pPartie)
			pPartie->Continuer ();
	}
	else if (ActionChoix == ACTION_MENU && pPartie && pPartie->GetEstPartieFini ())
	{
		#ifdef _DEBUG
			cout << "CMenu::Executer (), fin partie" << endl;
		#endif //_DEBUG
		delete pPartie;
		pPartie = NULL;
	}
}

void CMenu::SetMenuPrincipalePosition (const menu_t Menu)
{
	if (Menu == MENU_INCREMENTE)
	{
		if (iMenuPrincipalePosition < MENU_PRINCIPALE_MAX)
			iMenuPrincipalePosition++;
		else
			iMenuPrincipalePosition = MENU_PRINCIPALE_MAX;
	}
	else
	{
		if (bPartieCommencer)
			if (iMenuPrincipalePosition > 0)
				iMenuPrincipalePosition--;
			else
				iMenuPrincipalePosition = 0;
		else
			if (iMenuPrincipalePosition > 1)
				iMenuPrincipalePosition--;
			else
				iMenuPrincipalePosition = 1;
	}
}

void CMenu::CommencerPartie (CInterface & Interface, const player_info_t Joueur1Information, const player_info_t Joueur2Information)
{
	pPartie = new CPartie (Interface, Joueur1Information, Joueur2Information);
	bPartieCommencer = true;
	ActionChoix = ACTION_CONTINUER_PARTIE;
}

// Groove - 12/02/2003 - Fonctions "Affichage" pour l'affichage dans le HUD
void CMenu::AfficherCommencer () const
{
	ShowTitle ();

	ShowMsg (Resolution.iLargeur / 2, Resolution.iHauteur - FONT_SIZE * 6, string (Text.GetJoueur1 ()), false);
	ShowChoicePlayerType (Resolution.iLargeur / 2, Resolution.iHauteur - FONT_SIZE * 7, string (Text.GetJoueurType ()), GetMenuCommencerPosition () == 0, PlayerInfo[0]);
	if (PlayerInfo[0].Type == JOUEUR_IA)
		ShowChoiceLevelIA (Resolution.iLargeur / 2, Resolution.iHauteur - FONT_SIZE * 8, string (Text.GetJoueurNiveau ()), GetMenuCommencerPosition () == 1, PlayerInfo[0]);
	else
		ShowPlayerName (Resolution.iLargeur / 2, Resolution.iHauteur - FONT_SIZE * 8, string (Text.GetJoueurNom ()), GetMenuCommencerPosition () == 1, PlayerInfo[0]);

	ShowMsg (Resolution.iLargeur / 2, Resolution.iHauteur - FONT_SIZE * 10, string (Text.GetJoueur2 ()), false);
	ShowChoicePlayerType (Resolution.iLargeur / 2, Resolution.iHauteur - FONT_SIZE * 11, string (Text.GetJoueurType ()), GetMenuCommencerPosition () == 2, PlayerInfo[1]);
	if (PlayerInfo[1].Type == JOUEUR_IA)
		ShowChoiceLevelIA (Resolution.iLargeur / 2, Resolution.iHauteur - FONT_SIZE * 12, string (Text.GetJoueurNiveau ()), GetMenuCommencerPosition () == 3, PlayerInfo[1]);
	else
		ShowPlayerName (Resolution.iLargeur / 2, Resolution.iHauteur - FONT_SIZE * 12, string (Text.GetJoueurNom ()), GetMenuCommencerPosition () == 3, PlayerInfo[1]);

	ShowMsg (Resolution.iLargeur / 2, Resolution.iHauteur - FONT_SIZE * 14, string (Text.GetPartieCommencer ()), GetMenuCommencerPosition () == 4);
}

void CMenu::AfficherScore ()
{
	ShowTitle ();

	if (pMeilleurScore == NULL)
		pMeilleurScore = new CMeilleurScore;

	for (short i=0; i<pMeilleurScore->GetNbr (); i++)
	{
		PrintCharacter (FONT_SIZE, Resolution.iHauteur - FONT_SIZE * (6 + i * 2), i);
		ShowScore (Resolution.iLargeur / 2, Resolution.iHauteur - FONT_SIZE * (6 + i * 2), (*pMeilleurScore)[i]);
	}
}

void CMenu::AfficherHUD () const
{
	ShowCurrentScore ();

	string szMsg;
	switch (MsgID)
	{
	default:
	case MSG_NULL:
		break;
	case MSG_JOUER_1:
		szMsg = pPartie->GetJoueurAdr (JOUEUR_1)->GetNom () + Text.GetMsgJouer ();
		break;
	case MSG_JOUER_2:
		szMsg = pPartie->GetJoueurAdr (JOUEUR_2)->GetNom () + Text.GetMsgJouer ();
		break;
	case MSG_GAGNE_1:
		szMsg = pPartie->GetJoueurAdr (JOUEUR_1)->GetNom () + Text.GetMsgGagnant ();
		break;
	case MSG_GAGNE_2:
		szMsg = pPartie->GetJoueurAdr (JOUEUR_2)->GetNom () + Text.GetMsgGagnant ();
		break;
	};

	ShowMsg (Resolution.iLargeur / 2, Resolution.iHauteur - FONT_SIZE, szMsg, false);
}

void CMenu::AfficherMenu ()
{
	ShowTitle ();

	if (pMeilleurScore)
	{
		delete pMeilleurScore;
		pMeilleurScore = NULL;
	}

	if (bPartieCommencer) 
		ShowMsg (Resolution.iLargeur / 2, Resolution.iHauteur - FONT_SIZE * 6, string (Text.GetPartieContinuer ()), GetMenuPrincipalePosition () == 0);
	ShowMsg (Resolution.iLargeur / 2, Resolution.iHauteur - FONT_SIZE * 7, string (Text.GetPartieCommencer ()), GetMenuPrincipalePosition () == 1);
	ShowMsg (Resolution.iLargeur / 2, Resolution.iHauteur - FONT_SIZE * 8, string (Text.GetMeilleurScores ()), GetMenuPrincipalePosition () == 2);
	ShowMsg (Resolution.iLargeur / 2, Resolution.iHauteur - FONT_SIZE * 9, string (Text.GetQuitter ()), GetMenuPrincipalePosition () == 3);
}

void CMenu::Initialiser (CInterface *_pInterface, const resolution_t _Resolution)
{
	pInterface = _pInterface;
	Text.Load ("text.txt");

	#ifdef _DEBUG
		cout << "CMenu::Initialiser (), debut" << endl;
		cout << "CMenu::Initialiser (), chargement titre, debut" << endl;
	#endif //_DEBUG
	
	if (!ImageTitre.Load (STRCAT (REP_IMAGE, "title.bmp")))
		exit (0);

	#ifdef _DEBUG
		cout << "CMenu::Initialiser (), chargement titre, fin" << endl;
		cout << "CMenu::Initialiser (), Load Font, debut" << endl;
	#endif //_DEBUG

	LoadFont ();

	#ifdef _DEBUG
		cout << "CMenu::Initialiser (), Load Font, fin" << endl;
	#endif //_DEBUG

	Resolution = _Resolution;

	#ifdef _DEBUG
		cout << "CMenu::Initialiser (), fin" << endl;
	#endif //_DEBUG
}

///////////////////////////////////////////////////////

void CMenu::InitialiserJoueursInformation ()
{
	PlayerInfo[0].szNom = "";
	PlayerInfo[0].Type = JOUEUR_HUMAIN;
	PlayerInfo[0].Niveau = NIVEAU_IA_3;
	PlayerInfo[0].iScore = 0;

	PlayerInfo[1].szNom = "";
	PlayerInfo[1].Type = JOUEUR_HUMAIN;
	PlayerInfo[1].Niveau = NIVEAU_IA_3;
	PlayerInfo[1].iScore = 0;
}

void CMenu::ChangerTypeJoueur (const joueur_index_t Index)
{
	if (Index == JOUEUR_1)
		if (PlayerInfo[0].Type == JOUEUR_HUMAIN)
			PlayerInfo[0].Type = JOUEUR_IA;
		else if (PlayerInfo[0].Type == JOUEUR_IA)
			PlayerInfo[0].Type = JOUEUR_HUMAIN;
	if (Index == JOUEUR_2)
		if (PlayerInfo[1].Type == JOUEUR_HUMAIN)
			PlayerInfo[1].Type = JOUEUR_IA;
		else if (PlayerInfo[1].Type == JOUEUR_IA)
			PlayerInfo[1].Type = JOUEUR_HUMAIN;
}

void CMenu::AjouterLettreAuNom (const joueur_index_t Index, unsigned char key)
{
	if (Index == JOUEUR_1)
		if (key == 8)
			PlayerInfo[0].szNom = string ("");
		else if (PlayerInfo[0].szNom.size () <= 16)
			PlayerInfo[0].szNom += key;
	if (Index == JOUEUR_2)
		if (key == 8)
			PlayerInfo[1].szNom = string ("");
		else if (PlayerInfo[0].szNom.size () <= 16)
			PlayerInfo[1].szNom += key;
}

joueur_type_t CMenu::GetJoueurType (const joueur_index_t Index) const
{
	if (Index == JOUEUR_1)
		return PlayerInfo[0].Type;
	else if (Index == JOUEUR_2)
		return PlayerInfo[1].Type;
	return JOUEUR_NULL;
}

void CMenu::SetNiveauIA (const joueur_index_t Index, const menu_t Menu)
{
	if (Index == JOUEUR_1)
		if (Menu == MENU_INCREMENTE)
		{
			PlayerInfo[0].Niveau++;
			if (PlayerInfo[0].Niveau > NIVEAU_IA_5)
				PlayerInfo[0].Niveau = NIVEAU_IA_5;
		}
		else if (Menu == MENU_DECREMENTE)
		{
			PlayerInfo[0].Niveau--;
			if (PlayerInfo[0].Niveau < NIVEAU_IA_1)
				PlayerInfo[0].Niveau = NIVEAU_IA_1;
		}
	if (Index == JOUEUR_2)
		if (Menu == MENU_INCREMENTE)
		{
			PlayerInfo[1].Niveau++;
			if (PlayerInfo[1].Niveau > NIVEAU_IA_5)
				PlayerInfo[1].Niveau = NIVEAU_IA_5;
		}
		else if (Menu == MENU_DECREMENTE)
		{
			PlayerInfo[1].Niveau--;
			if (PlayerInfo[1].Niveau < NIVEAU_IA_1)
				PlayerInfo[1].Niveau = NIVEAU_IA_1;
		}		
}

void CMenu::PrintCharacter (const short x, const short y, const char cCharacter) const
{
	short iLetterIndex = 0;
	switch (cCharacter)
	{
	default: break;
	case ' ': iLetterIndex = 0; break;
	case 'A': iLetterIndex = 1; break;
	case 'B': iLetterIndex = 2; break;
	case 'C': iLetterIndex = 3; break;
	case 'D': iLetterIndex = 4; break;
	case 'E': iLetterIndex = 5; break;
	case 'F': iLetterIndex = 6; break;
	case 'G': iLetterIndex = 7; break;
	case 'H': iLetterIndex = 8; break;
	case 'I': iLetterIndex = 9; break;
	case 'J': iLetterIndex = 10; break;
	case 'K': iLetterIndex = 11; break;
	case 'L': iLetterIndex = 12; break;
	case 'M': iLetterIndex = 13; break;
	case 'N': iLetterIndex = 14; break;
	case 'O': iLetterIndex = 15; break;
	case 'P': iLetterIndex = 16; break;
	case 'Q': iLetterIndex = 17; break;
	case 'R': iLetterIndex = 18; break;
	case 'S': iLetterIndex = 19; break;
	case 'T': iLetterIndex = 20; break;
	case 'U': iLetterIndex = 21; break;
	case 'V': iLetterIndex = 22; break;
	case 'W': iLetterIndex = 23; break;
	case 'X': iLetterIndex = 24; break;
	case 'Y': iLetterIndex = 25; break;
	case 'Z': iLetterIndex = 26; break;
	case 'a': iLetterIndex = 27; break;
	case 'b': iLetterIndex = 28; break;
	case 'c': iLetterIndex = 29; break;
	case 'd': iLetterIndex = 30; break;
	case 'e': iLetterIndex = 31; break;
	case 'f': iLetterIndex = 32; break;
	case 'g': iLetterIndex = 33; break;
	case 'h': iLetterIndex = 34; break;
	case 'i': iLetterIndex = 35; break;
	case 'j': iLetterIndex = 36; break;
	case 'k': iLetterIndex = 37; break;
	case 'l': iLetterIndex = 38; break;
	case 'm': iLetterIndex = 39; break;
	case 'n': iLetterIndex = 40; break;
	case 'o': iLetterIndex = 41; break;
	case 'p': iLetterIndex = 42; break;
	case 'q': iLetterIndex = 43; break;
	case 'r': iLetterIndex = 44; break;
	case 's': iLetterIndex = 45; break;
	case 't': iLetterIndex = 46; break;
	case 'u': iLetterIndex = 47; break;
	case 'v': iLetterIndex = 48; break;
	case 'w': iLetterIndex = 49; break;
	case 'x': iLetterIndex = 50; break;
	case 'y': iLetterIndex = 51; break;
	case 'z': iLetterIndex = 52; break;
	case '0': case 0: iLetterIndex = 53; break;
	case '1': case 1: iLetterIndex = 54; break;
	case '2': case 2: iLetterIndex = 55; break;
	case '3': case 3: iLetterIndex = 56; break;
	case '4': case 4: iLetterIndex = 57; break;
	case '5': case 5: iLetterIndex = 58; break;
	case '6': case 6: iLetterIndex = 59; break;
	case '7': case 7: iLetterIndex = 60; break;
	case '8': case 8: iLetterIndex = 61; break;
	case '9': case 9: iLetterIndex = 62; break;
	case ':': iLetterIndex = 63; break;
	case '>': iLetterIndex = 64; break;
	case '<': iLetterIndex = 65; break;
	}

	glRasterPos2f (x, y);
	glDrawPixels (FONT_SIZE, FONT_SIZE, GL_RGB, GL_UNSIGNED_BYTE, ImageFont[iLetterIndex].GetData ());
}

void CMenu::LoadFont ()
{
	ImageFont[0].Load ((string (REP_FONT) + string (FILE_FONT_ESPACE)).c_str ()); 
	ImageFont[1].Load ((string (REP_FONT) + string (FILE_FONT_A)).c_str ());
	ImageFont[2].Load ((string (REP_FONT) + string (FILE_FONT_B)).c_str ());
	ImageFont[3].Load ((string (REP_FONT) + string (FILE_FONT_C)).c_str ());
	ImageFont[4].Load ((string (REP_FONT) + string (FILE_FONT_D)).c_str ());
	ImageFont[5].Load ((string (REP_FONT) + string (FILE_FONT_E)).c_str ());
	ImageFont[6].Load ((string (REP_FONT) + string (FILE_FONT_F)).c_str ());
	ImageFont[7].Load ((string (REP_FONT) + string (FILE_FONT_G)).c_str ());
	ImageFont[8].Load ((string (REP_FONT) + string (FILE_FONT_H)).c_str ());
	ImageFont[9].Load ((string (REP_FONT) + string (FILE_FONT_I)).c_str ());
	ImageFont[10].Load ((string (REP_FONT) + string (FILE_FONT_J)).c_str ());
	ImageFont[11].Load ((string (REP_FONT) + string (FILE_FONT_K)).c_str ());
	ImageFont[12].Load ((string (REP_FONT) + string (FILE_FONT_L)).c_str ());
	ImageFont[13].Load ((string (REP_FONT) + string (FILE_FONT_M)).c_str ());
	ImageFont[14].Load ((string (REP_FONT) + string (FILE_FONT_N)).c_str ());
	ImageFont[15].Load ((string (REP_FONT) + string (FILE_FONT_O)).c_str ());
	ImageFont[16].Load ((string (REP_FONT) + string (FILE_FONT_P)).c_str ());
	ImageFont[17].Load ((string (REP_FONT) + string (FILE_FONT_Q)).c_str ());
	ImageFont[18].Load ((string (REP_FONT) + string (FILE_FONT_R)).c_str ());
	ImageFont[19].Load ((string (REP_FONT) + string (FILE_FONT_S)).c_str ());
	ImageFont[20].Load ((string (REP_FONT) + string (FILE_FONT_T)).c_str ());
	ImageFont[21].Load ((string (REP_FONT) + string (FILE_FONT_U)).c_str ());
	ImageFont[22].Load ((string (REP_FONT) + string (FILE_FONT_V)).c_str ());
	ImageFont[23].Load ((string (REP_FONT) + string (FILE_FONT_W)).c_str ());
	ImageFont[24].Load ((string (REP_FONT) + string (FILE_FONT_X)).c_str ());
	ImageFont[25].Load ((string (REP_FONT) + string (FILE_FONT_Y)).c_str ());
	ImageFont[26].Load ((string (REP_FONT) + string (FILE_FONT_Z)).c_str ());
	ImageFont[27].Load ((string (REP_FONT) + string (FILE_FONT_a)).c_str ());
	ImageFont[28].Load ((string (REP_FONT) + string (FILE_FONT_b)).c_str ());
	ImageFont[29].Load ((string (REP_FONT) + string (FILE_FONT_c)).c_str ());
	ImageFont[30].Load ((string (REP_FONT) + string (FILE_FONT_d)).c_str ());
	ImageFont[31].Load ((string (REP_FONT) + string (FILE_FONT_e)).c_str ());
	ImageFont[32].Load ((string (REP_FONT) + string (FILE_FONT_f)).c_str ());
	ImageFont[33].Load ((string (REP_FONT) + string (FILE_FONT_g)).c_str ());
	ImageFont[34].Load ((string (REP_FONT) + string (FILE_FONT_h)).c_str ());
	ImageFont[35].Load ((string (REP_FONT) + string (FILE_FONT_i)).c_str ());
	ImageFont[36].Load ((string (REP_FONT) + string (FILE_FONT_j)).c_str ());
	ImageFont[37].Load ((string (REP_FONT) + string (FILE_FONT_k)).c_str ());
	ImageFont[38].Load ((string (REP_FONT) + string (FILE_FONT_l)).c_str ());
	ImageFont[39].Load ((string (REP_FONT) + string (FILE_FONT_m)).c_str ());
	ImageFont[40].Load ((string (REP_FONT) + string (FILE_FONT_n)).c_str ());
	ImageFont[41].Load ((string (REP_FONT) + string (FILE_FONT_o)).c_str ());
	ImageFont[42].Load ((string (REP_FONT) + string (FILE_FONT_p)).c_str ());
	ImageFont[43].Load ((string (REP_FONT) + string (FILE_FONT_q)).c_str ());
	ImageFont[44].Load ((string (REP_FONT) + string (FILE_FONT_r)).c_str ());
	ImageFont[45].Load ((string (REP_FONT) + string (FILE_FONT_s)).c_str ());
	ImageFont[46].Load ((string (REP_FONT) + string (FILE_FONT_t)).c_str ());
	ImageFont[47].Load ((string (REP_FONT) + string (FILE_FONT_u)).c_str ());
	ImageFont[48].Load ((string (REP_FONT) + string (FILE_FONT_v)).c_str ());
	ImageFont[49].Load ((string (REP_FONT) + string (FILE_FONT_w)).c_str ());
	ImageFont[50].Load ((string (REP_FONT) + string (FILE_FONT_x)).c_str ());
	ImageFont[51].Load ((string (REP_FONT) + string (FILE_FONT_y)).c_str ());
	ImageFont[52].Load ((string (REP_FONT) + string (FILE_FONT_z)).c_str ());
	ImageFont[53].Load ((string (REP_FONT) + string (FILE_FONT_0)).c_str ());
	ImageFont[54].Load ((string (REP_FONT) + string (FILE_FONT_1)).c_str ());
	ImageFont[55].Load ((string (REP_FONT) + string (FILE_FONT_2)).c_str ());
	ImageFont[56].Load ((string (REP_FONT) + string (FILE_FONT_3)).c_str ());
	ImageFont[57].Load ((string (REP_FONT) + string (FILE_FONT_4)).c_str ());
	ImageFont[58].Load ((string (REP_FONT) + string (FILE_FONT_5)).c_str ());
	ImageFont[59].Load ((string (REP_FONT) + string (FILE_FONT_6)).c_str ());
	ImageFont[60].Load ((string (REP_FONT) + string (FILE_FONT_7)).c_str ());
	ImageFont[61].Load ((string (REP_FONT) + string (FILE_FONT_8)).c_str ());
	ImageFont[62].Load ((string (REP_FONT) + string (FILE_FONT_9)).c_str ());
	ImageFont[63].Load ((string (REP_FONT) + string (FILE_FONT_2_POINT)).c_str ());
	ImageFont[64].Load ((string (REP_FONT) + string (FILE_FONT_SUP)).c_str ());
	ImageFont[65].Load ((string (REP_FONT) + string (FILE_FONT_INF)).c_str ());
}

// Groove - 12/02/2003 - Fonction "Affichage" créer a partir des fonctions "show"
void CMenu::ShowScore (const short iPositionX, const short iPositionY, const CResultat & Resultat) const
{
	short iScoreBuffer;
	string::const_iterator it;
	string szNom;
	short iPositionCurrentX;

	iPositionCurrentX = iPositionX - 2 * FONT_SIZE;
	iScoreBuffer = Resultat.GetScoreGagnant ();

	do
	{
		PrintCharacter (iPositionCurrentX, iPositionY, iScoreBuffer % 10);
		iPositionCurrentX -= FONT_SIZE;
	}
	while (iScoreBuffer /= 10);

	iPositionCurrentX = iPositionX + 2 * FONT_SIZE;
	iScoreBuffer = Resultat.GetScorePerdant ();

	do
	{
		PrintCharacter (iPositionCurrentX, iPositionY, iScoreBuffer % 10);
		iPositionCurrentX -= FONT_SIZE;
	}
	while (iScoreBuffer /= 10);
	
	iPositionCurrentX = iPositionX - 5 * FONT_SIZE - Resultat.GetNomGagnant ().size () * FONT_SIZE;
	szNom = Resultat.GetNomGagnant ();
	for (it = szNom.begin (); it != szNom.end (); it++)
	{
		PrintCharacter (iPositionCurrentX, iPositionY, *it);
		iPositionCurrentX += FONT_SIZE;
	}

	iPositionCurrentX = iPositionX + 5 * FONT_SIZE;
	szNom = Resultat.GetNomPerdant ();
	for (it = szNom.begin (); it != szNom.end (); it++)
	{
		PrintCharacter (iPositionCurrentX, iPositionY, *it);
		iPositionCurrentX += FONT_SIZE;
	}
}

void CMenu::ShowPlayerName (const short x, const short y, string szMsg, const bool bCursor, const player_info_t & PlayerInfo) const
{
	szMsg += PlayerInfo.szNom;

	const short iSize = szMsg.size ();
	short iPositionX = x - iSize / 2 * FONT_SIZE;

	for (string::iterator It = szMsg.begin (); It != szMsg.end (); It++)
	{
		PrintCharacter (iPositionX, y, *It);
		iPositionX += FONT_SIZE;
	}

	if (bCursor)
		ShowCursor (x, y, iSize);
}

void CMenu::ShowFPS (short iFps) const
{
	// Groove - 14/01/2003 - Print the player 1 score.
	short iPositionX = Resolution.iLargeur - FONT_SIZE;
	short iPositionY = Resolution.iHauteur - FONT_SIZE;
	do
	{
		PrintCharacter (iPositionX, iPositionY, iFps % 10);
		iPositionX -= FONT_SIZE;
	}
	while (iFps /= 10);
}

void CMenu::ShowCurrentScore () const
{
	short iSize;
	short iPositionX;
	short iPositionY;
	string szNom;
	string::const_iterator it;

	// Groove - 14/01/2003 - Print the player 1 name.
	szNom = pPartie->GetJoueurAdr (JOUEUR_1)->GetNom ();
	iSize = szNom.size ();
	iPositionX = 0;
	iPositionY = Resolution.iHauteur - FONT_SIZE * 5;

	for (it = szNom.begin (); it != szNom.end (); it++)
	{
		PrintCharacter (iPositionX, iPositionY, *it);
		iPositionX += FONT_SIZE;
	}

	// Groove - 14/01/2003 - Print the player 2 name.
	szNom = pPartie->GetJoueurAdr (JOUEUR_2)->GetNom ();
	iSize = szNom.size ();
	iPositionX = Resolution.iLargeur - iSize * FONT_SIZE;
	iPositionY = Resolution.iHauteur - FONT_SIZE * 5;

	for (it = szNom.begin (); it != szNom.end ();it++)
	{
		PrintCharacter (iPositionX, iPositionY, *it);
		iPositionX += FONT_SIZE;
	}

	short iNumberBuffer;

	// Groove - 14/01/2003 - Print the player 1 score.
	iPositionX = FONT_SIZE * 2;
	iPositionY = Resolution.iHauteur - FONT_SIZE * 6;
	iNumberBuffer = pPartie->GetJoueurAdr (JOUEUR_1)->GetScore ();
	do
	{
		PrintCharacter (iPositionX, iPositionY, iNumberBuffer % 10);
		iPositionX -= FONT_SIZE;
	}
	while (iNumberBuffer /= 10);

	// Groove - 14/01/2003 - Print the player 2 score.
	iPositionX = Resolution.iLargeur - FONT_SIZE * 2;
	iPositionY = Resolution.iHauteur - FONT_SIZE * 6;
	iNumberBuffer = pPartie->GetJoueurAdr (JOUEUR_2)->GetScore ();
	do
	{
		PrintCharacter (iPositionX, iPositionY, iNumberBuffer % 10);
		iPositionX -= FONT_SIZE;
	}
	while (iNumberBuffer /= 10);
}

void CMenu::ShowChoiceLevelIA (const short x, const short y, string szMsg, const bool bCursor, const player_info_t & PlayerInfo) const
{
	switch (PlayerInfo.Niveau)
	{
	default:
	case NIVEAU_IA_1:
		szMsg += '1';
		break;
	case NIVEAU_IA_2:
		szMsg += '2';
		break;
	case NIVEAU_IA_3:
		szMsg += '3';
		break;
	case NIVEAU_IA_4:
		szMsg += '4';
		break;
	case NIVEAU_IA_5:
		szMsg += '5';
		break;
	}

	const short iSize = szMsg.size ();
	short iPositionX = x - iSize / 2 * FONT_SIZE;

	for (string::const_iterator cit = szMsg.begin (); cit != szMsg.end (); cit++)
	{
		PrintCharacter (iPositionX, y, *cit);
		iPositionX += FONT_SIZE;
	}

	if (bCursor)
		ShowCursor (x, y, iSize);
}

void CMenu::ShowChoicePlayerType (const short x, const short y, string szMsg, const bool bCursor, const player_info_t & PlayerInfo) const
{
	if (PlayerInfo.Type == JOUEUR_IA)
		szMsg += Text.GetJoueurIA ();
	else
		szMsg += Text.GetJoueurHumain ();

	const short iSize = szMsg.size ();
	short iPositionX = x - iSize / 2 * FONT_SIZE;

	for (string::const_iterator cit = szMsg.begin (); cit != szMsg.end (); cit++)
	{
		PrintCharacter (iPositionX, y, *cit);
		iPositionX += FONT_SIZE;
	}

	if (bCursor)
		ShowCursor (x, y, iSize);
}

void CMenu::ShowMsg (const short x, const short y, const string & szMsg, const bool bCursor) const
{
	const short iSize = szMsg.size ();
	short iPositionX = x - iSize / 2 * FONT_SIZE ;

	for (string::const_iterator cit = szMsg.begin (); cit != szMsg.end (); cit++)
	{
		PrintCharacter (iPositionX, y, *cit);
		iPositionX += FONT_SIZE;
	}

	if (bCursor)
		ShowCursor (x, y, iSize);
}

void CMenu::ShowTitle () const
{
	glRasterPos2f (Resolution.iLargeur / 2 - ImageTitre.GetWidth () / 2, Resolution.iHauteur - ImageTitre.GetHeight ());
	glDrawPixels (ImageTitre.GetWidth (), ImageTitre.GetHeight (), GL_RGB, GL_UNSIGNED_BYTE, ImageTitre.GetData ());
}

void CMenu::ShowCursor (const short x, const short y, const short iSize) const
{
	short iPositionX;
	iPositionX = Resolution.iLargeur / 2 - iSize * FONT_SIZE / 2 - 2 * FONT_SIZE;
	PrintCharacter (iPositionX, y, '>');
	iPositionX = Resolution.iLargeur / 2 + iSize * FONT_SIZE / 2 + 1 * FONT_SIZE;
	PrintCharacter (iPositionX, y, '<');
}
