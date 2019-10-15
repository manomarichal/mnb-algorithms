//
// Created by mano on 15.10.19.
//

#ifndef CFG_ALGORITHMS_H
#define CFG_ALGORITHMS_H

#include "./CFG.h"
#include "./PDA.h"

PDA convertToPda(CFG &cfg);
CFG convertToCfg(PDA &pda);


#endif //CFG_ALGORITHMS_H
