#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
* _printf - A function that simulates Printf function.
* @format: A format.
* Return: To printed chars.
 */

int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);
	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')/*Check condition if true*/
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write (1, &format[i], 1);*/
			printed_chars++;
		}
		else	/*Check condition if false*/
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}
	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
* print_buffer - A function that Prints the contents of
*	the buffer if it exist.
* @buffer: An array of chars.
* @buff_ind: Index at which to add next char, represents the length.
* Return: No return.
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
