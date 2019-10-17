//
// Created by mano on 03.10.19.
//

#include "PDA.h"

std::string epsilon(std::vector<std::string> s)
{
    if (s.empty()) return "ε";
    else if (s[0].empty()) return "ε";
    else {
        std::string rVal;
        for (auto string: s)
        {
            rVal+=string;
        }
        return rVal;
    }
}

std::string cEpsilon(const std::string &s)
{
    if (s.empty()) return "ε";
    else return s;
}
PDA::PDA()
{
}

StatePDA* PDA::findState(std::string name)
{
    for (auto &state:states)
    {
        if (state.stateName == name) return &state;
    }
    return nullptr;
}
bool PDA::transition(std::string &input)
{
    std::map<StatePDA* , std::stack<std::string>> newState;

    for (auto &state:currentState)
    {
        std::string stackTop = state.second.top();

        // get next action
        StatePDA::Action nextAction = state.first->getTransition(input, stackTop);

        // stack action
        if (!doAction(nextAction, &state.second)) continue;

        // look for possible epsilon transitions
        for (auto &trans: std::get<0>(nextAction)->transitions)
        {
            if (trans.first.first == "" and trans.first.second == state.second.top())
            {
                std::stack<std::string> tempStack = state.second;
                doAction(trans.second, &tempStack);
                newState[std::get<0>(trans.second)] = tempStack;
            }
        }
        newState[std::get<0>(nextAction)] = state.second;
    }
    currentState = newState;

    return true;
}

bool PDA::doAction(StatePDA::Action &action, std::stack<std::string> *stack)
{
    if (std::get<1>(action) == none)
    {
        return false;
    }

    if (std::get<1>(action) == push)
    {
        // we push every symbol except the last one from the action

        for (u_long i=0;i<std::get<2>(action).size()-1;i++)
        {
            stack->push(std::get<2>(action)[i]);
        }

    }
    else if (std::get<1>(action) == pop)
    {
        stack->pop();
    }
    return true;
}


bool PDA::inputString(std::string input)
{
    std::stack<std::string> tempStack;
    tempStack.push(startStackSymbol);
    currentState[&startState] = tempStack;
    // check eclosure startstate
    for (auto &trans:startState.getTransitions())
    {
        if (trans.first.first == "")
        {
            currentState[std::get<0>(trans.second)] = tempStack;
        }
    }


    for (auto symbol:input)
    {
        std::string temp(1, symbol);
        this->transition(temp);
    }

    for (auto &state:currentState)
    {
        if (state.second.empty() and !finalState) return true;
        else if (finalState)
        {
            for (auto &fstate:endStates)
            {
                if (state.first->stateName == fstate) return true;
            }
        }
    }

    return false;
}

void PDA::convertToDot(std::string filename)
{
    std::fstream file;
    file.open(filename, std::fstream::out);
    file << "digraph {\n" << std::endl;
    file << "rankdir = LR" << std::endl;

    for (auto state:endStates)
    {
         file << state << "[peripheries=2, label=\"" << state << "\"]" << std::endl;
    }

    std::vector<StatePDA*> used;

    for (const auto &state:states)
    {

        file << state.stateName << "[label=\""<< state.stateName << "\"]" << std::endl;

        for (const auto &end:states)
        {
            std::string transition;

            for (const auto &trans:state.transitions)
            {
                if (std::get<0>(trans.second)->stateName == end.stateName)
                {
                    if (!transition.empty()) transition += "\n";
                    transition += "(" + cEpsilon(trans.first.first) + ", " + cEpsilon(trans.first.second)
                            + "/" + epsilon(std::get<2>(trans.second)) + ")";

                }
            }

            if (transition.empty()) continue;
            file  << state.stateName << "->" << end.stateName << "[label=\"" <<
                  transition << "\"]" << ";" << std::endl;
        }
    }
    for (const auto &state:states)
    {
        for (const auto &trans:state.transitions)
        {

        }
    }
    // start state
    file << "head [style=invis]\n   head->" << startState.stateName << std::endl;
    file  << "}";

    file.close();
}

void PDA::setAlphabet(const std::vector<std::string> &alphabet) {
    PDA::alphabet = alphabet;
}

void PDA::setStackAlphabet(const std::vector<std::string> &stackAlphabet) {
    PDA::stackAlphabet = stackAlphabet;
}

void PDA::setStartState(StatePDA *startState) {
    PDA::startState = *startState;
}

void PDA::setStartStackSymbol(const std::string &startStackSymbol) {
    PDA::startStackSymbol = startStackSymbol;
}

void PDA::setStates(const std::vector<StatePDA > &states) {
    PDA::states = states;
}

void PDA::setEndStates(const std::vector<std::string> &endStates) {
    PDA::endStates = endStates;
}

const std::vector<std::string> &PDA::getAlphabet() const {
    return alphabet;
}

const std::vector<std::string> &PDA::getStackAlphabet() const {
    return stackAlphabet;
}

const std::vector<StatePDA> &PDA::getStates() const {
    return states;
}

const std::vector<std::string> &PDA::getEndStates() const {
    return endStates;
}

const std::string &PDA::getStartStackSymbol() const {
    return startStackSymbol;
}

PDA::PDA(std::string filename)
{
    std::ifstream file(filename);
    nlohmann::json root;
    file >> root;

    for (auto &var: root["Alphabet"])
    {
        alphabet.emplace_back(var);
    }


    for (auto &var: root["StackAlphabet"])
    {
        stackAlphabet.emplace_back(var);
        if (root["StackAlphabet"] == var) startStackSymbol = var;
    }

    for (std::string name: root["States"])
    {
        StatePDA temp(name);
        states.emplace_back(temp);
        if (root["StartState"] == temp.stateName)
        {
            startState = temp;
        }

        if (root.contains("FinalStates"))
        {
            for (auto stateName:root["FinalStates"])
            {
                finalState = true;
                if (stateName == name) endStates.emplace_back(temp.stateName);
            }
        }

    }


    for (auto &state:states)
    {
        for (auto &trans:root["Transitions"])
        {
            if (trans["from"] == state.stateName)
            {
                stackAction action = none;
                if (trans["replacement"].empty()) action = pop;
                else if (trans["replacement"].size() == 1) action = nothing;
                else action = push;
                state.addTransition({trans["input"], trans["stacktop"]}, findState(trans["to"]), action, trans["replacement"]);
            }
        }
    }


    return;
}

const StatePDA &PDA::getStartState() const {
    return startState;
}

