//
// Created by calle on 24-7-26.
//


struct valueObject;
struct mioneObject;
struct variableObject;

#ifndef OBJ_H
#define OBJ_H

typedef struct valueObject
{
    //值的類別
    int ValueType;

    //數字
    int NoPointNumber;
    double PointNumber;

    //字串
    char* String;

    //表單
    struct valueObject* Table;

    //函數
    struct mioneObject* Fuc;

} valObj;

typedef struct variableObject
{
    char*Name;
    struct valueObject Value;
}
varObj;

typedef struct mioneObject
{
    int CaseType;

    int CaseSelf; //if CaseType == 1,2,3

    struct variableObject variable_object; //if CaseType == 4

    struct valueObject  value_object; //if CaseType == 5
} mioObj;



#endif //OBJ_H
