//Comando de compilaçção g++ -o teste  "teste.cpp" "Modelos/Pinguim.hpp" "Modelos/Pinguim.cpp" -lfreeglut -lopengl32 -lglu32
// Inclusão de bibliotecas padrão do OpenGL, utilitários de tempo, matemática e carregamento de imagens (stb_image)
#include <GL/glut.h>
#include <GL/glext.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Modelos/Pinguim.hpp"

Pinguim mae(0,0);
// Identificadores de textura utilizados no cenário e objetos
int texID[9]; 
int iteradorAza =0;

void desenharGelo() {
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(40.0f, 0.1f, 40.0f);
    //glBindTexture( GL_TEXTURE_2D, texID[0]);
    glBegin(GL_QUADS);
      glNormal3f(0, 0, 1);
  glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, 0.5);
  glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, 0.5);
  glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, 0.5);
  glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, 0.5);

  // Face traseira
  glNormal3f(0, 0, -1);
  glTexCoord2f(0, 0); glVertex3f(0.5, -0.5, -0.5);
  glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, -0.5);
  glTexCoord2f(1, 1); glVertex3f(-0.5, 0.5, -0.5);
  glTexCoord2f(0, 1); glVertex3f(0.5, 0.5, -0.5);

  // Face esquerda
  glNormal3f(-1, 0, 0);
  glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, -0.5);
  glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, 0.5);
  glTexCoord2f(1, 1); glVertex3f(-0.5, 0.5, 0.5);
  glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.5);

  // Face direita
  glNormal3f(1, 0, 0);
  glTexCoord2f(0, 0); glVertex3f(0.5, -0.5, 0.5);
  glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, -0.5);
  glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, -0.5);
  glTexCoord2f(0, 1); glVertex3f(0.5, 0.5, 0.5);

  // Face de cima
  glNormal3f(0, 1, 0);
  glTexCoord2f(0, 0); glVertex3f(-0.5, 0.5, 0.5);
  glTexCoord2f(1, 0); glVertex3f(0.5, 0.5, 0.5);
  glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, -0.5);
  glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.5);

  // Face de baixo
  glNormal3f(0, -1, 0);
  glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, -0.5);
  glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, -0.5);
  glTexCoord2f(1, 1); glVertex3f(0.5, -0.5, 0.5);
  glTexCoord2f(0, 1); glVertex3f(-0.5, -0.5, 0.5);
    glEnd();
    glPopMatrix();
}

// Nomes dos arquivos de textura utilizados para aplicar materiais em objetos e no ambiente
char* textureFileNames[9] = {   
    "..\\textura\\gelo.jpg",
    "..\\textura\\agua.jpg",
    "..\\textura\\escama.jpg",
    "..\\textura\\posx.jpg",
    "..\\textura\\negx.jpg",
    "..\\textura\\posy.jpg",
    "..\\textura\\negy.jpg",
    "..\\textura\\posz.jpg",
    "..\\textura\\negz.jpg"
};

// Função responsável pela inicialização do ambiente 3D e estado inicial do jogo
void init() {
    glEnable(GL_DEPTH_TEST);       // Ativa teste de profundidade
    glEnable(GL_LIGHTING);         // Ativa sistema de iluminação
    glEnable(GL_LIGHT0);           // Ativa fonte de luz 0
    glEnable(GL_LIGHT1);           // Ativa fonte de luz 1
    glEnable(GL_COLOR_MATERIAL);   // Permite que cores influenciem o material
    glClearColor(0.6f, 0.85f, 1.0f, 1.0f);  // Cor de fundo do ambiente (azul claro)

    // Configuração da luz 0
    GLfloat light0_pos[] = { 0.0, 0.0, 8.0, 0.0 };
    GLfloat light0_amb[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light0_diff[] = { 0.8, 0.8, 0.8, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);

    // Configuração da luz 1
    GLfloat light1_pos[] = { -1.0, 1.0, -1.0, 0.0 };
    GLfloat light1_diff[] = { 0.6, 0.6, 0.6, 1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diff);

    // Define material branco como padrão (ideal para texturização)
    float white[4] = { 1, 1, 1, 1 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

    // Inicializa gerador de números aleatórios
    srand(time(NULL));

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-10, 5.0, 0.0,  
              mae.posicaoX, 0.0, mae.posicaoZ,
              0.0, 1.0, 0.0);

     glPushMatrix();
            mae.Desenhar();
            mae.HitBox();
    glPopMatrix();

        glPushMatrix();
            desenharGelo();
    glPopMatrix();


    std::cout << mae.posicaoX <<std::endl;;
    glutSwapBuffers();
}

// Função de callback para redimensionamento da janela.
// Atualiza a matriz de projeção com perspectiva e redefine o viewport para manter a proporção da tela.

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}

// Função de callback para teclas especiais pressionadas (setas do teclado).
// Ativa os flags de movimento do pinguim para frente, trás e rotações esquerda/direita.


void keyboardSpecial(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            mae.RecebeAndandoFrente(true);
            break;
        case GLUT_KEY_DOWN:
            mae.RecebeAndandoTras(true);
            break;
        case GLUT_KEY_LEFT:
            mae.RecebeVirandoEsquerda(true);
            break;
        case GLUT_KEY_RIGHT:
            mae.RecebeVirandoDireita(true);
            break;
    }
}

// Função de callback para teclas especiais soltas.
// Desativa os flags de movimento do pinguim quando as teclas de direção são liberadas.

void keyboardSpecialUp(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            mae.RecebeAndandoFrente(false);
            break;
        case GLUT_KEY_DOWN:
           mae.RecebeAndandoTras(false);
            break;
        case GLUT_KEY_LEFT:
           mae.RecebeVirandoEsquerda(false);
            break;
        case GLUT_KEY_RIGHT:
            mae.RecebeVirandoDireita(false);
            break;
    }
}



 

void update(int value) {
    if (mae.RetornaVirandoEsquerda()) 
    {
        mae.angle -= mae.rotacaoVel;
    }

    if (mae.RetornaVirandoDireita()) 
    {
        mae.angle += mae.rotacaoVel;
    }

    float rad = mae.angle * M_PI / 180.0f;

        float novaX, novaZ;
        if (mae.RetornaAndandoFrente()) 
        {
            novaX = mae.posicaoX + mae.velocidade * sin(rad);
            novaZ =  mae.posicaoZ + mae.velocidade * cos(rad);
            // Só atualiza se a nova posição estiver dentro dos limites do gelo [-5, 5]
            if (fabs(novaX) <= 15.0f && fabs(novaZ) <= 15.0f)
            {
                mae.posicaoX = novaX;
                 mae.posicaoZ = novaZ;
            }
        }
        if (mae.RetornaAndandoTras()) 
        {
            novaX = mae.posicaoX - mae.velocidade * sin(rad);
            novaZ =  mae.posicaoZ - mae.velocidade * cos(rad);
            // Só atualiza se a nova posição estiver dentro dos limites do gelo [-5, 5]
            if (fabs(novaX) <= 15.0f && fabs(novaZ) <= 15.0f)
            {
                mae.posicaoX = novaX;
                 mae.posicaoZ = novaZ;
            }
        }

        
    glutTimerFunc(16, update, 0);
    glutPostRedisplay();
}

// Função de atualização do estado do jogo chamada periodicamente (~60 FPS).
// Controla o tempo do jogo, energia do filhote e movimentação do pinguim mãe com base nos flags de entrada.
// Restringe o movimento dentro dos limites do cenário e verifica colisões com buracos, definindo game over.
// Gera e reposiciona peixes aleatoriamente quando necessário.
// Atualiza a dinâmica dos buracos, removendo e adicionando novos a cada 3 segundos.
// Verifica a captura do peixe pela mãe e a entrega do peixe ao filhote para recarregar energia.
// Agenda a próxima chamada de update e solicita redesenho da tela.



// Função principal que inicializa a janela e o contexto OpenGL/GLUT.
// Configura o modo de exibição, tamanho da janela, e fullscreen.
// Inicializa o estado do jogo e registra callbacks de display, reshape, teclado e timer.
// Carrega as texturas necessárias para o jogo.
// Entra no loop principal do GLUT, iniciando a execução do programa.

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Jogo do Pinguim 3D");
    glutFullScreen();
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialUpFunc(keyboardSpecialUp);
    glutSpecialFunc(keyboardSpecial);
    glutTimerFunc(0, update, 0);
    //loadTextures();
    glutMainLoop();
    return 0;
}