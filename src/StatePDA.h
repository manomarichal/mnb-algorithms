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

class StatePDA
{
private:
    std::map<std::pair<std::string, std::string>, std::tuple<StatePDA*, stackAction, std::string >> transitions;
public:
    StatePDA(std::string name) {stateName = name;};
    std::string stateName;
    std::tuple<StatePDA*, stackAction, std::string> getTransition(std::pair<std::string, std::string> input);
    std::vector<StatePDA*> getEclosure(std::string stackTop);
    void addTransition(std::pair<std::string, std::string> input , StatePDA* state, stackAction action, std::string stackValue="");
};


#endif //CFG_STATEPDA_H
