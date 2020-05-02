/*
** EPITECH PROJECT, 2020
** init_elf_struct.c
** File description:
** init_elf_struct
*/

#include "ftrace.h"
#include <libelf.h>
#include <gelf.h>

static int open_file(char *file)
{
    int fd = open(file, O_RDONLY, 0);

    if (fd == -1) {
        perror("open: ");
        return -1;
    } else
        return fd;
}

static void *print_error_msg(char const *file, char const *msg, void *value)
{
    write(2, file, strlen(file));
    write(2, msg, strlen(msg));
    return value;
}

Elf *init_struct_elf(char *exec)
{
    int fd = 0;
    Elf *elf = NULL;
    int return_value = 0;

    fd = open_file(exec);
    if (fd == -1)
        return NULL;
    if (elf_version(EV_CURRENT) == EV_NONE)
        return print_error_msg("", "Bad version of lib\n", NULL);
    elf = elf_begin(fd, ELF_C_READ, NULL);
    if (elf == NULL)
        return print_error_msg(exec, ": header invalid, can't open\n", NULL);
    return_value = elf_kind(elf);
    if (return_value != ELF_K_ELF)
        return print_error_msg(exec, ": is not an elf file\n", NULL);
    if (gelf_getclass(elf) == ELFCLASS32)
        return print_error_msg("", "Wrong format, use 64\n", NULL);
    else
        return elf;
}