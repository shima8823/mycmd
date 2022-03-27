CC = gcc
CFLAGS = -Wall -Wextra -Werror
# -fsanitize=address
SRCS = srcs/hexdump.c srcs/get_set.c srcs/print.c
OBJS = $(SRCS:%.c=%.o)
NAME = hexdump
CPPFLAGS = -I includes/
CMD = ./$(NAME)
CAT = | cat -e
.PHONY: test

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) 
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
test:
	$(CMD) test/* $(CAT)
	$(CMD) test/same_file1 test/same_file2 $(CAT)
	$(CMD) test/large.txt $(CAT)
	$(CMD) test/t3 test/t4 $(CAT)
	$(CMD) test/t3 $(CAT)
	$(CMD) test/same $(CAT)
	$(CMD) test/z $(CAT)
# option
	$(CMD) -c test/* $(CAT)
	$(CMD) -c test/same_file1 test/same_file2 $(CAT)
	$(CMD) -c test/large.txt $(CAT)
	$(CMD) -c test/t3 test/t4 $(CAT)
	$(CMD) -c test/t3 $(CAT)
	$(CMD) -c test/same $(CAT)
	$(CMD) -c test/z $(CAT)
# option
oritest:
	hexdump test/* $(CAT)
	hexdump test/same_file1 test/same_file2 $(CAT)
	hexdump test/large.txt $(CAT)
	hexdump test/t3 test/t4 $(CAT)
	hexdump test/t3 $(CAT)
	hexdump test/same $(CAT)
	hexdump test/z $(CAT)
# option
	hexdump -c test/* $(CAT)
	hexdump -c test/same_file1 test/same_file2 $(CAT)
	hexdump -c test/large.txt $(CAT)
	hexdump -c test/t3 test/t4 $(CAT)
	hexdump -c test/t3 $(CAT)
	hexdump -c test/same $(CAT)
	hexdump -c test/z $(CAT)