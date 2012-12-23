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
*	joueur_ia.cpp, 20/02/2003							*
*	par Groove, groove@g-truc.fr.st						*
\*******************************************************/

#include "../header/grille.h"
#include "../header/joueur_ia.h"
#include "../gtl/include/gtl_rand.h"
#include <time.h>
#include <fstream>
#include <iostream>

using namespace gtl;
using namespace std;

CJoueurIA::CJoueurIA (const char* szFileName, CInterface *_pInterface, joueur_index_t _Index)
{
	pInterface = _pInterface;
	iPionNb = 2;
	Index = _Index;
	TimeStart = 0;

	LoadModelIA (szFileName);
}

position_t CJoueurIA::DemanderPositionPion (CReglesJeu & Regles)
{
	pInterface->DemanderPositionPion (Index);

	short iMaxReversePawn = 0;
	short iMaxPoints = 0;
	position_t Position = {-1, -1};
	cases_t PositionList;

	if (TimeStart == 0)
		TimeStart = time (NULL);

	if ((time (NULL) - TimeStart) < TEMPS_PR_JOUER)
		return Position;

	TimeStart = 0;

	for (short i=0; i<64; i++)
	{
		if (Regles.GetValeurGrille (i) == PION_NULL)
		{
			short iBufferNumberPawn = Regles.VerifierPose (i%GRID_SIZE, i/GRID_SIZE, Index == JOUEUR_1 ? PION_BLANC : PION_NOIR);
			
			if (iMaxReversePawn == iBufferNumberPawn && iMaxPoints == iModelIA[i])
			{
				PositionList.insert (i);
			}
			else if (iMaxReversePawn < iBufferNumberPawn && iMaxPoints == iModelIA[i])
			{
				iMaxReversePawn = iBufferNumberPawn;
				PositionList.clear ();
				PositionList.insert (i);
			}
			else if (iBufferNumberPawn > 0 && iMaxPoints < iModelIA[i])
			{
				iMaxPoints = iModelIA[i];
				iMaxReversePawn = iBufferNumberPawn;
				PositionList.clear ();
				PositionList.insert (i);
			}
		}
	}

	short iSize = PositionList.size ();
	long iChoosePosition = RandInt (0, iSize);

	cases_cit pos_cit = PositionList.begin ();
	for (short j = 0; j < iChoosePosition; j++, pos_cit++);
	Position.x = (*pos_cit) % GRID_SIZE;
	Position.y = (*pos_cit) / GRID_SIZE;

	if (Position.x == 0 && Position.y == 0)
		iModelIA[1] = iModelIA[8] = iModelIA[9] = 9;
	if (Position.x == 7 && Position.y == 0)
		iModelIA[6] = iModelIA[14] = iModelIA[15] = 9;
	if (Position.x == 0 && Position.y == 7)
		iModelIA[48] = iModelIA[49] = iModelIA[57] = 9;
	if (Position.x == 7 && Position.y == 7)
		iModelIA[54] = iModelIA[55] = iModelIA[62] = 9;

	pInterface->DeplacerCurseur (Position);

	return Position;
}

/*void CJoueurIA::GenerateModelIA ()
{
	for (short i=0; i<GRID_SIZE; i++)
		for (short j=0; j<GRID_SIZE; j++)
			iModelIA[j * GRID_SIZE + i] = RandInt (1, 9);

	iModelIA[7] = iModelIA[56] = iModelIA[63] = iModelIA[0];
	iModelIA[14] = iModelIA[49] = iModelIA[54] = iModelIA[9];
	iModelIA[21] = iModelIA[42] = iModelIA[45] = iModelIA[18];
	iModelIA[28] = iModelIA[35] = iModelIA[36] = iModelIA[27];

	iModelIA[15] = iModelIA[48] = iModelIA[55] = iModelIA[8] = iModelIA[6] = iModelIA[57] = iModelIA[62] = iModelIA[1];
	iModelIA[23] = iModelIA[40] = iModelIA[47] = iModelIA[16] = iModelIA[5] = iModelIA[58] = iModelIA[61] = iModelIA[2];
	iModelIA[31] = iModelIA[32] = iModelIA[39] = iModelIA[24] = iModelIA[4] = iModelIA[59] = iModelIA[60] = iModelIA[3];
	
	iModelIA[22] = iModelIA[41] = iModelIA[46] = iModelIA[17] = iModelIA[13] = iModelIA[50] = iModelIA[53] = iModelIA[10];
	iModelIA[30] = iModelIA[33] = iModelIA[38] = iModelIA[25] = iModelIA[12] = iModelIA[51] = iModelIA[52] = iModelIA[11];
	iModelIA[29] = iModelIA[34] = iModelIA[37] = iModelIA[26] = iModelIA[20] = iModelIA[43] = iModelIA[44] = iModelIA[19];
}*/

void CJoueurIA::LoadModelIA (const char* szNameFile)
{
	ifstream in (STRCAT (REP_DATA, szNameFile));
	if (!in.good ())
	{
		cerr << "Erreur lors de l'ouverture du fichier " << szNameFile << endl;
		return;
	}

	getline (in, szNom);

	szNom += " IA";

	for (int i=0; i<64; i++)
		in >> iModelIA[i];
}

/*void CJoueurIA::SaveModelIA (const char* szNameFile)
{
	ofstream out ((string (REP_DATA) + string (szNameFile)).c_str (), ios::out | ios::trunc);
	if (!out.good ())
	{
		cerr << "Erreur lors de l'ouverture du fichier " << szNameFile << endl;
		return;
	}

	for (short i=0; i<64; i++)
		out << iModelIA[i] << endl;
}*/
