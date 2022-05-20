#include "Util.h"
using namespace std;


// Variáveis de Entrada
double X, Y, Z, M;
int numCx;
vector <Caixa> tamCx;
vector <Caixa> caixas;
int tempoLimiteCplex = 120;


bool ordena(Caixa a, Caixa b){
    /*-----------------------------------------------------------------------------
        *  
        * Função que ordena as caixas, de forma que sejam impressas de baixo para cima
        * 
    --------------------------------------------------------------------------------*/
    if(a.y == b.y){
        if(a.z == b.z){
            return a.x < b.x;
        }
        return a.z < b.z;
    }
    return a.y < b.y;
}


//==============================================================================
//
//                          FUNÇÕES DE DESENHO
//
//==============================================================================


void desenha(){
    /*-----------------------------------------------------------------------------
        *  
        * Função que faz o desenho do container e das caixas na tela
        * 
    --------------------------------------------------------------------------------*/

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    //Inicialização do eixo, e rotação a partir das variáveis de rotação
    glTranslatef(0, -0.2, 0.33);
    glRotatef(rotate_x, 1, 0, 0);
    glRotatef(rotate_y, 0, 1, 0);
    


    for(int i = 0; i < min(totalCx, caixas.size()); i++){   //Laço para as caixas
        
/*-----------------------------------------------------------------------------------
                                CALCULOS
-----------------------------------------------------------------------------------*/

        float xx, yy, zz, coorx, coory, coorz, r, g, b; 

        if(X >= Y && X >= Z){   //Caso o container tenha o maior tamanho em x
            //Definição das proporções da caixa em relação ao container
            xx = caixas[i].tx/X * 0.6;  
            yy = caixas[i].ty/X * 0.6;
            zz = caixas[i].tz/X * 0.6;
            //Definição das coordenadas da caixa em relação ao container
            coorx = caixas[i].x/X * 0.6;
            coory = caixas[i].y/X * 0.6;
            coorz = caixas[i].z/X * 0.6;
        }
        else if (Y >= X && Y >= Z){  //Caso o container tenha o maior tamanho em y
            xx = caixas[i].tx/Y * 0.6;
            yy = caixas[i].ty/Y * 0.6;
            zz = caixas[i].tz/Y * 0.6;
            coorx = caixas[i].x/Y * 0.6;
            coory = caixas[i].y/Y * 0.6;
            coorz = caixas[i].z/Y * 0.6;
        }
        else{   //Caso o container tenha o maior tamanho em z
            xx = caixas[i].tx/Z * 0.6;
            yy = caixas[i].ty/Z * 0.6;
            zz = caixas[i].tz/Z * 0.6;
            coorx = caixas[i].x/Z * 0.6;
            coory = caixas[i].y/Z * 0.6;
            coorz = caixas[i].z/Z * 0.6;
        }
        r = caixas[i].r; g = caixas[i].g; b = caixas[i].b;  //Definição das cores da caixa


/*-----------------------------------------------------------------------------------
                                DESENHO
-----------------------------------------------------------------------------------*/

        glTranslatef(coorx, coory, coorz);  //Translação do ponto de origem da caixa para a posição correta

        //Desenho dos polígonos da caixa
        glColor3f(r,g,b);
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1.0, 1.0);
        

        glBegin(GL_POLYGON);    //Baixo
            glVertex3f(0,0,0);
            glVertex3f(0,0,zz);
            glVertex3f(xx,0,zz);
            glVertex3f(xx,0,0);
        glEnd();
        glBegin(GL_POLYGON);   
            glVertex3f(0,yy,0);
            glVertex3f(0,yy,zz);
            glVertex3f(xx,yy,zz);
            glVertex3f(xx,yy,0);
        glEnd();
        glBegin(GL_POLYGON);  //Frente
            glVertex3f(0,0,0);
            glVertex3f(0,yy,0);
            glVertex3f(xx,yy,0);
            glVertex3f(xx,0,0);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex3f(0,0,zz);
            glVertex3f(0,yy,zz);
            glVertex3f(xx,yy,zz);
            glVertex3f(xx,0,zz);
        glEnd();
        glBegin(GL_POLYGON);  //Esquerda
            glVertex3f(0,0,0);
            glVertex3f(0,0,zz);
            glVertex3f(0,yy,zz);
            glVertex3f(0,yy,0);
        glEnd();
        glBegin(GL_POLYGON);  //Direita
            glVertex3f(xx,0,0);
            glVertex3f(xx,0,zz);
            glVertex3f(xx,yy,zz);
            glVertex3f(xx,yy,0);
        glEnd();


        //Desenho das linhas da caixa
        glColor3f(0,0,0);
        glLineWidth(0.5);

        glBegin(GL_LINE_LOOP);    //Baixo
            glVertex3f(0,0,0);
            glVertex3f(0,0,zz);
            glVertex3f(xx,0,zz);
            glVertex3f(xx,0,0);
        glEnd();
           //Cima
        glBegin(GL_LINE_LOOP);   
            glVertex3f(0,yy,0);
            glVertex3f(0,yy,zz);
            glVertex3f(xx,yy,zz);
            glVertex3f(xx,yy,0);
        glEnd();
        glBegin(GL_LINE_LOOP);  //Frente
            glVertex3f(0,0,0);
            glVertex3f(0,yy,0);
            glVertex3f(xx,yy,0);
            glVertex3f(xx,0,0);
        glEnd();
        glBegin(GL_LINE_LOOP);
            glVertex3f(0,0,zz);
            glVertex3f(0,yy,zz);
            glVertex3f(xx,yy,zz);
            glVertex3f(xx,0,zz);
        glEnd();
        glBegin(GL_LINE_LOOP);  //Esquerda
            glVertex3f(0,0,0);
            glVertex3f(0,0,zz);
            glVertex3f(0,yy,zz);
            glVertex3f(0,yy,0);
        glEnd();
        glBegin(GL_LINE_LOOP);  //Direita
            glVertex3f(xx,0,0);
            glVertex3f(xx,0,zz);
            glVertex3f(xx,yy,zz);
            glVertex3f(xx,yy,0);
        glEnd();

        glTranslatef(-coorx, -coory, -coorz);   //Retorna as coordenadas para o ponto de origem
    }


    /*---------------------------------------------------------------------------------
        *  
        * Desenho do Container
        *
    -----------------------------------------------------------------------------------*/
    glLineWidth(5.0);   //Peso da linha
    
    glColor3f(0,0,0);   //Cor preta
    glBegin(GL_LINE_LOOP);    //Baixo
        glVertex3f(0,0,0);
        glVertex3f(0,0,z);
        glVertex3f(x,0,z);
        glVertex3f(x,0,0);
    glEnd();
    glBegin(GL_LINE_LOOP);   
        glVertex3f(0,y,0);
        glVertex3f(0,y,z);
        glVertex3f(x,y,z);
        glVertex3f(x,y,0);
    glEnd();
    glBegin(GL_LINE_LOOP);  //Frente
        glVertex3f(0,0,0);
        glVertex3f(0,y,0);
        glVertex3f(x,y,0);
        glVertex3f(x,0,0);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(0,0,z);
        glVertex3f(0,y,z);
        glVertex3f(x,y,z);
        glVertex3f(x,0,z);
    glEnd();
    glBegin(GL_LINE_LOOP);  //Esquerda
        glVertex3f(0,0,0);
        glVertex3f(0,0,z);
        glVertex3f(0,y,z);
        glVertex3f(0,y,0);
    glEnd();
    glBegin(GL_LINE_LOOP);  //Direita
        glVertex3f(x,0,0);
        glVertex3f(x,0,z);
        glVertex3f(x,y,z);
        glVertex3f(x,y,0);
    glEnd();

    glFlush();  //Mostra o desenho
}



//=============================================================================================
//=============================================================================================



void SpecialKeys(int key, int x, int y){
     /*-----------------------------------------------------------------------------
        *  
        * Função que faz o tratamento ao apertar as teclas especiais
        * 
    --------------------------------------------------------------------------------*/

    if(key == GLUT_KEY_LEFT){   //Tecla esquerda efetua rotação em torno do eixo y
        rotate_y += 1;  
    }
    else if(key == GLUT_KEY_RIGHT){  //Tecla direita efetua rotação em torno do eixo y
        rotate_y -= 1;
    }

    //---------------------------------------------------------------------------------

    else if(key == GLUT_KEY_UP){    //Tecla cima efetua rotação em torno do eixo x
        rotate_x += 1;
    }
    else if(key == GLUT_KEY_DOWN){  //Tecla baixo efetua rotação em torno do eixo x
        rotate_x -= 1;
    }

    //---------------------------------------------------------------------------------


    else if(key == GLUT_KEY_PAGE_UP)  //Tecla de adiciona uma caixa ao total, fazendo-a ser impressa
        totalCx = totalCx == caixas.size() ? totalCx : totalCx + 1;
    
    else if(key == GLUT_KEY_PAGE_DOWN) //Tecla de subtrai uma caixa ao total, fazendo-a ser removida
        totalCx = totalCx == 0 ? totalCx : totalCx - 1;


    //---------------------------------------------------------------------------------


    else if(key == GLUT_KEY_HOME){  //Tecla home efetua a impressão de todas as caixas ou retira todas as caixas
        totalCx = totalCx < caixas.size() ? caixas.size() : 0;
    }

    //cout << "roteX: " << rotate_x << "  roteY: " << rotate_y << endl;

    glutPostRedisplay();    //Chama a função de redesenho
}


//=============================================================================================
//=============================================================================================



void inicializa(){
     /*-----------------------------------------------------------------------------
        *  
        * Função que inicializa as configurações do OpenGL e as variáveis do programa
        * 
    --------------------------------------------------------------------------------*/

    glClearColor(1, 1, 1, 1.0);  //Cor de fundo

    //---------------------------------------------------------------------------------
    //Calculo das proporções do container
    //---------------------------------------------------------------------------------

    if(X >= Y && X >= Z){  //Caso o container tenha o maior tamanho em X
        x = 0.6;    //Define o tamanho do container em X
        y = (double)((Y/X) * 0.6);   //Calcula a proporção do container em relação ao tamanho em X
        z = (double)((Z/X) * 0.6);
    }
    else if(Y >= X && Y >= Z){  //Caso o container tenha o maior tamanho em Y
        x = (double)((X/Y) * 0.6);
        y = 0.6;
        z = (double)((Z/Y) * 0.6);
    }
    else{   //Caso o container tenha o maior tamanho em Z
        x = (double)((X/Z) * 0.6);
        y = (double)((Y/Z) * 0.6);
        z = 0.6;
    }

    sort(caixas.begin(), caixas.end(), ordena); //Ordena as caixas pelas posições

}




int main(int argc, char **argv){
    cin >> X >> Y >> Z;
    M = X > Y ? X > Z ? X : Z : Y > Z ? Y : Z;
    M++;
    long qtTipos;
    numCx = 0;

    cin >> qtTipos;

    tamCx.push_back({0, 0, 0});

    for(int i = 0; i < qtTipos; i++){
        float xc, yc, zc, qt=0;
        cin >> xc >> yc >> zc >> qt;
        for(int j = 0; j < qt; j++){
            Caixa cx = {xc, yc, zc};
            cx.id = i+1;
            tamCx.push_back(cx);
            numCx++;
        }
    }

    cout << "Entrada Concluída!" << endl;

    // Criando o Modelo
    auto Inicio = chrono::system_clock::now();
    IloEnv env;            // Criando o ambiente    (IloEnv)

    try{
        IloModel model(env, "Modelo");  // Criando o modelo (IloModel)
        IloCplex cplex(env);          // Criando o Cplex (IloCplex)

        // Variáveis de Decisão
        IloBoolVarArray s(env, numCx+1);
        NumVarMatrix2D pos(env, numCx+1);
        BoolVarMatrix a(env, numCx+1);
        BoolVarMatrix b(env, numCx+1);
        BoolVarMatrix c(env, numCx+1);
        BoolVarMatrix d(env, numCx+1);
        BoolVarMatrix e(env, numCx+1);
        BoolVarMatrix f(env, numCx+1);

        for(int i = 1; i <= numCx; i++){    // Inicialização das variáveis de decisão
            pos[i] = IloNumVarArray(env, 3, 0, IloInfinity, ILOFLOAT);
            a[i] = IloBoolVarArray(env, numCx+1);
            b[i] = IloBoolVarArray(env, numCx+1);
            c[i] = IloBoolVarArray(env, numCx+1);
            d[i] = IloBoolVarArray(env, numCx+1);
            e[i] = IloBoolVarArray(env, numCx+1);
            f[i] = IloBoolVarArray(env, numCx+1);
        }

        cout << "Variáveis de Decisão Criadas!" << endl;

        IloExpr Objetivo(env);  // Criando a função objetivo
        for(int i = 1; i <= numCx; i++){
            Objetivo += s[i]*tamCx[i].x*tamCx[i].y*tamCx[i].z;   // Função objetivo
        }
        model.add(IloMaximize(env, Objetivo)); // Adicionando a função objetivo ao modelo

        cout << "Criando as restrições..." << endl;

        // Restrições
        IloConstraintArray restricoes(env);
        
        for(int i = 1; i <= numCx; i++){
            for(int j = 1; j <= numCx; j++){
                if(i < j){
                    restricoes.add(pos[i][0] + tamCx[i].x <= pos[j][0] + (1 - a[i][j])*M);
                    restricoes.add(pos[j][0] + tamCx[j].x <= pos[i][0] + (1 - b[i][j])*M);

                    restricoes.add(pos[i][1] + tamCx[i].y <= pos[j][1] + (1 - c[i][j])*M);
                    restricoes.add(pos[j][1] + tamCx[j].y <= pos[i][1] + (1 - d[i][j])*M);

                    restricoes.add(pos[i][2] + tamCx[i].z <= pos[j][2] + (1 - e[i][j])*M);
                    restricoes.add(pos[j][2] + tamCx[j].z <= pos[i][2] + (1 - f[i][j])*M);
            
                    restricoes.add(a[i][j] + b[i][j] + c[i][j] + d[i][j] + e[i][j] + f[i][j] >= (s[i] + s[j] - 1));                    
                }   
            }
        }

        for(int i = 1; i <= numCx; i++){
            restricoes.add(pos[i][0] + tamCx[i].x <= X + (1 - s[i])*M);
            restricoes.add(pos[i][1] + tamCx[i].y <= Y + (1 - s[i])*M);
            restricoes.add(pos[i][2] + tamCx[i].z <= Z + (1 - s[i])*M);
        }

        model.add(restricoes);  // Adicionando as restrições ao modelo
        cplex.extract(model);   // Extraindo o modelo para o Cplex

        // Solução
        cplex.setParam(IloCplex::TiLim, tempoLimiteCplex);  // Limite de tempo para o Cplex
        cplex.solve();

        // Imprimindo o resultado
        auto Fim = chrono::system_clock::now();
        chrono::duration<double> Diferenca = Fim - Inicio;


        cout << "\nTempo: " << Diferenca.count() << "s" << endl;
        cout << "Valor da Função Objetivo: " << cplex.getObjValue() << endl;
        cout << "Aproveitamento de " << cplex.getObjValue()/(X*Y*Z)*100 << "% do volume." << endl;
        cout << "\nValor das Variáveis de Decisão: " << endl;

        //Atribuição das cores da caixa inicial
        float cr, cg, cb; 
        srand((unsigned)time(0));
        cr = (rand() % 255)/255.0;
        cg = (rand() % 255)/255.0;
        cb = (rand() % 255)/255.0;
        int j=0;

        for(int i = 1; i <= numCx; i++){
            cout << "Caixa " << i << ": É do tipo " << tamCx[i].id;
            cout << " e está na posição [" << cplex.getValue(pos[i][0]) << ", " << 
            cplex.getValue(pos[i][1]) << ", " << cplex.getValue(pos[i][2]) << "]";
            cout << " e" << (cplex.getValue(s[i]) ? "" : " nao") << " está empilhada" << endl;


            //Insersão de caixas no vetor para impressão
            if(cplex.getValue(s[i])){   // Se a caixa está empilhada
                //Insere os dados da caixa no vetor 
                Caixa cx = {cplex.getValue(pos[i][0]), cplex.getValue(pos[i][1]), cplex.getValue(pos[i][2]), tamCx[i].x, tamCx[i].y, tamCx[i].z};
                
                if(j > 0 && (cx.tx != caixas[j-1].tx || cx.ty != caixas[j-1].ty || cx.tz != caixas[j-1].tz)){
                //Caso a caixa atual não seja igual a caixa anterior, atribui uma nova cor
                    cr = (rand() % 255)/255.0;
                    cg = (rand() % 255)/255.0;
                    cb = (rand() % 255)/255.0;
                }

                cx.r = cr; cx.g = cg; cx.b = cb;    // Atribuição das cores
                sort(caixas.begin(), caixas.end(), ordena); //Ordena as caixas pelas posições
                caixas.push_back(cx);   // Insere a caixa no vetor
                j++;    // Incrementa o contador de caixas
            }
        }
        tamCx.clear();

        //Imprime as caixas na tela
        glutInit(&argc, argv);  //Inicializa o glut
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);   //Define o modo de exibição
        glutInitWindowSize(700, 700);   //Define o tamanho da janela
        glutCreateWindow("CONTAINER"); 
        inicializa();       //Inicializa os parâmetros
        glutDisplayFunc(desenha);   //Define a função de redesenho
        glutSpecialFunc(SpecialKeys);   //Define a função de teclas especiais
        glEnable(GL_DEPTH_TEST);    //Habilita o teste de profundidade
        glutMainLoop();   //Inicia o loop principal do glut
        
        return 0;

    }
    catch(IloException& e){
        cerr << "Erro: " << e << endl;
    }
    catch(...){
        cerr << "Erro: " << endl;
    }

}
