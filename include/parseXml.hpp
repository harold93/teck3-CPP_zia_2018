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
#include <vector>
#include "pugixml.hpp"


class parseXml
{
private:
    pugi::xml_parse_result _result;
    pugi::xml_document _doc;
    pugi::xml_node _conf;
    std::map<std::string,std::string> _params;
    std::vector<std::string> _modules;
public:
    parseXml() {
    }
    void parse(const std::string file)
    {
        _modules.clear();
        _params.clear();
        _result = _doc.load_file(file.c_str()) == 0 ? throw : _result;
        _conf = _doc.child("server");
        _params.insert(std::make_pair("ip", _conf.child_value("Ip")));
        _params.insert(std::make_pair("port", _conf.child_value("Port")));

        for (pugi::xml_node child: _conf.children("Module")) {
            for (pugi::xml_node tmp: child.children()) {
                _modules.emplace_back(tmp.value());
            }
        }
    }
    ~parseXml() {};

    const std::map< std::string, std::string> getParams() noexcept {
        return _params;
    }

    const std::vector<std::string> getModules() noexcept {
        return _modules;
    }
};

#endif /* !PARSEXML_HPP_ */
