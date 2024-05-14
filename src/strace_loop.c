/*
** EPITECH PROJECT, 2022
** strace
** File description:
** strace_loop
*/

#include "strace.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <wait.h>

static int wait_syscall(pid_t child, struct user_regs_struct *registers)
{
    int status;
    int syscall;

    while (1) {
        ptrace(PTRACE_SINGLESTEP, child, 0, 0);
        waitpid(child, &status, 0);
        syscall = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * ORIG_RAX);
        if (syscall != -1)
            return (0);
        ptrace(PTRACE_GETREGS, child, NULL, registers);
        if (WIFEXITED(status))
            return (1);
    }
}

int main_loop(pid_t child, int display_full)
{
    int syscall_number;
    unsigned long rax_content;
    struct user_regs_struct registers;

    while (1) {
        if (wait_syscall(child, &registers) != 0) {
            display_syscall_args(
                child, registers.rax, &registers, display_full);
            fprintf(stderr, "?\n+++ exited with %lld +++\n", registers.rdi);
            break;
        }
        syscall_number =
            ptrace(PTRACE_PEEKUSER, child, sizeof(long) * ORIG_RAX);
        display_syscall_args(child, syscall_number, &registers, display_full);
        rax_content = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * RAX);
        display_syscall_return_value(
            syscall_number, rax_content, display_full, child);
    }
    return (0);
}
