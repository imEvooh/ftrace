/*
** EPITECH PROJECT, 2020
** init_sym.c
** File description:
** init_sym
*/

#include "ftrace.h"

static sym_t *new_link(long address, char *funct)
{
    sym_t *new = malloc(sizeof(sym_t));

    if (new == NULL)
        return NULL;
    new->next = NULL;
    new->prev = NULL;
    new->funct = funct;
    new->exit = 1;
    new->address = address;
    return new;
}

static sym_t *add_in_list(sym_t *list, sym_t *new)
{
    sym_t *save = NULL;

    if (list == NULL)
        return new;
    else
        save = list;
    for (; save->next; save = save->next);
    save->next = new;
    new->prev = save;
    return list;
}

static sym_t *check(param_t *param, Elf *elf, Elf64_Shdr *shdr, Elf64_Sym *sym)
{
    char *str = NULL;
    sym_t *new = NULL;
    int tmp = ELF64_ST_TYPE(sym[param->i].st_info);

    if (tmp == STT_NOTYPE || tmp == STT_FUNC) {
        str = elf_strptr(elf, shdr->sh_link, sym[param->i].st_name);
        new = new_link(sym[param->i].st_value, str);
        param->list = add_in_list(param->list, new);
    }
    return param->list;
}

static sym_t *return_sym(Elf *elf, Elf64_Shdr *shdr, Elf_Data *data)
{
    int nb_of_sym = shdr->sh_size / shdr->sh_entsize;
    sym_t *list = NULL;
    Elf64_Sym *sym = data->d_buf;
    int i = 0;
    param_t *param = NULL;

    while (i < nb_of_sym) {
        param = malloc(sizeof(param_t));
        param->i = i;
        param->list = list;
        list = check(param, elf, shdr, sym);
        if ( list == NULL)
            return NULL;
        free(param);
        i = i + 1;
    }
    return list;
}

sym_t *init_sym(Elf *elf)
{
    Elf64_Shdr *shdr = NULL;
    Elf_Scn *s = NULL;
    Elf_Data *data = NULL;
    sym_t *list = NULL;

    for (; (s = elf_nextscn(elf, s)) != NULL;) {
        shdr = elf64_getshdr(s);
        if (shdr != NULL && shdr->sh_type == SHT_SYMTAB) {
            data = elf_getdata(s, NULL);
            list = return_sym(elf, shdr, data);
            return list;
        } else if (shdr == NULL)
            return NULL;
        else
            shdr = elf64_getshdr(s);
    }
    return NULL;
}