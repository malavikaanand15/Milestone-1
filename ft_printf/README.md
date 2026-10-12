*This project has been created as part of the 42 curriculum by <manand>.*

# ft_printf

## Description

`ft_printf` is a 42 Core Curriculum project whose goal is to recreate the behavior of the standard C `printf()` function.

The project focuses on understanding and implementing **variadic functions** in C, while designing a structured and extensible solution for processing different format specifiers.

The mandatory implementation provides the following conversions:

| Conversion | Description |
|------------|-------------|
| `%c` | Prints a single character |
| `%s` | Prints a string |
| `%p` | Prints a pointer address in hexadecimal format |
| `%d` | Prints a signed decimal integer |
| `%i` | Prints an integer in base 10 |
| `%u` | Prints an unsigned decimal integer |
| `%x` | Prints an integer in lowercase hexadecimal |
| `%X` | Prints an integer in uppercase hexadecimal |
| `%%` | Prints a percent sign |

The function prototype is:

```c
int ft_printf(const char *format, ...);
```

The project does **not** require the implementation of the original `printf()` buffer management.

The final library is named:

```text
libftprintf.a
```

and is intended to be reusable in future 42 C projects.

## Project Goals

The main learning objectives of this project are:

- Understanding **variadic functions** in C.
- Working with `va_list`, `va_start`, `va_arg`, `va_copy`, and `va_end`.
- Understanding how formatted output functions process a format string.
- Designing a modular and extensible program.
- Working with different integer representations and number bases.
- Handling pointers and hexadecimal addresses.
- Managing dynamically allocated memory correctly where applicable.
- Creating and using a static library with `ar`.
- Writing a Makefile that follows the 42 project requirements.

## Algorithm and Data Structure

### Format-string parsing

The core algorithm scans the format string from left to right.

For each character:

1. If the character is not `%`, it is written directly to standard output.
2. If `%` is encountered, the next character is interpreted as a conversion specifier.
3. The corresponding argument is retrieved from the variadic argument list using `va_arg`.
4. A dedicated conversion routine formats and prints the value.
5. The number of characters written is added to the total return value.
6. The parser continues until the terminating `'\0'` of the format string is reached.

Conceptually, the processing flow is:

```text
format string
      |
      v
 scan character
      |
      +---- normal character ----> write()
      |
      +---- '%' -----------------> read conversion
                                      |
                                      v
                              retrieve argument
                                      |
                                      v
                              conversion handler
                                      |
                                      v
                                  write output
                                      |
                                      v
                              update character count
```

### Conversion handling

The conversion logic is organized around the supported specifiers:

```text
%c  -> character output
%s  -> string output
%p  -> pointer -> hexadecimal
%d  -> signed decimal
%i  -> signed decimal
%u  -> unsigned decimal
%x  -> lowercase hexadecimal
%X  -> uppercase hexadecimal
%%  -> percent character
```

Keeping the conversion logic separate makes the implementation easier to understand, test, debug, and extend.

### Number conversion

Integer conversions use a base-dependent representation.

For decimal numbers:

```text
base = 10
```

For hexadecimal numbers:

```text
base = 16
```

A typical recursive or iterative conversion algorithm repeatedly divides the number by the selected base and uses the remainder to determine the corresponding digit.

For example, hexadecimal digits are represented using:

```text
0123456789abcdef
```

for `%x`, and:

```text
0123456789ABCDEF
```

for `%X`.

The same general approach can therefore be reused for several numeric conversions by changing the base and digit set.

### Pointer conversion

For `%p`, the pointer is interpreted as an address and printed in hexadecimal notation.

A pointer is handled as an unsigned integer representation of its address, allowing the hexadecimal conversion logic to be reused.

### Data structures

The mandatory project does not require a complex data structure such as a linked list, tree, or hash table.

The main data structures used by the implementation are:

- The format string (`const char *`).
- A `va_list` object for accessing the variable arguments.
- Primitive integer types such as `int` and `unsigned int`.
- Pointer values for `%p`.

The choice of simple structures keeps the implementation lightweight and appropriate for the problem: the main challenge is parsing the format string and correctly dispatching each conversion rather than managing a complex collection of data.

## Return Value

Like the standard `printf()`, `ft_printf()` returns the total number of characters written.

For example:

```c
int count;

count = ft_printf("Hello %s!\n", "42");
```

The value stored in `count` represents the number of characters printed.

Maintaining the return count is therefore an important part of every conversion handler.

## Instructions

### Requirements

The project is written in C and follows the 42 Norm.

This implementation is standalone and does not use `libft`.

The mandatory part allows the following external functions:

```text
malloc
free
write
va_start
va_arg
va_copy
va_end
```


The project must produce a static library called:

```text
libftprintf.a
```

at the root of the repository.

The library must be created using `ar`; the `libtool` command is not allowed.

### Compilation

Clone the repository and enter the project directory:

```bash
git clone <repository_url>
cd ft_printf
```

Compile the project:

```bash
make
```

This should create:

```text
libftprintf.a
```

### Makefile commands

The Makefile provides the standard project rules:

```bash
make
make all
make clean
make fclean
make re
```

Their purposes are:

- `make` / `make all` — compile the project and create `libftprintf.a`.
- `make clean` — remove object files.
- `make fclean` — remove object files and the compiled library.
- `make re` — perform a full clean rebuild.

The project should be compiled using:

```text
-Wall -Wextra -Werror
```

with `cc`, as required by the subject.

### Using ft_printf in another program

After compiling the library, it can be linked with another C program.

For example:

```bash
cc main.c -L. -lftprintf -o test
```

Then run:

```bash
./test
```

Alternatively, the library can be passed directly:

```bash
cc main.c libftprintf.a -o test
```

Example program:

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Character: %c\n", 'A');
    ft_printf("String: %s\n", "Hello, 42!");
    ft_printf("Decimal: %d\n", -42);
    ft_printf("Integer: %i\n", 42);
    ft_printf("Unsigned: %u\n", 42u);
    ft_printf("Hex lowercase: %x\n", 255);
    ft_printf("Hex uppercase: %X\n", 255);
    ft_printf("Pointer: %p\n", (void *)main);
    ft_printf("Percent: %%\n");

    return (0);
}
```

## Project Structure

A typical project structure can look like:

```text
ft_printf/
├── Makefile
├── ft_printf.h
├── ft_printf.c
├── ft_printf_utils.c
├── ...
└── libftprintf.a
```

The exact source-file organization may differ depending on the implementation.

A modular structure is recommended so that:

- format parsing is separated from output routines;
- each conversion is easy to locate;
- number conversion logic can be reused;
- the code remains readable and maintainable.

## Testing

The project should be tested against the behavior of the original `printf()`.

Useful test categories include:

### Characters

```c
printf("%c\n", 'A');
ft_printf("%c\n", 'A');
```

### Strings

```c
printf("%s\n", "Hello");
ft_printf("%s\n", "Hello");
```

### Signed integers

```c
printf("%d %i\n", -42, 42);
ft_printf("%d %i\n", -42, 42);
```

### Unsigned integers

```c
printf("%u\n", 4294967295u);
ft_printf("%u\n", 4294967295u);
```

### Hexadecimal

```c
printf("%x %X\n", 255, 255);
ft_printf("%x %X\n", 255, 255);
```

### Pointers

```c
printf("%p\n", (void *)main);
ft_printf("%p\n", (void *)main);
```

### Percent sign

```c
printf("100%%\n");
ft_printf("100%%\n");
```

Testing should also include combinations of multiple conversions in a single format string and boundary values for integer conversions.

## Error and Memory Management

The implementation should avoid unexpected termination such as:

- segmentation faults;
- bus errors;
- double frees;
- invalid memory access.

Any heap-allocated memory must be properly released when it is no longer needed.

Memory leaks should be checked during development using appropriate tools available in the development environment.

## Resources

### Official / primary references

- 42 ft_printf subject — the project specification provided by the 42 curriculum.
- `printf(3)` / C library documentation — reference for the behavior of the original `printf()` function.
- `stdarg(3)` / C variadic arguments documentation — reference for `va_list`, `va_start`, `va_arg`, `va_copy`, and `va_end`.
- C language documentation — reference for integer types, pointers, strings, and standard C behavior.

### Learning topics

The main topics studied while developing this project include:

- Variadic functions in C.
- Format-string parsing.
- Static libraries.
- Character and string output with `write()`.
- Decimal and hexadecimal number conversion.
- Pointer representation.
- Makefiles.
- Memory management.
- Modular C program design.

### AI usage

AI tools was used for **documentation support**, specifically to help structure and draft this `README.md` according to the README requirements in the 42 `ft_printf` subject.
