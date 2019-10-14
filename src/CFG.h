//
// Created by mano on 29.09.19.
//

#ifndef CFG_CFG_H
#define CFG_CFG_H

#include "../json/json.hpp"
#include "../src/PDA.h"
#include <iostream>
#include <fstream>

class CFG
{
private:
    std::vector<std::string> variables;
    std::vector<std::string> terminals;
    std::string start;
    std::map<std::string, std::vector<std::vector<std::string>>> productions;
public:
    CFG(std::string filename);
    void print();
    PDA convertToPda();

};


#endif //CFG_CFG_H
