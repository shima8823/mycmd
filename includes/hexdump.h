#ifndef HEXDUMP_H
# define HEXDUMP_H

# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>

// hexdump.c
bool	seek_on_same_arr(char *prev, char *cur, size_t *i, size_t size_files);
void	cntl_offset_idx(size_t size, char *str, size_t *i, bool *is_same_arr);
void	hexdump(size_t size_files, char *str_files, bool has_option);

// get_set.c
bool	option(int argc, char *argv[]);
size_t	get_size_files(int argc, char *argv[]);
char	*set_str_files(int argc, char *argv[], char *str_files, size_t size);
// print.c
void	print_offset(size_t file_size_i);
void	print_space_char(char c);
void	print_space_hex_char(char ascii);
void	print_alignment(bool is_same_arr, size_t i, bool has_option);
void	print_error(char *file);
#endif
