##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

NAME	= ftrace

CC	= gcc -g

RM	= rm -rf

SRCS	= 	./srcs/main.c				\
			./srcs/errors_manager.c		\
			./srcs/init_elf_struct.c	\
			./srcs/ftrace.c				\
			./srcs/check_child.c		\
			./srcs/init_sym.c

CPPFLAGS = -I ./include/ -l elf
CPPFLAGS += -W -Wall -Wextra

MAKEFLAGS += --silent

OBJS = $(SRCS:.c=.o)

all: ftrace_ex
$(NAME):	$(OBJS)
	printf "\033[0;33mBuilding Binary : %s...\033[0m\n" $(NAME)
	$(CC) -o $(NAME) $(OBJS) $(CPPFLAGS)
	printf "[\033[0;32mFtrace is now built\033[0m]   \t\t\t\t%s\n" $(NAME)

ftrace_ex : $(NAME)

clean:
	$(RM) $(OBJS)
	printf "[\033[0;31mdeleted\033[0m] \t\t\t\t\t\t%s\n" $(OBJS)

fclean:
	$(RM) $(NAME)
	printf "[\033[0;31mdeleted\033[0m] \t\t\t\t\t\t%s\n" $(NAME)
	$(RM) $(OBJS)
	printf "[\033[0;31mdeleted\033[0m] \t\t\t\t\t\t%s\n" $(OBJS)

re: fclean all

.PHONY: all clean fclean re