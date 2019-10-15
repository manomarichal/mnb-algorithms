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

void generateBody(std::vector<std::string> stack, std::string body, PDA &pda, CFG &cfg, const std::string &top)
{
    if (stack.empty())
    {
        for (const auto &state:pda.getStates())
        {
            body += state->stateName + "]";
            cfg.addProduction(top, body);
        }
        return;
    }
    for (const auto &state:pda.getStates())
    {
        body+=stack[0] + state->stateName + "][" + state->stateName;
        std::vector<std::string> newstack = stack;
        newstack.erase(stack.begin());
        generateBody(newstack, body, pda, cfg, top);
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
        cfg.addProduction("S", pda.getStartState()->stateName + pda.getStartStackSymbol() + v1->stateName);

        //productions for the rest
        for (const auto &transition:v1->getTransitions())
        {
            generateBody( std::get<2>(transition.second), transition.first.first + "[" + v1->stateName, pda, cfg, v1->stateName + transition.first.second + std::get<0>(transition.second)->stateName);
        }
    }

    return cfg;
}

