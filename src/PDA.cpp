//
// Created by mano on 03.10.19.
//

#include "PDA.h"

PDA::PDA()
{
}
bool PDA::transition(std::string &input)
{
    std::map<StatePDA* , std::stack<std::string>*> newState;

    for (auto &state:currentState)
    {
        std::string stackTop = state.second->top();

        std::tuple<StatePDA*, stackAction, std::string> nextAction = state.first->getTransition({input, stackTop});
        if (std::get<1>(nextAction) == none)
        {
            continue;
        }
        if (std::get<1>(nextAction) == push)
        {
            for(auto symbol: std::get<2>(nextAction))
            {
                state.second->push(std::string(1, symbol));
            }

        }
        else if (std::get<1>(nextAction) == pop)
        {
            state.second->pop();
        }

        for (auto &eState: std::get<0>(nextAction)->getEclosure(state.second->top()))
        {
            newState[eState] = state.second;
        };

        newState[std::get<0>(nextAction)] = state.second;
    }
    currentState = newState;
}

bool PDA::inputString(std::string input)
{
    std::stack<std::string> tempStack;
    tempStack.push(startStackSymbol);
    currentState[startState] = &tempStack;

    for (auto symbol:input)
    {
        std::string temp(1, symbol);
        this->transition(temp);
    }

    for (auto &state:currentState)
    {
        for (auto endState:endStates)
        {
            if (state.first->stateName == endState->stateName) return true;
        }
    }

    return false;
}
void PDA::setAlphabet(const std::vector<std::string> &alphabet) {
    PDA::alphabet = alphabet;
}

void PDA::setStackAlphabet(const std::vector<std::string> &stackAlphabet) {
    PDA::stackAlphabet = stackAlphabet;
}

void PDA::setStartState(StatePDA *startState) {
    PDA::startState = startState;
}

void PDA::setStartStackSymbol(const std::string &startStackSymbol) {
    PDA::startStackSymbol = startStackSymbol;
}

void PDA::setStates(const std::vector<StatePDA *> &states) {
    PDA::states = states;
}

void PDA::setEndStates(const std::vector<StatePDA *> &endStates) {
    PDA::endStates = endStates;
}
