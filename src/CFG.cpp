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

void CFG::print(std::string filename = "default.txt")
{
    std::fstream file;
    file.open(filename, std::fstream::out);

    file << "G = (V, T, R, S), where:\n\n";
    file << "V = {";

    for (u_int i=0;i<variables.size();i++)
    {
        if (variables[i] != "S") file << "[" + variables[i] + "]";
        else file << variables[i];


        if (i != variables.size()-1)
        {
            file << ",";
        }
    }
    file << "}\n\nT = {";
    for (u_int i=0;i<terminals.size();i++)
    {
        file << terminals[i];

        if (i != terminals.size()-1)
        {
            file << ",";
        }
    }
    file << "}\n\nS = ";
    file << start;

    file << "\n\nProductions in R:\n";
    for (auto& production:productions)
    {
        // voor alle producties voor 1 variable
        for (auto body = production.second.begin();body != production.second.end();body++)
        {

            // we write the head
            file << "\n" <<production.first << " -> ";

            // if the body is empty we write epsilon
            if (body->empty()) std::cout << "e";
            else for (auto var: *body)
            {
                file << var;
            }
        }

        file << std::endl;
    }
    file.close();
}

void CFG::addProduction(std::string top, std::string body)
{
    std::vector<std::string> newBody = {};
    for (int i=0;i<body.size();i++)
    {
        std::string temp = body.substr(i, 1);
        newBody.emplace_back(temp);
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
