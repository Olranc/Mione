//
// Created by calle on 24-7-27.
//

valObj createValue(char*Case,int caseValue);

#ifndef VALUE_H
#define VALUE_H

valObj createValue(char*Case,int caseValue)
{
    valObj obj;
    obj.ValueType = caseValue == 2 ? 1 :
                      caseValue == 3 ? 4 :
                      caseValue == 4 ? 5 :
                      caseValue == 5 ? 2 :
                      caseValue == 6 ? 3 : 0;
    if (obj.ValueType == 1)
    {
        obj.String = Case;
    }else if (obj.ValueType == 2)
    {
       obj.NoPointNumber = atoi(Case);
    }else if (obj.ValueType == 3)
    {
        obj.PointNumber = atof(Case);
    }else if (obj.ValueType == 4)
    {
        //obj
    }


    return obj;
}

#endif //VALUE_H
