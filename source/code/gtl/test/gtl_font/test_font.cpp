#include "../../include/gtl_image_tga.h"
#include "../../include/gtl_font.h"
#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>

using namespace gtl;

CFont Font;
short iFpsBuffer = 0, iFps = 0;
clock_t FpsTimeStart = 0;

void InitGL ()
{
	Font.Load ("../../data/font1.tga");
	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth (1.0f);
}

void CompteFPS ()
{
	iFpsBuffer++;
	if ((clock() - FpsTimeStart) >= 1000)
	{
		iFps = iFpsBuffer;
		FpsTimeStart = clock ();
		iFpsBuffer = 0;
	}
	
	Font.Print (576, 0, "%d", iFps);
}


void Display ()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport (0,0,640,480);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0.0f,640,480,0.0f,-1.0f,1.0f);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();

	Font.SetSize (32);
	Font.SetRadio (0.5); // Radio largeur sur hauteur
	glColor3f (0.5f,0.25f,0.0f);
	Font.Print (46, 14, "G.T.L. Alpha 3.00");
	Font.Print (48, 16, "G.T.L. Alpha 3.00");
	glColor3f (1.0f,0.75f,0.5f);
	Font.Print (50, 18, "G.T.L. Alpha 3.00");

	Font.SetSize (24);
	glColor3f (0.0f,1.0f,0.0f);
	Font.Print (350, 40, "Par Groove");

	Font.SetSize (12);
	Font.SetRadio (0.75);
	glColor3f (0.75f,0.75f,1.0f);
	Font.Print (64, 96, "Test de CFont :");
	Font.SetRadio (0.5);
	Font.Print (64, 128, "- Chargement de la font.");
	Font.Print (64, 144, "- Changement de couleur.");
	Font.Print (64, 160, "- Changement de la taille des");
	Font.Print (64, 176, "caracteres.");
	Font.Print (64, 192, "- Ration de la largeur sur la hauteur.");

	Font.SetSize (16);
	Font.SetRadio (0.5);
	glColor3f (1.0f,1.0f,1.0f);
	CompteFPS ();

	glutSwapBuffers ();
}

void CreerFenetre (bool bFullscreen)
{
	if (bFullscreen)
	{
		char szResolutionBuffer[32];
		sprintf (szResolutionBuffer,"%dx%d:%d@%d", 640, 480, 32, 75);
		glutGameModeString (szResolutionBuffer);
		glutEnterGameMode ();
	}
	else
	{
		glutInitWindowPosition (0, 0);
		glutInitWindowSize (640, 480);
		glutCreateWindow ("coucou");
	}
}

void Clavier (unsigned char touche, int x, int y)
{
	switch (touche)
    {
	default:
		break;
	case 27 :
		exit (0);
		break;
	}
}

int main ()
{
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	CreerFenetre (false);

	InitGL ();	

	glutKeyboardFunc (Clavier);
	glutDisplayFunc (Display);
	glutIdleFunc (Display);
	glutMainLoop ();

	return 0;
}
