#include "../includes/hexdump.h"

void	print_offset(size_t file_size_i)
{
	char	offset[7];
	char	*base;
	int		i;

	i = 0;
	while (i < 7)
		offset[i++] = '0';
	base = "0123456789abcdef";
	i = 0;
	while (file_size_i != 0)
	{
		offset[i] = base[file_size_i % 16];
		file_size_i /= 16;
		i++;
	}
	i = 6;
	while (i >= 0)
		write(STDOUT_FILENO, &offset[i--], 1);
}

void	print_space_char(char c)
{
	if (' ' <= c && c <= '~')
	{
		write(STDOUT_FILENO, "   ", 3);
		write(STDOUT_FILENO, &c, 1);
	}
	else if (c == '\n')
		write(STDOUT_FILENO, "  \\n", 4);
	else if (c == '\t')
		write(STDOUT_FILENO, "  \\t", 4);
}

void	print_alignment(bool is_same_arr, size_t i, bool has_option)
{
	size_t	tmp;

	tmp = i;
	while (tmp % 16 != 0)
	{
		if (has_option)
			write(STDOUT_FILENO, "    ", 4);
		else
			write(STDOUT_FILENO, "   ", 3);
		tmp++;
	}
	if (!(is_same_arr) && i % 16 != 0)
		write(1, "\n", 1);
	print_offset(i);
	write(1, "\n", 1);
}

void	print_error(char *file)
{
	write(STDOUT_FILENO, "hexdump: ", 9);
	write(STDOUT_FILENO, file, strlen(file));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, strerror(errno), strlen(strerror(errno)));
	write(STDOUT_FILENO, "\n", 1);
}

void	print_space_hex_char(char c)
{
	char	reverse_hex_ascii[2];
	char	*base;
	int		i;

	reverse_hex_ascii[1] = '0';
	base = "0123456789abcdef";
	i = 0;
	while (c != 0)
	{
		reverse_hex_ascii[i] = base[c % 16];
		c /= 16;
		i += 1;
	}
	write(STDOUT_FILENO, " ", 1);
	i = 1;
	while (i >= 0)
		write(STDOUT_FILENO, &reverse_hex_ascii[i--], 1);
}
