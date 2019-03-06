/*
** EPITECH PROJECT, 2019
** CPP_zia_2018
** File description:
** parseXml
*/

#ifndef PARSEXML_HPP_
#define PARSEXML_HPP_

#include <iostream>
#include <map>
#include "pugixml.hpp"


class parseXml
{
private:
    pugi::xml_parse_result _result;
    pugi::xml_document _doc;
    pugi::xml_node _conf;
    std::map<const std::string,const std::string> _params;
public:
    parseXml(const std::string file) {
        _result = _doc.load_file(file.c_str()) == 0 ? throw : _result;
        _conf = _doc.child("conf");
        _params.insert(std::make_pair("ip", _conf.child_value("Ip")));
        _params.insert(std::make_pair("port", _conf.child_value("Port")));
        pugi::xml_document doc;
    }
    ~parseXml() {};

    const std::map<const std::string, const std::string> getParams() {
        return _params;
    };
};

#endif /* !PARSEXML_HPP_ */
