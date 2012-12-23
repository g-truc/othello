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
*	affichage_plateau.h, 20/02/2003						*
*	par Groove, groove@g-truc.fr.st						*
\*******************************************************/

#ifndef AFFICHAGE_PLATEAU_H
#define AFFICHAGE_PLATEAU_H

#include "../gtl/include/gtl_color.h"
#include "../gtl/include/gtl_image.h"
#include "affichage_plateau.h"
#include "common.h"
#include "grille.h"
#include <string>

using namespace std;
using namespace gtl;

#define PAWN_SIZE	 0.4
#define PAWN_HEIGHT  0.05

typedef enum
{
	IMPUT_TYPE_PLAYER_1 = 0,
	IMPUT_NAME_PLAYER_1,
	IMPUT_AI_LEVEL_1,
	IMPUT_TYPE_PLAYER_2,
	IMPUT_NAME_PLAYER_2,
	IMPUT_AI_LEVEL_2,
	IMPUT_START_GAME,
} create_game_t;

typedef enum
{
	ROTATE_NULL = 0,
	ROTATE_X_PLUS,
	ROTATE_X_MOINS,
	ROTATE_Y_PLUS,
	ROTATE_Y_MOINS,
	ROTATE_Z_PLUS,
	ROTATE_Z_MOINS,
}rotate_t;

typedef enum
{
	MOVE_NULL = 0,
	MOVE_Z_PLUS,
	MOVE_Z_MOINS
} deplacement_t;

typedef enum
{
	DIRECTION_HAUT = 0,
	DIRECTION_BAS,
	DIRECTION_GAUCHE,
	DIRECTION_DROITE,
} direction_t;

class CAffichagePlateau
{
private:
	CGrille *pGrille;
	position_t PositionPion, CursorPosition;

	struct display_list_s // Groove - 13/01/2003 - Display list index
	{
		short iCursorID;
		short iFigureID[10];
		short iTrayID;
		short iPawnID;
	} DispListID;

	struct angle_s
	{
		short x;
		short y;
		short z;
	} Angle;

	float fDeplacementZ;

	float fCursorAngle;

	void DisplayInGameHUD ();
	void DisplayStartGame ();
	void DisplayStartGameCursor (short iSizeOfString, short y);
	void DisplayHighScore ();
	void DisplayMenu ();
	void DisplayMenuCursor (short iSizeOfString, short y);

	short iSurfaceId;
	short iPlateauId;

	void LoadPlateau ();

	// Groove - 13/01/2003 - LDL pour Load Display List
	void LDL_Cursor ();
	void LDL_Figures ();
	void LDL_Pawn ();
	void LDL_Tray ();

	void DrawCursor (float x, float y, float z = 0.3);
	void DrawFigure (short iFigure, float x, float y, float z, color3_t color);
/*#ifdef _DEBUG
	void DrawModelForIA ();
#endif //_DEBUG*/
	void DrawPawn (pion_t Pion, float x, float y, float z = 0.0);
	// Groove - 13/01/2003 - To use DrawTray (), Tray must be loaded with LoadTray ().
	void DrawTray ();

	pion_t GetValeurGrille (const short iCase) {return (*pGrille)[iCase];}

public:
	CAffichagePlateau () {pGrille = NULL;}

	position_t GetPosition ();

	void SetPosition (const position_t _PositionPion) {PositionPion = _PositionPion;}

	void Initialiser (CGrille *_pGrille);

	void DisplayInGameScene ();
	void DeplacerCurseur (int key);

	void AfficherPlateau ();
	void ValiderCurseur ();

	void DeplacerCurseur (const position_t Position) {CursorPosition = Position;}
	
	void TournerPlateau (const rotate_t Rotate);
	void DeplacerPlateau (const deplacement_t Deplacement);
};

#endif //AFFICHAGE_PLATEAU_H
