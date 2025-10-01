#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>

/*
    Tentativa de implementação de servidor UDP. Nosso servidor é experimental e foi concebido depois de conversa com um amigo,
    portanto possívelmente haverá muitas modificações.
*/

constexpr int PORTA = 4040 // Depois vejo qual será a porta correta
constexpr int BUFFER_SIZE = 1024

int conexaoplayer(){
    /*Conecta e gerenciar os clientes em cada uma das threads */
    /*Pensando em alto nível:
        Depois que a conexão ser estabelecida, devo colocar este cliente em um vetor de clientes, onde cada um dos clientes
        tem um ID unico ou manipulador, para que seja possível alterar os estados dos clientes quando necessário.
        
        Quando um cliente que já está com conexão estabelecida envia um pacote de rede, isto pode significar duas coisas:
        1. O cliente está online;
        2. O cliente cliente interagiu no mapa

        Para cada caso existe ações diferentes, mas para o caso 1 a ação pode ser sobreescrita pelo caso 2, isto ajuda
        a evitar problemas com alto tráfego no nosso servidor.
        
        Problema 1: Como nossa conexão é UDP, eu perco algumas garantias. Desta forma preciso criar este conjunto de
        garantias de forma manual.
        Problema 2: Alto tráfego no servidor, pode ser resolvido com a sobreescrita do caso caso 2, mas a experiência
        vai mostrar o que ocorre de fato.
        Problema 3: Multiplos players interagindo no mesmo mapa provoca inconsistencias nos estados e ausencia de recursos.
        O problema é famoso e tem vários nomes.
        Problema 4: Não existem muitos exemplos usando classes, apesar de classes simplificar muito o a implementação,
        tornar o servidor orientado a objetos o mais rápido possível depois de validar o primeiro funcionamento.
        Problema 5: Não sei ainda vamos ver...

    */
}

int iniciar(){
    /*Inicia o servidor do jogo*/
    try
    {
        boost::asio::io_context io_context;
        boost::asio::ip::udp::socket socket(io_context, udp::endpoint(udp::v4(), PORTA));
        std::cout << "Servidor pronto e disponivel na porta: " << PORTA  << "\n";

        while(true){
            /*
            Isso aqui é muito básico. Na verdade é necessário colocar threads, depois faço isso
            Aqui eu chamo a função conexaoplayer() em uma thread, irei verificar os pametros depois
            */
            char data[BUFFER_SIZE];
            boost::asio::ip::udp::endpoint sender_endpoint;
        }

    }
    catch(const std::exception& e)
    {
        std::cout << "Falha ao iniciar servidor \n";
        std::cerr << e.what() << '\n';
    }
}

