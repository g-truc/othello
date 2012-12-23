/***********************************************\
*	GTL (G-Truc Library)						*
*	Copyright (c) 2003, G-Truc Creation.		*
*************************************************
*	G-Truc Creation, www.g-truc.fr.st			*
*	par Groove, groove@g-truc.fr.st				*
*************************************************
*	test_image_raw.cpp, 01/03/2003				*
\***********************************************/

#include "../../include/gtl_image_raw.h"
#include "../../include/gtl_image_bmp.h"
#include "../../include/gtl_image_tga.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

using namespace gtl;

GLuint TextureID1;
GLuint TextureID2;
GLuint TextureID3;
GLuint TextureID4;

void init ()
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);

	CImageTGA ImageTGA24 ("image24.tga", COLOR_FORMAT_RGB24);
	glGenTextures (1, &TextureID1);
	glBindTexture (GL_TEXTURE_2D, TextureID1);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, ImageTGA24.GetWidth (), ImageTGA24.GetHeight (), 0, GL_RGB, GL_UNSIGNED_BYTE, ImageTGA24.GetData ());

	CImageTGA ImageTGA08 ("image8.tga", COLOR_FORMAT_RGB24);
	glGenTextures (1, &TextureID2);
	glBindTexture (GL_TEXTURE_2D, TextureID2);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, ImageTGA08.GetWidth (), ImageTGA08.GetHeight (), 0, GL_RGB, GL_UNSIGNED_BYTE, ImageTGA08.GetData ());

	CImageBMP ImageBMP24 ("image24.bmp", COLOR_FORMAT_RGB24);
	glGenTextures (1, &TextureID3);
	glBindTexture (GL_TEXTURE_2D, TextureID3);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, ImageBMP24.GetWidth (), ImageBMP24.GetHeight (), 0, GL_RGB, GL_UNSIGNED_BYTE, ImageBMP24.GetData ());

	CImageRAW ImageRAW24 ("image24.raw", 64, 64, COLOR_FORMAT_RGB24);
	glGenTextures (1, &TextureID4);
	glBindTexture (GL_TEXTURE_2D, TextureID4);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, ImageRAW24.GetWidth (), ImageRAW24.GetHeight (), 0, GL_RGB, GL_UNSIGNED_BYTE, ImageRAW24.GetData ());
}

void display ()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable (GL_TEXTURE_2D);

	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	glPushMatrix ();
		glTranslated (-1,1,0);
		glBindTexture (GL_TEXTURE_2D, TextureID1);
		glBegin (GL_QUADS);
			glTexCoord2f (0.0, 0.0); glVertex3f (-1.0, -0.5, 0.0);
			glTexCoord2f (0.0, 1.0); glVertex3f (-1.0,  0.5, 0.0);
			glTexCoord2f (1.0, 1.0); glVertex3f ( 0.0,  0.5, 0.0);
			glTexCoord2f (1.0, 0.0); glVertex3f ( 0.0, -0.5, 0.0);
		glEnd ();
	glPopMatrix ();

	glPushMatrix ();
		glTranslated (1,1,0);
		glBindTexture (GL_TEXTURE_2D, TextureID2);
		glBegin (GL_QUADS);
			glTexCoord2f (0.0, 0.0); glVertex3f (-1.0, -0.5, 0.0);
			glTexCoord2f (0.0, 1.0); glVertex3f (-1.0,  0.5, 0.0);
			glTexCoord2f (1.0, 1.0); glVertex3f ( 0.0,  0.5, 0.0);
			glTexCoord2f (1.0, 0.0); glVertex3f ( 0.0, -0.5, 0.0);
		glEnd ();
	glPopMatrix ();

	glPushMatrix ();
		glTranslated (-1,-1,0);
		glBindTexture (GL_TEXTURE_2D, TextureID3);
		glBegin (GL_QUADS);
			glTexCoord2f (0.0, 0.0); glVertex3f (-1.0, -0.5, 0.0);
			glTexCoord2f (0.0, 1.0); glVertex3f (-1.0,  0.5, 0.0);
			glTexCoord2f (1.0, 1.0); glVertex3f ( 0.0,  0.5, 0.0);
			glTexCoord2f (1.0, 0.0); glVertex3f ( 0.0, -0.5, 0.0);
		glEnd ();
	glPopMatrix ();

	glPushMatrix ();
		glTranslated (1,-1,0);
		glBindTexture (GL_TEXTURE_2D, TextureID4);
		glBegin (GL_QUADS);
			glTexCoord2f (0.0, 0.0); glVertex3f (-1.0, -0.5, 0.0);
			glTexCoord2f (0.0, 1.0); glVertex3f (-1.0,  0.5, 0.0);
			glTexCoord2f (1.0, 1.0); glVertex3f ( 0.0,  0.5, 0.0);
			glTexCoord2f (1.0, 0.0); glVertex3f ( 0.0, -0.5, 0.0);
		glEnd ();
	glPopMatrix ();

	glFlush ();

	glDisable (GL_TEXTURE_2D);
}

void reshape (int w, int h)
{
	glViewport (0, 0, w, h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (60.0, (GLfloat)w/h, 1.0, 30.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glTranslatef (0.0,0.0,-3.6);
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit (0);
		break;
	default:
		break;
	}
}

int main (int argc, char ** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (640,480);
	glutInitWindowPosition (0, 0);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
	glutKeyboardFunc (keyboard);
	glutMainLoop ();
	return 0;
}
