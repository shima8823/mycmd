#include "hexdump.h"

bool	option(int argc, char *argv[])
{
	int	i;

	if (argc == 1)
		return (false);
	i = 0;
	while (argv[1][i])
	{
		if (i == 1 && (argv[1][0] == '-' && argv[1][1] == 'c'))
		{
			return (true);
			break ;
		}
		i++;
	}
	return (false);
}

size_t	get_size_files(int argc, char *argv[])
{	
	int		fd;
	char	c;
	int		i;
	size_t	size_files;

	i = 1;
	if (option(argc, argv))
		i = 2;
	size_files = 0;
	while (i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd == -1)
			print_error(argv[i]);
		while (read(fd, &c, 1) > 0)
			size_files += 1;
		close(fd);
		i++;
	}
	if (size_files == 0 && errno > 0)
		print_error(argv[i - 1]);
	return (size_files);
}

char	*set_str_files(int argc, char *argv[], char *str_files, size_t size)
{
	char	c;
	int		fd;
	int		i;
	int		file_i;

	str_files = malloc(size);
	if (str_files == NULL)
		return (NULL);
	i = 0;
	if (option(argc, argv))
		i = 1;
	file_i = 0;
	while (++i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd == -1)
			continue ;
		while (read(fd, &c, 1) > 0)
			str_files[file_i++] = c;
		close (fd);
	}
	return (str_files);
}
