//
// Created by harold Armijo Leon on 2019-03-05.
//

//#ifndef ZIA_SERVER_H
//#define ZIA_SERVER_H

#pragma once

#include <vector>
#include "TcpConnection.h"
#include "../../services/ModulesManager.hpp"

/**
 * Server TCP
 */
class Server {
public:
    Server(boost::asio::io_service &,
            ModulesManager &,
            int port = 80,
            int entityHeader = 8000);
private:
    void _accept();
    void _handleAccept(TcpConnection::pointer,
                       const boost::system::error_code &);
    tcp::acceptor _acceptor;
    std::vector<TcpConnection::pointer> _clients;
    int _entityHeader;
    ModulesManager &_modulesManager;
};


//#endif //ZIA_SERVER_H
