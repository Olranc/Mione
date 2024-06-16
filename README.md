# Mione 🪶
###### 便捷，快速，實用的程式語言。
#
![MIONE](./mione.svg) 

#

<hr>

# ⭐Mione的五大別類：
###### 在學習Mione前，你需要知道什麼是【五大別類】。
###### 【五大別類】是Mione主要實現的方法，它主要由 `HEAD` ,`PROMPT` ,`SYMBOL`,`VALUE`,`VARIABLE`組成的。
## 標頭`HEAD`：
#### 顧名思義，它是大部分Mione語言程式碼的開頭，主要的工作是告訴Mione這端程式碼是要做什麼的。
#### 舉個例子：
```MIONE
set //這是一個 HEAD//
x
```
#### 常見的 `HEAD`：
|   標頭   | 標配序號 |
|:------:|:----:|
|  set   |  ?   |
| return |  ?   |
|  get   |  ?   |
| break  |  ?   |
| input  |  ?   |
|   等等   | ...  |

## 參數投入`PROMPT`：
#### `PROMPT` 是參數投入的前奏表達符號。
#### 舉個例子：
```MIONE
x
= //這個 "=" 是一個PROMPT//
1 //參數在這//
```
#### 常見的 `PROMPT`：
| 參數投入 | 標配序號 |
|:----:|:----:|
|  =   |  ?   |
|  as  |  ?   |
|  do  |  ?   |
| than |  ?   |
| else |  ?   |
|  等等  | ...  |

## 運算符號`SYMBOL`：
#### `SYMBOL` 是運算會使用到的符號。通常搭配V/V(`VALUE`,`VARIABLE`)使用，而不會單獨存在。
#### 舉個例子：
```MIONE
x
= //⚠️不是 SYMBOL//
1
+ //😁這是 SYMBOL//
1
```
#### 常見的 `SYMBOL`：
| 運算符號 | 標配序號 |
|:----:|:----:|
|  +   |  ?   |
|  -   |  ?   |
|  *   |  ?   |
|  /   |  ?   |
|  ==  |  ?   |
|  等等  | ...  |

## 變數`VARIABLE`：
#### `VARIABLE` 是變數，可以當作程式碼的開頭。
#### 舉個例子：
```MIONE
x //😁這是VARIABLE//
=
15 //⚠️這不是VARIABLE//
```
#### 常見的 `VARIABLE`：
| 變數 | 標配序號 |
|:--:|:----:|
| 多態 |  動態  |

## 值`VALUE`：
#### `VALUE` 是值，可以當作程式碼的開頭。
#### 舉個例子：
```MIONE
x //⚠️這不是VALUE//
=
30 //😁這是VALUE//
```
#### 常見的 `VALUE`：
| 值  | 標配序號 |
|:--:|:----:|
| 多態 |  動態  |

<hr>

# Mione語法：
###### Mione從最初設計至今都要求【簡易】,【整齊】,【有規則】,【易修改】，【好實現】的語法。
###### 我們從基本的語法開始介紹吧！

#


```mione
set  x = "Hello ,World!"
```
###### 這是一個設定變數的程式碼，以 `x` 當作變數的名稱，在使用 `"Hello ,World` 當作該變數的值。

<hr>

# 開發日誌：
### ⚠️24年六月一日前的紀錄都存在了Discord伺服器裡，有興趣的可以去看看。

### 😊[快速到該版本：MIONE_AP_202406016](#MIONE_AP_20240616)

## 😎--2024年：
### 😗----6月:
#### 🫠------第一次提交:


###### MIONE_AP_20240601
```text
MIONE:
    日期 (MM/DD/YYYY) ： 06/01/2024;
    人員 (暱稱,...) ： Hxx;
    版本 (版本名稱，版本代號) ： 陳，MIONE_AP_20240601;
    版本說明 (說明) ： 修改了 `COUNT.h` 裡的 2 項變數;
    可正常執行 (是與否) ： 否;
    非正常執行原因 (原因) ： `COUNT.h` 裡的 'FunctionCall' 尚未修改完整，沒法傳達正確的數據至 'CasesCount';
    可完全執行 (是與否) ： 否;
    非完全執行原因 (原因) ： 尚未全數完成Mione的架構。;
```
#### 🫠------第二次提交:
###### MIONE_AP_20240602
```text
MIONE:
    日期 (MM/DD/YYYY) ： 06/02/2024;
    人員 (暱稱,...) ： 99;
    版本 (版本名稱，版本代號) ： 陳，MIONE_AP_20240602;
    版本說明 (說明) ： 新增了Function Calling的基礎架構！;
    可正常執行 (是與否) ： 可;
    非正常執行原因 (原因) ： ();
    可完全執行 (是與否) ： 否;
    非完全執行原因 (原因) ： 尚未全數完成Mione的架構。;
```
#### 🫠------第三次提交:
###### MIONE_AP_20240604
```text
MIONE:
    日期 (MM/DD/YYYY) ： 06/04/2024;
    人員 (暱稱,...) ： 99;
    版本 (版本名稱，版本代號) ： 陳，MIONE_AP_20240604;
    版本說明 (說明) ： 修改了Function Calling的回傳值處理器。;
    可正常執行 (是與否) ： 可;
    非正常執行原因 (原因) ： ();
    可完全執行 (是與否) ： 否;
    非完全執行原因 (原因) ： 尚未全數完成Mione的架構。;
```
#### 🫠------第四次提交:
###### MIONE_AP_20240605
```text
MIONE:
    日期 (MM/DD/YYYY) ： 06/05/2024;
    人員 (暱稱,...) ： 99;
    版本 (版本名稱，版本代號) ： 陳，MIONE_AP_20240605;
    版本說明 (說明) ： 新增了多函數呼叫系統。。;
    可正常執行 (是與否) ： 可;
    非正常執行原因 (原因) ： ();
    可完全執行 (是與否) ： 否;
    非完全執行原因 (原因) ： 尚未全數完成Mione的架構。;
```
#### 🫠------第五次提交:
###### MIONE_AP_20240606
```text
MIONE:
    日期 (MM/DD/YYYY) ： 06/06/2024;
    人員 (暱稱,...) ： 99;
    版本 (版本名稱，版本代號) ： 陳，MIONE_AP_20240606;
    版本說明 (說明) ： 修改了Memory的配置。;
    可正常執行 (是與否) ： 否;
    非正常執行原因 (原因) ： Memory配置錯誤，估計是Memory Group沒有對準所在值。;
    可完全執行 (是與否) ： 否;
    非完全執行原因 (原因) ： 尚未全數完成Mione的架構。;
```
#### 🫠------第六次提交:
###### MIONE_AP_20240607
```text
MIONE:
    日期 (MM/DD/YYYY) ： 06/07/2024;
    人員 (暱稱,...) ： 99;
    版本 (版本名稱，版本代號) ： 陳，MIONE_AP_20240607;
    版本說明 (說明) ： 修復了Return的Memory Group配置。;
    可正常執行 (是與否) ： 是;
    非正常執行原因 (原因) ： ();
    可完全執行 (是與否) ： 否;
    非完全執行原因 (原因) ： 尚未全數完成Mione的架構。;
```
#### 🫠------第七次提交:
###### MIONE_AP_20240609
```text
MIONE:
    日期 (MM/DD/YYYY) ： 06/09/2024;
    人員 (暱稱,...) ： 99;
    版本 (版本名稱，版本代號) ： 陳，MIONE_AP_20240609;
    版本說明 (說明) ： 修復了呼叫回傳函數。;
    可正常執行 (是與否) ： 是;
    非正常執行原因 (原因) ： ();
    可完全執行 (是與否) ： 否;
    非完全執行原因 (原因) ： 尚未全數完成Mione的架構。;
```
#### 🫠------第八次提交:
###### MIONE_AP_20240611
```text
MIONE:
    日期 (MM/DD/YYYY) ： 06/11/2024;
    人員 (暱稱,...) ： 99;
    版本 (版本名稱，版本代號) ： 陳，MIONE_AP_20240611;
    版本說明 (說明) ： 新增了括號內運算子的支持。;
    可正常執行 (是與否) ： 是;
    非正常執行原因 (原因) ： ();
    可完全執行 (是與否) ： 否;
    非完全執行原因 (原因) ： 尚未全數完成Mione的架構。;
```
#### 🫠------第九次提交:
###### MIONE_AP_20240613
```text
MIONE:
    日期 (MM/DD/YYYY) ： 06/13/2024;
    人員 (暱稱,...) ： 99;
    版本 (版本名稱，版本代號) ： 陳，MIONE_AP_20240613;
    版本說明 (說明) ： 新增了運算單元運算的支持。;
    可正常執行 (是與否) ： 是;
    非正常執行原因 (原因) ： ();
    可完全執行 (是與否) ： 否;
    非完全執行原因 (原因) ： 尚未全數完成Mione的架構。;
```
#### 🫠------第十次提交:
###### MIONE_AP_20240614
```text
MIONE:
    日期 (MM/DD/YYYY) ： 06/14/2024;
    人員 (暱稱,...) ： 99;
    版本 (版本名稱，版本代號) ： 陳，MIONE_AP_20240614;
    版本說明 (說明) ： 更新了對運算單元的支持。;
    可正常執行 (是與否) ： 是;
    非正常執行原因 (原因) ： ();
    可完全執行 (是與否) ： 否;
    非完全執行原因 (原因) ： 尚未全數完成Mione的架構。;
```
#### 🫠------第十一次提交:
###### MIONE_AP_20240615
```text
MIONE:
    日期 (MM/DD/YYYY) ： 06/15/2024;
    人員 (暱稱,...) ： 99;
    版本 (版本名稱，版本代號) ： 陳，MIONE_AP_20240615;
    版本說明 (說明) ： 更新了對運算單元的支持。;
    可正常執行 (是與否) ： 是;
    非正常執行原因 (原因) ： ();
    可完全執行 (是與否) ： 否;
    非完全執行原因 (原因) ： 尚未全數完成Mione的架構。;
```
#### 🫠------第十二次提交:
###### MIONE_AP_20240616
```text
MIONE:
    日期 (MM/DD/YYYY) ： 06/16/2024;
    人員 (暱稱,...) ： 99;
    版本 (版本名稱，版本代號) ： 陳，MIONE_AP_20240616;
    版本說明 (說明) ： 更新並修復了錯誤行列。;
    可正常執行 (是與否) ： 是;
    非正常執行原因 (原因) ： ();
    可完全執行 (是與否) ： 否;
    非完全執行原因 (原因) ： 尚未全數完成Mione的架構。;
```
<hr>

# 誰幫助了
| 貢獻者 |     貢獻     |
|:---:|:----------:|
| 陳奈奈 | 前期的架構設計並開發 |
| Hxx |  主要的設計並實現  |
#
#


## Mione初衷就兩個【好實現】，【好開發】。
#### 【好實現】：
###### 希望Mione可以在高級的應用開發環進上出現。像是：Roblox Studio,Visual Studio,Unity 等等的。我們也提供了我們Mione的實現方法。
#### 【好開發】：
###### 希望Mione可以讓全世界的開發者帶來一定的方便及對世界的貢獻，不管年而老少都可以使用並開發出強大的應用。