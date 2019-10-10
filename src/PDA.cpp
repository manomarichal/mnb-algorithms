//
// Created by mano on 03.10.19.
//

#include "PDA.h"

std::string epsilon(std::string s)
{
    if (s.empty()) return "ε";
    else return s;
}
PDA::PDA()
{
}
bool PDA::transition(std::string &input)
{
    std::map<StatePDA* , std::stack<std::string>> newState;

    for (auto &state:currentState)
    {
        std::string stackTop = state.second.top();

        // get next action
        std::tuple<StatePDA*, stackAction, std::string> nextAction = state.first->getTransition(input, stackTop);

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
        // we push every character except the last one
        for (ulong k=0;k<std::get<2>(action).length()-1;k++)
        {
            stack->push(std::string(1, std::get<2>(action)[k]));
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
    currentState[startState] = tempStack;

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

void PDA::convertToDot(std::string filename)
{
    std::fstream file;
    file.open(filename, std::fstream::out);
    file << "digraph {\n" << std::endl;
    file << "rankdir = LR" << std::endl;

    for (auto state:endStates)
    {
         file << state->stateName << "[peripheries=2, image=\"arch.png\", label=\"" << state->stateName << "\" imagescale=true, labelloc=b]" << std::endl;
    }

    std::vector<StatePDA*> used;

    for (const auto &state:states)
    {
        file << state->stateName << "[image=\"arch.png\", label=\""<< state->stateName << "\",imagescale=true, labelloc=b]" << std::endl;

        for (const auto &end:states)
        {
            std::string transition;

            for (const auto &trans:state->transitions)
            {
                if (std::get<0>(trans.second)->stateName == end->stateName)
                {
                    if (!transition.empty()) transition += "\n";
                    transition += "(" + epsilon(trans.first.first) + ", " + epsilon(trans.first.second)
                            + "/" + epsilon(std::get<2>(trans.second)) + ")";

                }
            }

            if (transition.empty()) continue;
            file  << state->stateName << "->" << end->stateName << "[label=\"" <<
                  transition << "\"]" << ";" << std::endl;
        }
    }
    for (const auto &state:states)
    {
        for (const auto &trans:state->transitions)
        {

        }
    }
    // start state
    file << "head [style=invis]\n   head->" << startState->stateName << std::endl;
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
