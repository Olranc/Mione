# Mione 🪶 
Mione programming language

## 前言
Mione是個輕量、手稿、簡潔、貼近自然語言的程式語言，不管男女老少都能輕鬆地上手。
Mione是My own的相似音，意思是「我所擁有的」，便讓使用者寫出的程式碼有成就感，my own program。


## Mione 五大類別

五大類別是組成Mione的最基本字詞單位。
舉個例子：

|Mione File|
|---|
|set x = 1+2|

而以下則是上方程式句的類別分類：

|詞 | 類別 |
|---| --- |
|set| Head，標頭 |
|x| Variable ，變數|
|=| Prompt，說明 |
|1| Value，立即值|
|+|Symbol ，符號|
|2|Value，立即值|

下方將會講解詳細的5大別類說明。


### 1 . HEAD，標頭
為大部分程式句的起始頭，主要是告訴直譯器程式句的具體目的為何。
Head有可以自行透過底層函數去提示或警告最低的Prompt或資源數量。 

常見的HEAD有：
|HEAD|
|---|
|set|
|input|
|for|
|if|
|while|
|return|

### 2 . PROMPT，說明
PROMPT後方一定要有資源。
為大部分程式句的補充說明。例如：
set x

而我們可以補充說明要讓這個x變數為多少：
= 1
合體之後：

|Mione File|
|---|
|set x = 1|


常見的PROMPT有：

|PROMPT|
|---|
|do|
|then|
|=|
|as|
|else|


### 3 . SYMBOL，符號
並不是只有符號能成為SYMBOL。
為每個VV（Value 或 Variable ）的算法符號，其中有些SYMBOL不具有算法功能。例如：
print()
“(“ 與 “)” 並不具有算法功能，而是一種包裝容器，也是一種函數呼叫符號（Mione直譯器會先查看是否有”(“符號，再去逐一的去偵測”)”才會呼叫函數。”(“與”)”必須在同一個層級，可支持多行列呼叫。）

常見的SYMBOL 有：

|SYMBOL|
|---|
|+|
|-|
|*|
|/|
|(|
|)|

### 4 . Variable，變數
是個變數，在未聲稱的情況下，所有變數將不會有任何值（Value）。
Variable 後方可接受PROMPT，目的則因PROMPT而異。例如：
|Mione File|
|---|
|x = 11|

這裡的 「=」符號是「設定」之意。與「set x = 11」相似。
|Mione File|
|---|
|y into table|

意指快速地讓「y」灌入至「table」的最後段（創建新空間，並讓y的值導入）。與「`table[table:len()+1]=y」`、「`table:new(y)`」相似。



### 5 . Value，立即值

**立即值只會在程式結束時才會從內存消失**

取名為立即值的原因是因為每個Value都只能創建一個新的Object，不會因為與之前對比有相同的數值而使用相同的內存位置。（Mione官方直譯器）

是個值，分為幾種不同的類型：
|類型|意思|
|---|---|
|String|字串|
|NPNumber|整數|
|PNumber|浮點數|
|Function|函數|
|Range|執行式|
|Table|表單|


## Mione架構

**本章節將會採用Mione官方的直譯器進行解析**



### 值類型



#### 1 . Value Object 
立即值的類型。
簡稱為ValueObj，在類型聲稱也使用ValueObj。
|內容物  |  說明|
|---  | ---|
|Int ValueType  |  Value值的類型。|
|AreaObj Area   | 給予函數或執行式的數值，僅在ValueType為4或5時才會使用到。|
|char* String  |  給予字串的數值，僅在ValueType為1時才會使用到。|
|long int NPNumber   | 給予無小數點數值，僅在ValueType為2時才會使用到。|
|long double PNumber |   給予小數點數值，僅在ValueType為3時才會使用到。|
|TableObj Table  |  給予表單數值，僅在ValueType為6時才會使用到。|

ValueType有這幾個固定數值：
|數值  |  類型|
|---  | ---|
|1  |  字串|
|2  |  整數|
|3  |  浮點數|
|4 |   函數|
|5  |  執行式|
|6   |  表單|




#### 2 . Mione Object
簡稱為MioneObj，類型聲明也以MioneObj使用。
在CTM（CASE_TO_MIONE）所編譯完的類型。
包住5大別類的類型容器。


|內容物 |   說明|
|---|---|
|int ObjType  |  此Mione Object的類型。|
|ValueObj Area |   當ObjType為5時，將會使用此數值。|
|char*Text  |  ObjType為5以外的數都將會使用到此數值。|

ObjType有以下5種類型：
|類型  |  HPSVV|
|---|---|
|1  |  Head，標頭|
|2  |  Prompt，說明|
|3  |  Symbol，符號|
|4  |  Variable，變數|
|5  |  Value，立即值|

#### 3 . Case Object
簡稱CaseObj，在聲稱中也以CaseObj形式出現。
為在FTC（FILE_TO_CASE）的回傳類型。

|內容物  |  說明|
|---|---|
|char* ObjName    |每個CASE本身。|
|int ObjType  |  ObjName最後字元的CharType。（可能因某些原因導致ObjType不會是最後字元的CharType。例如：Data3，因應字母、數字與符號的組合。）|


#### 4 . Variable Object
記錄變數本身。
簡稱為VariableObj，聲稱為VariableObj。

|內容物  |  說明|
|---|---|
|char* Name  |  變數名稱。|
|ValueObj V  |  變數的值。|

#### 5 . Area Object
記錄函數或執行式。
簡稱為AreaObj，聲稱為AreaObj。

|內容物 |   說明|
|---|---|
|int Size |   Area大小。|
|MioneObj* Area  |  函數或執行式本身。|

#### 6 . Table Object
記錄Table值。
簡稱為TableObj，聲稱為TableObj。

|內容物 |   說明|
|---|---|
|int Size   | Table大小。|
|VariableObj * Table  |  數值本身。若子項的Name為Null時，則以子項順序表示子項值位置。且計數器僅記錄這類子項。|



## 運行

### 1.檔案轉換成CaseObj（FTC，FILE_TO_CASE）
Mione直譯器會先將導入進來檔案內的字符位元組，再參考CharType逐一的去分配至不同的CaseObj。

String CaseObj的組成是先檢測「”」字元是否出現。若出現，那將把自身以及自身之後的所有字元包著，直到下個「”」出現。若有「/」字元在字串裡頭，那將會開啟「Super Char」模式，這時就不會去檢測「”」並結束字串。

CharType數值如下：
（以空格隔開每個相同CharType的字元，或是加以描述）
|字元   | CharType  |  說明|
|---|---|--|
|( ) [ ] { } |   10  |  不可連接符號。|
|. + - * /   | 9 |   可連接符號。|
|空格  |  11 |   空格。|
|\  |  12  |  字串特殊功能符號。|
|換行符號  |  13  |  10，換行符號（\n）。|
|負1  |  0  |  檔案結束標識符。|
|0至9  |  2  |  數字。|
|“  |  3  |  字串宣告符號。|
|‘ |   4  |  字串宣告符號2。|
|其餘  |  1  |  一般文字。|

未制定或廢棄的CharType：
|CharType|
|---|
|5|
|6|
|7|
|8|

所回傳的值是CaseObj陣列。

### 2.多個CaseObj轉MioneObj（CASE_TO_MIONE）
在上個進程中的回傳數值，CaseObj（多個），會逐一的轉為MioneObj。

Mione直譯器會在組成MioneObj的過程中一直檢測該CaseObj是否有「function」、「range」、「end」字詞，並組成函數或執行式再進行值包裝。除此之外，直譯器也會組成其他值，這些值是比較好去做判斷的，僅需抽取CaseObj裡的CaseType，也就是CharType就可得知值的類型。剩下的Head、Symbol、Prompt是直接通過事先準備好的char*去一一做判斷。最後還是沒分配到的會成為Variable。

所回傳的類型會是MioneObj陣列。

### 3.運行 （RUN_WITH_MIONE）
直譯器會先將剛剛回傳的MioneObj陣列一一的檢測Head為何，再去進行Prompt、Symbol、Variable、Value檢測。

直譯器先讀取Head的具體行為，並記錄下這個Head。之後，直譯器會提取出Prompt與對應的資源（Head後的資源則以Prompt = NULL表示），並打包至Head的底層函數。




## 特殊用詞

### #Case 
表示一個或多個（Cases）相同（部分情況下）CharType組成的文字。

例如：
程式句為：
|Mione File|
|---|
|set hello = “Hello”|

| Cases|
|---|
|set|
|hello|
|=|
|“Hello”|

Case會直接判斷並轉換成CaseObj，再經過一系列的文法篩選，變成MioneObj。


### #資源
表示可被Mione直譯器算出任何Value或多個Value的Case。
例如：
|Case|
|---|
|1|
|“Hello”|
|1 + 3|
|(1+5)-3|
|a()|

以上這些都是「資源」。

### #SuperChar 
僅在字串中有SuperChar模式。
由於無法直接使用鍵盤上的輸入或會產生影響直譯器的執行，因此發明SuperChar模式。

若需啟用SuperChar模式，須在字串內輸入「\」符號，接著輸入模式類型（SuperCharType），每個類型所回傳的字元都不盡相同。

可使用的SuperChar單元：

\n 換行符號：
是最為常見的SuperChar之一。
使用此SuperChar將會導入10字元進入字串。例如：
|Mione File|
|---|
|“Hello, \nWorld” |
字串解析為：
| 行 | 內容 |
|行一  |  Hello, |
|行二  |  World|

\u() 客製字元：

是常見的SuperChar之一。
使用此SuperChar將會導入括號內的參數值。
一般情況下，括號的兩數開頭為位元編組模式。例如 ：\u(16) 代表將以16進位去處置客製字元。
位元編組目前僅有16進位可選，且英文字母也該為大寫，其餘的將視為錯誤，
客製字元可以是連在一起的（每兩字為一組，一組共有256個組合）。例如：
|Mione File|
|---|
|“\u(16E4BDA0E5A5BD)”|
「你好」的16位元編碼。
 
字串解析為：
|內容|
|---|
|你好|
