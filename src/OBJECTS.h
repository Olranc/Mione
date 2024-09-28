//
// Created by chenn on 24-8-3.
//

typedef struct _MioneObject;
typedef struct _CaseObject;
typedef struct _ValueObject;
typedef struct _VariableObject;

#define HEAD 1
#define PROMPT 2
#define SYMBOL 3
#define VALUE 4
#define VARIABLE  5

#ifndef OBJECTS_H
#define OBJECTS_H

typedef struct _ValueObject
{
    int ValueType; //值類型
    /*
    1:字串
    2:整數
    3:浮點數
    4:函數
    5:執行式
    6:表單
    */
    struct _MioneObject * Area; //給於函數(function)或者執行式(range)。
    char * String; //給予文字(string)。
    long int NPNumber; //給予無小數點數字(no point number)。
    long double PNumber; //給予小數點數字(point number)。
    struct _ValueObject * Table; //給予表格(table)。
} ValueObj;

typedef struct _VariableObject
{
    char* Name; //變數名稱
    ValueObj V; //值
} VariableObj;

typedef struct _MioneObject
{
    int ObjType; //HPSVV宏 1H 2P 3S 4VAR 5VAL


    ValueObj Area;  //當ObjType為VALUE宏時，會用到此值。
    char* Text; //如果不是Value的話，將會採用此char*來儲存文字。

} MioneObj;

typedef struct _CaseObject
{
    int ObjType; /*
    CharType...
    */
    char * ObjName;
} CaseObj;





#endif //OBJECTS_H
