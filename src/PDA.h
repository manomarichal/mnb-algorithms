//
// Created by mano on 03.10.19.
//

#ifndef CFG_PDA_H
#define CFG_PDA_H

#include "StatePDA.h"
#include <fstream>
#include <iostream>
#include "../json/json.hpp"

class PDA {
private:
    std::vector<std::string> alphabet;
    std::vector<std::string> stackAlphabet;
    std::vector<StatePDA> states;
    std::vector<StatePDA> realStates;
    std::vector<StatePDA*> endStates;
    StatePDA startState;
    std::string startStackSymbol;
    std::map<StatePDA* , std::stack<std::string>> currentState;
    StatePDA* findState(std::string name);
public:
    PDA();

    PDA(std::string filename);

    bool doAction (StatePDA::Action &action, std::stack<std::string>* stack);

    void setAlphabet(const std::vector<std::string> &alphabet);

    void setStackAlphabet(const std::vector<std::string> &stackAlphabet);

    void setStates(const std::vector<StatePDA> &states);

    void setEndStates(const std::vector<StatePDA *> &endStates);

    void setStartState(StatePDA *startState);

    void setStartStackSymbol(const std::string &startStackSymbol);

    bool transition(std::string &input);

    bool inputString(std::string input);

    void convertToDot(std::string filename);

    const std::vector<std::string> &getAlphabet() const;

    const std::vector<std::string> &getStackAlphabet() const;

    const std::vector<StatePDA> &getStates() const;

    const std::vector<StatePDA *> &getEndStates() const;

    const std::string &getStartStackSymbol() const;

    const StatePDA &getStartState() const;
};


#endif //CFG_PDA_H
