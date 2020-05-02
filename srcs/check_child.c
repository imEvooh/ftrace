/*
** EPITECH PROJECT, 2020
** ftp
** File description:
** ftp
*/

#include "all_syscall.h"
#include "ftrace.h"

char *get_args_syscall(struct user_regs_struct regs)
{
    int av[6] = {regs.rdi, regs.rsi, regs.rdx, regs.rcx, regs.r8, regs.r9};
    char *args = malloc(sizeof(char *) * 100);
    char *space = strdup(", ");
    char *test;

    args = strcpy(args, "\0");
    for (int i = 0; i < all_sys[regs.orig_rax].nb_arg; i++) {
        test = malloc(sizeof(char * ) * 100);
        sprintf(test, "%#lx", (size_t)av[i]);
        args = strcat(args, test);
        if (i != all_sys[regs.orig_rax].nb_arg - 1)
            args = strcat(args, space);
        free(test);
    }
    free(space);
    return args;
}

int check_child(char **av)
{
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    if (execv(av[1], av + 1) == -1)
        return 0;
    return 1;
}