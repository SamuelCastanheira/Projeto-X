#include <string>
#include "../uteis/Coordenada.hpp"
#include "../uteis/ElementoEnum.hpp"

class ElementoDoCenario {
  public:
    virtual std::string getId() = 0;
    virtual ElementoEnum getTipo() = 0;
    virtual Coordenada getPosicao() = 0;
    virtual void setPosicao(Coordenada novaPosicao) = 0;
    virtual void desenhar() = 0;
};