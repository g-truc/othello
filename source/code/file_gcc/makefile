LIBS_GL = -lglut -lGL -lGLU -lm
GTL_INCLUDE = ../gtl/include
GTL_LIB = ../gtl/lib/*.o

REP_LIBS = $(LIBS_GL)
REP_SOURCE = ../source
REP_HEADER = ../header
REP_OBJ = ./obj
REP_INCLUDE = -I$(REP_HEADER) -I$(GTL_INCLUDE)

CC = g++
OPTIMISATION = -O3 -Wall

DO_CC=$(CC) $(OPTIMISATION) $(REP_INCLUDE) -o $@ -c $<

OBJ = \
	$(REP_OBJ)/affichage_plateau.o \
	$(REP_OBJ)/grille.o \
	$(REP_OBJ)/interface.o \
	$(REP_OBJ)/joueur_humain.o \
	$(REP_OBJ)/joueur_ia.o \
	$(REP_OBJ)/main_othello.o \
	$(REP_OBJ)/meilleur_score.o \
	$(REP_OBJ)/menu.o \
	$(REP_OBJ)/partie.o \
	$(REP_OBJ)/regles_jeu.o \
	$(REP_OBJ)/resultat.o \
	$(REP_OBJ)/text.o

othello-gl: $(OBJ)
	$(CC) $(REP_INCLUDE) $(REP_LIBS) $(OBJ) $(GTL_LIB) -o ../../../$@

$(REP_OBJ)/%.o: $(REP_SOURCE)/%.cpp $(REP_HEADER)/%.h
	$(DO_CC)
