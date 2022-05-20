#include "Util.h"
using namespace std;


void leArgumentos(int argc, char *argv[]) {
    //Função de leitura de argumentos de inicialização

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-opengl") == 0) {
            OpenGL = true;
        }
        else if (strcmp(argv[i], "-tl") == 0) {
            tempoLimiteCplex = atoi(argv[i + 1]);
            i++;
        }
        else if (strcmp(argv[i], "-i") == 0) {
            nomeArquivo = string(argv[i + 1]);
            i++;
        }
        else if (strcmp(argv[i], "-threads") == 0) {
            threads = atoi(argv[i + 1]);
            alteraThreads = true;
            i++;
        }
        else if (strcmp(argv[i], "-log") == 0) {
            cplexLog = true;
        }
        else if (strcmp(argv[i], "-mem") == 0) {
            setMemLimit = true;
            memLimit = atoi(argv[i + 1]);
            i++;
        }
        else if (strcmp(argv[i], "-plog") == 0) {
            problemLog = true;
        }


    }
}


void inicializa(){
    //Função de inicialização do programa para a chamada do OpenGL

    glClearColor(1, 1, 1, 1.0);  //Cor de fundo

    //------------------------------------
    //Calculo das proporções do container
    //------------------------------------
    if(X >= Y && X >= Z){  //Caso o container tenha o maior tamanho em X
        x = scale;    //Define o tamanho do container em X
        y = (double)((Y/X) * scale);   //Calcula a proporção do container em relação ao tamanho em X
        z = (double)((Z/X) * scale);
    }
    else if(Y >= X && Y >= Z){  //Caso o container tenha o maior tamanho em Y
        x = (double)((X/Y) * scale);
        y = scale;
        z = (double)((Z/Y) * scale);
    }
    else{   //Caso o container tenha o maior tamanho em Z
        x = (double)((X/Z) * scale);
        y = (double)((Y/Z) * scale);
        z = scale;
    }

}


bool ordena(Caixa a, Caixa b){
    //Função que ordena as caixas, de forma que sejam impressas de baixo para cima
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
    //Função que faz o desenho do container e das caixas na tela

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpa a tela e o depth buffer
    glLoadIdentity();
    
    //Inicialização do eixo, e rotação a partir das variáveis de rotação
    glTranslatef(0+middle, -0.2, 0.33+rotZ);    //Translação do eixo
    glRotatef(rotate_x, 1, 0, 0);
    glRotatef(rotate_y, 0, 1, 0);
    


    for(int i = 0; i < min(totalCx, caixas.size()); i++){   //Laço para as caixas

        float xx, yy, zz, coorx, coory, coorz, r, g, b; 

        if(X >= Y && X >= Z){   //Caso o container tenha o maior tamanho em x
            //Definição das proporções da caixa em relação ao container
            xx = caixas[i].tx/X * scale;  
            yy = caixas[i].ty/X * scale;
            zz = caixas[i].tz/X * scale;
            //Definição das coordenadas da caixa em relação ao container
            coorx = caixas[i].x/X * scale;
            coory = caixas[i].y/X * scale;
            coorz = caixas[i].z/X * scale;
        }
        else if (Y >= X && Y >= Z){  //Caso o container tenha o maior tamanho em y
            xx = caixas[i].tx/Y * scale;
            yy = caixas[i].ty/Y * scale;
            zz = caixas[i].tz/Y * scale;
            coorx = caixas[i].x/Y * scale;
            coory = caixas[i].y/Y * scale;
            coorz = caixas[i].z/Y * scale;
        }
        else{   //Caso o container tenha o maior tamanho em z
            xx = caixas[i].tx/Z * scale;
            yy = caixas[i].ty/Z * scale;
            zz = caixas[i].tz/Z * scale;
            coorx = caixas[i].x/Z * scale;
            coory = caixas[i].y/Z * scale;
            coorz = caixas[i].z/Z * scale;
        }
        r = caixas[i].r; g = caixas[i].g; b = caixas[i].b;  //Definição das cores da caixa a partir das variáveis de cor


        /*---------------------
            DESENHO DAS CAIXAS
        ----------------------*/

        glTranslatef(coorx, coory, coorz);  //Translação do ponto de origem da caixa para a posição correta

        //Desenho da caixa
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


    /*--------------------------
        Desenho do Container
    ----------------------------*/
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


void SpecialKeys(int key, int x, int y){
    // Função que faz o tratamento ao apertar as teclas especiais


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

    else if(key == GLUT_KEY_HOME){  //Tecla home efetua a impressão de todas as caixas ou retira todas as caixas
        totalCx = totalCx < caixas.size() ? caixas.size() : 0;
    }

    glutPostRedisplay();    //Chama a função de redesenho
}


void keyboard(unsigned char key, int mx, int my){
    // Função que faz o tratamento ao apertar as teclas normais

    if(key == 'q')   //Tecla que fecha o programa 
        exit(0);

    if(key == 'm')  //Tecla de adiciona uma caixa ao total, fazendo-a ser impressa
        totalCx = totalCx == caixas.size() ? totalCx : totalCx + 1;
        
    else if(key == 'n') //Tecla de subtrai uma caixa ao total, fazendo-a ser removida
        totalCx = totalCx == 0 ? totalCx : totalCx - 1;

    else if(key == 'z') //Tecla que aumenta o valor de Z, aproximando os objetos
        rotZ+=0.05;
    else if(key == 'x') //Tecla que diminui o valor de Z, aproximando os objetos
        rotZ-=0.05;
    else if(key == 's'){ //Tecla que diminui o valor da escala de impressão
        scale-=0.05;
        inicializa();
    }
    else if(key == 'd'){ //Tecla que aumenta o valor da escala de impressão
        scale+=0.05;
        inicializa();
    }
    else if(key == 'o') //Tecla que diminui o valor de Y, alterando onde o container é impresso
        middle-=0.05;
    else if(key == 'p') //Tecla que aumenta o valor de Y, alterando onde o container é impresso
        middle+=0.05;

    glutPostRedisplay();    //Chama a função de redesenho
}


int main(int argc, char **argv){

    leArgumentos(argc, argv);
    string ignore;  

    //Leitura do arquivo de entrada
    ifstream arq;
    arq.open(nomeArquivo);
    arq >> X >> Y >> Z;

    M = X > Y ? X > Z ? X : Z : Y > Z ? Y : Z;
    M++;
    long qtTipos;
    numCx = 0;

    arq >> qtTipos;

    tamCx.push_back({0, 0, 0}); //Inicializa o vetor com o tamanho da caixa, já que a posição 0 não é usada

    for(int i = 0; i < qtTipos; i++){
        int id, rx, ry, rz, p;
        float xc, yc, zc, qt=0;
        arq >> id >> xc >> rx >> yc >> ry >> zc >> rz >> qt >> p;
        for(int j = 0; j < qt; j++){
            Caixa cx = {xc, yc, zc};
            cx.id = id;
            cx.rx = rx;
            cx.ry = ry;
            cx.rz = rz;
            cx.priority = p;
            tamCx.push_back(cx);
            numCx++;
        }
    }

    if(problemLog) cout << "Entrada Concluída!" << endl;

    // Criando o Modelo
    auto Inicio = chrono::system_clock::now();
    IloEnv env;            // Criando o ambiente    (IloEnv)

    try{
        IloModel model(env, "Modelo");  // Criando o modelo (IloModel)
        IloCplex cplex(env);          // Criando o Cplex (IloCplex)

        // Variáveis de Decisão
        IloBoolVarArray s(env, numCx+1);    //Se a caixa está, ou não, no container
        NumVarMatrix2D pos(env, numCx+1);   //Posição da caixa no container
        
        //Posições relativas entre as caixas.
        BoolVarMatrix a(env, numCx+1); //à esquerda
        BoolVarMatrix b(env, numCx+1); //à direita
        BoolVarMatrix c(env, numCx+1); //atrás
        BoolVarMatrix d(env, numCx+1); //a frente
        BoolVarMatrix e(env, numCx+1); //abaixo
        BoolVarMatrix f(env, numCx+1); //acima

        //Rotação da caixa, paralelo ao eixo X
        IloBoolVarArray Lx(env, numCx+1);
        IloBoolVarArray Ly(env, numCx+1);
        IloBoolVarArray Lz(env, numCx+1);

        //Rotação da caixa, paralelo ao eixo Z
        IloBoolVarArray Wx(env, numCx+1);
        IloBoolVarArray Wy(env, numCx+1);
        IloBoolVarArray Wz(env, numCx+1);

        //Rotação da caixa, paralelo ao eixo Y
        IloBoolVarArray Hx(env, numCx+1);
        IloBoolVarArray Hy(env, numCx+1);
        IloBoolVarArray Hz(env, numCx+1);

        for(int i = 1; i <= numCx; i++){    // Inicialização das variáveis de decisão
            pos[i] = IloNumVarArray(env, 3, 0, IloInfinity, ILOFLOAT);
            a[i] = IloBoolVarArray(env, numCx+1);
            b[i] = IloBoolVarArray(env, numCx+1);
            c[i] = IloBoolVarArray(env, numCx+1);
            d[i] = IloBoolVarArray(env, numCx+1);
            e[i] = IloBoolVarArray(env, numCx+1);
            f[i] = IloBoolVarArray(env, numCx+1);
        }

        if(problemLog) cout << "Variáveis de Decisão Criadas!" << endl;

        IloExpr Objetivo(env);  // Criando a função objetivo
        for(int i = 1; i <= numCx; i++){
            Objetivo += s[i]*tamCx[i].x*tamCx[i].y*tamCx[i].z*tamCx[i].priority;   // Função objetivo
        }
        model.add(IloMaximize(env, Objetivo)); // Adicionando a função objetivo ao modelo

        if(problemLog) cout << "Criando as restrições..." << endl;

        // Restrições
        IloConstraintArray restricoes(env);
        
        for(int i = 1; i <= numCx; i++){
            for(int j = 1; j <= numCx; j++){
                if (i < j)
                {
                    restricoes.add(pos[i][0] + tamCx[i].x * Lx[i] + tamCx[i].y * Hx[i] + tamCx[i].z * Wx[i] <= pos[j][0] + (1 - a[i][j]) * M);
                    restricoes.add(pos[i][1] + tamCx[i].x * Ly[i] + tamCx[i].y * Hy[i] + tamCx[i].z * Wy[i] <= pos[j][1] + (1 - c[i][j]) * M);
                    restricoes.add(pos[i][2] + tamCx[i].x * Lz[i] + tamCx[i].y * Hz[i] + tamCx[i].z * Wz[i] <= pos[j][2] + (1 - e[i][j]) * M);

                    restricoes.add(pos[j][0] + tamCx[j].x * Lx[j] + tamCx[j].y * Hx[j] + tamCx[j].z * Wx[j] <= pos[i][0] + (1 - b[i][j]) * M);
                    restricoes.add(pos[j][1] + tamCx[j].x * Ly[j] + tamCx[j].y * Hy[j] + tamCx[j].z * Wy[j] <= pos[i][1] + (1 - d[i][j]) * M);
                    restricoes.add(pos[j][2] + tamCx[j].x * Lz[j] + tamCx[j].y * Hz[j] + tamCx[j].z * Wz[j] <= pos[i][2] + (1 - f[i][j]) * M);

                    restricoes.add(a[i][j] + b[i][j] + c[i][j] + d[i][j] + e[i][j] + f[i][j] >= (s[i] + s[j] - 1));
                }   
            }
        }

        for(int i = 1; i <= numCx; i++){
            restricoes.add(pos[i][0] + tamCx[i].x*Lx[i] + tamCx[i].y*Hx[i] + tamCx[i].z*Wx[i] <= X + (1 - s[i])*M);
            restricoes.add(pos[i][1] + tamCx[i].x*Ly[i] + tamCx[i].y*Hy[i] + tamCx[i].z*Wy[i] <= Y + (1 - s[i])*M);
            restricoes.add(pos[i][2] + tamCx[i].x*Lz[i] + tamCx[i].y*Hz[i] + tamCx[i].z*Wz[i] <= Z + (1 - s[i])*M);
            restricoes.add(Lx[i] + Ly[i]*tamCx[i].rx + Lz[i] == 1);
            restricoes.add(Wx[i] + Wy[i]*tamCx[i].rz + Wz[i] == 1);
            restricoes.add(Hx[i] + Hy[i]*tamCx[i].ry + Hz[i] == 1);
            restricoes.add(Lx[i] + Wx[i] + Hx[i] == 1);
            restricoes.add(Ly[i]*tamCx[i].rx + Wy[i]*tamCx[i].rz + Hy[i]*tamCx[i].ry == 1);
            restricoes.add(Lz[i] + Wz[i] + Hz[i] == 1);

            //Testes
            restricoes.add(Lx[i] <= (1-tamCx[i].rx) + tamCx[i].rz + tamCx[i].ry);
            restricoes.add(Lz[i] <= (1-tamCx[i].rx) + tamCx[i].rz + tamCx[i].ry);

            restricoes.add(Hx[i] <= (1-tamCx[i].ry) + tamCx[i].rz + tamCx[i].rx);
            restricoes.add(Hz[i] <= (1-tamCx[i].ry) + tamCx[i].rz + tamCx[i].rx);

            restricoes.add(Wx[i] <= (1-tamCx[i].rz) + tamCx[i].rx + tamCx[i].ry);
            restricoes.add(Wz[i] <= (1-tamCx[i].rz) + tamCx[i].rx + tamCx[i].ry);
        
            
            restricoes.add(s[i] >= tamCx[i].priority -1);

        }

        if(problemLog) cout << "Restrições Criadas!" << endl;

        model.add(restricoes);  // Adicionando as restrições ao modelo
        cplex.extract(model);   // Extraindo o modelo para o Cplex

        if(problemLog) cout << "Resolvendo o Modelo..." << endl;

        // Solução
        cplex.setParam(IloCplex::TiLim, tempoLimiteCplex);  // Limite de tempo para o Cplex
        if(alteraThreads) cplex.setParam(IloCplex::Threads, threads);  // Alteração do número de threads
        if(!cplexLog) cplex.setOut(env.getNullStream());  // Desativa o log do Cplex
        if(setMemLimit) cplex.setParam(IloCplex::TreLim, memLimit);  // Limite de memória para o Cplex
        cplex.solve();  // Resolvendo o modelo

        // Imprimindo o resultado
        auto Fim = chrono::system_clock::now();
        chrono::duration<double> Diferenca = Fim - Inicio;

        long volUtilizado = 0;
        for(long i = 1; i <= numCx; i++){
            volUtilizado += tamCx[i].x*tamCx[i].y*tamCx[i].z*cplex.getValue(s[i]);
        }


        if(problemLog){
            cout << "\nTempo: " << Diferenca.count() << "s" << endl;
            cout << "Valor da Função Objetivo: " << cplex.getObjValue() << endl;
            cout << "Volume total do Container: " << X*Y*Z << endl;
            cout << "Volume utilizado: " << volUtilizado << endl;
            cout << "Aproveitamento de " << volUtilizado/(X*Y*Z)*100 << "% do volume." << endl;
            cout << "Número de restrições: " << restricoes.getSize() << endl;
            if(alteraThreads) cout << "Número de Threads: " << threads << endl;
            if(setMemLimit) cout << "Limite de Memória: " << memLimit << endl;
            cout << "\nValor das Variáveis de Decisão: " << endl;
        }

        //Atribuição das cores da caixa inicial
        float cr, cg, cb; 
        srand((unsigned)time(0));
        cr = (rand() % 255)/255.0;
        cg = (rand() % 255)/255.0;
        cb = (rand() % 255)/255.0;
        int j=0;

        if(!OpenGL) cout << X << " " << Y << " " << Z << endl << numCx << endl;

        for(int i = 1; i <= numCx; i++){
            if(OpenGL){
                cout << "Caixa " << i << ": É do tipo " << tamCx[i].id;
                cout << " possui prioridade " << tamCx[i].priority;
                cout << " e está na posição [" << cplex.getValue(pos[i][0]) << ", " << 
                cplex.getValue(pos[i][1]) << ", " << cplex.getValue(pos[i][2]) << "]";
                cout << " e" << (cplex.getValue(s[i]) ? "" : " nao") << " está empilhada" << endl;


                //Insersão de caixas no vetor para impressão
                if(cplex.getValue(s[i])){   // Se a caixa está empilhada
                    //Insere os dados da caixa no vetor 
                    
                    Caixa cx = {cplex.getValue(pos[i][0]), cplex.getValue(pos[i][1]), cplex.getValue(pos[i][2])};
                    cx.tx = (tamCx[i].x*cplex.getValue(Lx[i]) + tamCx[i].y*cplex.getValue(Hx[i]) + tamCx[i].z*cplex.getValue(Wx[i]));
                    cx.ty = (tamCx[i].x*cplex.getValue(Ly[i]) + tamCx[i].y*cplex.getValue(Hy[i]) + tamCx[i].z*cplex.getValue(Wy[i]));
                    cx.tz = (tamCx[i].x*cplex.getValue(Lz[i]) + tamCx[i].y*cplex.getValue(Hz[i]) + tamCx[i].z*cplex.getValue(Wz[i]));
                    cx.id = tamCx[i].id;
  
                    if(j > 0 && cx.id != caixas[j-1].id){
                    //Caso a caixa atual não seja igual a caixa anterior, atribui uma nova cor
                        cr = (rand() % 255)/255.0;
                        cg = (rand() % 255)/255.0;
                        cb = (rand() % 255)/255.0;
                    }

                    cx.r = cr; cx.g = cg; cx.b = cb;    // Atribuição das cores
                    caixas.push_back(cx);   // Insere a caixa no vetor
                    j++;    // Incrementa o contador de caixas
                }
            }
            else{
                cout << (tamCx[i].x*cplex.getValue(Lx[i]) + tamCx[i].y*cplex.getValue(Hx[i]) + tamCx[i].z*cplex.getValue(Wx[i])) << " "
                << (tamCx[i].x*cplex.getValue(Ly[i]) + tamCx[i].y*cplex.getValue(Hy[i]) + tamCx[i].z*cplex.getValue(Wy[i])) << " " 
                << (tamCx[i].x*cplex.getValue(Lz[i]) + tamCx[i].y*cplex.getValue(Hz[i]) + tamCx[i].z*cplex.getValue(Wz[i])) 
                << " " << tamCx[i].id << endl;
                cout << cplex.getValue(s[i]) << " ";
                cout << cplex.getValue(pos[i][0]) << " " << 
                cplex.getValue(pos[i][1]) << " " << cplex.getValue(pos[i][2]) << endl;
            }
        }
        sort(caixas.begin(), caixas.end(), ordena); //Ordena as caixas pelas posições
        tamCx.clear();

        if(OpenGL){
            //Imprime as caixas na tela
            glutInit(&argc, argv);  //Inicializa o glut
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);   //Define o modo de exibição
            glutInitWindowSize(700, 700);   //Define o tamanho da janela
            glutCreateWindow("CONTAINER"); 
            inicializa();       //Inicializa os parâmetros
            glutDisplayFunc(desenha);   //Define a função de redesenho
            glutSpecialFunc(SpecialKeys);   //Define a função de teclas especiais
            glutKeyboardFunc(keyboard);   //Define a função de teclas normais
            glEnable(GL_DEPTH_TEST);    //Habilita o teste de profundidade
            glutMainLoop();   //Inicia o loop principal do glut
        }
        
        return 0;

    }
    catch(IloException& e){
        cerr << "Erro: " << e << endl;
    }
    catch(...){
        cerr << "Erro: " << endl;
    }

}
