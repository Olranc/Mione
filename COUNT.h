//
// Created by calle on 24-11-3.
//

ValueObj* COUNT(MioneObj*Pack,int PackSize);


#ifndef COUNT_H
#define COUNT_H

ValueObj* COUNT(MioneObj*Pack,int PackSize)
{
    int FirstBracketIndex = 0;
    int IfBrackets = 0; // 0 = 0 1 = only ( 2 = ()
    int PairsOfBrackets = 0;


    for(int i = 0;i <PackSize;i++)
    {
        if (Pack[i].ObjType == 3) // S
        {

            if (strcmp(Pack[i].Text,"(")==0)
            {
                FirstBracketIndex = i;
                IfBrackets=1;

            }else if (strcmp(Pack[i].Text,")")==0)
            {
                if (IfBrackets)
                {
                    PairsOfBrackets++;
                    IfBrackets = 0;

                    if (Pack[FirstBracketIndex-1].ObjType == 4 || Pack[FirstBracketIndex-1].ObjType == 5){
                        if (Pack[FirstBracketIndex-1].ObjType == 4)
                        {
                            if(Pack[FirstBracketIndex-1].Var.V.ValueType == 4)
                            {

                            }else
                            {

                                ErrCall("The Type of the Value isn't FUNCTION","M001");
                            }

                        }else
                        {
                            if(Pack[FirstBracketIndex-1].Area.ValueType == 4)
                            {

                            }else
                            {
                                    //HOW??
                            }
                        }

                    }
                };
            }
        }
    }
}

#endif //COUNT_H
