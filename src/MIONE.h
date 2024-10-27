//
// Created by calle on 24-10-25.
//

#include "OBJECTS.h"
void mione(const MioneObj* Objs ,const int ObjsSize,int *Rows);

#ifndef MIONE_H
#define MIONE_H





void mione(const MioneObj* Objs ,const int ObjsSize,int *Rows)
{
    //system("clear");
    int (*Fuc)(struct _PairObject*Pairs,int PairsSize) = 0;

    PairObj Pairs;

    Pairs.Source = malloc(0);
    Pairs.SourceSize = 0;




    for(int index=0;index<ObjsSize;index++)
    {
        MioneObj Mio = Objs[index];

        if (Mio.ObjType == 1) //HEAD
        {
            for (int i = 0; i <sizeof(Heads)/sizeof(Heads[0]); i++) if (Heads[i].Name == Mio.Text)
            {
                int (*Fuc)(struct _PairObject*Pairs,int PairsSize) = Heads[i].Fuc;
                //Pairs.Prompt = (MioneObj){};
            }
        }

        if (Mio.ObjType == 3 || Mio.ObjType == 4 || Mio.ObjType == 5)
        {
            Pairs.SourceSize++;
            Pairs.Source = realloc(Pairs.Source,sizeof(MioneObj)*Pairs.SourceSize);
            Pairs.Source[Pairs.SourceSize-1] = Mio;
        }
    }

}

#endif //MIONE_H
