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
*	interface.cpp, 20/02/2003							*
*	par Groove, groove@g-truc.fr.st						*
\*******************************************************/

#include "../header/interface.h"
#include <GL/glut.h>
#include <iostream>

CInterface *g_Interface = NULL;

void CB_Afficher ();
void CB_Idle ();
void CB_Clavier (unsigned char key, int x, int y);
void CB_ClavierSP (int key,int x,int y);

CInterface::CInterface (int argc, char **argv)
{
	#ifdef _DEBUG
		std::cout << "Constructeur de CInterface, debut" << std::endl;
	#endif //_DEBUG

	g_Interface = this;
	FpsTimeStart = 0;
	iFps = 0;
	
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	#ifdef _DEBUG
		std::cout << "Creation de la fenetre, debut" << std::endl;
	#endif //_DEBUG

	CreerFenetre (argc, argv);

	#ifdef _DEBUG
		std::cout << "Creation de la fenetre, fin" << std::endl;
		std::cout << "Initialisation de l'affichage plateau, debut" << std::endl;
	#endif //_DEBUG

	// Groove - 13/01/2003 - Call InitGL () before other call function in DisplayGL class.
//	AffichagePlateau.Initialiser ();

	#ifdef _DEBUG
		std::cout << "Initialisation de l'affichage plateau, fin" << std::endl;
		std::cout << "Initialisation du menu, debut" << std::endl;
	#endif //_DEBUG

	Menu.Initialiser (this, Resolution);

	#ifdef _DEBUG
		std::cout << "Initialisation du menu, fin" << std::endl;
	#endif //_DEBUG

	glutDisplayFunc (CB_Afficher);
	glutIdleFunc (CB_Idle);
	glutKeyboardFunc (CB_Clavier);
	glutSpecialFunc (CB_ClavierSP);
	glutSetCursor (GLUT_CURSOR_NONE);

	#ifdef _DEBUG
		std::cout << "Constructeur de CInterface, fin" << std::endl;
	#endif //_DEBUG

	glutMainLoop ();
}

void CInterface::Idle ()
{
	Menu.Executer ();
	glutPostRedisplay();
}

void CInterface::AfficherEn2D () const
{
 	glMatrixMode (GL_PROJECTION);
   	glLoadIdentity ();
 	gluOrtho2D (0, (GLfloat)Resolution.iLargeur, 0, (GLfloat)Resolution.iHauteur);
   	glMatrixMode (GL_MODELVIEW);
   	glLoadIdentity ();
}

void CInterface::AfficherEn3D () const
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (45.0, (GLfloat)Resolution.iLargeur/(GLfloat)Resolution.iHauteur, 0.1 ,200.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

void CInterface::CompteFPS ()
{
	iFpsBuffer++;
	if ((time (NULL) - FpsTimeStart) >= 1)
	{
		#ifdef _DEBUG
			std::cout << iFpsBuffer << " fps" << std::endl;
		#endif //_DEBUG
		iFps = iFpsBuffer;
		FpsTimeStart = time (NULL);
		iFpsBuffer = 0;
	}
	
	Menu.ShowFPS (iFps);
}

void CInterface::Afficher ()
{
	glClearColor (0,0,0,0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	AfficherEn2D ();
	CompteFPS ();

	switch (Menu.DemanderChoixAction ())
	{
	default:
		break;
	case ACTION_COMMENCER_PARTIE:
		Menu.AfficherCommencer ();
		break;
	case ACTION_FIN_PARTIE:
	case ACTION_CONTINUER_PARTIE:
		Menu.AfficherHUD ();
		AfficherEn3D ();
		AffichagePlateau.AfficherPlateau ();
		break;
	case ACTION_MENU:
		Menu.AfficherMenu ();
		break;
	case ACTION_VOIR_MEILLEUR_SCORE:
		Menu.AfficherScore ();
		break;
	}

	glutSwapBuffers ();
}

void CInterface::Clavier (unsigned char key)
{
	#ifdef _DEBUG
		std::cout << "CInterface::Clavier ()" << std::endl;
	#endif //_DEBUG

	if (key == 27)
		Menu.SetActionChoix (ACTION_MENU);

	switch (Menu.DemanderChoixAction ())
	{
	default:
	case ACTION_NULL:
		break;
	case ACTION_COMMENCER_PARTIE:
		switch (key)
		{
		default:
			if (Menu.GetMenuCommencerPosition () == 1)
				Menu.AjouterLettreAuNom (JOUEUR_1, key);
			if (Menu.GetMenuCommencerPosition () == 3)
				Menu.AjouterLettreAuNom (JOUEUR_2, key);
			break;
		case '8':
			Menu.SetMenuCommencerPosition (MENU_DECREMENTE);
			break;
		case '2':
			Menu.SetMenuCommencerPosition (MENU_INCREMENTE);
			break;
		case 13:
			if (Menu.GetMenuCommencerPosition () == 4)
				Menu.CommencerPartie (*this, Menu.GetJoueurInformation (JOUEUR_1), Menu.GetJoueurInformation (JOUEUR_2));
			break;
		}
		break;
	case ACTION_CONTINUER_PARTIE:
		switch (key)
		{
		case '+':
			AffichagePlateau.DeplacerPlateau (MOVE_Z_PLUS);
			break;
		case '-':
			AffichagePlateau.DeplacerPlateau (MOVE_Z_MOINS);
			break;
		case 'x':
			AffichagePlateau.TournerPlateau (ROTATE_X_PLUS);
			break;
		case 'X':
			AffichagePlateau.TournerPlateau (ROTATE_X_MOINS);
			break;
		case 'y':
			AffichagePlateau.TournerPlateau (ROTATE_Y_PLUS);
			break;
		case 'Y':
			AffichagePlateau.TournerPlateau (ROTATE_Y_MOINS);
			break;
		case 'z':
			AffichagePlateau.TournerPlateau (ROTATE_Z_PLUS);
			break;
		case 'Z':
			AffichagePlateau.TournerPlateau (ROTATE_Z_MOINS);
			break;
		case 13: case ' ':
			AffichagePlateau.ValiderCurseur ();
			break;
		case '2': case '4': case '6': case '8':
			AffichagePlateau.DeplacerCurseur (key);
			break;
		}
		break;
	case ACTION_FIN_PARTIE:
		Menu.SetActionChoix (ACTION_MENU);
		break;
	case ACTION_MENU:
		switch (key)
		{
		case 13: case ' ':
			if (Menu.GetMenuPrincipalePosition () == 0) Menu.SetActionChoix (ACTION_CONTINUER_PARTIE);
			if (Menu.GetMenuPrincipalePosition () == 1) {Menu.SetActionChoix (ACTION_COMMENCER_PARTIE); Menu.InitialiserJoueursInformation ();}
			if (Menu.GetMenuPrincipalePosition () == 2) Menu.SetActionChoix (ACTION_VOIR_MEILLEUR_SCORE);
			if (Menu.GetMenuPrincipalePosition () == 3) exit (0);
			break;
		case '8':
			Menu.SetMenuPrincipalePosition (MENU_DECREMENTE);
			break;
		case '2':
			Menu.SetMenuPrincipalePosition (MENU_INCREMENTE);
			break;
		}
		break;
	case ACTION_VOIR_MEILLEUR_SCORE:
		break;
	}	
}

void CInterface::ClavierSP (int key)
{
	#ifdef _DEBUG
		std::cout << "CInterface::ClavierSP ()" << std::endl;
	#endif //_DEBUG
	switch (Menu.DemanderChoixAction ())
	{
	default:
		break;
	case ACTION_COMMENCER_PARTIE:
		switch (key)
		{
		case GLUT_KEY_UP:
			Menu.SetMenuCommencerPosition (MENU_DECREMENTE);
			break;
		case GLUT_KEY_DOWN:
			Menu.SetMenuCommencerPosition (MENU_INCREMENTE);
			break;
		case GLUT_KEY_RIGHT:
			if (Menu.GetMenuCommencerPosition () == 0)
				Menu.ChangerTypeJoueur (JOUEUR_1);
			else if (Menu.GetMenuCommencerPosition () == 1 && Menu.GetJoueurType (JOUEUR_1) == JOUEUR_IA)
				Menu.SetNiveauIA (JOUEUR_1, MENU_INCREMENTE);
			else if (Menu.GetMenuCommencerPosition () == 2)
				Menu.ChangerTypeJoueur (JOUEUR_2);
			else if (Menu.GetMenuCommencerPosition () == 3 && Menu.GetJoueurType (JOUEUR_2) == JOUEUR_IA)
				Menu.SetNiveauIA (JOUEUR_2, MENU_INCREMENTE);
			break;
		case GLUT_KEY_LEFT:
			if (Menu.GetMenuCommencerPosition () == 0)
				Menu.ChangerTypeJoueur (JOUEUR_1);
			else if (Menu.GetMenuCommencerPosition () == 1 && Menu.GetJoueurType (JOUEUR_1) == JOUEUR_IA)
				Menu.SetNiveauIA (JOUEUR_1, MENU_DECREMENTE);
			else if (Menu.GetMenuCommencerPosition () == 2)
				Menu.ChangerTypeJoueur (JOUEUR_2);
			else if (Menu.GetMenuCommencerPosition () == 3 && Menu.GetJoueurType (JOUEUR_2) == JOUEUR_IA)
				Menu.SetNiveauIA (JOUEUR_2, MENU_DECREMENTE);
			break;
		}
		break;
	case ACTION_CONTINUER_PARTIE:
		switch (key)
		{
		case GLUT_KEY_UP: case GLUT_KEY_DOWN: case GLUT_KEY_RIGHT: case GLUT_KEY_LEFT:
			AffichagePlateau.DeplacerCurseur (key);
			break;
		}
	case ACTION_MENU:
		switch (key)
		{
		case GLUT_KEY_UP:
			Menu.SetMenuPrincipalePosition (MENU_DECREMENTE);
			break;
		case GLUT_KEY_DOWN:
			Menu.SetMenuPrincipalePosition (MENU_INCREMENTE);
			break;
		}
	}
}

void CInterface::CreerFenetre (int argc, char **argv)
{
	bool bFullscreen;
	Resolution.iFrequence = RESOLUTION_FREQUENCE;
	Resolution.iCouleur = RESOLUTION_COULEUR;
	
	if (argc == 2)
		if (argv[1][0] == '-' && argv[1][1] == '0')
		{
			bFullscreen = false;
			Resolution.iLargeur = 640;
			Resolution.iHauteur = 480;
		}
		else if (argv[1][0] == '-' && argv[1][1] == '1')
		{
			bFullscreen = true;
			Resolution.iLargeur = 640;
			Resolution.iHauteur = 480;
		}
		else if (argv[1][0] == '-' && argv[1][1] == '2')
		{
			bFullscreen = true;
			Resolution.iLargeur = 800;
			Resolution.iHauteur = 600;
		}
		else if (argv[1][0] == '-' && argv[1][1] == '3')
		{
			bFullscreen = true;
			Resolution.iLargeur = 1024;
			Resolution.iHauteur = 768;
		}
		else if (argv[1][0] == '-' && argv[1][1] == '4')
		{
			bFullscreen = true;
			Resolution.iLargeur = 1280;
			Resolution.iHauteur = 960;
		}
		else if (argv[1][0] == '-' && argv[1][1] == '5')
		{
			bFullscreen = true;
			Resolution.iLargeur = 1600;
			Resolution.iHauteur = 1200;
		}
		else
		{
			bFullscreen = false;
			Resolution.iLargeur = 640;
			Resolution.iHauteur = 480;
		}
	else
	{
		bFullscreen = false;
		Resolution.iLargeur = 640;
		Resolution.iHauteur = 480;
	}

	#if (defined(_WIN32))
	if (bFullscreen)
	{
		char cResolutionBuffer[32];
		sprintf (cResolutionBuffer,"%dx%d:%d@%d", Resolution.iLargeur, Resolution.iHauteur, Resolution.iCouleur, Resolution.iFrequence);
		glutGameModeString (cResolutionBuffer);
		glutEnterGameMode ();
	}
	else
	{
		glutInit (&argc, argv);
		glutInitWindowSize (Resolution.iLargeur, Resolution.iHauteur);
		glutInitWindowPosition (0,0);
		glutCreateWindow (WINDOW_NAME);
	}
	#else
		glutInit (&argc, argv);
		glutInitWindowSize (Resolution.iLargeur, Resolution.iHauteur);
		glutInitWindowPosition (0,0);
		glutCreateWindow (WINDOW_NAME);
	#endif //_WIN32

/*#if (defined(_WIN32) && defined (USE_FULLSCREEN))
	char cResolutionBuffer[32];
	sprintf (cResolutionBuffer,"%dx%d:%d@%d", Resolution.iLargeur, Resolution.iHauteur, Resolution.iCouleur, Resolution.iFrequence);
	glutGameModeString (cResolutionBuffer);
	glutEnterGameMode ();
#else 
	glutInit (&argc, argv);
	glutInitWindowSize (Resolution.iLargeur, Resolution.iHauteur);
	glutInitWindowPosition (0,0);
	glutCreateWindow (WINDOW_NAME);
#endif //USE_FULLSCREEN*/
}

void CB_Afficher ()
{
	#ifdef _DEBUG
		if (g_Interface != NULL)
	#endif //_DEBUG
	g_Interface->Afficher ();
}

void CB_Idle ()
{
	#ifdef _DEBUG
		if (g_Interface != NULL)
	#endif //_DEBUG
	g_Interface->Idle ();
}

void CB_Clavier (unsigned char key, int x, int y)
{
	#ifdef _DEBUG
		if (g_Interface != NULL)
	#endif //_DEBUG
	g_Interface->Clavier (key);
}

void CB_ClavierSP (int key,int x,int y)
{
	#ifdef _DEBUG
		if (g_Interface != NULL)
	#endif //_DEBUG
	g_Interface->ClavierSP (key);
}
