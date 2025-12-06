## 251205
### 2139
Interestingly, it is possible to initialize specific variables of a structure
by indicating the variable prefixed with a dot. I found this from
[GNU's intro to C](https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Designated-Inits.html).

```c
struct point { int x; int y; };
struct point foo = { .y = 42 };
```

### 2252
When an instruction is described "indirect" it means that the instruction uses
a register as a pointer, rather than using the register’s value directly.

So for `LD (BC)`, instead of operating on the value in register BC, it is
instead operated on the memory pointed to by BC. This is why parentheses are
used.

It is identical to the C language's:

```c
*(BC) = A;
```
