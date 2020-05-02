/*
** EPITECH PROJECT, 2020
** ftp
** File description:
** ftp
*/

#include "ftrace.h"
#include <sys/ptrace.h>
#include <signal.h>
#include <libelf.h>

int sig_pid;

int main(int ac, char **av)
{
    Elf *elf = NULL;
    sym_t *list = NULL;

    handle_error(ac, av);
    elf = init_struct_elf(av[1]);
    if (elf == NULL)
        return EXIT_ERROR;
    list = init_sym(elf);
    if (list == NULL)
        return 84;
    tracing_syscall(av, list);
    elf_end(elf);
    return 0;
}