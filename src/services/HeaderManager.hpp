//
// Created by harold Armijo Leon on 2019-03-24.
//

#ifndef ZIA_HEADERMANAGER_HPP
#define ZIA_HEADERMANAGER_HPP

#include <unordered_map>
#include "Heading.hpp"

class HeaderManager : public dems::header::IHeaders {
public:
    HeaderManager();
    ~HeaderManager();
    std::string &operator[](const std::string &headerName) override;
    std::string const &getHeader(const std::string &headerName) const override;
    std::string getWholeHeaders() const override;
    void setHeader(const std::string &headerName, const std::string &value) override;

private:
    std::unordered_map< std::string , std::string> _headers;
};


#endif //ZIA_HEADERMANAGER_HPP
