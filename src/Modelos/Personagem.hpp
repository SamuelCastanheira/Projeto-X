#pragma once
#include "../interface/ElementoDocenario.hpp"

	class Personagem : ElementoDoCenario
	{
	public:
		~Personagem() = default;
		virtual void Desenhar() = 0;
		virtual void HitBox() = 0;
	};

