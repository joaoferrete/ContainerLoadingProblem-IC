#SYSTEM  = x86-64_sles10_4.1
SYSTEM  = x86-64_linux
LIBFORMAT = static_pic

OPTIONS = -O3 #-g
COMP = g++ -c

#------------------------------------------------------------
#
# When you adapt this makefile to compile your CPLEX programs
# please copy this makefile and set CPLEXDIR and CONCERTDIR to
# the directories where CPLEX and CONCERT are installed.
#
#------------------------------------------------------------
CPLEXDIR      = /opt/ibm/ILOG/CPLEX_Studio201/cplex
CONCERTDIR    = /opt/ibm/ILOG/CPLEX_Studio201/concert

# ---------------------------------------------------------------------
# Compiler selection 
# ---------------------------------------------------------------------
CCC = g++
#CPPC = g++ $(OPTIONS)

# ---------------------------------------------------------------------
# Compiler options 
# ---------------------------------------------------------------------
#CCOPT = -m32 -O3 -fPIC -fexceptions -DNDEBUG -DIL_STD
CCOPT = -std=c++11 -m64 -O3 -fPIC -fexceptions -DNDEBUG -DIL_STD
OpenGL = -lm -lGL -lGLU -lglut



# ---------------------------------------------------------------------
# Link options and libraries
# ---------------------------------------------------------------------
CPLEXBINDIR   = $(CPLEXDIR)/bin/$(BINDIST)
CPLEXJARDIR   = $(CPLEXDIR)/lib/cplex.jar
CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)

#CCLNFLAGS = -L$(CPLEXLIBDIR) -lilocplex -lcplex -L$(CONCERTLIBDIR) -lconcert -m32 -lm -lpthread 
CCLNFLAGS = -L$(CPLEXLIBDIR) -lilocplex -lcplex -L$(CONCERTLIBDIR) -lconcert -m64 -lm -lpthread -ldl

CONCERTINCDIR = $(CONCERTDIR)/include
CPLEXINCDIR   = $(CPLEXDIR)/include
SRCDIR = 
OBJDIR = obj

OBJ_PRJ = Mod.o

CCFLAGS = $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR)

OBJ_LIB = 

Projeto :  $(OBJ_PRJ) $(OBJ_LIB) $(OpenGL)
	$(CCC) $(CCFLAGS) -o Mod $(OBJ_PRJ) $(OBJ_LIB) $(CCLNFLAGS) $(OpenGL)

Exato.o:Exato.cpp
	$(CCC) -c $(CCFLAGS) $(OpenGL) Mod.cpp -o Mod.o 


clean:
	rm -f *.o
	rm -f *~
	rm Mod


