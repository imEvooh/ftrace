/*
** EPITECH PROJECT, 2020
** ftp
** File description:
** ftp
*/

#include "all_syscall.h"
#include "ftrace.h"

char *get_args_syscall(struct user_regs_struct);

static void display_syscall(struct user_regs_struct regs)
{
    char *tmp = NULL;

    if ((int)regs.orig_rax != -1) {
        if (regs.orig_rax == 231) {
            printf("+++ exited with %lld +++\n", regs.rdi);
            return ;
        }
        switch (regs.orig_rax <= NB_SYS) {
            case true:
                tmp = get_args_syscall(regs);
                printf("Syscall %s(%s) = %#llx\n", all_sys[regs.orig_rax].str, \
tmp, regs.rax);
                free(tmp);
                break;
            default:
                printf("Unknown syscall\n");
                break;
        }
    }
}

static void seek_enter_func(struct user_regs_struct regs, sym_t *list, \
pid_t tmp, unsigned long rip)
{
    int status;
    unsigned long ins;

    ptrace(PTRACE_SINGLESTEP, tmp, NULL, NULL);
    wait(&status);
    ptrace(PTRACE_GETREGS, tmp, NULL, &regs);
    ins = ptrace(PTRACE_PEEKTEXT, tmp, regs.rip, NULL);
    if ((((unsigned)0xFF00 & ins) >> 8) == 0x48)
        for (sym_t *new = list; new != NULL; new = new->next)
            if (regs.rip == new->address) {
                printf("Entering function %s at %#lx\n", new->funct, new->address);
                new->exit = rip;
            }
}

static void seek_data_process(pid_t tmp, sym_t *list, \
struct user_regs_struct regs)
{
    unsigned long ins;
    unsigned long exit;

    ins = ptrace(PTRACE_PEEKTEXT, tmp, regs.rip, NULL);
    if (((unsigned)0xFF & ins) == 0xE8) {
        seek_enter_func(regs, list, tmp, regs.rip);
    } else if (((unsigned)0xFF & ins) == 0xC3) {
        exit = (ptrace(PTRACE_PEEKTEXT, tmp, regs.rsp, 0) - 5);
        for (sym_t *new = list; new != NULL; new = new->next) {
            if (exit == new->exit) {
                printf("Leaving function %s\n", new->funct);
                break;
            }
        }
    } else
        display_syscall(regs);
}

static int ftrace(pid_t tmp, sym_t *list)
{
    int status;
    struct user_regs_struct regs;

    for (sym_t *tmp = list; tmp != NULL; tmp = tmp->next)
        if (strcmp(tmp->funct, "main") == 0)
            printf("Entering function %s at %#lx\n", tmp->funct, tmp->address);
    while (1) {
        ptrace(PTRACE_SINGLESTEP, tmp, NULL, NULL);
        wait(&status);
        if (WIFEXITED(status)) {
            printf("+++ exited with %lld +++\n", regs.rdi);
            break;
        }
        ptrace(PTRACE_GETREGS, tmp, NULL, &regs);
        seek_data_process(tmp, list, regs);
    }
    printf("Leaving function main\n");
    return 0;
}

int tracing_syscall(char **av, sym_t *list)
{
    pid_t tmp;

    tmp = fork();
    if (tmp == 0 && check_child(av)) {
        ptrace(PTRACE_TRACEME);
        kill(SIGSTOP, getpid());
        return 1;
    } else if (tmp < 0)
        return 0;
    return ftrace(tmp, list);
}