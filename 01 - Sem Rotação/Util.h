#ifndef ___UTIL_H__
#define ___UTIL_H__



#include <bits/stdc++.h>
#include <GL/glut.h>
#include <time.h>
#include <limits.h>
#include <sys/time.h>
#include <ilcplex/ilocplex.h>

using namespace std;



typedef IloArray<IloNumVarArray> NumVarMatrix2D;
typedef IloArray<NumVarMatrix2D> NumVarMatrix3D;
typedef IloArray<IloExprArray>   ExprMatrix;
typedef IloArray<IloBoolVarArray> BoolVarMatrix;
typedef unsigned long long llu;



//==============================================================================
//                      ESTRUTURAS
//==============================================================================
typedef struct {
    double x, y, z;  // Coordenadas
    double tx, ty, tz;   // Tamanho
    double r, g, b;  // Cor
} Caixa;




//==============================================================================
//                        VARIÁVEIS GLOBAIS    
//==============================================================================
float rotate_x = -22, rotate_y = 130;   //Variáveis de rotação
float x, y, z;                      //Posição do container
size_t totalCx = 0;                 //Total de caixas





//==============================================================================
//                        FUNÇÕES AUXILIARES
//==============================================================================

bool ordena(Caixa a, Caixa b);



#endif
