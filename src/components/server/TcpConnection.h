//
// Created by harold Armijo Leon on 2019-03-05.
//

//#ifndef ZIA_TCPCONNECTION_H
//#define ZIA_TCPCONNECTION_H

#pragma once

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "../../services/ModulesManager.hpp"

using boost::asio::ip::tcp;

class TcpConnection : public boost::enable_shared_from_this<TcpConnection> {
public:
    typedef boost::shared_ptr<TcpConnection> pointer;
    tcp::socket& getSocket();
    void start(ModulesManager *, const int = 8000);
    static pointer create(boost::asio::io_service& io_service)
    {
        return pointer(new TcpConnection(io_service));
    }
private:
    TcpConnection(boost::asio::io_service& io_service)
            : _socket(io_service)
    {
        std::fill(_buff.begin(), _buff.end(), 0);
    }

    void _handleRead(const boost::system::error_code & /*error*/,
                      size_t /*bytes_transferred*/);
    void _handleWrite(const boost::system::error_code & /*error*/,
                      size_t /*bytes_transferred*/);

    tcp::socket _socket;
    std::string _message;
    std::array<char, 8000>          _buff;
    ModulesManager *_modulesManager;
};


//#endif //ZIA_TCPCONNECTION_H
