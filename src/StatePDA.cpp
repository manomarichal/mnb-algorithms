//
// Created by mano on 04.10.19.
//

#include "StatePDA.h"

StatePDA::Action StatePDA::getTransition(std::string symbol, std::string stackSymbol)
{
    for (auto &transition:transitions)
    {
        if (transition.first.first == symbol and transition.first.second == stackSymbol)
        {
            return transition.second;
        };
    }
    Action returnVal ={NULL, none, {""}};

    return returnVal;
}

void StatePDA::addTransition(std::pair<std::string, std::string> input, StatePDA *state, stackAction action, std::vector<std::string> stackValue)
{
    transitions[input] = {state, action, stackValue};
}

