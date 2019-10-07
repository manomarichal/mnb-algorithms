//
// Created by mano on 04.10.19.
//

#ifndef CFG_STATEPDA_H
#define CFG_STATEPDA_H

#include <vector>
#include <string>
#include <stack>
#include <map>
#include <stack>

enum stackAction { pop, push, nothing, none };

struct StatePDA
{
    using Action = std::tuple<StatePDA*, stackAction, std::string >;

    std::map<std::pair<std::string, std::string>, Action> transitions;
    StatePDA(std::string name) {stateName = name;};
    std::string stateName;
    Action getTransition(std::string symbol, std::string stackSymbol);
    void addTransition(std::pair<std::string, std::string> input , StatePDA* state, stackAction action, std::string stackValue="");
};


#endif //CFG_STATEPDA_H
