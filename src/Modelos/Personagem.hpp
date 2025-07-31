#pragma once


	class Personagem
	{
	public:
		~Personagem() = default;
		virtual void Desenhar() = 0;
		virtual void HitBox() = 0;
	};

