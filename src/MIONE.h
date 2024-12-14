//
// Created by calle on 24-10-25.
//


void mione(const MioneObj* Objs ,const int ObjsSize);
MioneObj * Function(const MioneObj* Objs ,const int ObjsSize);

#ifndef MIONE_H
#define MIONE_H

#include "main.h"

MioneObj * Function(const MioneObj* Objs, const int ObjsSize)
{

    MioneObj Head = (MioneObj) {
        .ObjType = 0
    };

    int (*HeadFuc)(struct _PairObject* Pairs, int PairsSize) = 0;
    PairObj *Pairs = malloc(0);
    int PairsSize = 0;

    int inFucReq = 0;

    MioneObj * FucReqs = malloc(0);
    int FucReqsSize = 0;

    for (int index = 0; index < ObjsSize; index++)
    {

        if (inFucReq)
        {

            if (Objs[index].ObjType == 3 && strcmp(Objs[index].Symbol.Name, ")") == 0)
            {
                printf("AAA %d\n",FucReqsSize);

                RequestObj Req = REQUEST(FucReqs, FucReqsSize);
            }
            else
            {
                FucReqsSize++;
                FucReqs = realloc(FucReqs, sizeof(MioneObj) * FucReqsSize);
                FucReqs[FucReqsSize - 1] = Objs[index];
            }
        }
        else
        {
            if (index == 0)
            {
                if (Objs[index].ObjType == 3 && strcmp(Objs[index].Symbol.Name, "(") == 0) inFucReq = 1;
                else ErrCall("Function Request didn't work.", "MG006", "");
            }
            else
            {
                MioneObj Mio = Objs[index];

                if (Mio.ObjType == 1) Head = Mio;

                if ((Mio.ObjType == 3 && strcmp(Mio.Symbol.Name, ";") == 0) || Mio.ObjType == 1)
                {
                    if (HeadFuc != 0) {
                        int IndexUseless = HeadFuc(Pairs, PairsSize);
                        index = index - IndexUseless;

                        HeadFuc = 0;
                        Pairs = NULL;
                        PairsSize = 0;
                    }
                }

                if (Mio.ObjType == 1) // Head
                {
                    for (int i = 0; i < sizeof(HeadFucs) / sizeof(HeadFucObj); i++)
                    {
                        if (strcmp(Mio.Head.Name, HeadFucs[i].Name) == 0)
                        {
                            PairsSize++;
                            Pairs = realloc(Pairs, sizeof(struct _PairObject) * PairsSize);
                            Pairs[PairsSize - 1].Prompt = Mio; // Type = 1

                            Pairs[PairsSize - 1].SourceSize = 0;
                            Pairs[PairsSize - 1].Source = malloc(0);

                            HeadFuc = HeadFucs[i].Fuc;
                        }
                    }
                }

                if (Mio.ObjType == 2) // PROMPT
                {
                    PairsSize++;
                    Pairs = realloc(Pairs, sizeof(struct _PairObject) * PairsSize);

                    Pairs[PairsSize - 1].SourceSize = 0;
                    Pairs[PairsSize - 1].Source = malloc(0);
                    Pairs[PairsSize - 1].Prompt = Mio; // Type = 2
                }

                if (Mio.ObjType == 3 || Mio.ObjType == 4 || Mio.ObjType == 5) // SVV
                {
                    if (Head.ObjType == 0) { // 偽HeadFuc
                        PairsSize++;
                        Pairs = realloc(Pairs, sizeof(struct _PairObject) * PairsSize);
                        Pairs[PairsSize - 1].Prompt = Mio; // 自主

                        Pairs[PairsSize - 1].SourceSize = 0;
                        Pairs[PairsSize - 1].Source = malloc(0);

                        HeadFuc = SVV;
                    }

                    (Pairs[PairsSize - 1].SourceSize)++;
                    (Pairs[PairsSize - 1].Source) = realloc(Pairs[PairsSize - 1].Source, sizeof(MioneObj) * (Pairs[PairsSize - 1].SourceSize));
                    Pairs[PairsSize - 1].Source[Pairs[PairsSize - 1].SourceSize - 1] = Mio;
                }

                if (ObjsSize - 1 == index)
                {
                    if (HeadFuc != 0) {
                        int IndexUseless = HeadFuc(Pairs, PairsSize);
                        index = index - IndexUseless;

                        HeadFuc = 0;
                        Pairs = NULL;
                        PairsSize = 0;
                    }
                }
            }
        }
        WorkOnMioIndex++;

    }
}

void mione(const MioneObj* Objs, const int ObjsSize)
{
    // system("clear");

    MioneObj Head = (MioneObj) {
        .ObjType = 0
    };

    int (*HeadFuc)(struct _PairObject* Pairs, int PairsSize) = 0;
    PairObj *Pairs = malloc(0);
    int PairsSize = 0;

    for (int index = 0; index < ObjsSize; index++)
    {
        MioneObj Mio = Objs[index];

        if (Mio.ObjType == 1) Head = Mio;

        if ((Mio.ObjType == 3 && strcmp(Mio.Symbol.Name, ";") == 0) || Mio.ObjType == 1)
        {
            if (HeadFuc != 0) {
                int IndexUseless = HeadFuc(Pairs, PairsSize);
                index = index - IndexUseless;

                HeadFuc = 0;
                Pairs = NULL;
                PairsSize = 0;
            }
        }

        if (Mio.ObjType == 1) // Head
        {
            for (int i = 0; i < sizeof(HeadFucs) / sizeof(HeadFucs[0]); i++)
            {
                if (strcmp(Mio.Head.Name, HeadFucs[i].Name) == 0)
                {
                    PairsSize++;
                    Pairs = realloc(Pairs, sizeof(struct _PairObject) * PairsSize);
                    Pairs[PairsSize - 1].Prompt = Mio; // Type = 1

                    Pairs[PairsSize - 1].SourceSize = 0;
                    Pairs[PairsSize - 1].Source = malloc(0);

                    HeadFuc = HeadFucs[i].Fuc;
                }
            }
        }

        if (Mio.ObjType == 2) // PROMPT
        {
            PairsSize++;
            Pairs = realloc(Pairs, sizeof(struct _PairObject) * PairsSize);

            Pairs[PairsSize - 1].SourceSize = 0;
            Pairs[PairsSize - 1].Source = malloc(0);
            Pairs[PairsSize - 1].Prompt = Mio; // Type = 2
        }

        if (Mio.ObjType == 3 || Mio.ObjType == 4 || Mio.ObjType == 5) // SVV
        {
            if (Head.ObjType == 0) { // 偽HeadFuc
                PairsSize++;
                Pairs = realloc(Pairs, sizeof(struct _PairObject) * PairsSize);
                Pairs[PairsSize - 1].Prompt = Mio; // 自主

                Pairs[PairsSize - 1].SourceSize = 0;
                Pairs[PairsSize - 1].Source = malloc(0);

                HeadFuc = SVV;
            }

            (Pairs[PairsSize - 1].SourceSize)++;
            (Pairs[PairsSize - 1].Source) = realloc(Pairs[PairsSize - 1].Source, sizeof(MioneObj) * (Pairs[PairsSize - 1].SourceSize));
            Pairs[PairsSize - 1].Source[Pairs[PairsSize - 1].SourceSize - 1] = Mio;
        }

        if (ObjsSize - 1 == index)
        {
            if (HeadFuc != 0) {
                int IndexUseless = HeadFuc(Pairs, PairsSize);
                index = index - IndexUseless;

                HeadFuc = 0;
                Pairs = NULL;
                PairsSize = 0;
            }
        }
        WorkOnMioIndex++;
    }
}

#endif // MIONE_H
