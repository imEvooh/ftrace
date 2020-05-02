/*
** EPITECH PROJECT, 2020
** open_exec.c
** File description:
** open_exec
*/

#include "ftrace.h"

int open_file(char *file)
{
    int fd = open(file, O_RDONLY, 0);

    if (fd == -1) {
        perror("open: ");
        return -1;
    } else
        return fd;
}