//
// Created by mano on 03.10.19.
//

#ifndef CFG_PDA_H
#define CFG_PDA_H

#include "StatePDA.h"

class PDA {
private:
    std::vector<std::string> alphabet;
    std::vector<std::string> stackAlphabet;
    std::vector<StatePDA*> states;
    std::vector<StatePDA*> endStates;
    StatePDA* startState;
    std::string startStackSymbol;
    std::map<StatePDA* , std::stack<std::string>*> currentState;
public:
    PDA();

    void setAlphabet(const std::vector<std::string> &alphabet);

    void setStackAlphabet(const std::vector<std::string> &stackAlphabet);

    void setStates(const std::vector<StatePDA *> &states);

    void setEndStates(const std::vector<StatePDA *> &endStates);

    void setStartState(StatePDA *startState);

    void setStartStackSymbol(const std::string &startStackSymbol);

    bool transition(std::string &input);

    bool inputString(std::string input);

};


#endif //CFG_PDA_H
