# Mione

![Mione](https://raw.githubusercontent.com/CallHxx/Mione/main/Mione.svg)  

# POWER BY MIOPRETY
![Mioprety](https://raw.githubusercontent.com/CallHxx/Mione/main/Mioprety-nobackground.svg) 


**Hi there!** I'm Hxx, and I'm embarking on an exciting adventure to create a brand new high-level language called Mione, even with no prior experience. Feel free to join the journey on Discord: [me](https://discordapp.com/users/973907883274166283)

**Protecting Your Work:**

It's fantastic that you've included a link to your copyright information. Protecting your intellectual property is crucial! COPYRIGHT: [COPYRIGHT](https://raw.githubusercontent.com/CallHxx/Mione/main/COPYRIGHT.txt)

## Exploring Mione's Building Blocks

**Variable Creation and Acquisition:**

```
set Hello = "Your answer is: "

set x = 1
turn x to 2 

set y = 2

print(Hello, x + y)
```

- **Variable Declaration:** `set` is used to create variables like `Hello`, `x`, and `y`.
- **Assignment:** Values are assigned with `=`.
- **Potential Mutability:** The line `turn x to 2` requires clarification regarding variable types and mutability in Mione.
- **Printing:** `print` displays the value of `Hello` followed by the sum of `x` and `y`.

**Function Creation, Return, and Calling:**

```
set add = &
 get x, y
 return x + y
@

print(add(25, 75))
```

- **Function Definition:** `add` is defined with the `&` symbol.
- **Arguments and Retrieval:** `get` retrieves the values of `x` and `y` (more information needed on scope and behavior).
- **Return Value:** `return` sends the sum of `x` and `y` back.
- **Function Closure (or Definition Terminator):** The `@` symbol needs clarification.
- **Function Call:** `add(25, 75)` calls the function with arguments and prints the returned value.

**Control Flow: While Loops and If Statements:**

```
set index = 0
while (index < 3)
 $
  index = index + 1
  print("Times :",index")
 @
if (index == 3)
than $
 print ("index is actually 3")
@
else $
 print ("what?! How is it possible")
@
```

- **While Loop:** The loop continues as long as `index` is less than 3.
- **Increment:** `index = index + 1` increases the value of `index`.
- **If Statement:** `if (index == 3)` checks a condition.
- **Nested Control Flow:** Both `if` and `else` can have nested functions (more information needed).

**Asynchronous Functions:**

```
set infLoop = $
 while (true)
 $
  print("This is a message.")
 @
#

infLoop()
print("Hello World")
```

- **Asynchronous Function:** `infLoop` runs in the background without blocking the main program.
- **Function Call and Continuation:** Calling `infLoop()` starts the asynchronous execution, and `print("Hello World")` continues immediately.

**Remember:** This is just a glimpse into Mione based on the provided information. More details about specific aspects like variable mutability, function closure, and nested control flow are needed for a complete understanding.

I'm excited to see how Mione evolves! Feel free to share more details and I'll be happy to adapt and refine this explanation.
