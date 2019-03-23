//
// Created by harold Armijo Leon on 2019-03-05.
//

#include "TcpConnection.h"

tcp::socket& TcpConnection::getSocket()
{
    return _socket;
}

void TcpConnection::start(ModulesManager *modulesManager, const int entityHeader)
{
    _modulesManager = modulesManager;
    _socket.async_receive(boost::asio::buffer(_buff, entityHeader), 0,
        boost::bind(
                &TcpConnection::_handleRead, shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
         ));
}

void TcpConnection::_handleRead(const boost::system::error_code & error, size_t bytesTransferred)
{
    if (!error) {
        std::cout << _buff.data();
        std::cout << "byte received: " << bytesTransferred << '\n';
        std::string res;
        res += "HTTP/1.1 200 OK\n";
        res += "Server: Zia\n\n";
        res += "hello world lol";
        _socket.async_send(boost::asio::buffer(res, res.size()),
            boost::bind(
                   &TcpConnection::_handleWrite, shared_from_this(),
                   boost::asio::placeholders::error,
                   boost::asio::placeholders::bytes_transferred
            ));
        _socket.close();
        std::fill(_buff.begin(), _buff.end(), 0);
        this->start(_modulesManager);
    } else {
        // deconnetion et rm pointeur TcpConnection
        std::cerr << "maybe error or a deconnection TcpConnection::test\n";
    }
}

void TcpConnection::_handleWrite(const boost::system::error_code & /*error*/,
                  size_t /*bytes_transferred*/)
{
}