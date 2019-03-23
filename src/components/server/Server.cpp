//
// Created by harold Armijo Leon on 2019-03-05.
//

#include "Server.h"

Server::Server(boost::asio::io_service &io_service, ModulesManager &modulesManager, int port, int entityHeader)
        : _acceptor(io_service, tcp::endpoint(tcp::v4(), port)),
          _modulesManager(modulesManager),
          _entityHeader(entityHeader)
{
    _accept();
}

void Server::_accept()
{
    TcpConnection::pointer newConnection =
            TcpConnection::create(_acceptor.get_io_service());
    _clients.push_back(newConnection);

    _acceptor.async_accept(
           newConnection->getSocket(),
           boost::bind(
                   &Server::_handleAccept, 
                   this, 
                   newConnection, 
                   boost::asio::placeholders::error));
}

void Server::_handleAccept(TcpConnection::pointer newConnection,
                   const boost::system::error_code& error)
{
    if (error ||
        (boost::asio::error::eof == error) ||
        (boost::asio::error::connection_reset == error)) {
        // handle the disconnect.
    } else {
        // when connected read the data
        _modulesManager.callHooksConnection(newConnection->getSocket().native_handle());
        newConnection->start(&_modulesManager);
    }
}