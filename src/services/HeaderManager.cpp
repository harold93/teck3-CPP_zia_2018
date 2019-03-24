//
// Created by harold Armijo Leon on 2019-03-24.
//

#include "HeaderManager.hpp"

HeaderManager::HeaderManager()
{}

HeaderManager::~HeaderManager()
{}

std::string &HeaderManager::operator[](const std::string &headerName)
{
        return _headers[headerName];
}

std::string const &HeaderManager::getHeader(const std::string &headerName) const
{
//    return *((std::string *)nullptr);
    static const std::string    empty = "";
    auto it = _headers.find(headerName);

    if (it != _headers.end()) {
        return it->second;
    } else
        return empty;
}

std::string HeaderManager::getWholeHeaders() const
{
    std::string ret;

    for (auto &[key, val] : _headers) {
        ret += val + '\n';
    }
    return ret;
}

void HeaderManager::setHeader(const std::string &headerName, const std::string &value)
{
    _headers.insert({headerName, value});
}