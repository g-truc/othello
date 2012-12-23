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
*	affichage_menu.h, 29/03/2003						*
*	par Groove, groove@g-truc.fr.st						*
\*******************************************************/

#ifndef MENU_H
#define MENU_H

#include "common.h"
#include "joueur.h"
#include "meilleur_score.h"
#include "menu.h"
#include "partie.h"
#include "resultat.h"
#include "text.h"
#include "../gtl/include/gtl_image_bmp.h"
#include "../gtl/include/gtl_image_tga.h"
#include <string>

using namespace gtl;
using namespace std;

#define FONT_SIZE		16

#define REP_FONT		"./font/"
#define REP_IMAGE		"./image/"

#define FILE_FONT_ESPACE	"_.tga"
#define FILE_FONT_a			"_a.tga"
#define FILE_FONT_b			"_b.tga"
#define FILE_FONT_c			"_c.tga"
#define FILE_FONT_d			"_d.tga"
#define FILE_FONT_e			"_e.tga"
#define FILE_FONT_f			"_f.tga"
#define FILE_FONT_g			"_g.tga"
#define FILE_FONT_h			"_h.tga"
#define FILE_FONT_i			"_i.tga"
#define FILE_FONT_j			"_j.tga"
#define FILE_FONT_k			"_k.tga"
#define FILE_FONT_l			"_l.tga"
#define FILE_FONT_m			"_m.tga"
#define FILE_FONT_n			"_n.tga"
#define FILE_FONT_o			"_o.tga"
#define FILE_FONT_p			"_p.tga"
#define FILE_FONT_q			"_q.tga"
#define FILE_FONT_r			"_r.tga"
#define FILE_FONT_s			"_s.tga"
#define FILE_FONT_t			"_t.tga"
#define FILE_FONT_u			"_u.tga"
#define FILE_FONT_v			"_v.tga"
#define FILE_FONT_w			"_w.tga"
#define FILE_FONT_x			"_x.tga"
#define FILE_FONT_y			"_y.tga"
#define FILE_FONT_z			"_z.tga"
#define FILE_FONT_A			"a.tga"
#define FILE_FONT_B			"b.tga"
#define FILE_FONT_C			"c.tga"
#define FILE_FONT_D			"d.tga"
#define FILE_FONT_E			"e.tga"
#define FILE_FONT_F			"f.tga"
#define FILE_FONT_G			"g.tga"
#define FILE_FONT_H			"h.tga"
#define FILE_FONT_I			"i.tga"
#define FILE_FONT_J			"j.tga"
#define FILE_FONT_K			"k.tga"
#define FILE_FONT_L			"l.tga"
#define FILE_FONT_M			"m.tga"
#define FILE_FONT_N			"n.tga"
#define FILE_FONT_O			"o.tga"
#define FILE_FONT_P			"p.tga"
#define FILE_FONT_Q			"q.tga"
#define FILE_FONT_R			"r.tga"
#define FILE_FONT_S			"s.tga"
#define FILE_FONT_T			"t.tga"
#define FILE_FONT_U			"u.tga"
#define FILE_FONT_V			"v.tga"
#define FILE_FONT_W			"w.tga"
#define FILE_FONT_X			"x.tga"
#define FILE_FONT_Y			"y.tga"
#define FILE_FONT_Z			"z.tga"
#define FILE_FONT_0			"0.tga"
#define FILE_FONT_1			"1.tga"
#define FILE_FONT_2			"2.tga"
#define FILE_FONT_3			"3.tga"
#define FILE_FONT_4			"4.tga"
#define FILE_FONT_5			"5.tga"
#define FILE_FONT_6			"6.tga"
#define FILE_FONT_7			"7.tga"
#define FILE_FONT_8			"8.tga"
#define FILE_FONT_9			"9.tga"
#define FILE_FONT_2_POINT	"2p.tga"
#define FILE_FONT_INF		"inf.tga"
#define FILE_FONT_SUP		"sup.tga"

typedef enum
{
	MSG_NULL = 0,
	MSG_JOUER_1,
	MSG_JOUER_2,
	MSG_ERREUR_1,
	MSG_ERREUR_2,
	MSG_GAGNE_1,
	MSG_GAGNE_2,
}msg_id_t;

typedef enum 
{
	ACTION_NULL = 0,
	ACTION_COMMENCER_PARTIE,
	ACTION_CONTINUER_PARTIE,
	ACTION_FIN_PARTIE,
	ACTION_MENU,
	ACTION_QUITTER,
	ACTION_VOIR_MEILLEUR_SCORE,
} action_t;

typedef enum
{
	MENU_INCREMENTE = 0,
	MENU_DECREMENTE,
} menu_t;

#define MENU_PRINCIPALE_MAX		3
#define MENU_COMMENCER_MAX		4

class CPartie;

class CMenu
{
private:
	CImageBMP ImageTitre;
	CImageTGA ImageFont[66];
	CText Text;
	msg_id_t MsgID;
	resolution_t Resolution;
	
	player_info_t PlayerInfo[2];

	CMeilleurScore *pMeilleurScore;
	CPartie *pPartie;
	CInterface *pInterface;

	unsigned char iMenuPrincipalePosition;
	unsigned char iMenuCommencerPosition;
	bool bPartieCommencer;
	action_t ActionChoix;

	// Groove - 02/02/2003 - Affichage charactère par charactère
	void PrintCharacter (const short x, const short y, const char cCharacter) const;
	// Groove - 02/02/2003 - Chargement des charactères dans des display list.
	void LoadFont ();

	// Groove - 02/02/2003 - Fonctions de génération de menu dans le HUD
	void ShowChoiceLevelIA (const short x, const short y, string szMsg, const bool bCursor, const player_info_t & PlayerInfo) const;
	void ShowChoicePlayerType (const short x, const short y, string szMsg, const bool bCursor, const player_info_t & PlayerInfo) const;
	void ShowCurrentScore () const;
	void ShowCursor (const short x, const short y, short iSize) const;
	void ShowMsg (const short x, const short y, const string & szMsg, const bool bCursor) const;
	void ShowPlayerName (const short x, const short y, string szMsg, const bool bCursor, const player_info_t & PlayerInfo) const;
	void ShowTitle () const;
	void ShowScore (const short iPositionX, const short iPositionY, const CResultat & Resultat) const;

public:
	CMenu () {pPartie = NULL; pMeilleurScore = NULL; pInterface = NULL; ActionChoix = ACTION_MENU; iMenuPrincipalePosition = 1; iMenuCommencerPosition = 0; bPartieCommencer = false;}
	~CMenu () {if (pPartie) delete pPartie;}

	void Initialiser (CInterface *_pInterface, const resolution_t Resolution);

	void AjouterLettreAuNom (const joueur_index_t Index, const unsigned char key);
	void ChangerTypeJoueur (const joueur_index_t Index);
	joueur_type_t GetJoueurType (const joueur_index_t Index) const ;
	player_info_t GetJoueurInformation (const joueur_index_t Index) const {return Index == JOUEUR_1 ? PlayerInfo[0] : PlayerInfo[1];}
	void InitialiserJoueursInformation ();
	void SetNiveauIA (const joueur_index_t Index, const menu_t Menu);
	void SetMsgHUD (const msg_id_t _MsgID) {MsgID = _MsgID;}

	void ShowFPS (short iFps) const;

	// Groove - 02/02/2003 - Affichage suivant page
	void AfficherCommencer () const;
	void AfficherHUD () const;
	void AfficherMenu ();
	void AfficherScore ();

	action_t DemanderChoixAction () const {return ActionChoix;}
	void SetActionChoix (const action_t _ActionChoix) {ActionChoix = _ActionChoix;}

	unsigned char GetMenuPrincipalePosition () const {return iMenuPrincipalePosition;}
	void SetMenuPrincipalePosition (const menu_t Menu);
	unsigned char GetMenuCommencerPosition () const {return iMenuCommencerPosition;}
	void SetMenuCommencerPosition (const menu_t Menu) {Menu == MENU_INCREMENTE ? (iMenuCommencerPosition < MENU_COMMENCER_MAX ? iMenuCommencerPosition++ : iMenuCommencerPosition = MENU_COMMENCER_MAX) : (iMenuCommencerPosition > 0 ? iMenuCommencerPosition-- : iMenuCommencerPosition = 0);}

	void Executer ();
	void CommencerPartie (CInterface & Interface, const player_info_t Joueur1Information, const player_info_t Joueur2Information);
};

#endif //MENU_H
