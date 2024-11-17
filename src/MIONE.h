//
// Created by calle on 24-10-25.
//


void mione(const MioneObj* Objs ,const int ObjsSize,int *Rows);



#ifndef MIONE_H
#define MIONE_H




void mione(const MioneObj* Objs ,const int ObjsSize,int *Rows)
{
    //system("clear");


    MioneObj Head = (MioneObj){
        .ObjType = 0
    };
    
    int (*HeadFuc)(struct _PairObject*Pairs,int PairsSize) = 0;

    PairObj *Pairs = malloc(0);
    int PairsSize = 0;


    for(int index=0;index<ObjsSize;index++)
    {

        MioneObj Mio = Objs[index];

        if (Mio.ObjType == 1) Head = Mio;

        if ((Mio.ObjType == 3 && strcmp(Mio.Text,";")==0) || Mio.ObjType == 1)
        {
            if (HeadFuc!=0) {
                int IndexUseless = HeadFuc(Pairs,PairsSize);
                index = index-IndexUseless;

                HeadFuc = 0;
                Pairs = NULL;
                PairsSize = 0;


            }
        }




        if (Mio.ObjType == 1) //Head
        {

            for (int i = 0; i <sizeof(Heads)/sizeof(Heads[0]); i++)
                if (strcmp(Mio.Text,Heads[i].Name) == 0)
                {

                    PairsSize++;
                    Pairs = realloc(Pairs,sizeof(struct _PairObject)*PairsSize);
                    Pairs[PairsSize-1].Prompt = Mio; // Type = 1


                    Pairs[PairsSize-1].SourceSize = 0;
                    Pairs[PairsSize-1].Source = malloc(0);



                    HeadFuc = Heads[i].Fuc;
                    //Pairs.Prompt = (MioneObj){};
                }
            }


        if (Mio.ObjType == 2) // PROMPT
        {
            PairsSize++;
            Pairs[PairsSize-1].SourceSize=0;
            Pairs[PairsSize-1].Source = malloc(0);
            Pairs[PairsSize-1].Prompt = Mio; // Type = 2
        }

        if (Mio.ObjType == 3 || Mio.ObjType == 4 || Mio.ObjType == 5) // SVV
        {
            if (Head.ObjType==0) { //偽HeadFuc
                PairsSize++;
                Pairs = realloc(Pairs,sizeof(struct _PairObject)*PairsSize);
                Pairs[PairsSize-1].Prompt = Head; // Type = 1


                Pairs[PairsSize-1].SourceSize = 0;
                Pairs[PairsSize-1].Source = malloc(0);

                HeadFuc = SVV;
            }

            Pairs[PairsSize-1].SourceSize++;
            Pairs[PairsSize-1].Source = realloc(Pairs[PairsSize-1].Source,sizeof(MioneObj)*Pairs[PairsSize-1].SourceSize);
            Pairs[PairsSize-1].Source[Pairs[PairsSize-1].SourceSize-1] = Mio;
        }

        if (ObjsSize-1 == index )
        {

            if (HeadFuc!=0) {
                int IndexUseless = HeadFuc(Pairs,PairsSize);
                index = index-IndexUseless;

                HeadFuc = 0;
                Pairs = NULL;
                PairsSize = 0;


            }
        }
        WorkOnMioIndex++;
    }
}

#endif //MIONE_H
