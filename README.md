Jogo do Piguim - Multiplayer
---
Este é um projeto que tem o objetivo de tornar um jogo single player em multiplayer. O código base foi desenvolvido como um dos projetos de entrega de disciplina do curso pelos integrantes citados abaixo: 

* Samuel Rocha Castanheira
* Vicente Lopes

Os demais participantes citados abaixo são responsáveis por tornar o jogo multiplayer:
* Samuel Rocha Castanheira
* Henrique Oliveira

---

## Pré-requisitos (Obrigatório)
Este projeto é desenvolvido e compilado usando o ambiente **MSYS2** no Windows. Você **precisa** dele para que o CMake encontre o compilador e as bibliotecas Boost corretas.
1.  **Instale o MSYS2:**
    * Vá para [msys2.org](https://www.msys2.org/) e faça a instalação.

2.  **Abra o terminal MSYS2 MINGW64:**
    * No Menu Iniciar, abra o terminal `MSYS2 MINGW64` (o de ícone roxo 💜).

3.  **Instale as Ferramentas (Compilador, Boost, CMake):**
    * Dentro do terminal MINGW64, rode o seguinte comando para instalar tudo:
        ```bash
        pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-boost mingw-w64-x86_64-cmake
        ```
    *(Nosso ambiente de desenvolvimento atual usa GCC/G++ 15.2.0 ou superior).*

## Instruções de compilação
Alterada por causa de problemas com compiladores e bibliotecas boost
Necessário refazer as instruções

Estamos construindo o projeto com o compilador MSYS2 GCC/G++ 15.2.0
**Importante:** Execute todos os comandos a partir do terminal **MSYS2 MINGW64**.

```bash
# 1. Clone o repositório (se ainda não o fez)
# git clone ...
# cd Jogo-do-Piguim-Multiplayer

# 2. Crie a pasta de build
mkdir build

# 3. Entre na pasta
cd build

# 4. Configure o projeto com o CMake
# (Isso procura o g++ e a Boost que o pacman instalou)
cmake .. -G "MinGW Makefiles"

# 5. Compile o projeto
cmake --build .
```
**Bases de rede**

Por questões de conveniencia a rede do projeto será implementada com o uso da biblioteca Boost.Asio, pois com ela evitamos descrever as premissas de redes para mais de uma plataforma (LINUX/WINDOWS)

***Versionamento :***
> 0.1: Inclusões de cabeçalhos e corpo básico da função iniciar


**Melhorias na implementação do jogo**
> 0.1: Tornar o jogo transparente com orientações a objeto ?