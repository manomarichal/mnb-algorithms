#include <iostream>
#include "./src/CFG.h"
#include "./src/PDA.h"
#include "./src/StatePDA.h"
#include "./src/algorithms.h"
int main() {

    StatePDA p("p");
    StatePDA q("q");

    q.addTransition({"1", "Z0"}, &q, push, {"X", "z0"});
    q.addTransition({"1", "X"}, &q, push, {"X", "X"});
    q.addTransition({"0", "X"}, &p, nothing, {"X"});
    q.addTransition({"", "X"}, &q, pop);

    p.addTransition({"1", "X"}, &p, pop);
    p.addTransition({"0", "Z0"}, &q, nothing, {"Z0"});

    PDA pda;
    pda.setAlphabet({"1", "0"});
    pda.setStartState(&q);
    pda.setStartStackSymbol("Z0");
    pda.setStates({q, p});
    pda.setEndStates({&p});
    pda.setStackAlphabet({"X", "Z0"});

    // PDA TO CFG
    CFG cfg2 = convertToCfg(pda);
    cfg2.print();

    // INLEZEN PDA
    PDA pda2("./testfiles/pda1.json");
    pda2.convertToDot("pda2.dot");
    std::string dotstring2 = "dot -Tpng ./pda2.dot -o pda2.png";
    system(dotstring2.c_str());

    if (pda2.inputString("aabbbb")) std::cout << "string geaccepteerd";

    return 0;
}