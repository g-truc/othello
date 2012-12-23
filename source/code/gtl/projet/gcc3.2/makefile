LIBS_X = -L/usr/X11/lib -L/usr/X11R6/lib -lX11 -lXext -lXi -lXmu -lXt -lSM -lICE 
LIBS_GL = -lglut -lGL -lGLU -lm

REP_LIBS = $(LIBS_GL) $(LIBS_X)
REP_SOURCE = ../../src
REP_HEADER = ../../include
REP_OBJ = ../../lib
REP_INCLUDE = -I$(REP_HEADER)

CC = g++
OPTIMISATION = -O2 -Wall

DO_CC=$(CC) $(OPTIMISATION) $(REP_INCLUDE) -o $@ -c $<

OBJ = \
	$(REP_OBJ)/gtl_color.o \
	$(REP_OBJ)/gtl_font.o \
	$(REP_OBJ)/gtl_image.o \
	$(REP_OBJ)/gtl_image_bmp.o \
	$(REP_OBJ)/gtl_image_raw.o \
	$(REP_OBJ)/gtl_image_tga.o \
	$(REP_OBJ)/gtl_math.o

gtl: $(OBJ)
# Groove - 20/03/2003 - Pas de fonction main pour linker 
#	$(CC) $(REP_INCLUDE) $(REP_LIBS) $(OBJ) -o $@

$(REP_OBJ)/%.o: $(REP_SOURCE)/%.cpp
	$(DO_CC)
