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
                std::cout << var << " ";
            }

            if (std::next(body) != production.second.end()) std::cout << "| ";
        }

        std::cout << std::endl;
    }

}

PDA CFG::convertToPda()
{
    StatePDA* q = new StatePDA("q");

    PDA pda;
    pda.setStartStackSymbol(start);
    pda.setAlphabet(terminals);
    pda.setStates({q});
    pda.setStartState(q);

    std::vector<std::string> stackAlphabet;
    stackAlphabet.reserve( terminals.size() + variables.size() ); // preallocate memory
    stackAlphabet.insert( stackAlphabet.end(), terminals.begin(), terminals.end() );
    stackAlphabet.insert( stackAlphabet.end(), variables.begin(), variables.end() );
    pda.setStackAlphabet(stackAlphabet);

    for (const auto &var:variables)
    {
        for (const auto &production:productions[var])
        {
            q->addTransition( {"", var}, q, push, production);
        }
    }

    for (const auto &terminal:terminals)
    {
        q->addTransition({"", terminal}, q, pop);
    }
    return pda;
}