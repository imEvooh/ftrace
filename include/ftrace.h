/*
** EPITECH PROJECT, 2020
** ftp
** File description:
** ftp
*/

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libelf.h>

#define EXIT_ERROR      84
#define EXIT_SUCCESS    0

pid_t pid_for_all;

typedef struct ftrace_s
{
    char *cmd;
    char **args;
} ftrace_t;

typedef struct sym_s
{
	unsigned long address;
    char *funct;
    unsigned long exit;
	struct sym_s *next;
	struct sym_s *prev;
} sym_t;

typedef struct elf_s
{
    Elf64_Ehdr *Ehdr_elf;
    Elf64_Shdr *Shdr_elf;
    int return_value;
    char *path;
    char *exec;
} elf_t;

typedef struct pass_param_s
{
    int i;
    sym_t *list;
} param_t;

int print_error(char const *, int);
void handle_error(int, char **);
Elf *init_struct_elf(char *);
sym_t *init_sym(Elf *);
int tracing_syscall(char **, sym_t *);
int check_child(char **);