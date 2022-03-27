#include "../includes/hexdump.h"
//注意: decimal:268435455、hex:fffffffを超えた後のオフセットは未定義

int	main(int argc, char *argv[])
{
	bool	has_option;
	char	*str_files;
	size_t	size_files;

	has_option = option(argc, argv);
	size_files = get_size_files(argc, argv);
	if (size_files == 0)
		return (0);
	str_files = NULL;
	str_files = set_str_files(argc, argv, str_files, size_files);
	hexdump(size_files, str_files, has_option);
	free(str_files);
	return (0);
}

bool	seek_on_same_arr(char *prev, char *cur, size_t *i, size_t size_files)
{
	size_t	j;	

	j = 0;
	while (j < 16)
	{
		if (j >= size_files - (*i))
			return (false);
		if (!(cur[j]) || prev[j] != cur[j])
			return (false);
		j++;
	}
	(*i) += 16;
	if (*i >= size_files)
		return (true);
	seek_on_same_arr(cur, &cur[16], i, size_files);
	return (true);
}

void	cntl_offset_idx(size_t size, char *str, size_t *i, bool *is_same_arr)
{
	*is_same_arr = false;
	if (*i == 0)
	{
		print_offset(*i);
		return ;
	}
	if (*i % 16 != 0)
		return ;
	*is_same_arr = seek_on_same_arr(&str[*i - 16], &str[*i], i, size);
	if (*is_same_arr)
		write(STDOUT_FILENO, "*\n", 2);
	else
		print_offset(*i);
}

void	hexdump(size_t size_files, char *str_files, bool has_option)
{
	bool	is_same_arr;
	size_t	i;

	is_same_arr = false;
	i = 0;
	while (i < size_files)
	{
		cntl_offset_idx(size_files, str_files, &i, &is_same_arr);
		if (is_same_arr)
			continue ;
		if (has_option)
			print_space_char(str_files[i++]);
		else
			print_space_hex_char(str_files[i++]);
		if (i % 16 == 0)
			write(STDOUT_FILENO, "\n", 1);
	}
	print_alignment(is_same_arr, i, has_option);
}
