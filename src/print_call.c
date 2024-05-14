/*
** EPITECH PROJECT, 2022
** strace
** File description:
** display_call
*/

#include "errno_array.h"
#include "strace.h"
#include "syscall.h"
#include <stdio.h>
#include <string.h>
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

static void display_arg(
    syscall_t *syscall_infos, unsigned long int arg, int arg_pos, pid_t child)
{
    display_value_type(
        arg, child, ((int *)&syscall_infos->arg1_type)[arg_pos]);
    fprintf(stderr, (arg_pos == syscall_infos->arg_count - 1) ? ") = " : ", ");
}

void display_syscall_args(pid_t child, int call_number,
    struct user_regs_struct *registers, int display_full)
{
    syscall_t *syscall_infos = find_syscall(call_number);
    unsigned long int args[6] = {registers->rdi, registers->rsi,
        registers->rdx, registers->rcx, registers->r8, registers->r9};

    if (syscall_infos == NULL) {
        fprintf(stderr, "UNKNOWN SYSCALL");
        return;
    }
    fprintf(stderr, "%s(", syscall_infos->name);
    if (syscall_infos->arg_count < 1) {
        fprintf(stderr, ") = ");
        return;
    }
    for (int i = 0; i < syscall_infos->arg_count; i++) {
        if (!display_full)
            fprintf(stderr, "%#lx%s", args[i],
                (i == syscall_infos->arg_count - 1) ? ") = " : ", ");
        else
            display_arg(syscall_infos, args[i], i, child);
    }
}

void display_syscall_return_value(
    int call_number, long int rax_value, int display_full, pid_t child)
{
    syscall_t *syscall_infos = find_syscall(call_number);
    int error = 0;

    if (syscall_infos == NULL) {
        fprintf(stderr, "?\n");
        return;
    }
    if (display_full) {
        if (rax_value < 0 && rax_value > -132) {
            error = rax_value * -1;
            rax_value = -1;
        }
        display_value_type(rax_value, child, syscall_infos->return_type);
        if (error)
            fprintf(
                stderr, " %s (%s)", errno_values[error - 1], strerror(error));
    } else
        fprintf(stderr, "%#lx", rax_value);
    write(STDERR_FILENO, "\n", 1);
}
