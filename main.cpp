#include <iostream>
#include "./src/CFG.h"
#include "./src/PDA.h"
#include "./src/StatePDA.h"
#include "./src/algorithms.h"
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
    pda.setStackAlphabet({"a", "Z"});

    // CFG TO PDA
    CFG cfg("./testfiles/example1.json");
    PDA pda2 = convertToPda(cfg);

    pda2.convertToDot("pda2.dot");
    std::string dotstring2 = "dot -Tpng ./pda2.dot -o pda2.png";
    system(dotstring2.c_str());


    // PDA TO CFG
    CFG cfg2 = convertToCfg(pda);
    cfg2.print();

    return 0;
}