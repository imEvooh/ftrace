/*
** EPITECH PROJECT, 2020
** ftp
** File description:
** ftp
*/

#include "ftrace.h"
#include <string.h>

int print_error(char const *msg, int value)
{
    write(2, msg, strlen(msg));
    return value;
}

void handle_error(int ac, char **av)
{
    if (ac != 2 && ac != 3) {
        write(2, "./ftrace --help to know how to use this program.\n", 50);
        exit(EXIT_ERROR);
    } else if (ac == 2 && strcmp("--help", av[1]) == 0) {
        printf("USAGE: ftrace <command>\n");
        exit(EXIT_SUCCESS);
    }
}