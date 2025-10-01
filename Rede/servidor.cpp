#include <iostream>
#include <vector>
#include <boost/asio.hpp>

/*
    Tentativa de implementação de servidor UDP, 
*/

constexpr int PORTA = 4040 // Depois vejo qual será a porta correta
constexpr int BUFFER_SIZE = 1024

int iniciar(){

    try
    {
        boost::asio::io_context io_context;
        boost::asio::ip::udp::socket socket(io_context, udp::endpoint(udp::v4(), PORTA));
        std::cout << "Servidor pronto e disponivel na porta: " << PORTA  << "\n";
    }
    catch(const std::exception& e)
    {
        std::cout << "Falha ao iniciar servidor \n";
        std::cerr << e.what() << '\n';
    }
    



}