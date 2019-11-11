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

    else if (strcmp(argv[1], "pda2cfg") == 0)
    {
        PDA pda = PDA(std::string(argv[2]));
        CFG cfg = convertToCfg(pda);
        cfg.print(std::string(argv[3]));
    }

    else if (strcmp(argv[1], "cyk") == 0)
    {
        CFG cfg = CFG(std::string(argv[2]));
        std::vector<std::string> input;
        for (auto c:std::string(argv[3]))
        {
            input.emplace_back(std::string(1,c));
        }
        CYK(cfg, input, std::string(argv[4]));
    }
}