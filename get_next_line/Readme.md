*This project has been created as part of the 42 curriculum by <login>.*

## Description
Get Next Line is a foundational programming project in the 42 curriculum. Its primary goal is to write a C function (`get_next_line`) that returns a single line read from a file descriptor. Repeated calls to the function allow reading a text file or standard input one line at a time until the end of the file is reached. This project introduces a critical concept in C programming: static variables.

## Instructions
To compile and test the project, use your C compiler with the mandatory flags and define the buffer size using the `-D BUFFER_SIZE` option:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

main.c
```
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int	fd;
	char	*line;

	if (argc != 2)
	{
		printf("Usage: ./a.out <filename>\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line); // Always free the line returned by get_next_line
	}
	close(fd);
	return (0);
}

```
## Testing

Use the below usecases to test and verify the implementation.
1. Extreme buffer size: tested with BUFFER_SIZE=1 and large values like BUFFER_SIZE=9999.
First add this script in your terminal
```
echo -e "Hello 42 Prague\nThis is line two\nEnd of file" > test.txt
```
```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c
./a.out test.txt
```
```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 get_next_line.c get_next_line_utils.c main.c
./a.out test.txt
```

2) Files with no final new line:
```
echo -n "Line 1\nLine 2 (no newline at end)" > no_nl.txt
./a.out no_nl.txt
```

3) Empty File: Create a file with no content and run the output file, the program will not return anything.
```
touch empty
./a.out empty.txt
```
4) Multiple Consecutive Newlines and empty lines:
```
echo -e "\n\nHello\n\n\nWorld\n" > empty_lines.txt
./a.out empty_lines.txt
```
It should successfully return strings containing just \n for the empty lines

## Resources
* [42 Docs - Get Next Line Guide](https://harm-smits.github.io/42docs/projects/get_next_line)
* [Fran Byte's GNL Approach Guide](https://42-fran-byte-f94097.gitlab.io/docs/get_next_line/get_next_line-approach-en/)
* [DEV Community - File Descriptors & I/O](https://dev.to/aerrfig/get-next-line-a-42-project-to-learn-how-to-deal-with-file-descriptors-and-io-of-system-3652)

**AI Usage:**
* **Tasks and Parts:** AI tools were used during the initial setup and research phases to gain a deeper understanding of file descriptor mechanics, static memory allocation, and handling dynamic strings in C. All logic and code were implemented and verified independently to ensure full adherence to 42 school policies and guidelines.