//
// Created by mano on 29.09.19.
//

#include "CFG.h"

CFG::CFG(std::string filename)
{
    std::ifstream file(filename);
    nlohmann::json root;
    file >> root;

    for (auto &var: root["Variables"])
    {
        CFG::variables.emplace_back(var);

        productions[var]= std::vector<std::vector<std::string>>();
    }

    for (auto &terminal: root["Terminals"])
    {
        CFG::terminals.emplace_back(terminal);
    }

    CFG::start = root["Start"];

    for (auto &production: root["Productions"])
    {
        productions[production["head"]].emplace_back(production["body"]);
    }
    return;
}

void CFG::print()
{
    for (auto& production:productions)
    {
        std::cout<<production.first << " -> ";

        for (auto body = production.second.begin();body != production.second.end();body++)
        {
            if (body->empty()) std::cout << "e";
            else for (auto var: *body)
            {
                std::cout << var;
            }

            if (std::next(body) != production.second.end()) std::cout << "| ";
        }

        std::cout << std::endl;
    }

}

void CFG::addProduction(std::string top, std::string body)
{
    std::vector<std::string> newBody;
    for (const auto &s:body)
    {
        newBody.emplace_back(std::string(1, s));
    }
    productions[top].emplace_back(newBody);
}

const std::vector<std::string> &CFG::getVariables() const {
    return variables;
}

const std::vector<std::string> &CFG::getTerminals() const {
    return terminals;
}

const std::string &CFG::getStart() const {
    return start;
}

std::map<std::string, std::vector<std::vector<std::string>>> &CFG::getProductions() {
    return productions;
}

void CFG::setVariables(const std::vector<std::string> &variables) {
    CFG::variables = variables;
}

void CFG::setTerminals(const std::vector<std::string> &terminals) {
    CFG::terminals = terminals;
}

void CFG::setStart(const std::string &start) {
    CFG::start = start;
}

void CFG::setProductions(const std::map<std::string, std::vector<std::vector<std::string>>> &productions) {
    CFG::productions = productions;
}
