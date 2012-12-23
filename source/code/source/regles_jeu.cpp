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
*	regles_jeu.cpp, 12/03/2003							*
*	par MatRem, matrem@codegba.fr.st					*
\*******************************************************/

#include "../header/regles_jeu.h"

pion_t CReglesJeu::PionInverse (const pion_t Pion) const
{

	switch(Pion)
	{
	case PION_INVALID:return PION_INVALID;
	case PION_NULL:return PION_NULL;
	case PION_BLANC:return PION_NOIR;
	case PION_NOIR:return PION_BLANC;
	default: return PION_INVALID;
	}
}
	
pion_t CReglesJeu::GetPion (const short x, const short y)
{
//MatRem 15/02/2003 On retourne la valeur du pion contenu dans la liste de la grille
	return Grille[x+GRID_SIZE*y];
}

short CReglesJeu::CompterPion (const pion_t Pion)
{
//MatRem 15/02/2003 on cherche le nombre de pion de cette couleur
    short b=0;
	for(short a=0; a<(GRID_SIZE*GRID_SIZE); a++)
	if(Grille[a]==Pion) b++;
	return b;
}


short CReglesJeu::VerifierPose (const short x, const short y, const pion_t Pion)
{
//MatRem 15/02/2003

	int b=0,c=0,dx=x,dy=y;

	if(GetPion(x,y)!=PION_NULL) return 0;
	else
	{
		while(dx!=0)
		{
			dx--;
			if(GetPion(dx,y)==PionInverse(Pion)) c++;
			else
			{
				if(GetPion(dx,y)==Pion && dx!=x-1)
				{
					b+=c;
				}
				break;
			}
		}
		dx=x;
		c=0;

		while(dx!=GRID_SIZE-1)
		{
			dx++;
			if(GetPion(dx,y)==PionInverse(Pion)) c++;
			else
			{
				if(GetPion(dx,y)==Pion && dx!=x+1)
				{
					b+=c;
				}
				break;
			}
		}
		dx=x;
		c=0;
		
		while(dy!=0)
		{
			dy--;
			if(GetPion(x,dy)==PionInverse(Pion)) c++;
			else
			{
				if(GetPion(x,dy)==Pion && dy!=y-1)
				{
					b+=c;
				}
				break;
			}
		}
		dy=y;
		c=0;

		while(dy!=GRID_SIZE-1)
		{
			dy++;
			if(GetPion(x,dy)==PionInverse(Pion)) c++;
			else
			{
				if(GetPion(x,dy)==Pion && dy!=y+1)
				{
					b+=c;
				}
				break;
			}
		}
		dy=y;
		c=0;

		while(dx!=0 && dy!=0)
		{
			dx--;
			dy--;
			if(GetPion(dx,dy)==PionInverse(Pion)) c++;
			else
			{
				if(GetPion(dx,dy)==Pion && dx!=x-1 && dy!=y-1) b+=c;
				break;
			}
		}
		dx=x;
		dy=y;
		c=0;

		while(dx!=GRID_SIZE-1 && dy!=0)
		{
			dx++;
			dy--;
			if(GetPion(dx,dy)==PionInverse(Pion)) c++;
			else
			{
				if(GetPion(dx,dy)==Pion && dx!=x+1 && dy!=y-1) b+=c;
				break;
			}
		}
		dx=x;
		dy=y;
		c=0;

		while(dx!=0 && dy!=GRID_SIZE-1)
		{
			dx--;
			dy++;
			if(GetPion(dx,dy)==PionInverse(Pion)) c++;
			else
			{
				if(GetPion(dx,dy)==Pion && dx!=x-1 && dy!=y+1) b+=c;
				break;
			}
		}
		dx=x;
		dy=y;
		c=0;

		while(dx!=GRID_SIZE-1 && dy!=GRID_SIZE-1)
		{
			dx++;
			dy++;
			if(GetPion(dx,dy)==PionInverse(Pion)) c++;
			else
			{
				if(GetPion(dx,dy)==Pion && dx!=x+1 && dy!=y+1) b+=c;
				break;
			}
		}
	return b;
	}
}


short CReglesJeu::EssayerPose (const short x, const short y, const pion_t Pion)
{
	int b=0,c=0,dx=x,dy=y;

	if(GetPion(x,y)!=PION_NULL) return 0;
	
	else
	{
		while(dx!=0)
		{
			dx--;
			if(GetPion(dx,y)==PionInverse(Pion)) c++;
			else
			{
				if(GetPion(dx,y)==Pion && dx!=x-1)
				{
					while(dx!=x)
					{
						dx++;
						SetPion(dx,y,Pion);
					}
					b+=c;
				}
				break;
			}
		}
		dx=x;
		c=0;

		while(dx!=GRID_SIZE-1)
		{
			dx++;
			if(GetPion(dx,y)==PionInverse(Pion)) c++;
			else
			{
				if(GetPion(dx,y)==Pion && dx!=x+1)
				{
					while(dx!=x)
					{
						dx--;
						SetPion(dx,y,Pion);
					}
					b+=c;
				}
				break;
			}
		}
		dx=x;
		c=0;

		while(dy!=0)
		{
			dy--;
			if(GetPion(x,dy)==PionInverse(Pion)) c++;
			else
			{
				if(GetPion(x,dy)==Pion && dy!=y-1)
				{
					while(dy!=y)
					{
						dy++;
						SetPion(x,dy,Pion);
					}
					b+=c;
				}
				break;
			}
		}
		dy=y;
		c=0;

		while(dy!=GRID_SIZE-1)
		{
			dy++;
			if(GetPion(x,dy)==PionInverse(Pion)) c++;
			else
			{
				if(GetPion(x,dy)==Pion && dy!=y+1)
				{
					while(dy!=y)
					{
						dy--;
						SetPion(x,dy,Pion);
					}
					b+=c;
				}
				break;
			}
		}
		dy=y;
		c=0;

		while(dx!=0 && dy!=0)
		{
			dx--;
			dy--;
			if(GetPion(dx,dy)==PionInverse(Pion)) c++;
			else
			{
				if(GetPion(dx,dy)==Pion && dx!=x-1 && dy!=y-1)
				{
					while(dx!=x && dy!=y)
					{
						dx++;
						dy++;
						SetPion(dx,dy,Pion);
					}
					b+=c;
				}
				break;
			}
		}
		dx=x;
		dy=y;
		c=0;

		while(dx!=GRID_SIZE-1 && dy!=0)
		{
			dx++;
			dy--;
			if(GetPion(dx,dy)==PionInverse(Pion)) c++;
			else
			{
				if(GetPion(dx,dy)==Pion && dx!=x+1 && dy!=y-1)
				{
					while(dx!=x && dy!=y)
					{
						dx--;
						dy++;
						SetPion(dx,dy,Pion);
					}
					b+=c;
				}
				break;
			}
		}
		dx=x;
		dy=y;
		c=0;

		while(dx!=0 && dy!=GRID_SIZE-1)
		{
			dx--;
			dy++;
			if(GetPion(dx,dy)==PionInverse(Pion)) c++;
			else
			{
				if(GetPion(dx,dy)==Pion && dx!=x-1 && dy!=y+1)
				{
					while(dx!=x && dy!=y)
					{
						dx++;
						dy--;
						SetPion(dx,dy,Pion);
					}
					b+=c;
				}
				break;
			}
		}
		dx=x;
		dy=y;
		c=0;

		while(dx!=GRID_SIZE-1 && dy!=GRID_SIZE-1)
		{
			dx++;
			dy++;
			if(GetPion(dx,dy)==PionInverse(Pion)) c++;
			else
			{
				if(GetPion(dx,dy)==Pion && dx!=x+1 && dy!=y+1)
				{
					while(dx!=x && dy!=y)
					{
						dx--;
						dy--;
						SetPion(dx,dy,Pion);
					}
					b+=c;
				}
				break;
			}
		}

	return b;
	}
}	

bool CReglesJeu::VerifierJoueurPeutJouer (const pion_t Pion)
{
	for(int a=0;a<GRID_SIZE;a++)
	{
		for(int b=0;b<GRID_SIZE;b++)
		{
			if(VerifierPose(a,b,Pion))
			{
				return true;
			}
		}
	}

	return false;

}
