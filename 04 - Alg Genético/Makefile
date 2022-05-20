SYSTEM  = x86-64_linux
LIBFORMAT = static_pic

OPTIONS = -O3 #-g
COMP = g++ -c

CPLEXDIR      = /opt/ibm/ILOG/CPLEX_Studio201/cplex
CONCERTDIR    = /opt/ibm/ILOG/CPLEX_Studio201/concert

CCC = g++
CCOPT = -std=c++11 -m64 -O3 -fPIC -fexceptions -DNDEBUG -DIL_STD
OpenGL = -lm -lGL -lGLU -lglut

CPLEXBINDIR   = $(CPLEXDIR)/bin/$(BINDIST)
CPLEXJARDIR   = $(CPLEXDIR)/lib/cplex.jar
CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CCLNFLAGS = -L$(CPLEXLIBDIR) -lilocplex -lcplex -L$(CONCERTLIBDIR) -lconcert -m64 -lm -lpthread -ldl

CONCERTINCDIR = $(CONCERTDIR)/include
CPLEXINCDIR   = $(CPLEXDIR)/include
SRCDIR = 
OBJDIR = obj

OBJ_PRJ = Mod.o

CCFLAGS = $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR)

EXECUTAVEL = Mod

all: $(EXECUTAVEL)

$(EXECUTAVEL) :  $(OBJ_PRJ) $(OBJ_LIB) $(OpenGL)
	$(CCC) $(CCFLAGS) -o $(EXECUTAVEL) $(OBJ_PRJ) $(OBJ_LIB) $(CCLNFLAGS) $(OpenGL)

Modelo.o: Mod.cpp
	$(CCC) -c $(CCFLAGS) $(OpenGL) Mod.cpp -o Mod.o 


run: $(EXECUTAVEL)
	./$(EXECUTAVEL) -opengl

terminal: $(EXECUTAVEL)
	./$(EXECUTAVEL)

clean:
	rm -f *.o
	rm -f *~
	rm Mod


