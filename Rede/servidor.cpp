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

int iniciar(){

    try
    {
        boost::asio::io_context io_context;
        boost::asio::ip::udp::socket socket(io_context, udp::endpoint(udp::v4(), PORTA));
        std::cout << "Servidor pronto e disponivel na porta: " << PORTA  << "\n";

        while(true){
            // Isso aqui é muito básico. Na verdade é necessário colocar threads, depois faço isso
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