#include <GL/glut.h>
#include <GL/glext.h>
#include <cmath>
#include "Pinguim.hpp"

extern int iteradorAza;

Pinguim::Pinguim(float x, float z, float scale)
{
    this->posicaoX = x;
    this->posicaoY = 0;
    this->posicaoZ = z;
    this->angle = 0;
    this->scale = scale;
    this->capturouPeixe = false;
    this->velocidade = 0.16f;
    this->rotacaoVel = 2.5f;
}

Pinguim::Pinguim(float x, float z)
{
    this->posicaoX = x;
    this->posicaoY = 0;
    this->posicaoZ = z;
    this->angle = 0;
    this->scale = 1;
    this->capturouPeixe = false;
    this->velocidade = 0.16f;
    this->rotacaoVel = 2.5f;
}

//Definições Geométricas
void Pinguim::Patas() 
{
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
}

void Pinguim::Torso()
{
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
}

void Pinguim::Cabeca()
{
    glColor3f(0.1f, 0.1f, 0.1f); // Cabe�a
    glPushMatrix();
    glTranslatef(0.0f, 1.3f * scale, 0.0f);
    glScalef(0.8f * scale, 0.8f * scale, 0.7f * scale);
    glutSolidSphere(0.6 * scale, 40, 40);
    glPopMatrix();

    this->Olhos();
    this->Bico();

}

void Pinguim::Bico() 
{
    glColor3f(1.0f, 0.5f, 0.0f); // Bico
    glPushMatrix();
    glTranslatef(0.0f, 1.2f * scale, 0.5f * scale);
    glScalef(1.0f * scale, 1.0f * scale, 1.5f * scale);
    glutSolidCone(0.12 * scale, 0.3 * scale, 20, 20);
    glPopMatrix();
}

void Pinguim::Olhos()
{
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
    glTranslatef(-0.18f * scale, 1.35f * scale, 0.52f * scale);
    glScalef(0.04f * scale, 0.04f * scale, 0.04f * scale);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.18f * scale, 1.35f * scale, 0.52f * scale);
    glScalef(0.04f * scale, 0.04f * scale, 0.04f * scale);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
}

void Pinguim::Asas()
{
    glColor3f(0.1f, 0.1f, 0.1f); // Asas
    glPushMatrix();

     if (this->andandoFrente || this->andandoTras)
     {
         this->posicaoY = sin(iteradorAza * 0.1) * 30;
         iteradorAza++;
     }

    glTranslatef(-0.9f * scale, 0.1f * scale, 0.0f);
    glRotatef(posicaoY, 1, 0, 0);
    glRotatef(-30, 0, 0, 1);
    glScalef(0.25f * scale, 1.0f * scale, 0.15f * scale);
    glutSolidSphere(1.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.9f * scale, 0.1f * scale, 0.0f);
    glRotatef(posicaoY, 1, 0, 0);
    glRotatef(30, 0, 0, 1);
    glScalef(0.25f * scale, 1.0f * scale, 0.15f * scale);
    glutSolidSphere(1.0, 30, 30);
    glPopMatrix();
}

void Pinguim::Peixe()
{
    glPushMatrix();
    glTranslatef(0.0f, 1.7f * scale, 1.2f * scale);
    glRotatef(90, 0, 1, 0);
    //desenharPeixe(0, 0);
    glPopMatrix();
}

void Pinguim::Desenhar()  {
        glPushMatrix();
        glTranslatef(posicaoX, 0.0f, posicaoZ);
        glRotatef(angle, 0, 1, 0);
        glTranslatef(0.0f, 1.4f * scale, 0.0f); // Alinhamento dos p�s com Y=0

        this->Cabeca();
        this->Torso();
        this->Patas();
        this->Asas();
        if (capturouPeixe) 
        {
            this->Peixe();
        }
        glPopMatrix();
}

void Pinguim::HitBox()
{
    glPushMatrix();
    glTranslatef(posicaoX, 0.0f, posicaoZ);
    glTranslatef(0.0f, 1.4f * scale, 0.0f);
    glScalef(1,2,0.8);
    glColor3f(1,0,0);
    glutWireCube(2);
    glPopMatrix();
}

//Setters
void Pinguim::RecebeAndandoFrente(bool valor) {
    andandoFrente = valor;
}

void Pinguim::RecebeAndandoTras(bool valor) {
    andandoTras = valor;
}

void Pinguim::RecebeVirandoEsquerda(bool valor) {
    virandoEsquerda = valor;
}

void Pinguim::RecebeVirandoDireita(bool valor) {
    virandoDireita = valor;
}

void Pinguim::RecebeCapturouPeixe(bool captura)
{
    this->capturouPeixe = captura ;
}

// Getters
bool Pinguim::RetornaAndandoFrente() const {
    return andandoFrente;
}

bool Pinguim::RetornaAndandoTras() const {
    return andandoTras;
}

bool Pinguim::RetornaVirandoEsquerda() const {
    return virandoEsquerda;
}

bool Pinguim::RetornaVirandoDireita() const {
    return virandoDireita;
}

bool Pinguim::RetornaCapturouPeixe()
{
    return this->capturouPeixe;
}

ElementoEnum Pinguim::getTipo()
{
    return this->tipo;
}