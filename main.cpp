#include <iostream>
#include "./src/CFG.h"
#include "./src/PDA.h"
#include "./src/StatePDA.h"
int main() {

    StatePDA q0("q0");
    StatePDA q1("q1");
    StatePDA qf("qf");

    q0.addTransition({"a", "a"}, &q0, push, "aa");
    q0.addTransition({"a", "Z"}, &q0, push, "aa");
    q0.addTransition({"b", "a"}, &q1, pop);

    q1.addTransition({"b", "a"}, &q1 ,pop);
    q1.addTransition({"", "Z"}, &qf ,nothing);


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


    return 0;
}