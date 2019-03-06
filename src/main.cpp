/*
** EPITECH PROJECT, 2019
** zia
** File description:
** main
*/

#include "parseXml.hpp"

int main(int argc, const char **av)
{
    (void)av;
    if (argc != 1)
        return 84;
    try
    {
        parseXml test("test.xml");    
    }
    catch (const std::exception& e)
    {
         std::cout << e.what() << '\n';
         return 78;
    }
    
    return 0;
}