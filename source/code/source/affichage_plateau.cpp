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
*	affichage_plateau.cpp, 20/02/2003					*
*	par Groove, groove@g-truc.fr.st						*
\*******************************************************/

#include "../header/menu.h"
#include "../header/affichage_plateau.h"
#include "../gtl/include/gtl_math.h"
#include "../gtl/include/gtl_color.h"
#include <GL/glut.h>
#include <iostream>

using namespace gtl;
using namespace std;

void CAffichagePlateau::Initialiser (CGrille *_pGrille)
{
	pGrille = _pGrille;

	glEnable (GL_DEPTH_TEST);

	// Groove - 12/01/2003 - Culling initialisation
	glFrontFace (GL_CCW);
	glCullFace (GL_BACK);
	glEnable (GL_CULL_FACE);

	// Groove - 12/01/2003 - Antialiasing on row
	glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
//	glHint (GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable (GL_LINE_SMOOTH);
//	glEnable (GL_POLYGON_SMOOTH);

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLineWidth (1.5);

	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	PositionPion.x = -1;
	PositionPion.y = -1;
	CursorPosition.x = 4;
	CursorPosition.y = 4;
	Angle.x = 0;
	Angle.y = 0;
	Angle.z = 0;
	fDeplacementZ = 0.;

	LoadPlateau ();

	LDL_Cursor ();
	LDL_Figures ();
	LDL_Pawn ();
	LDL_Tray ();
}

void CAffichagePlateau::DeplacerPlateau (const deplacement_t Deplacement)
{
	if (Deplacement == MOVE_Z_PLUS)
	{
		fDeplacementZ += 0.1;
		if (fDeplacementZ > 2.0)
			fDeplacementZ = 2.0;
	}
	else if (Deplacement == MOVE_Z_MOINS)
	{
		fDeplacementZ -= 0.1;
		if (fDeplacementZ < -10.0)
			fDeplacementZ = -10.0;
	}
}

void CAffichagePlateau::TournerPlateau (const rotate_t Rotate)
{
	switch (Rotate)
	{
	default:
	case ROTATE_NULL:
		break;
	case ROTATE_X_PLUS:
		Angle.x++;
		if (Angle.x > 45)
			Angle.x = 45;
		break;
	case ROTATE_X_MOINS:
		Angle.x--;
		if (Angle.x < -35)
			Angle.x = -35;
		break;
	case ROTATE_Y_PLUS:
		Angle.y++;
		if (Angle.y > 90)
			Angle.y = 90;
		break;
	case ROTATE_Y_MOINS:
		Angle.y--;
		if (Angle.y < -90)
			Angle.y = -90;
		break;
	case ROTATE_Z_PLUS:
		Angle.z++;
		break;
	case ROTATE_Z_MOINS:
		Angle.z--;
		break;
	}
}

void CAffichagePlateau::DeplacerCurseur (const int key)
{
	#ifdef _DEBUG
		cout << "Deplacement Curseur" << endl;
	#endif //_DEBUG

	if (key == GLUT_KEY_UP || key == '8')
	{
		CursorPosition.y++;
		if (CursorPosition.y > 7)
			CursorPosition.y = 7;
	}
	else if (key == GLUT_KEY_DOWN || key == '2')
	{
		CursorPosition.y--;
		if (CursorPosition.y < 0)
			CursorPosition.y = 0;
	}	
	else if (key == GLUT_KEY_RIGHT || key == '6')
	{
		CursorPosition.x++;
		if (CursorPosition.x > 7)
			CursorPosition.x = 7;
	}
	else if (key == GLUT_KEY_LEFT || key == '4')
	{
		CursorPosition.x--;
		if (CursorPosition.x < 0)
			CursorPosition.x = 0;
	}	
}

void CAffichagePlateau::ValiderCurseur ()
{
	#ifdef _DEBUG
		cout << "CAffichagePlateau::ValiderCurseur ()" << endl;
	#endif //_DEBUG
	SetPosition (CursorPosition);
}

position_t CAffichagePlateau::GetPosition ()
{
	position_t Retour = PositionPion;
	PositionPion.x = -1;
	PositionPion.y = -1;
	return Retour;
}

void CAffichagePlateau::AfficherPlateau ()
{
	gluLookAt (0,-10,10,0,0,0,0,1,0);

	glTranslatef (0, -fDeplacementZ, fDeplacementZ);
	glRotated (Angle.x, 1, 0, 0);
	glRotated (Angle.y, 0, 1, 0);
	glRotated (Angle.z, 0, 0, 1);

	glPushMatrix ();
		glTranslatef (-4,-4,0);

		DrawTray ();

		glEnable (GL_TEXTURE_2D);				//Activate the texture_2D
			glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glBindTexture (GL_TEXTURE_2D, iPlateauId);
			glCallList (iSurfaceId);
		glDisable (GL_TEXTURE_2D);				//Unactivate the texture

		DrawCursor (CursorPosition.x, CursorPosition.y);
	
		for (int i=0; i<GRID_SIZE; i++)
			for (int j=0; j<GRID_SIZE; j++)
				DrawPawn (GetValeurGrille (j * GRID_SIZE + i), i, j);

/*#ifdef _DEBUG
	DrawModelForIA ();
#endif //_DEBUG*/
	glPopMatrix ();
}

/*#ifdef _DEBUG
void CAffichagePlateau::DrawModelForIA ()
{
	color3_t fColorRed = {1.0, 0.0, 0.0};

	for (short i=0; i<GRID_SIZE; i++)
		for (short j=0; j<GRID_SIZE; j++)
			DrawFigure (g_piModel[j * GRID_SIZE + i], i, j, 0.2, fColorRed);
}
#endif //_DEBUG*/

void CAffichagePlateau::DrawFigure (short Chiffre, float x, float y, float z, color3_t color)
{
	glPushMatrix ();
		glColor3fv (color);
		glTranslatef (x,y,z);
		if (Chiffre < 0 || Chiffre > 9)
			Chiffre = 0;
		glCallList (DispListID.iFigureID[Chiffre]);
	glPopMatrix ();
}

void CAffichagePlateau::DrawCursor (float x, float y, float z)
{
	glPushMatrix ();
		glTranslatef (x + 0.5, y + 0.5, z);
		fCursorAngle += 5;
		if (fCursorAngle > 360)
			fCursorAngle = 0;
		glRotatef (fCursorAngle, 0, 0, 1);
		glCallList (DispListID.iCursorID);
	glPopMatrix ();
}

void CAffichagePlateau::DrawPawn (pion_t Pion, float x, float y, float z)
{
	glPushMatrix ();
		glTranslatef (x + 0.5,y + 0.5,z + PAWN_HEIGHT);
		if (Pion == PION_BLANC)
			glCallList (DispListID.iPawnID);
		else if (Pion == PION_NOIR)
		{
			glRotatef (-180,1,0,0);
			glCallList (DispListID.iPawnID);
		}
	glPopMatrix ();
}

void CAffichagePlateau::DrawTray ()
{
	glCallList (DispListID.iTrayID);

	glPushMatrix ();
		color3_t fColorChiffre = {232./255., 192./255., 152./255.};
		// Groove - 12/01/2003 - Row
		for (short i = 1; i <= GRID_SIZE; i++)
			DrawFigure (i, -1, i-1, 0.3, fColorChiffre);

		// Groove - 12/01/2003 - Column
		for (short j = 1; j <= GRID_SIZE; j++)
			DrawFigure (j, j-1, -1, 0.3, fColorChiffre);
	glPopMatrix ();
}

void CAffichagePlateau::LoadPlateau ()
{
	CImageTGA Image = CImageTGA (STRCAT (REP_IMAGE, "plateau.tga"), COLOR_FORMAT_RGB24);

	glBindTexture (GL_TEXTURE_2D, iPlateauId);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, Image.GetWidth (), Image.GetHeight (), 0, GL_RGB, GL_UNSIGNED_BYTE, Image.GetData ());

	iSurfaceId = glGenLists (1);
	glNewList (iSurfaceId, GL_COMPILE);
		glBegin (GL_QUADS);
			glVertex3f (0.00, 0.00, 0.00);
//			glNormal3f (0.00, 0.00, 0.00);
			glTexCoord2f (0.00, 1.00);

			glVertex3f (GRID_SIZE, 0.00, 0.00);
//			glNormal3f (GRID_SIZE, 0.00, 0.00);
			glTexCoord2f (1.00, 1.00);

			glVertex3f (GRID_SIZE, GRID_SIZE, 0.00);
//			glNormal3f (GRID_SIZE, GRID_SIZE, 0.00);
			glTexCoord2f (1.00, 0.00);

			glVertex3f (0.00, GRID_SIZE, 0.00);
//			glNormal3f (0.00, GRID_SIZE, 0.00);
			glTexCoord2f (0.00, 0.00);
		glEnd ();
	glEndList (); 
}

////////////////////////////////////////////////////////////////////////
// Groove - 13/01/2003 - Function witch load the displays lists (LDL) //
////////////////////////////////////////////////////////////////////////

// Groove - 13/01/2003 - Load the select cursor display list
void CAffichagePlateau::LDL_Cursor ()
{
	DispListID.iCursorID = glGenLists (1);
	glNewList (DispListID.iCursorID, GL_COMPILE);
		glPushMatrix ();

			glBegin (GL_TRIANGLE_FAN);
				glColor3fv (fColorWhite);
				glVertex3f (0.00,  0.00, 0.50);
				glTexCoord2f (1.0, 1.0);

				glColor3fv(  fColorRed );
				glVertex3f(  1.00 * PAWN_SIZE,  0.00,  0.00 );
				glNormal3f(  1.00 * PAWN_SIZE,  0.00,  0.00 );

				glColor3fv(  fColorOrange );
				glVertex3f(  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE,  0.00 );
				glNormal3f(  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE,  0.00 );
				
				glColor3fv(  fColorYellow );
				glVertex3f(  0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.00 );
				glNormal3f(  0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.00 );

				glColor3fv(  fColorYellowGreen );
				glVertex3f(  0.00,  1.00 * PAWN_SIZE,  0.00 );
				glNormal3f(  0.00,  1.00 * PAWN_SIZE,  0.00 );

				glColor3fv(  fColorGreen );
				glVertex3f( -0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.00 );
				glNormal3f( -0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.00 );

				glColor3fv(  fColorGreenSkyBlue );
				glVertex3f( -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE,  0.00 );
				glNormal3f( -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE,  0.00 );

				glColor3fv(  fColorSkyBlue );
				glVertex3f( -1.00 * PAWN_SIZE,  0.00,  0.00 );
				glNormal3f( -1.00 * PAWN_SIZE,  0.00,  0.00 );

				glColor3fv(  fColorSkyBlueBlue );
				glVertex3f( -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE,  0.00 );
				glNormal3f( -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE,  0.00 );

				glColor3fv(  fColorBlue );
				glVertex3f( -0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.00 );
				glNormal3f( -0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.00 );

				glColor3fv(  fColorBluePurple );
				glVertex3f(  0.00, -1.00 * PAWN_SIZE,  0.00 );
				glNormal3f(  0.00, -1.00 * PAWN_SIZE,  0.00 );

				glColor3fv(  fColorPurple );
				glVertex3f(  0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.00 );
				glNormal3f(  0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.00 );

				glColor3fv(  fColorPurpleRed );
				glVertex3f(  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE,  0.00 );
				glNormal3f(  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE,  0.00 );

				glColor3fv(  fColorRed );
				glVertex3f(  1.00 * PAWN_SIZE,  0.00,  0.00 );
				glNormal3f(  1.00 * PAWN_SIZE,  0.00,  0.00 );
				glTexCoord2f (0.00, 0.00);
			glEnd ();
		glPopMatrix ();
	glEndList ();
}

// Groove - 13/01/2003 - Load the pawn display list
void CAffichagePlateau::LDL_Pawn ()
{
	DispListID.iPawnID = glGenLists (1);
	glNewList (DispListID.iPawnID, GL_COMPILE);
		GLfloat fColorBlack1[] = {0.3,0.3,0.3};
		GLfloat fColorBlack2[] = {0.1,0.1,0.1};
		GLfloat fColorBlack3[] = {0.0,0.0,0.0};
		GLfloat fColorWhite1[] = {1.0,1.0,1.0};
		GLfloat fColorWhite2[] = {0.8,0.8,0.8};
		GLfloat fColorWhite3[] = {0.7,0.7,0.7};
		
		glBegin (GL_TRIANGLE_FAN);
			glColor3fv (fColorWhite2);
			glVertex3f(  0.00,  0.00, 0.1);
			glNormal3f(  0.00,  0.00, 0.1);

			glColor3fv (fColorWhite1);
			glVertex3f(  1.00 * PAWN_SIZE,  0.00, PAWN_HEIGHT);
			glNormal3f(  1.00 * PAWN_SIZE,  0.00, PAWN_HEIGHT);

			glVertex3f(  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE, PAWN_HEIGHT);
			glNormal3f(  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE, PAWN_HEIGHT);
			
			glVertex3f(  0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, PAWN_HEIGHT);
			glNormal3f(  0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, PAWN_HEIGHT);

			glVertex3f(  0.00,  1.00 * PAWN_SIZE, PAWN_HEIGHT);
			glNormal3f(  0.00,  1.00 * PAWN_SIZE, PAWN_HEIGHT);

			glVertex3f( -0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, PAWN_HEIGHT);
			glNormal3f( -0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, PAWN_HEIGHT);

			glVertex3f( -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE, PAWN_HEIGHT);
			glNormal3f( -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE, PAWN_HEIGHT);

			glVertex3f( -1.00 * PAWN_SIZE,  0.00, PAWN_HEIGHT);
			glNormal3f( -1.00 * PAWN_SIZE,  0.00, PAWN_HEIGHT);

			glVertex3f( -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE, PAWN_HEIGHT);
			glNormal3f( -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE, PAWN_HEIGHT);

			glVertex3f( -0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, PAWN_HEIGHT);
			glNormal3f( -0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, PAWN_HEIGHT);

			glVertex3f(  0.00, -1.00 * PAWN_SIZE, PAWN_HEIGHT);
			glNormal3f(  0.00, -1.00 * PAWN_SIZE, PAWN_HEIGHT);

			glVertex3f(  0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, PAWN_HEIGHT);
			glNormal3f(  0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, PAWN_HEIGHT);

			glVertex3f(  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE, PAWN_HEIGHT);
			glNormal3f(  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE, PAWN_HEIGHT);

			glVertex3f(  1.00 * PAWN_SIZE,  0.00, PAWN_HEIGHT);
			glNormal3f(  1.00 * PAWN_SIZE,  0.00, PAWN_HEIGHT);
		glEnd ();
		// Support
		glBegin (GL_QUAD_STRIP);
			glColor3fv (fColorWhite1);
			glVertex3f(  1.00 * PAWN_SIZE,  0.00, PAWN_HEIGHT);
			glColor3fv (fColorWhite3);
			glVertex3f(  1.00 * PAWN_SIZE,  0.00, 0);

			glColor3fv (fColorWhite1);
			glVertex3f(  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE, PAWN_HEIGHT);
			glColor3fv (fColorWhite3);
			glVertex3f(  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE, 0);

			glColor3fv (fColorWhite1);
			glVertex3f(  0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, PAWN_HEIGHT);
			glColor3fv (fColorWhite3);
			glVertex3f(  0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, 0);

			glColor3fv (fColorWhite1);
			glVertex3f(  0.00,  1.00 * PAWN_SIZE, PAWN_HEIGHT);
			glColor3fv (fColorWhite3);
			glVertex3f(  0.00,  1.00 * PAWN_SIZE, 0);

			glColor3fv (fColorWhite1);
			glVertex3f( -0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, PAWN_HEIGHT);
			glColor3fv (fColorWhite3);
			glVertex3f( -0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, 0);

			glColor3fv (fColorWhite1);
			glVertex3f( -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE, PAWN_HEIGHT);
			glColor3fv (fColorWhite3);
			glVertex3f( -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE, 0);

			glColor3fv (fColorWhite1);
			glVertex3f( -1.00 * PAWN_SIZE,  0.00, PAWN_HEIGHT);
			glColor3fv (fColorWhite3);
			glVertex3f( -1.00 * PAWN_SIZE,  0.00, 0);

			glColor3fv (fColorWhite1);
			glVertex3f( -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE, PAWN_HEIGHT);
			glColor3fv (fColorWhite3);
			glVertex3f( -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE, 0);

			glColor3fv (fColorWhite1);
			glVertex3f( -0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, PAWN_HEIGHT);
			glColor3fv (fColorWhite3);
			glVertex3f( -0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, 0);

			glColor3fv (fColorWhite1);
			glVertex3f(  0.00, -1.00 * PAWN_SIZE, PAWN_HEIGHT);
			glColor3fv (fColorWhite3);
			glVertex3f(  0.00, -1.00 * PAWN_SIZE, 0);

			glColor3fv (fColorWhite1);
			glVertex3f(  0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, PAWN_HEIGHT);
			glColor3fv (fColorWhite3);
			glVertex3f(  0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, 0);

			glColor3fv (fColorWhite1);
			glVertex3f(  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE, PAWN_HEIGHT);
			glColor3fv (fColorWhite3);
			glVertex3f(  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE, 0);

			glColor3fv (fColorWhite1);
			glVertex3f(  1.00 * PAWN_SIZE,  0.00, PAWN_HEIGHT);
			glColor3fv (fColorWhite3);
			glVertex3f(  1.00 * PAWN_SIZE,  0.00, 0);
		glEnd ();
		// Groove - 13/01/2003 - Black disk of the pawn
		glBegin (GL_TRIANGLE_FAN);
			glColor3fv (fColorBlack2);
			glVertex3f(  0.00,  0.00, - 0.1);
			glNormal3f(  0.00,  0.00, - 0.1);

			glColor3fv (fColorBlack1);
			glVertex3f (1.00 * PAWN_SIZE,  0.00, -PAWN_HEIGHT);
			glNormal3f (1.00 * PAWN_SIZE,  0.00, -PAWN_HEIGHT);

			glVertex3f ((GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE, -PAWN_HEIGHT);
			glNormal3f ((GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE, -PAWN_HEIGHT);
			
			glVertex3f (0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -PAWN_HEIGHT);
			glNormal3f (0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -PAWN_HEIGHT);

			glVertex3f (0.00, -1.00 * PAWN_SIZE, -PAWN_HEIGHT);
			glNormal3f (0.00, -1.00 * PAWN_SIZE, -PAWN_HEIGHT);

			glVertex3f (-0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -PAWN_HEIGHT);
			glNormal3f (-0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -PAWN_HEIGHT);

			glVertex3f (-(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE, -PAWN_HEIGHT);
			glNormal3f (-(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE, -PAWN_HEIGHT);

			glVertex3f (-1.00 * PAWN_SIZE,  0.00, -PAWN_HEIGHT);
			glNormal3f (-1.00 * PAWN_SIZE,  0.00, -PAWN_HEIGHT);

			glVertex3f (-(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE, -PAWN_HEIGHT);
			glNormal3f (-(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE, -PAWN_HEIGHT);

			glVertex3f (-0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -PAWN_HEIGHT);
			glNormal3f (-0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -PAWN_HEIGHT);

			glVertex3f (0.00,  1.00 * PAWN_SIZE, -PAWN_HEIGHT);
			glNormal3f (0.00,  1.00 * PAWN_SIZE, -PAWN_HEIGHT);

			glVertex3f (0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -PAWN_HEIGHT);
			glNormal3f (0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -PAWN_HEIGHT);
			
			glVertex3f ((GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE, -PAWN_HEIGHT);
			glNormal3f ((GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE, -PAWN_HEIGHT);

			glVertex3f (1.00 * PAWN_SIZE,  0.00, -PAWN_HEIGHT);
			glNormal3f (1.00 * PAWN_SIZE,  0.00, -PAWN_HEIGHT);
		glEnd ();
		// Groove - 13/01/2003 - Black cylinder of the pawn
		glBegin (GL_QUAD_STRIP);
			glColor3fv (fColorBlack3);
			glVertex3f(  1.00 * PAWN_SIZE,  0.00, 0);
			glColor3fv (fColorBlack1);
			glVertex3f(  1.00 * PAWN_SIZE,  0.00, -PAWN_HEIGHT);

			glColor3fv (fColorBlack3);
			glVertex3f(  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE, 0);
			glColor3fv (fColorBlack1);
			glVertex3f(  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE, -PAWN_HEIGHT);

			glColor3fv (fColorBlack3);
			glVertex3f(  0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, 0);
			glColor3fv (fColorBlack1);
			glVertex3f(  0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -PAWN_HEIGHT);

			glColor3fv (fColorBlack3);
			glVertex3f(  0.00,  1.00 * PAWN_SIZE, 0);
			glColor3fv (fColorBlack1);
			glVertex3f(  0.00,  1.00 * PAWN_SIZE, -PAWN_HEIGHT);

			glColor3fv (fColorBlack3);
			glVertex3f( -0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, 0);
			glColor3fv (fColorBlack1);
			glVertex3f( -0.50 * PAWN_SIZE,  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -PAWN_HEIGHT);

			glColor3fv (fColorBlack3);
			glVertex3f( -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE, 0);
			glColor3fv (fColorBlack1);
			glVertex3f( -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE,  0.50 * PAWN_SIZE, -PAWN_HEIGHT);

			glColor3fv (fColorBlack3);
			glVertex3f( -1.00 * PAWN_SIZE,  0.00, 0);
			glColor3fv (fColorBlack1);
			glVertex3f( -1.00 * PAWN_SIZE,  0.00, -PAWN_HEIGHT);

			glColor3fv (fColorBlack3);
			glVertex3f( -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE, 0);
			glColor3fv (fColorBlack1);
			glVertex3f( -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE, -PAWN_HEIGHT);

			glColor3fv (fColorBlack3);
			glVertex3f( -0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, 0);
			glColor3fv (fColorBlack1);
			glVertex3f( -0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -PAWN_HEIGHT);

			glColor3fv (fColorBlack3);
			glVertex3f(  0.00, -1.00 * PAWN_SIZE, 0);
			glColor3fv (fColorBlack1);
			glVertex3f(  0.00, -1.00 * PAWN_SIZE, -PAWN_HEIGHT);

			glColor3fv (fColorBlack3);
			glVertex3f(  0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, 0);
			glColor3fv (fColorBlack1);
			glVertex3f(  0.50 * PAWN_SIZE, -(GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -PAWN_HEIGHT);

			glColor3fv (fColorBlack3);
			glVertex3f(  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE, 0);
			glColor3fv (fColorBlack1);
			glVertex3f(  (GLfloat)RACINE_DE_3_SUR_2 * PAWN_SIZE, -0.50 * PAWN_SIZE, -PAWN_HEIGHT);

			glColor3fv (fColorBlack3);
			glVertex3f(  1.00 * PAWN_SIZE,  0.00, 0);
			glColor3fv (fColorBlack1);
			glVertex3f(  1.00 * PAWN_SIZE,  0.00, -PAWN_HEIGHT);
		glEnd ();

	glEndList();
}

// Groove - 13/01/2003 - Load the tray display list
void CAffichagePlateau::LDL_Tray ()
{
	DispListID.iTrayID = glGenLists (1);
	glNewList (DispListID.iTrayID, GL_COMPILE);
		glPushMatrix ();
			glTranslatef (0,0,0.25);
			//color3_t fColor1 = {232./255., 192./255., 152./255.};
			//color3_t fColor1 = {155./255., 95./255., 37./255.};
			color3_t fColor2 = {104./255., 64./255., 24./255.};
			color3_t fColor3 = {52./255., 32./255., 12./255.};
			// Over
			glBegin (GL_QUAD_STRIP);
				glColor3fv (fColor3);
				glVertex3f (-1, -1, 0);
				glColor3fv (fColor2);
				glVertex3f ( 0,  0, 0);
				glColor3fv (fColor3);
				glVertex3f (-1, GRID_SIZE + 1, 0);
				glColor3fv (fColor2);
				glVertex3f ( 0, GRID_SIZE, 0);
				glColor3fv (fColor3);
				glVertex3f (GRID_SIZE + 1, GRID_SIZE + 1, 0);
				glColor3fv (fColor2);
				glVertex3f (GRID_SIZE, GRID_SIZE, 0);
				glColor3fv (fColor3);
				glVertex3f (GRID_SIZE + 1, -1, 0);
				glColor3fv (fColor2);
				glVertex3f (GRID_SIZE,  0, 0);
				glColor3fv (fColor3);
				glVertex3f (-1, -1, 0);
				glColor3fv (fColor2);
				glVertex3f ( 0,  0, 0);
			glEnd ();
			// Internal
			glBegin (GL_QUAD_STRIP);
				glColor3fv (fColor2);
				glVertex3f ( 0,  0, 0);
				glColor3fv (fColor3);
				glVertex3f ( 0,  0,-0.25);
				glColor3fv (fColor2);
				glVertex3f ( 0, GRID_SIZE, 0);
				glColor3fv (fColor3);
				glVertex3f ( 0, GRID_SIZE,-0.25);
				glColor3fv (fColor2);
				glVertex3f (GRID_SIZE, GRID_SIZE, 0);
				glColor3fv (fColor3);
				glVertex3f (GRID_SIZE, GRID_SIZE,-0.25);
				glColor3fv (fColor2);
				glVertex3f (GRID_SIZE,  0, 0);
				glColor3fv (fColor3);
				glVertex3f (GRID_SIZE,  0,-0.25);
				glColor3fv (fColor2);
				glVertex3f ( 0,  0, 0);
				glColor3fv (fColor3);
				glVertex3f ( 0,  0,-0.25);
			glEnd ();
			// Outside
			glBegin (GL_QUAD_STRIP);
				glColor3fv (fColor2);
				glVertex3f (-1, -1,-0.25);
				glColor3fv (fColor3);
				glVertex3f (-1, -1, 0);
				glColor3fv (fColor2);
				glVertex3f (-1, GRID_SIZE + 1,-0.25);
				glColor3fv (fColor3);
				glVertex3f (-1, GRID_SIZE + 1, 0);
				glColor3fv (fColor2);
				glVertex3f (GRID_SIZE + 1, GRID_SIZE + 1,-0.25);
				glColor3fv (fColor3);
				glVertex3f (GRID_SIZE + 1, GRID_SIZE + 1, 0);
				glColor3fv (fColor2);
				glVertex3f (GRID_SIZE + 1, -1,-0.25);
				glColor3fv (fColor3);
				glVertex3f (GRID_SIZE + 1, -1, 0);
				glColor3fv (fColor2);
				glVertex3f (-1, -1,-0.25);
				glColor3fv (fColor3);
				glVertex3f (-1, -1, 0);
			glEnd ();
		glPopMatrix ();
	glEndList ();
}

// Groove - 13/01/2003 - Load the figures display list
void CAffichagePlateau::LDL_Figures ()
{
	DispListID.iFigureID[0] = glGenLists (1);
	glNewList (DispListID.iFigureID[0], GL_COMPILE);
		glBegin (GL_LINE_LOOP);
			glVertex3f (0.7, 0.2, 0);
			glVertex3f (0.7, 0.8, 0);
			glVertex3f (0.3, 0.8, 0);
			glVertex3f (0.3, 0.2, 0);
		glEnd ();
	glEndList();

	DispListID.iFigureID[1] = glGenLists (1);
	glNewList (DispListID.iFigureID[1], GL_COMPILE);
		glBegin (GL_LINES);
			glVertex3f (0.7, 0.2, 0);
			glVertex3f (0.7, 0.8, 0);
		glEnd ();
	glEndList();

	DispListID.iFigureID[2] = glGenLists (1);
	glNewList (DispListID.iFigureID[2], GL_COMPILE);
		glBegin (GL_LINE_STRIP);
			glVertex3f (0.7, 0.2, 0);
			glVertex3f (0.3, 0.2, 0);
			glVertex3f (0.3, 0.5, 0);
			glVertex3f (0.7, 0.5, 0);
			glVertex3f (0.7, 0.8, 0);
			glVertex3f (0.3, 0.8, 0);
		glEnd ();
	glEndList();

	DispListID.iFigureID[3] = glGenLists (1);
	glNewList (DispListID.iFigureID[3], GL_COMPILE);
		glBegin (GL_LINES);
			glVertex3f (0.3, 0.2, 0);
			glVertex3f (0.7, 0.2, 0);
			glVertex3f (0.7, 0.2, 0);
			glVertex3f (0.7, 0.8, 0);
			glVertex3f (0.7, 0.8, 0);
			glVertex3f (0.3, 0.8, 0);
			glVertex3f (0.3, 0.5, 0);
			glVertex3f (0.7, 0.5, 0);
		glEnd ();
	glEndList();

	DispListID.iFigureID[4] = glGenLists (1);
	glNewList (DispListID.iFigureID[4], GL_COMPILE);
		glBegin (GL_LINE_STRIP);
			glVertex3f (0.3, 0.8, 0);
			glVertex3f (0.3, 0.5, 0);
			glVertex3f (0.7, 0.5, 0);
			glVertex3f (0.7, 0.8, 0);
			glVertex3f (0.7, 0.2, 0);
		glEnd ();
	glEndList();

	DispListID.iFigureID[5] = glGenLists (1);
	glNewList (DispListID.iFigureID[5], GL_COMPILE);
		glBegin (GL_LINE_STRIP);
			glVertex3f (0.3, 0.2, 0);
			glVertex3f (0.7, 0.2, 0);
			glVertex3f (0.7, 0.5, 0);
			glVertex3f (0.3, 0.5, 0);
			glVertex3f (0.3, 0.8, 0);
			glVertex3f (0.7, 0.8, 0);
		glEnd ();
	glEndList();

	DispListID.iFigureID[6] = glGenLists (1);
	glNewList (DispListID.iFigureID[6], GL_COMPILE);
		glBegin (GL_LINE_STRIP);
			glVertex3f (0.7, 0.8, 0);
			glVertex3f (0.3, 0.8, 0);
			glVertex3f (0.3, 0.2, 0);
			glVertex3f (0.7, 0.2, 0);
			glVertex3f (0.7, 0.5, 0);
			glVertex3f (0.3, 0.5, 0);
		glEnd ();
	glEndList();

	DispListID.iFigureID[7] = glGenLists (1);
	glNewList (DispListID.iFigureID[7], GL_COMPILE);
		glBegin (GL_LINE_STRIP);
			glVertex3f (0.3, 0.8, 0);
			glVertex3f (0.7, 0.8, 0);
			glVertex3f (0.7, 0.2, 0);
		glEnd ();
	glEndList();

	DispListID.iFigureID[8] = glGenLists (1);
	glNewList (DispListID.iFigureID[8], GL_COMPILE);
		glBegin (GL_LINE_STRIP);
			glVertex3f (0.3, 0.5, 0);
			glVertex3f (0.7, 0.5, 0);
			glVertex3f (0.7, 0.8, 0);
			glVertex3f (0.3, 0.8, 0);
			glVertex3f (0.3, 0.2, 0);
			glVertex3f (0.7, 0.2, 0);
			glVertex3f (0.7, 0.5, 0);
		glEnd ();
	glEndList();

	DispListID.iFigureID[9] = glGenLists (1);
	glNewList (DispListID.iFigureID[9], GL_COMPILE);
		glBegin (GL_LINE_STRIP);
			glVertex3f (0.3, 0.2, 0);
			glVertex3f (0.7, 0.2, 0);
			glVertex3f (0.7, 0.8, 0);
			glVertex3f (0.3, 0.8, 0);
			glVertex3f (0.3, 0.5, 0);
			glVertex3f (0.7, 0.5, 0);
		glEnd ();
	glEndList();
}
