#include <list>
#include "../interface/ElementoDocenario.hpp"

class Cenario  {
    public:
        void Desenhar();
        void AdicionarElemento_cenario(ElementoDoCenario novoElemento);
        void RemoverElemento_do_Cenario(std::String id);
        void setUpCenario(Camera);

    private:
        //-Camera
         std::list<ElementoDoCenario> elementos;
};