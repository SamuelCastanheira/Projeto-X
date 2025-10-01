// Inclusão de bibliotecas padrão do OpenGL, utilitários de tempo, matemática e carregamento de imagens (stb_image)
#include <GL/glut.h>
#include <GL/glext.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"  // <-- A referencia seria do src/stb_image.h ? então talvez devesse ser src/stb_image.h

// Identificadores de textura utilizados no cenário e objetos
int texID[9]; 

// Nomes dos arquivos de textura utilizados para aplicar materiais em objetos e no ambiente
char* textureFileNames[9] = {   
    "textura\\gelo.jpg",
    "textura\\agua.jpg",
    "textura\\escama.jpg",
    "textura\\posx.jpg",
    "textura\\negx.jpg",
    "textura\\posy.jpg",
    "textura\\negy.jpg",
    "textura\\posz.jpg",
    "textura\\negz.jpg"
};

// Variáveis para controle de rotação da câmera ou cenário
float rotateX = 0; 
float rotateY = 0;  

// Definições e variáveis globais do jogo
#define QNT_BURACOS  5
#define POSICOES_BURACOS  20
#define QNT_PEIXES 5

// Posição e orientação da personagem principal (mãe pinguim)
float maePosX = 3.0f, maePosZ = 3.0f, maeAngle = 0.0f;

// Estados e controles do jogo
bool temPeixe = false;
float filhoteEnergia = 60.0f;
float tempoJogo = 0.0f;
bool PeixeExiste[QNT_BURACOS];
float peixeX[QNT_PEIXES];
float peixeZ[QNT_PEIXES];
bool buraco[POSICOES_BURACOS][POSICOES_BURACOS] = {false};

// Flags de controle de movimento do personagem
bool andandoFrente = false;
bool andandoTras = false;
bool virandoEsquerda = false;
bool virandoDireita = false;

// Coordenadas para lógica dos buracos ou movimentação
int eixoX=0;
int eixoZ=0;

// Controle de tempo para eventos do jogo
float tempoDesdeUltimaTrocaBuracos = 0.0f;
float tempoPeixe = 0.0f;
bool peixeAtivo = true;
bool peixeVisivel = true;
bool gameOver = false;
int iteradorAza = 0;
float yMae;

// Declaração antecipada de função que desenha o peixe
void desenharPeixe(float, float);

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

    // Define posições aleatórias iniciais para os peixes
    for (int i = 0; i < QNT_PEIXES; i++) {
        peixeX[i] = rand() % 20 - 11;
        peixeZ[i] = rand() % 20 - 11;
        PeixeExiste[i] = true;
    }
}




// Função responsável por desenhar o pinguim filhote e o pinguim mãe em uma determinada posição (x, z) do cenário.
// O pinguim é composto por primitivas 3D: esferas para o corpo, cabeça, olhos, asas e patas; cone para o bico.
// Quando em movimento, as asas do pinguim adulto se movimentam com base em uma função seno.
// Se o pinguim adulto estiver carregando um peixe, este também é desenhado na parte frontal.
void desenharPinguim(float x, float z, bool filhote) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    if (!filhote) glRotatef(maeAngle, 0, 1, 0);

    float scale = filhote ? 0.7f : 1.0f;
    glTranslatef(0.0f, 1.4f * scale, 0.0f); // Alinhamento dos pés com Y=0

    glColor3f(0.1f, 0.1f, 0.1f); // Corpo
    glPushMatrix();
    glScalef(1.0f * scale, 1.6f * scale, 0.7f * scale);
    glutSolidSphere(1.0, 40, 40);
    glPopMatrix();

    glColor3f(0.95f, 0.95f, 0.95f); // Barriga
    glPushMatrix();
    glTranslatef(0.0f, -0.2f * scale, 0.65f * scale);
    glScalef(0.7f * scale, 0.9f * scale, 0.1f * scale);
    glutSolidSphere(1.0, 40, 40);
    glPopMatrix();

    glColor3f(0.1f, 0.1f, 0.1f); // Cabeça
    glPushMatrix();
    glTranslatef(0.0f, 1.3f * scale, 0.0f);
    glScalef(0.8f * scale, 0.8f * scale, 0.7f * scale);
    glutSolidSphere(0.6 * scale, 40, 40);
    glPopMatrix();

    glColor3f(1.0f, 0.5f, 0.0f); // Bico
    glPushMatrix();
    glTranslatef(0.0f, 1.2f * scale, 0.5f * scale);
    glScalef(1.0f * scale, 1.0f * scale, 1.5f * scale);
    glutSolidCone(0.12 * scale, 0.3 * scale, 20, 20);
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f); // Olhos brancos
    glPushMatrix();
    glTranslatef(-0.18f * scale, 1.35f * scale, 0.45f * scale);
    glScalef(0.1f * scale, 0.1f * scale, 0.1f * scale);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.18f * scale, 1.35f * scale, 0.45f * scale);
    glScalef(0.1f * scale, 0.1f * scale, 0.1f * scale);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f); // Pupilas
    glPushMatrix();
    glTranslatef(-0.18f * scale, 1.35f * scale, 0.5f * scale);
    glScalef(0.04f * scale, 0.04f * scale, 0.04f * scale);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.18f * scale, 1.35f * scale, 0.5f * scale);
    glScalef(0.04f * scale, 0.04f * scale, 0.04f * scale);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    glColor3f(0.1f, 0.1f, 0.1f); // Asas
    glPushMatrix();
    
    if (andandoFrente || andandoTras)
    {
        yMae = sin(iteradorAza* 0.009)*30;
        iteradorAza++;
    }

    glTranslatef(-0.9f * scale, 0.1f * scale , 0.0f);
    if (!filhote) glRotatef(-yMae, 1, 0, 0);
    glRotatef(-30, 0, 0, 1);
    glScalef(0.25f * scale, 1.0f * scale, 0.15f * scale);
    glutSolidSphere(1.0, 30, 30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.9f * scale, 0.1f * scale , 0.0f);
    if (!filhote) glRotatef(yMae, 1, 0, 0);
    glRotatef(30, 0, 0, 1);
    glScalef(0.25f * scale, 1.0f * scale, 0.15f * scale);
    glutSolidSphere(1.0, 30, 30);
    glPopMatrix();

    glColor3f(1.0f, 0.7f, 0.0f); // Patas
    glPushMatrix();
    glTranslatef(-0.35f * scale, -1.4f * scale, 0.2f * scale);
    glScalef(0.5f * scale, 0.15f * scale, 0.4f * scale);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.35f * scale, -1.4f * scale, 0.2f * scale);
    glScalef(0.5f * scale, 0.15f * scale, 0.4f * scale);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    if (temPeixe && !filhote) {
        glPushMatrix();
        glTranslatef(0.0f, 1.7f * scale, 1.2f * scale);
        glRotatef(90,0,1,0);
        desenharPeixe(0,0);
        glPopMatrix();
    }
    glPopMatrix();
}

// Função responsável por desenhar um peixe em uma determinada posição (x, z) do cenário.
// O peixe é formado por uma esfera texturizada representando o corpo, um cone como cauda e esferas para os olhos.
// A textura aplicada simula escamas, e a função usa quadrics (GLU) para texturização.
void desenharPeixe(float x, float z) {
    glPushMatrix();
    glTranslatef(x,0.0,z);
    glColor3f(0.0f, 0.5f, 0.0f);
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f); // Olhos brancos
        glPushMatrix();
            glTranslatef(x+0.2, -0.42f, z+0.15);
            glScalef(0.1, 0.1, 0.1);
           
            glutSolidSphere(1.0, 20, 20);
            
        glPopMatrix();
        glPushMatrix();
            glTranslatef(x+0.2, -0.42f, z-0.15);
            glScalef(0.1, 0.1, 0.1);
            glutSolidSphere(1.0, 20, 20);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(x, -0.5f, z);
            glScalef(0.5f, 0.3f, 0.2f);
            glColor3f(1.0f, 1.0f, 1.0f);
             glEnable(GL_TEXTURE_2D);
             GLUquadric* quad = gluNewQuadric();
            gluQuadricTexture(quad, GL_TRUE);
            glBindTexture(GL_TEXTURE_2D,texID[2]);
            gluSphere(quad, 1, 20, 20); 
        glPopMatrix();
            glColor3f(1.0f, 1.0f, 1.0f);
            glPushMatrix();
                glTranslatef(x-0.65, -0.5f, z);
                glRotatef(90, 0, 1, 0);
                glScalef(1,2,1);
                glutSolidCone(0.1, 0.2, 20, 20);
                gluDeleteQuadric(quad);
                glDisable(GL_TEXTURE_2D);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}


// Função que desenha um buraco na superfície, utilizado como obstáculo ou elemento interativo.
// O buraco é desenhado como uma esfera achatada, com textura aplicada simulando água.
// Utiliza GLU quadric para aplicar textura na esfera.
void desenharBuraco(float x, float z) {
    glEnable(GL_TEXTURE_2D);
    GLUquadric* quad = gluNewQuadric();
gluQuadricTexture(quad, GL_TRUE);
    glBindTexture( GL_TEXTURE_2D, texID[1]);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    glScalef(2.0f, 0.1f, 2.0f);
   gluSphere(quad, 0.8, 50, 50);
   gluDeleteQuadric(quad);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


// Função que desenha o chão do ambiente (gelo) como um grande cubo achatado com textura de gelo aplicada.
// As seis faces do cubo são desenhadas manualmente com mapeamento de textura e normais para iluminação.
void desenharGelo() {
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(40.0f, 0.1f, 40.0f);
    glBindTexture( GL_TEXTURE_2D, texID[0]);
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
 

// Função que desenha a skybox (caixa de céu) ao redor da cena, simulando um ambiente fechado com imagens panorâmicas.
// Cada face da skybox (direita, esquerda, frente, trás, topo e base) recebe uma textura diferente para criar imersão visual.
// A escala e rotação da skybox são ajustadas para envolver toda a cena.
void desenharSkybox() {
    float s = 20.0f;

    glPushMatrix();
    glRotatef(180, 0, 0, 1);
    glScalef(s, s, s);

    glEnable(GL_TEXTURE_2D);

    glColor3f(1, 1, 1);

    // DIREITA (+X)
glBindTexture(GL_TEXTURE_2D, texID[3]);
glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f( 1, -1,  1); 
    glTexCoord2f(1, 0); glVertex3f( 1, -1, -1); 
    glTexCoord2f(1, 1); glVertex3f( 1,  1, -1); 
    glTexCoord2f(0, 1); glVertex3f( 1,  1,  1); 
glEnd();


    // TRÁS (-Z)
    glBindTexture(GL_TEXTURE_2D, texID[8]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( 1, -1, -1); 
        glTexCoord2f(1, 0); glVertex3f(-1, -1, -1); 
        glTexCoord2f(1, 1); glVertex3f(-1,  1, -1); 
        glTexCoord2f(0, 1); glVertex3f( 1,  1, -1); 
    glEnd();

    // ESQUERDA (-X)
    glBindTexture(GL_TEXTURE_2D, texID[4]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-1, -1, -1);
        glTexCoord2f(1, 0); glVertex3f(-1, -1,  1); 
        glTexCoord2f(1, 1); glVertex3f(-1,  1,  1); 
        glTexCoord2f(0, 1); glVertex3f(-1,  1, -1);
    glEnd();

    // FRENTE (+Z)
    glBindTexture(GL_TEXTURE_2D, texID[7]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-1, -1,  1); 
        glTexCoord2f(1, 0); glVertex3f( 1, -1,  1); 
        glTexCoord2f(1, 1); glVertex3f( 1,  1,  1); 
        glTexCoord2f(0, 1); glVertex3f(-1,  1,  1); 
    glEnd();

    // TOPO (+Y)
    glBindTexture(GL_TEXTURE_2D, texID[5]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-1, 1, -1);
        glTexCoord2f(1, 0); glVertex3f( 1, 1, -1);
        glTexCoord2f(1, 1); glVertex3f( 1, 1,  1); 
        glTexCoord2f(0, 1); glVertex3f(-1, 1,  1); 
    glEnd();

    // BAIXO (-Y)
    glBindTexture(GL_TEXTURE_2D, texID[6]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-1, -1,  1); 
        glTexCoord2f(1, 0); glVertex3f( 1, -1,  1); 
        glTexCoord2f(1, 1); glVertex3f( 1, -1, -1); 
        glTexCoord2f(0, 1); glVertex3f(-1, -1, -1); 
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


// Função responsável por carregar e configurar as 9 texturas utilizadas no jogo, incluindo gelo, água, escama, e as faces da skybox.
// As texturas são carregadas com stb_image, associadas a identificadores OpenGL e configuradas com filtros lineares e mipmaps.

void loadTextures() {
	int width, height, nrChannels;
	unsigned char *data;

	glGenTextures(9, (GLuint*)texID);

	for(int i = 0; i < 9;i++)
	{
	glBindTexture(GL_TEXTURE_2D, texID[i]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load(textureFileNames[i], &width, &height, &nrChannels, 0);

	if (data)
	{
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	    glTexParameteri  (GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );
	}
	else
	{
		 printf("Failed to load texture\n");
	}
	stbi_image_free(data);
	}
}


// Função principal de renderização do jogo. 
// Desenha o skybox, o gelo (chão), os buracos, os peixes e os pinguins (adulto e filhote).
// Controla o posicionamento e visibilidade dos elementos com base nas variáveis de estado do jogo.

void jogo(){
    glPushMatrix();
    desenharSkybox();
    glEnable(GL_TEXTURE_2D);
    desenharGelo();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
        
        for (int i = -POSICOES_BURACOS/2; i < POSICOES_BURACOS/2; i++){
            for (int j = -POSICOES_BURACOS/2; j < POSICOES_BURACOS/2; j++){
                if (buraco[i + POSICOES_BURACOS/2][j + POSICOES_BURACOS/2]) {
                    
                    glPushMatrix();
                         desenharBuraco(i, j);
                   glPopMatrix();
                   
                }
            }
        }
    glPopMatrix();


        
        for (int i=0;i<QNT_PEIXES;i++)
        {
            if (PeixeExiste[i])
            {
                glPushMatrix();
                glTranslatef(peixeX[i], 0.85, peixeZ[i]);
                        glRotatef(90,0,1,0);
                    desenharPeixe(0, 0);
                glPopMatrix();
            }
        }


    glPushMatrix();
    desenharPinguim(0.0f, 0.0f, true);
    desenharPinguim(maePosX, maePosZ, false);
    glPopMatrix();

    glPopMatrix();
}


// Função de exibição (callback do OpenGL) responsável por renderizar os quatro pontos de vista diferentes do jogo na tela.
// Cada quadrante da janela recebe uma viewport com uma câmera distinta observando a cena.
// Em caso de fim de jogo (gameOver), exibe uma mensagem de "GAME OVER" e finaliza a aplicação.

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (gameOver) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDisable(GL_LIGHTING);
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(-0.15f, 0.0f);
        const char* msg = "GAME OVER! Reinicie o jogo para tentar novamente.";
        for (const char* c = msg; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
        glEnable(GL_LIGHTING);
        exit(0);
        glutSwapBuffers();
        return;
    } else {

    // Resto da câmera, cenário e desenho do jogo
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);

    glViewport(w/2,h/2, w/2, h/2);
    glLoadIdentity();
    gluLookAt(0.0, 15.0, 0.0,
             maePosX, 0.0, maePosZ,
            0.0, 0.0, 1.0);
            
    jogo();

    glViewport(w/2, 0, w/2, h/2);
    glLoadIdentity();
    gluLookAt(0.0, 2.0, 15,  
              maePosX, 0.0, maePosZ,
              0.0, 1.0, 0.0);
    jogo();

    glViewport(0, h/2, w/2, h/2);
    glLoadIdentity();
    gluLookAt(3.0, 5.0, 10.0,  
              maePosX, 0.0, maePosZ,
              0.0, 1.0, 0.0);
    jogo();


    glViewport(0, 0, w/2, h/2);
    glLoadIdentity();
 
    gluLookAt(-10, 5.0, 0.0,  
              maePosX, 0.0, maePosZ,
              0.0, 1.0, 0.0);
    jogo();
    
    }
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
            andandoFrente = true;
            break;
        case GLUT_KEY_DOWN:
            andandoTras = true;
            break;
        case GLUT_KEY_LEFT:
            virandoEsquerda = true;
            break;
        case GLUT_KEY_RIGHT:
            virandoDireita = true;
            break;
    }
}

// Função de callback para teclas especiais soltas.
// Desativa os flags de movimento do pinguim quando as teclas de direção são liberadas.

void keyboardSpecialUp(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            andandoFrente = false;
            //eixoX =0;
 
            break;
        case GLUT_KEY_DOWN:
            andandoTras = false;
         
            //eixoX=0;
            break;
        case GLUT_KEY_LEFT:
            virandoEsquerda = false;
    
            break;
        case GLUT_KEY_RIGHT:
            virandoDireita = false;
     
            break;
    }
}

// Função de atualização do estado do jogo chamada periodicamente (~60 FPS).
// Controla o tempo do jogo, energia do filhote e movimentação do pinguim mãe com base nos flags de entrada.
// Restringe o movimento dentro dos limites do cenário e verifica colisões com buracos, definindo game over.
// Gera e reposiciona peixes aleatoriamente quando necessário.
// Atualiza a dinâmica dos buracos, removendo e adicionando novos a cada 3 segundos.
// Verifica a captura do peixe pela mãe e a entrega do peixe ao filhote para recarregar energia.
// Agenda a próxima chamada de update e solicita redesenho da tela.

void update(int value) {
    if (gameOver) exit(0); // Para tudo se o jogo acabou

    tempoJogo += 0.016f;
    filhoteEnergia -= 0.016f;

    // Movimento contínuo da pinguim mãe
float velocidade = 0.16f;
float rotacaoVel = 2.5f;

if (virandoEsquerda) maeAngle -= rotacaoVel;
if (virandoDireita) maeAngle += rotacaoVel;

float rad = maeAngle * M_PI / 180.0f;

    float novaX, novaZ;
    if (andandoFrente) {
        novaX = maePosX + velocidade * sin(rad);
        novaZ = maePosZ + velocidade * cos(rad);
        // Só atualiza se a nova posição estiver dentro dos limites do gelo [-5, 5]
        if (fabs(novaX) <= 15.0f && fabs(novaZ) <= 15.0f)
            maePosX = novaX, maePosZ = novaZ;
    }
    if (andandoTras) {
        novaX = maePosX - velocidade * sin(rad);
        novaZ = maePosZ - velocidade * cos(rad);
        // Só permite o movimento se estiver dentro da área do gelo
        if (fabs(novaX) <= 15.0f && fabs(novaZ) <= 15.0f)
            maePosX = novaX, maePosZ = novaZ;
    }

    for (int i=0;i<POSICOES_BURACOS;i++)
    {
        for (int j=0;j<POSICOES_BURACOS;j++)
        {
            if (buraco[i][j])
            {
                float dx = novaX - (i - POSICOES_BURACOS/2);
                float dz = novaZ - (j - POSICOES_BURACOS/2);
                if ( dx*dx + dz*dz < 0.8f)
                {
                    gameOver = true;
                    return;  // para o update aqui mesmo
                }
            }
        }
    }
    
    if (filhoteEnergia <= 0 || tempoJogo >= 300) exit(0);

    tempoPeixe += 0.016f;



// Se não tem peixe visível nem carregado pela mãe, gera um novo peixe
if (!temPeixe) {
    int tentativas = 0;
    for (int p=0;p<QNT_PEIXES;p++)
    {
        if (!PeixeExiste[p]){
            while (tentativas < 100) 
            {
                int i = rand() % POSICOES_BURACOS;
                int j = rand() % POSICOES_BURACOS;

                if (!buraco[i][j]) {
                    peixeX[p] = (i - 11.0f);
                    peixeZ[p] = (j - 11.0f);
                    PeixeExiste[p] = true;
                    peixeVisivel = true;
                    tempoPeixe = 0.0f;
                    break;
                }
                tentativas++;
            }
        }
    }
}
   
// Acumula tempo desde a última troca
tempoDesdeUltimaTrocaBuracos += 0.016f;

// Executa a troca de buracos a cada 3 segundos
if (tempoDesdeUltimaTrocaBuracos >= 3.0f) {
    tempoDesdeUltimaTrocaBuracos = 0.0f;

    // Conta os buracos existentes
    int totalBuracos = 0;
    for (int i = 0; i < POSICOES_BURACOS; i++)
        for (int j = 0; j < POSICOES_BURACOS; j++)
            if (buraco[i][j]) totalBuracos++;

    // Remove 1 buraco aleatoriamente (se houver)
    if (totalBuracos > 0) {
        int tentativas = 0;
        while (tentativas < 100) {
            int i = rand() % POSICOES_BURACOS;
            int j = rand() % POSICOES_BURACOS;
            if (buraco[i][j]) {
                buraco[i][j] = false;
                totalBuracos--;
                break;
            }
            tentativas++;
        }
    }

    // Adiciona novo buraco se total ainda for < 5
        int tentativas = 0;
        bool adicionou = false;
        while ( !adicionou && (totalBuracos < QNT_BURACOS) && (tentativas < 100)) {
            int i = rand() % POSICOES_BURACOS;
            int j = rand() % POSICOES_BURACOS;
            float x = i - POSICOES_BURACOS/2;
            float z = j - POSICOES_BURACOS/2;

            // Impede buraco sob o pinguim filhote (0,0) ou o peixe
            if (!buraco[i][j] &&!(x == 0.0f && z == 0.0f)){
                for (int p=0;p<QNT_PEIXES;p++){
                    if (!(fabs(x - peixeX[p]) < 1.0f && fabs(z - peixeZ[p]) < 0.5f))
                    {
                        buraco[i][j] = true;
                        adicionou = true;
                        totalBuracos++;
                        break;
                    }
                }
            }
            tentativas++;
        }
}

        float dx;
        float dz;

for (int i=0;i<QNT_PEIXES;i++){
        dx = peixeX[i] - maePosX;
        dz = peixeZ[i] - maePosZ;
    if (!temPeixe && peixeVisivel && dx*dx + dz*dz < 0.5f) {
        temPeixe = true;
        PeixeExiste[i] = false;
        printf("Distancia: %f\n", sqrt(dx*dx + dz*dz));
        peixeVisivel = false;
        tempoPeixe = 0.0f;
    }
}

    dx = 0.0f - maePosX;
    dz = 0.0f - maePosZ;
    if (temPeixe && dx*dx + dz*dz < 0.5f) {
        temPeixe = false;
        filhoteEnergia = 60.0f;
        
    }

    glutTimerFunc(16, update, 0);
    glutPostRedisplay();
}

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
    loadTextures();
    glutMainLoop();
    return 0;
}