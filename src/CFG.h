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

    CFG()= default;

    void print();

    const std::vector<std::string> &getVariables() const;

    const std::vector<std::string> &getTerminals() const;

    const std::string &getStart() const;

    std::map<std::string, std::vector<std::vector<std::string>>> &getProductions();

    void setVariables(const std::vector<std::string> &variables);

    void setTerminals(const std::vector<std::string> &terminals);

    void setStart(const std::string &start);

    void setProductions(const std::map<std::string, std::vector<std::vector<std::string>>> &productions);

    void addProduction(std::string top, std::string body);


};


#endif //CFG_CFG_H
