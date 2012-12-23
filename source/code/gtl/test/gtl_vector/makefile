LIBS_X = -L/usr/X11/lib -L/usr/X11R6/lib -lX11 -lXext -lXi -lXmu -lXt -lSM -lICE 
LIBS_GL = -lglut -lGL -lGLU -lm
# Groove - 20/03/2003 - Indiquer ou se trouve (le repertoire) les .o de G.T.L.
GTL_LIB = ../../lib/*.o
GTL_INCLUDE = ../../include

REP_LIBS = $(LIBS_GL) $(LIBS_X)
REP_SOURCE = .
REP_HEADER = .
REP_OBJ = ./obj
REP_INCLUDE = -I$(REP_HEADER) -I$(GTL_INCLUDE)

CC = g++
OPTIMISATION = -O2 -Wall

DO_CC=$(CC) $(OPTIMISATION) $(REP_INCLUDE) -o $@ -c $<

OBJ = \
	$(REP_OBJ)/test_vector.o

test_vector: $(OBJ)
	$(CC) $(REP_INCLUDE) $(REP_LIBS) $(OBJ) ${GTL_LIB} -o $@

$(REP_OBJ)/%.o: $(REP_SOURCE)/%.cpp
	$(DO_CC)
