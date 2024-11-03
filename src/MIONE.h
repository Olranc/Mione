//
// Created by calle on 24-10-25.
//


void mione(const MioneObj* Objs ,const int ObjsSize,int *Rows);

#ifndef MIONE_H
#define MIONE_H


void mione(const MioneObj* Objs ,const int ObjsSize,int *Rows)
{
    //system("clear");
    int (*Head)(struct _PairObject*Pairs,int PairsSize) = 0;

    PairObj *Pairs = malloc(0);
    int PairsSize = 0;






    for(int index=0;index<ObjsSize;index++)
    {

        MioneObj Mio = Objs[index];

        if ((Mio.ObjType == 3 && strcmp(Mio.Text,";")) ||
            ObjsSize-1 == index ||
            Mio.ObjType == 1
            ) if (Head!=0)
        {
            int IndexUseless = Head(Pairs,PairsSize);
            index = index-IndexUseless;

            Head = 0;
            Pairs = NULL;
            PairsSize = 0;
        }

        if (Mio.ObjType == 1) //HEAD
        {

            for (int i = 0; i <sizeof(Heads)/sizeof(Heads[0]); i++)
                if (strcmp(Mio.Text,Heads[i].Name) == 0)
                {

                    PairsSize++;
                    Pairs = realloc(Pairs,sizeof(struct _PairObject)*PairsSize);
                    Pairs[PairsSize-1].Prompt = Mio; // Type = 1


                    Pairs[PairsSize-1].SourceSize = 0;
                    Pairs[PairsSize-1].Source = malloc(0);



                    Head = Heads[i].Fuc;
                    //Pairs.Prompt = (MioneObj){};
                }
            }


        if (Mio.ObjType == 2) // PROMPT
        {
            Pairs[PairsSize-1].SourceSize++;
            Pairs[PairsSize-1].Source = realloc(Pairs[PairsSize-1].Source,sizeof(MioneObj)*Pairs[PairsSize-1].SourceSize);
            Pairs[PairsSize-1].Source[Pairs[PairsSize-1].SourceSize-1] = Mio;
        }

        if (Mio.ObjType == 3 || Mio.ObjType == 4 || Mio.ObjType == 5) // SVV
        {
            if (Head==0) { //偽Head
                PairsSize++;
                Pairs = realloc(Pairs,sizeof(struct _PairObject)*PairsSize);
                Pairs[PairsSize-1].Prompt = Mio; // Type = 1


                Pairs[PairsSize-1].SourceSize = 0;
                Pairs[PairsSize-1].Source = malloc(0);

                Head = SVV;
            }

            Pairs[PairsSize-1].SourceSize++;
            Pairs[PairsSize-1].Source = realloc(Pairs[PairsSize-1].Source,sizeof(MioneObj)*Pairs[PairsSize-1].SourceSize);
            Pairs[PairsSize-1].Source[Pairs[PairsSize-1].SourceSize-1] = Mio;
        }
    }
}

#endif //MIONE_H
