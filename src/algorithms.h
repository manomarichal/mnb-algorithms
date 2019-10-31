//
// Created by mano on 15.10.19.
//

#ifndef CFG_ALGORITHMS_H
#define CFG_ALGORITHMS_H

#include "./CFG.h"
#include "./PDA.h"

CFG convertToCfg(PDA &pda);
bool CYK (CFG &cfg, std::vector<std::string> input, std::string filename);



#endif //CFG_ALGORITHMS_H
