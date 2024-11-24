//
// Created by calle on 24-11-23.
//


RequestObj REQUEST(MioneObj*Objs, int ObjsSize);

#ifndef REQUEST_H
#define REQUEST_H

RequestObj REQUEST(MioneObj*Objs, int ObjsSize)
{

    for (int i = 0; i < ObjsSize; i++)
    {
        if (Objs[i].ObjType == 3)
        {
            if(strcmp(Objs[i].Text, ",") == 0){
                
            }else
            {
                ErrCall("","AAA","");
            }
        }
    }
}

#endif //REQUEST_H
