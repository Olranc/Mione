//
// Created by calle on 24-11-3.
//

CountObj COUNT(MioneObj*Pack,int PackSize);


#ifndef COUNT_H
#define COUNT_H

#include "main.h"


CountObj COUNT(MioneObj*Pack,int PackSize)
{
    int FirstBracketIndex = 0;
    int IfBrackets = 0; // 0 = 0 1 = only ( 2 = ()
    int PairsOfBrackets = 0;

    MioneObj* inBracket = malloc(0);
    int inBracketSize = 0;

    int CalculateType = 0; /*
        0 : 無
        1 : 加法 : +
        2 : 減法 : -
        3 : 乘法 : *
        4 : 除法 : /
        5 : 餘數 : %
    */

    int CalculateLevel = 0;

    for(int i = 0; i < PackSize; i++)
    {
        if (Pack[i].ObjType == 3) // Symbol
        {
            if (strcmp(Pack[i].Symbol.Name, "(") == 0)
            {
                FirstBracketIndex = i;
                IfBrackets = 1;
            }
            else if (strcmp(Pack[i].Symbol.Name, ")") == 0)
            {
                if (IfBrackets)
                {
                    PairsOfBrackets++;
                    IfBrackets = 0;

                    CountObj ChildCount = COUNT(inBracket, inBracketSize);

                    MioneObj* NewPack = malloc(0);
                    int NewPackSize = 0;

                    for (int index = 0; index < FirstBracketIndex; index++)
                    {
                        NewPackSize++;
                        NewPack = realloc(NewPack, NewPackSize * sizeof(MioneObj));
                        NewPack[NewPackSize - 1] = Pack[index];
                    }

                    for (int index = 0; index < ChildCount.ValueSize; index++)
                    {
                        NewPackSize++;
                        NewPack = realloc(NewPack, NewPackSize * sizeof(MioneObj));
                        NewPack[NewPackSize - 1] = (MioneObj){
                            .ObjType = 5,
                            .Val = ChildCount.Value[index]
                        };
                    }

                    for (int index = i + 1; index < PackSize; index++)
                    {
                        NewPackSize++;
                        NewPack = realloc(NewPack, NewPackSize * sizeof(MioneObj));
                        NewPack[NewPackSize - 1] = Pack[index];
                    }

                    Pack = NewPack;
                    PackSize = NewPackSize;

                    i = FirstBracketIndex;



                    if (FirstBracketIndex > 0)
                    {

                        if (Pack[FirstBracketIndex - 1].ObjType == 4 || Pack[FirstBracketIndex - 1].ObjType == 5)
                        {

                            if (Pack[FirstBracketIndex - 1].ObjType == 4)
                            {

                                if (Pack[FirstBracketIndex - 1].Var.V.ValueType == 4)
                                {

                                    int ButterIndex = WorkOnMioIndex;
                                    WorkOnMioIndex = Pack[FirstBracketIndex - 1].Var.V.Area.Index;
                                    Function( Pack[FirstBracketIndex - 1].Var.V.Area.Area, Pack[FirstBracketIndex - 1].Var.V.Area.Size);


                                    //todo function call
                                    WorkOnMioIndex = ButterIndex;
                                }
                                else
                                {
                                    char *str1 = "The Type of `";
                                    char *str2 = "` isn't a FUNCTION";
                                    char *VName = Pack[FirstBracketIndex - 1].Var.Name;

                                    char *REASON = malloc(sizeof(char) * (int)(strlen(str1) + strlen(str2) + strlen(VName) + 1));
                                    strcpy(REASON, str1);
                                    strcat(REASON, VName);
                                    strcat(REASON, str2);

                                    ErrCall(
                                        REASON,
                                            "MG001",
                                        "Maybe you can change the Variable Type to FUNCTION."
                                    );
                                }
                            }
                            else
                            {
                                if (Pack[FirstBracketIndex - 1].Val.ValueType == 4)
                                {

                                    int ButterIndex = WorkOnMioIndex;
                                    WorkOnMioIndex = Pack[FirstBracketIndex - 1].Val.Area.Index;
                                    Function( Pack[FirstBracketIndex - 1].Val.Area.Area, Pack[FirstBracketIndex - 1].Val.Area.Size);
                                    //todo function call
                                    WorkOnMioIndex = ButterIndex;
                                }
                                else
                                {
                                    ErrCall(
                                        "The Value before `()` Isn't a Function",
                                        "MG002",
                                        "Maybe you can try `function() <...:Mione> end()`."
                                    );
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if(!IfBrackets)
                {
                    switch (Pack[i].Symbol.SymbolType)
                    {
                    case 1:
                        if (i == PackSize - 1 || i - 1 <0)
                        {
                            ErrCall(
                                "You can't connect any Two-side-count-symbols to VOID (Meaning Nothing, even no Mione Object).",
                                "MG003",
                                "Maybe you can try `1+1` or anything else."
                            );
                        }
                        for (int index = 0; index < sizeof(Symbols)/sizeof(Symbols[0]); index++)
                        {
                            if (Symbols[index].xIndex == CalculateLevel) if (strcmp(Symbols[index].Name, Pack[i].Symbol.Name) == 0)CalculateType = Symbols[index].CurNumber;
                        }
                        break;
                    case 2:
                        if (i == PackSize - 1)
                        {
                            ErrCall(
                                "bbbbb",
                                "MG007",
                                "Maybe you can try `typeof 1` or anything else."
                            );
                        }
                        for (int index = 0; index < sizeof(Symbols)/sizeof(Symbols[0]); index++)
                        {
                            if (Symbols[index].xIndex == CalculateLevel) if (strcmp(Symbols[index].Name, Pack[i].Symbol.Name) == 0)CalculateType = Symbols[index].CurNumber;
                        }
                       break;
                    case 3:
                        if (i == PackSize - 1)
                        {
                            ErrCall(
                               "ccccc",
                               "MG008",
                               "Maybe you can try `- 1` or anything else."
                           );
                        }

                        for (int index = 0; index < sizeof(Symbols)/sizeof(Symbols[0]); index++)
                        {
                            if (strcmp(Symbols[index].Name, Pack[i].Symbol.Name) == 0)
                            {

                                if (i-1>=0 && (Pack[i-1].ObjType == 4 || Pack[i-1].ObjType == 5))
                                {
                                    if (Symbols[index].yIndex == CalculateLevel)  CalculateType = Symbols[index].CurNumber;
                                }else
                                {

                                    if (Symbols[index].xIndex == CalculateLevel) CalculateType = Symbols[index].CurNumber;
                                }

                            }

                        }
                        break;
                    }

                }
            }
        }else if (Pack[i].ObjType == 4 || Pack[i].ObjType == 5)
        {
            if (CalculateType)
            {
                MioneObj Out;
                int UsePointNumber = 0;

                switch (CalculateType)
                {
                    case 1: // +

                        if (Pack[i - 2].ObjType == 4 || Pack[i - 2].ObjType == 5)
                        {
                            if (Pack[i - 2].ObjType == 4) if (Pack[i - 2].Var.V.ValueType == 3) UsePointNumber = 1;
                            if (Pack[i - 2].ObjType == 5) if (Pack[i - 2].Val.ValueType == 3) UsePointNumber = 1;
                            if (Pack[i].ObjType == 4) if (Pack[i].Var.V.ValueType == 3) UsePointNumber = 1;
                            if (Pack[i].ObjType == 5) if (Pack[i].Val.ValueType == 3) UsePointNumber = 1;

                            if (UsePointNumber)
                            {
                                long double Value1 = 0;
                                long double Value2 = 0;

                                if (Pack[i - 2].ObjType == 4)
                                {
                                    if (Pack[i - 2].Var.V.ValueType == 3)
                                    {
                                        Value1 = Pack[i - 2].Var.V.PNumber;
                                    }
                                    else
                                    {
                                        Value1 = (long double)Pack[i - 2].Var.V.NPNumber;
                                    }
                                }
                                else
                                {
                                    if (Pack[i - 2].Val.ValueType == 3)
                                    {
                                        Value1 = Pack[i - 2].Val.PNumber;
                                    }
                                    else
                                    {
                                        Value1 = (long double)Pack[i - 2].Val.NPNumber;
                                    }
                                }

                                if (Pack[i].ObjType == 4)
                                {
                                    if (Pack[i].Var.V.ValueType == 3)
                                    {
                                        Value2 = Pack[i].Var.V.PNumber;
                                    }
                                    else
                                    {
                                        Value2 = (long double)Pack[i].Var.V.NPNumber;
                                    }
                                }
                                else
                                {
                                    if (Pack[i].Val.ValueType == 3)
                                    {
                                        Value2 = Pack[i].Val.PNumber;
                                    }
                                    else
                                    {
                                        Value2 = (long double)Pack[i].Val.NPNumber;
                                    }
                                }

                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 3,
                                        .PNumber = Value1 + Value2,
                                    }
                                };
                            }
                            else
                            {
                                long int Value1 = 0;
                                long int Value2 = 0;

                                if (Pack[i - 2].ObjType == 4)
                                {
                                    Value1 = Pack[i - 2].Var.V.NPNumber;
                                }
                                else
                                {
                                    Value1 = Pack[i - 2].Val.NPNumber;
                                }

                                if (Pack[i].ObjType == 4)
                                {
                                    Value2 = Pack[i].Var.V.NPNumber;
                                }
                                else
                                {
                                    Value2 = Pack[i].Val.NPNumber;
                                }

                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 2,
                                        .NPNumber = Value1 + Value2,
                                    }
                                };
                            }
                        }
                        else
                        {
                            ErrCall(
                                "You must only connect Two-side-count-symbols to VV(Variable or Value).",
                                "MG005",
                                "Maybe you can try `1+1` or anything else."
                            );
                        }
                        CalculateType = 0;
                        break;

                    case 3: // *

                        if (Pack[i - 2].ObjType == 4 || Pack[i - 2].ObjType == 5)
                        {
                            if (Pack[i - 2].ObjType == 4) if (Pack[i - 2].Var.V.ValueType == 3) UsePointNumber = 1;
                            if (Pack[i - 2].ObjType == 5) if (Pack[i - 2].Val.ValueType == 3) UsePointNumber = 1;
                            if (Pack[i].ObjType == 4) if (Pack[i].Var.V.ValueType == 3) UsePointNumber = 1;
                            if (Pack[i].ObjType == 5) if (Pack[i].Val.ValueType == 3) UsePointNumber = 1;

                            if (UsePointNumber)
                            {
                                long double Value1 = 0;
                                long double Value2 = 0;

                                if (Pack[i - 2].ObjType == 4)
                                {
                                    if (Pack[i - 2].Var.V.ValueType == 3)
                                    {
                                        Value1 = Pack[i - 2].Var.V.PNumber;
                                    }
                                    else
                                    {
                                        Value1 = (long double)Pack[i - 2].Var.V.NPNumber;
                                    }
                                }
                                else
                                {
                                    if (Pack[i - 2].Val.ValueType == 3)
                                    {
                                        Value1 = Pack[i - 2].Val.PNumber;
                                    }
                                    else
                                    {
                                        Value1 = (long double)Pack[i - 2].Val.NPNumber;
                                    }
                                }

                                if (Pack[i].ObjType == 4)
                                {
                                    if (Pack[i].Var.V.ValueType == 3)
                                    {
                                        Value2 = Pack[i].Var.V.PNumber;
                                    }
                                    else
                                    {
                                        Value2 = (long double)Pack[i].Var.V.NPNumber;
                                    }
                                }
                                else
                                {
                                    if (Pack[i].Val.ValueType == 3)
                                    {
                                        Value2 = Pack[i].Val.PNumber;
                                    }
                                    else
                                    {
                                        Value2 = (long double)Pack[i].Val.NPNumber;
                                    }
                                }

                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 3,
                                        .PNumber = Value1 * Value2,
                                    }
                                };
                            }
                            else
                            {
                                long int Value1 = 0;
                                long int Value2 = 0;

                                if (Pack[i - 2].ObjType == 4)
                                {
                                    Value1 = Pack[i - 2].Var.V.NPNumber;
                                }
                                else
                                {
                                    Value1 = Pack[i - 2].Val.NPNumber;
                                }

                                if (Pack[i].ObjType == 4)
                                {
                                    Value2 = Pack[i].Var.V.NPNumber;
                                }
                                else
                                {
                                    Value2 = Pack[i].Val.NPNumber;
                                }

                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 2,
                                        .NPNumber = Value1 * Value2,
                                    }
                                };
                            }
                        }
                        else
                        {
                            ErrCall(
                                "You must only connect Two-side-count-symbols to VV(Variable or Value).",
                                "MG005",
                                "Maybe you can try `1*1` or anything else."
                            );
                        }
                        CalculateType = 0;
                        break;
                    case 5: // ^
                        
                        if (Pack[i - 2].ObjType == 4 || Pack[i - 2].ObjType == 5)
                        {
                            if (Pack[i - 2].ObjType == 4) if (Pack[i - 2].Var.V.ValueType == 3) UsePointNumber = 1;
                            if (Pack[i - 2].ObjType == 5) if (Pack[i - 2].Val.ValueType == 3) UsePointNumber = 1;
                            if (Pack[i].ObjType == 4) if (Pack[i].Var.V.ValueType == 3) UsePointNumber = 1;
                            if (Pack[i].ObjType == 5) if (Pack[i].Val.ValueType == 3) UsePointNumber = 1;

                            if (UsePointNumber)
                            {
                                long double Value1 = 0;
                                long double Value2 = 0;

                                if (Pack[i - 2].ObjType == 4)
                                {
                                    if (Pack[i - 2].Var.V.ValueType == 3)
                                    {
                                        Value1 = Pack[i - 2].Var.V.PNumber;
                                    }
                                    else
                                    {
                                        Value1 = (long double)Pack[i - 2].Var.V.NPNumber;
                                    }
                                }
                                else
                                {
                                    if (Pack[i - 2].Val.ValueType == 3)
                                    {
                                        Value1 = Pack[i - 2].Val.PNumber;
                                    }
                                    else
                                    {
                                        Value1 = (long double)Pack[i - 2].Val.NPNumber;
                                    }
                                }

                                if (Pack[i].ObjType == 4)
                                {
                                    if (Pack[i].Var.V.ValueType == 3)
                                    {
                                        Value2 = Pack[i].Var.V.PNumber;
                                    }
                                    else
                                    {
                                        Value2 = (long double)Pack[i].Var.V.NPNumber;
                                    }
                                }
                                else
                                {
                                    if (Pack[i].Val.ValueType == 3)
                                    {
                                        Value2 = Pack[i].Val.PNumber;
                                    }
                                    else
                                    {
                                        Value2 = (long double)Pack[i].Val.NPNumber;
                                    }
                                }

                                long double Value3 = Value1;
                                for (int p = 1; p < (int)Value2; p++) Value3 *= Value1;

                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 3,
                                        .PNumber = Value3
                                    }
                                };
                            }
                            else
                            {
                                long int Value1 = 0;
                                long int Value2 = 0;

                                if (Pack[i - 2].ObjType == 4)
                                {
                                    Value1 = Pack[i - 2].Var.V.NPNumber;
                                }
                                else
                                {
                                    Value1 = Pack[i - 2].Val.NPNumber;
                                }

                                if (Pack[i].ObjType == 4)
                                {
                                    Value2 = Pack[i].Var.V.NPNumber;
                                }
                                else
                                {
                                    Value2 = Pack[i].Val.NPNumber;
                                }

                                long int Value3 = Value1;
                                for (int p = 1; p < Value2; p++) Value3 *= Value1;

                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 2,
                                        .NPNumber = Value3
                                    }
                                };
                            }
                        }
                        else
                        {
                            ErrCall(
                                "You must only connect Two-side-count-symbols to VV(Variable or Value).",
                                "MG005",
                                "Maybe you can try `1^1` or anything else."
                            );
                        }
                        CalculateType = 0;
                        break;
                case 6: //-

                    if (i-2>=0 && (Pack[i - 2].ObjType == 4 || Pack[i - 2].ObjType == 5))
                    {
                        // 1- 1
                        if (Pack[i - 2].ObjType == 4) if (Pack[i - 2].Var.V.ValueType == 3) UsePointNumber = 1;
                            if (Pack[i - 2].ObjType == 5) if (Pack[i - 2].Val.ValueType == 3) UsePointNumber = 1;
                            if (Pack[i].ObjType == 4) if (Pack[i].Var.V.ValueType == 3) UsePointNumber = 1;
                            if (Pack[i].ObjType == 5) if (Pack[i].Val.ValueType == 3) UsePointNumber = 1;

                            if (UsePointNumber)
                            {
                                long double Value1 = 0;
                                long double Value2 = 0;

                                if (Pack[i - 2].ObjType == 4)
                                {
                                    if (Pack[i - 2].Var.V.ValueType == 3)
                                    {
                                        Value1 = Pack[i - 2].Var.V.PNumber;
                                    }
                                    else
                                    {
                                        Value1 = (long double)Pack[i - 2].Var.V.NPNumber;
                                    }
                                }
                                else
                                {
                                    if (Pack[i - 2].Val.ValueType == 3)
                                    {
                                        Value1 = Pack[i - 2].Val.PNumber;
                                    }
                                    else
                                    {
                                        Value1 = (long double)Pack[i - 2].Val.NPNumber;
                                    }
                                }

                                if (Pack[i].ObjType == 4)
                                {
                                    if (Pack[i].Var.V.ValueType == 3)
                                    {
                                        Value2 = Pack[i].Var.V.PNumber;
                                    }
                                    else
                                    {
                                        Value2 = (long double)Pack[i].Var.V.NPNumber;
                                    }
                                }
                                else
                                {
                                    if (Pack[i].Val.ValueType == 3)
                                    {
                                        Value2 = Pack[i].Val.PNumber;
                                    }
                                    else
                                    {
                                        Value2 = (long double)Pack[i].Val.NPNumber;
                                    }
                                }



                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 3,
                                        .PNumber = Value1-Value2
                                    }
                                };
                            }
                            else
                            {
                                long int Value1 = 0;
                                long int Value2 = 0;

                                if (Pack[i - 2].ObjType == 4)
                                {
                                    Value1 = Pack[i - 2].Var.V.NPNumber;
                                }
                                else
                                {
                                    Value1 = Pack[i - 2].Val.NPNumber;
                                }

                                if (Pack[i].ObjType == 4)
                                {
                                    Value2 = Pack[i].Var.V.NPNumber;
                                }
                                else
                                {
                                    Value2 = Pack[i].Val.NPNumber;
                                }



                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 2,
                                        .NPNumber = Value1-Value2
                                    }
                                };
                            }
                    }else
                    {
                        // -1
                        if (Pack[i].ObjType == 4) if (Pack[i].Var.V.ValueType == 3) UsePointNumber = 1;
                        if (Pack[i].ObjType == 5) if (Pack[i].Val.ValueType == 3) UsePointNumber = 1;


                        if (Pack[i].ObjType == 4)
                        {
                            if (UsePointNumber)
                            {
                                long double Value1 = 0;

                                Value1 = Pack[i].Var.V.PNumber*-1;

                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 3,
                                        .PNumber = Value1
                                    }
                                };
                            }else
                            {
                                long int Value1 = 0;

                                Value1 = Pack[i].Var.V.NPNumber*-1;


                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 2,
                                        .NPNumber = Value1
                                    }
                                };
                            }

                        }else
                        {
                            if (UsePointNumber)
                            {
                                long double Value1 = 0;

                                Value1 = Pack[i].Val.PNumber*-1;

                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 3,
                                        .PNumber = Value1
                                    }
                                };
                            }else
                            {
                                long int Value1 = 0;

                                Value1 = Pack[i].Val.NPNumber*-1;



                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 2,
                                        .NPNumber = Value1
                                    }
                                };
                            }
                        }

                    }

                    break;
                    default:
                        break;
                }

                MioneObj* NewPack = malloc(0);
                int NewPackSize = 0;

                for (int index = 0; index < i - 2; index++)
                {
                    NewPackSize++;
                    NewPack = realloc(NewPack, sizeof(MioneObj) * (NewPackSize));
                    NewPack[NewPackSize - 1] = Pack[index];
                }

                NewPackSize++;
                NewPack = realloc(NewPack, sizeof(MioneObj) * (NewPackSize));
                NewPack[NewPackSize - 1] = Out;
                int ToIndex = NewPackSize - 1;

                for (int index = i + 1; index < PackSize; index++)
                {
                    NewPackSize++;
                    NewPack = realloc(NewPack, sizeof(MioneObj) * (NewPackSize));
                    NewPack[NewPackSize - 1] = Pack[index];
                }

                PackSize = NewPackSize;
                Pack = NewPack;

                i = ToIndex;
            }
        }

        if (IfBrackets)
        {
            if (Pack[i].ObjType == 3 && strcmp(Pack[i].Symbol.Name, "(") == 0) {}
            else
            {
                inBracketSize++;
                inBracket = realloc(inBracket, sizeof(MioneObj) * (inBracketSize));
                inBracket[inBracketSize - 1] = Pack[i];
            }
        }

        if (i == PackSize - 1)
        {
            CalculateLevel++;
            i = 0;
            if (CalculateLevel > 3) { break; }
        }
    }

    ValueObj * VPack = malloc(0);
    int VPackSize = 0;


    for (int i = 0; i < PackSize; i++)
    {
       if ( Pack[i].ObjType == 5)
       {
           VPackSize ++;
           VPack = realloc(VPack, sizeof(MioneObj) * (VPackSize));
           VPack[VPackSize-1] = Pack[i].Val;
           printf("d %d\n",Pack[i].Val.NPNumber);
       }
    }

    CountObj Returns = (CountObj){
        .Value = VPack,
        .ValueSize= VPackSize
    };


    return Returns;
}

#endif // COUNT_H
