#include "Util.h"

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

void desenha(){
    //Função que faz o desenho do container e das caixas na tela

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpa a tela e o depth buffer
    glLoadIdentity();
    
    //Inicialização do eixo, e rotação a partir das variáveis de rotação
    glTranslatef(0+middle, -0.2, 0.33+rotZ);
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

int main(int argc, char** argv){
    string arq, ignore;
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-arq") == 0){
            arq = argv[i+1];
            i++;
        }
    }


    ifstream file;
    file.open(arq);
    getline(file, ignore);
    file >> X >> Y >> Z;
    file >> totalCx;

    cout << "X: " << X << endl;
    cout << "Y: " << Y << endl;
    cout << "Z: " << Z << endl;
    cout << "Total de caixas: " << totalCx << endl;

    //Atribuição das cores da caixa inicial
    float cr, cg, cb; 
    srand((unsigned)time(0));
    cr = (rand() % 255)/255.0;
    cg = (rand() % 255)/255.0;
    cb = (rand() % 255)/255.0;

    for(int i = 0; i < totalCx; i++){
        int in;
        Caixa cx;
        file >> cx.tx >> cx.ty >> cx.tz >> cx.id;
        file >> in;
        file >> cx.x >> cx.y >> cx.z;
        if(caixas.size() > 0 && cx.id != caixas[caixas.size()-1].id){
            cr = (rand() % 255)/255.0;
            cg = (rand() % 255)/255.0;
            cb = (rand() % 255)/255.0;
        }
        cx.r = cr; cx.g = cg; cx.b = cb;
        if(in == 1) caixas.push_back(cx);
    }

    sort(caixas.begin(), caixas.end(), ordena);
    
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