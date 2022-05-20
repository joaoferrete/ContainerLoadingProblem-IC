CCC = g++
OpenGL = -lm -lGL -lGLU -lglut
EXECUTAVEL = Graf

OBJ_PRJ = Graf.o

all: $(EXECUTAVEL)

$(EXECUTAVEL): $(OBJ_PRJ) $(OpenGL)
	$(CCC) -o $(EXECUTAVEL) $(OBJ_PRJ) $(OpenGL)

$(OBJ_PRJ): main.cpp
	$(CCC) -c $(OpenGL) main.cpp -o Graf.o

run: $(EXECUTAVEL)
	./$(EXECUTAVEL) -arq teste

clean:
	rm -f *.o
	rm -f *~
	rm Graf