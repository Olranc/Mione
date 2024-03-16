# Mione

![Mione](https://raw.githubusercontent.com/ChenNini0924/Mione/main/Mione.svg)

## Mioprety工作室製作 [Mioprety Discord](https://discord.gg/SzhmGcG23s)
![Mioprety](https://github.com/ChenNini0924/Mione/blob/main/Mioprety-nobackground.svg) 


**使用條款**



版權所有：[版權](https://raw.githubusercontent.com/ChenNini0924/Mione/main/COPYRIGHT.txt)
# 目錄
- ### 前往 [Mione語法](/#Mione語法)
- ### 前往 [Mione版本說明](/#Mione版本)


## Mione語法

**創建變數與使用變數：**

```
set Hello = "Your answer is: "

set x = 1
turn x to 2 

set y = 2

print(Hello, x + y)
```

- **變數宣告：** `set` 用於建立`Hello`、`x` 和`y` 等變數。
- **賦值：** 值用`=`來賦值。
- **潛在的可變性：** `turn x to 2` 行需要澄清 Mione 中的變數類型和可變性。
- **列印：** `print` 顯示 `Hello` 的值，後面跟著 `x` 和 `y` 的總和。

**函數建立、傳回與呼叫：**

```
set add = $
 get x, y
 return x + y
@

print(add(25, 75))
```

- **函數定義：** `add` 用`&` 符號定義。
- **參數和檢索：** `get` 檢索 `x` 和 `y` 的值（需要有關範圍和行為的更多資訊）。
- **傳回值：** `return` 傳回 `x` 和 `y` 的總和。
- **函數閉包（或定義終止符）：** `@` 符號需要澄清。
- **函數呼叫：** `add(25, 75)` 使用參數呼叫函數並列印傳回值。

**控制流：While 迴圈與 If 語句：**

```
set index = 0
while index < 3
 #
  index = index + 1
  print("Times :",index")
 @
if index == 3
than #
 print "index is actually 3"
@
else #
 print "what?! How is it possible"
@
```

- **While Loop:** 只要 `index` 小於 3，迴圈就會繼續。
- **增量：** `index = index + 1` 增加 `index` 的值。
- **If 語句：** `if (index == 3)` 檢查條件。
- **嵌套控制流：** `if` 和 `else` 都可以有巢狀函數（需要更多資訊）。

**記住：** 這只是初期Mione的基本語法，還未規定完善。

## Mione版本
- **0.0.1** 
```not-a-lang
-新增了主要的編譯器文件。

參與人員：陳奈奈
— 2024/03/14 21:37
```
- **0.0.1F** 
```not-a-lang
-新增了一個語法錯誤代碼：'1'
-更新錯誤題回報系統 prerr.h

參與人員：陳奈奈
— 2024/03/15 23:24
```
- **0.0.1G** 
```not-a-lang
-新增了語句段開系統，可以分開部分正確語法

參與人員：陳奈奈
— 2024/03/16 09:46
```
               
