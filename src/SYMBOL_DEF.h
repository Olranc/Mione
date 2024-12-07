//
// Created by calle on 24-12-7.
//

#include "OBJECTS.h"

SymbolsCaseObj Symbols[];

#ifndef SYMBOL_DEF_H
#define SYMBOL_DEF_H

SymbolsCaseObj Symbols[] =
{
    (SymbolsCaseObj){
        .Name = "+",
        .SymbolType = 1,
        .xIndex = 2,
        .CurNumber = 1
    },

    (SymbolsCaseObj){
        .Name = "-",
        .SymbolType = 1,
        .xIndex = 2,
        .CurNumber = 2
    },

    (SymbolsCaseObj){
        .Name = "*",
        .SymbolType = 1,
        .xIndex = 1,
        .CurNumber = 3
    },

    (SymbolsCaseObj){
        .Name = "/",
        .SymbolType = 1,
        .xIndex = 1,
        .CurNumber = 4
    },

    (SymbolsCaseObj){
        .Name = "(",
        .SymbolType = 0,
        .xIndex = 0,
        .CurNumber = 0
    },

    (SymbolsCaseObj){
        .Name = ")",
        .SymbolType = 0,
        .xIndex = 0,
        .CurNumber = 0
    },

    (SymbolsCaseObj){
        .Name = "^",
        .SymbolType = 1,
        .xIndex = 0,
        .CurNumber = 5
    },

    (SymbolsCaseObj){
        .Name = ";",
        .SymbolType = 1,
        .xIndex = 1,
        .CurNumber = 1
    },
};


#endif //SYMBOL_DEF_H
