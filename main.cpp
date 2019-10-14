#include <iostream>
#include "./src/CFG.h"
#include "./src/PDA.h"
#include "./src/StatePDA.h"
int main() {

    StatePDA q0("q0");
    StatePDA q1("q1");
    StatePDA qf("qf");

    q0.addTransition({"a", "a"}, &q0, push, {"a", "a", "a"});
    q0.addTransition({"a", "Z"}, &q0, push, {"a", "a", "Z"});
    q0.addTransition({"b", "a"}, &q1, pop);

    q1.addTransition({"b", "a"}, &q1 ,pop);
    q1.addTransition({"", "Z"}, &qf ,nothing, {"Z"});


    PDA pda;
    pda.setAlphabet({"a", "b"});
    pda.setStartState(&q0);
    pda.setStartStackSymbol("Z");
    pda.setStates({&q0, &q1, &qf});
    pda.setEndStates({&qf});


    if (pda.inputString("aabbbb"))
    {
        std::cout << "string was accepted" << std::endl;
    }

    else
        std::cout << "string was not accepted" << std::endl;

    if (pda.inputString("aab"))
    {
        std::cout << "string was accepted" << std::endl;
    }
    else
        std::cout << "string was not accepted" << std::endl;

    pda.convertToDot("pda.dot");
    std::string dotstring = "dot -Tpng ./pda.dot -o pda.png";
    system(dotstring.c_str());

    CFG cfg("./testfiles/example1.json");
    PDA pda2 = cfg.convertToPda();

    pda2.convertToDot("pda2.dot");
    std::string dotstring2 = "dot -Tpng ./pda2.dot -o pda2.png";
    system(dotstring2.c_str());

    return 0;
}