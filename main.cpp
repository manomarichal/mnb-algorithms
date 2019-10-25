#include <iostream>
#include "./src/CFG.h"
#include "./src/PDA.h"
#include "./src/StatePDA.h"
#include "./src/algorithms.h"
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        return 0;
    }

    else if (strcmp(argv[1], "pdatocfg") == 0)
    {
        PDA pda = PDA(std::string(argv[2]));
        pda.convertToDot("./outputfiles/" + std::string(argv[3]));
        std::string dotstring3 = "dot -Tpng ./outputfiles/" + std::string(argv[3]) + ".dot -o ./outputfiles/" + std::string(argv[3]) + ".png";
        system(dotstring3.c_str());
        CFG cfg = convertToCfg(pda);
        cfg.print("./outputfiles/" + std::string(argv[3]) + ".txt");
    }
}