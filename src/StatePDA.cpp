//
// Created by mano on 04.10.19.
//

#include "StatePDA.h"

std::tuple<StatePDA*, stackAction, std::string>  StatePDA::getTransition(std::pair<std::string, std::string> input)
{
    if (stateName == "qf")
    {
        int a =5;
    }
    for (auto &transition:transitions)
    {
        if (transition.first.first == input.first and transition.first.second == input.second)
        {
            return transition.second;
        };
    }
    std::tuple<StatePDA*, stackAction, std::string> returnVal ={NULL, none, ""};

    return returnVal;
}

std::vector<StatePDA*> StatePDA::getEclosure(std::string stackTop)
{
    std::vector<StatePDA*> eclosure;
    for (auto &state:transitions)
    {
        if (state.first.first.empty() and state.first.second == stackTop)
        {
            bool check = true;
            for (auto &eState:eclosure)
            {
                if (eState->stateName == std::get<0>(state.second)->stateName) check = false;
            }
            if (check) eclosure.emplace_back(std::get<0>(state.second));
        }
    }

    return eclosure;
}

void StatePDA::addTransition(std::pair<std::string, std::string> input, StatePDA *state, stackAction action, std::string stackValue)
{
    transitions[input] = {state, action, stackValue};
}