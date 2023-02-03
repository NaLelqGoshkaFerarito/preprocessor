
# The C Preprocessor
The C preprocessor (a.k.a. cpp) is a *macro processor* for C and C++ (you can use it with other languages, but we won't talk about that). A *macro processor*, well, processes macros. In short, it expands some standardized syntax (*macro*) into predifined code. You can think of it as an automatic text editor. This makes code less cluttered and easier to debug. It also provides other functionality, including (but not limited to):

- File inclusion - Makes it possible for other files with definitions (`.h`/`.hpp`) to be included in the code
- Conditional compilation - Based on some condition, parts of the code can be removed
- Line control - The current file and line can be reported if needed
- Diagnostics - Errors and warning can provide a better alternative to print debugging

![](https://i.imgur.com/MmrBLoo.png)

## Basics

### Using cpp
You can use the preprocessor directly with the `cpp` command (Linux/WSL). This should look something like this 
![](https://i.imgur.com/el708mV.png)
Alternatively you can use the `-E` flag when you compile with `gcc` or `g++`. This tells your compiler to stop after the preprocessing stage.

![](https://i.imgur.com/ubPfuyT.png)

Both produce the same code (text), but I personally prefer using `cpp` directly.

### Errors and warnings
You can throw an error using the following syntax `#error Some helpful text`

![](https://i.imgur.com/uPqk9I9.png)

And warnings use the same syntax

![](https://i.imgur.com/y7js21r.png)


### Includes
The unassuming `#include` statement is an integral part of C/C++. After all everyone learns to love it (or at the very least is forced to use it) at some point in their programming career. There isn't anything special about it, right. Well, you can get away with the simple `#include "stdio.h"`, but there is more to it (like using `<>` :P). Now lets call the preprocessor so we can see what it actually produces. We'll use
```cpp=
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

Having just learned how to invoke cpp directly we can see what it does to files we include. I'll save you the gruesome details, but `main_but_long.cpp` has ~29k lines and is ~700kB in size. {{{(>_<)}}}

![](https://i.imgur.com/XKSFeiy.png)

### CLI arguments
Lets say we need to print the output function `simple_function()` from `some_file.h` which is in a directory named `incl`. 

```cpp=
#include <iostream>
#include "some_file.h"
int main() {
    std::cout << simple_function() << std::endl;
    return 0;
}

```

This code produces the following error

![](https://i.imgur.com/dxUo7Wa.png)

If we compile

![](https://i.imgur.com/k7nj1bq.png)

This doesn't even scratch the surface of what command-line arguments can do. For more on them, see https://linux.die.net/man/1/cpp

## Macros

In simp-le terms macros are the way in which we define a constant to be used multiple times throughout the program. Most of the time you can identify them by the "#define" at the beginning, for exapmle:

### Object-like macros
usually these are used to simply store certain values like:
```cpp
#define MAX_ARRAY_LENGTH 69 //noice
```
this #define is actually a preprocessor directive supplied to your machine to store the value in ... this is in fact a better use of macros for reasons we will explain later on.


```cpp=
#define MAX_ARRAY_LENGTH 69 //noice

int main() {
    int noice = MAX_ARRAY_LENGTH;
    return 0;
}
```
compiles

![](https://i.imgur.com/dK2bHmu.png)

### Predefined macros
There are macros that have alreay been defined by default and they help out greatly in everyday programming. examples include `__FILE__` which gives you the path of the current file, `__LINE__` which gives you the line number of the the code in question, `__TIME__` which provides you with the current time, and many more.

If you want to see some more predefined macros (they are the main reason you need `ifdef`) go to https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html#Common-Predefined-Macros

### Function-like macros

but you can actually also use them for storing functions such as:

```cpp
#define MAX_ARRAY_LENGTH(x) ((x)== 0 ? 1 : 69) //noice
```

or for a more usefule example:
```cpp
#define FACTORIAL(n)               \
({                                 \
    int answer = 1;                \
    for (int i = 1; i <= n; i++) { \
        answer *= i;               \
    }                              \
    answer;                        \
})                   // end of macro
```
as seen in 

![](https://i.imgur.com/Ahtkp5E.png)

this compiles as: 

![](https://i.imgur.com/Mo2T9Cl.png)

notice how warning does not display the answer but rather the string value, you can read more about this in the warning section below.

but if you want the proper answer you can see it here:

![](https://i.imgur.com/xDI02rG.png)

from

![](https://i.imgur.com/ZfLUd5L.png)


## Conditionals
Preprocessor conditionals are a lot like if statements. They are most often used if you want to exclude some code based on, for example, operating system or the hardware it is ran on.

### Ifdef/ifndef
If you have some experience with C/C++ you're probably familiar with the following piece of code

```cpp=
#ifndef LONG_CPP_EXAMPLE_H
#define LONG_CPP_EXAMPLE_H
//some code
#endif //LONG_CPP_EXAMPLE_H
```

It's automatically generated by your IDE every time you create a new header. They check if the macro you pass to them is defined. `ifdef` skips code if the macro isn't defined and `ifndef` doesn't. `endif` ends the block of code to be executed/skipped. In the example, you might notice the macro name is commented out after the `endif`. This is because some older programs put the macro name after the `endif`. That's bad practice, but we encourage you to put it in a comment. An example of `ifdef`/`ifndef` would be something like

Code with `ifndef`

![](https://i.imgur.com/8DgEwfr.png)

Code with `ifdef`

![](https://i.imgur.com/bBgRbv2.png)

`cpp` is smart so if you look at the code it outputs, you will notice that it evaluates the conditionals and drops them after it's done. 


### If
The `if` syntax is as follows: 
```cpp=
#if expression
//code
#endif //expression
```

`if` isn't as useful as normal if statements. Due to developments in compilers, you don't gain much speed, but you sacrifice a lot of options for the expressions you can evaluate. For example, `expression` can't contain any language specific types. It can contain integers, but enums are a no go.
You can use `if` to do the following:
```cpp=
//new and improved code
#if 0
//old code I don't want to delete because I don't know how to use git
```

### Defined
One of the only redeeming qualities of `if` is that you can see if a macro is defined with `defined`. As you remember `ifdef` was used for that, but `if defined` can check multiple macros simultaneously by using chained boolean logic. For example the following code would need nested `ifdef`s.

```cpp=
#define MY_MACRO 42
#define OTHER_MACRO 41
#if defined(MY_MACRO) && defined(OTHER_MACRO)
#error Both macros defined
#endif //defined(MY_MACRO) && defined(OTHER_MACRO)
```

![](https://i.imgur.com/9HJLxS6.png)

### Else/elif
`else` and`elif` are pretty much the same as `if`. `else` differs slightly as it doesn't take in any arguments. An example of `else`/`elif` in code might be something like:
```cpp=
#define MY_MACRO 42
#define OTHER_MACRO 41
#if defined(MY_MACRO) && !defined(OTHER_MACRO)
#error Only MY_MACRO is defined
#elif !defined(MY_MACRO) && defined(OTHER_MACRO)
#error Only OTHER_MACRO is defined
#else
#error Both macros are defined
#endif //defined(MY_MACRO) && defined(OTHER_MACRO)
```

![](https://i.imgur.com/LvOPlsO.png)

## Pragmas
Pragmas can offer a lot of niche functionality, but they are compiler specific. Because we've been using gcc/g++ this whole time, you can find a list of gcc pragmas here https://gcc.gnu.org/onlinedocs/cpp/Pragmas.html#Pragmas
