//
// Created by mano on 15.10.19.
//
#include "./algorithms.h"

PDA convertToPda(CFG &cfg)
{
    StatePDA* q = new StatePDA("q");

    std::vector<std::string> stackAlphabet;
    stackAlphabet.reserve( cfg.getTerminals().size() + cfg.getVariables().size() ); // preallocate memory
    stackAlphabet.insert( stackAlphabet.end(), cfg.getTerminals().begin(), cfg.getTerminals().end() );
    stackAlphabet.insert( stackAlphabet.end(), cfg.getVariables().begin(), cfg.getVariables().end() );

    PDA pda;
    pda.setStartStackSymbol(cfg.getStart());
    pda.setAlphabet(cfg.getTerminals());
    pda.setStackAlphabet(stackAlphabet);
    pda.setStates({q});
    pda.setStartState(q);


    for (auto var:cfg.getVariables())
    {
        for (const auto &production: cfg.getProductions()[var])
        {
            q->addTransition( {"", var}, q, push, production);
        }
    }

    for (const auto &terminal:cfg.getTerminals())
    {
        q->addTransition({"", terminal}, q, pop);
    }
    return pda;
}

void generateBody(std::vector<std::string> &stack, std::string body, PDA &pda, CFG &cfg, const std::string &top, int level, int max)
{
    if (max == -1)
    {
        if (body[0] == '[')
        {
            cfg.addProduction(top + body.substr(1, body.size()-1), {"ε"});
        }
        else cfg.addProduction(top + body.substr(2, body.size()-2), {body[0]});
        return;
    };

    if (level == max)
    {
        for (const auto &state:pda.getStates())
        {
            std::string orgBody = body;
            orgBody +=stack[level] + state->stateName + "]";
            cfg.addProduction(top + state->stateName, orgBody);
        }
        return;
    }
    for (const auto &state:pda.getStates())
    {
        std::string orgBody = body;
        orgBody+=stack[level] + state->stateName + "][" + state->stateName;
        generateBody(stack, orgBody, pda, cfg, top, level+1, max);
    }
}

CFG convertToCfg(PDA &pda)
{
    CFG cfg;
    cfg.setTerminals(pda.getAlphabet());

    std::vector<std::string> variables;
    variables.emplace_back("S");

    for (const auto &v1:pda.getStates())
    {
        for (const auto &symbol:pda.getStackAlphabet())
        {
            for (const auto &v2:pda.getStates())
            {
                variables.emplace_back(v1->stateName + symbol + v2->stateName);
            }
        }
    }

    cfg.setVariables(variables);

    cfg.setStart("S");

    for (const auto &v1:pda.getStates())
    {
        // productions for startsymbol S
        cfg.addProduction("S", "[" + pda.getStartState()->stateName + pda.getStartStackSymbol() + v1->stateName + "]");

        //productions for the rest
        for (const auto &transition:v1->getTransitions())
        {
            std::vector<std::string> stack = std::get<2>(transition.second);
            generateBody( stack, transition.first.first + "[" + std::get<0>(transition.second)->stateName,
                    pda, cfg, v1->stateName + transition.first.second,
                    0, std::get<2>(transition.second).size() - 1);
        }
    }

    return cfg;
}

