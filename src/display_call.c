/*
** EPITECH PROJECT, 2022
** strace
** File description:
** display_call
*/

#include "strace.h"
#include "syscall.h"
#include <stdio.h>
#include <sys/ptrace.h>
#include <unistd.h>

static syscall_t *find_syscall(int call_number)
{
    for (size_t i = 0; i < (sizeof(table) / sizeof(*table)); i++) {
        if (table[i].number == call_number)
            return (&table[i]);
    }
    return (NULL);
}

void display_syscall_args(
    pid_t child, int call_number, struct user_regs_struct *registers)
{
    (void)child;

    syscall_t *syscall_infos = find_syscall(call_number);
    unsigned long int args[6] = {registers->rdi, registers->rsi,
        registers->rdx, registers->rcx, registers->r8, registers->r9};

    if (syscall_infos == NULL) {
        fprintf(stderr, "UNKNOWN SYSCALL");
        return;
    }
    fprintf(stderr, "%s(", syscall_infos->name);
    if (syscall_infos->arg_count == -1) {
        fprintf(stderr, ")");
    } else {
        for (int i = 0; i < syscall_infos->arg_count; i++) {
            fprintf(stderr, "%#lx%s", args[i],
                (i == syscall_infos->arg_count - 1) ? ")" : ", ");
        }
    }
    fprintf(stderr, " = ");
}

void display_syscall_return_value(int call_number, long unsigned int rax_value)
{
    (void)call_number;
    fprintf(stderr, "%#lx\n", rax_value);
}