#include "Personagem.hpp"

class Pinguim : Personagem
{
protected:
	void Patas();
	void Torso();
	void Cabeca();
	void Bico();
	void Olhos();
	void Asas();
	void Peixe();

	
public:
	
	float posicaoX;
	float posicaoY;
	float posicaoZ; 
	float angle;

	bool capturouPeixe;
	float scale;
	float velocidade;
	float rotacaoVel;

	bool andandoFrente;
	bool andandoTras;
	bool virandoEsquerda;
	bool virandoDireita;

	Pinguim(float x, float z);
	void Desenhar() override;
	void HitBox() override;
	bool RetornaCapturouPeixe();
	void RecebeCapturouPeixe(bool);

	 // Setters (Recebe)
    void RecebeAndandoFrente(bool valor);
    void RecebeAndandoTras(bool valor);
    void RecebeVirandoEsquerda(bool valor);
    void RecebeVirandoDireita(bool valor);

    // Getters (Retorna)
    bool RetornaAndandoFrente() const;
    bool RetornaAndandoTras() const;
    bool RetornaVirandoEsquerda() const;
    bool RetornaVirandoDireita() const;
	
};
