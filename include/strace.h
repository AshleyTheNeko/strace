/*
** EPITECH PROJECT, 2020
** strace.h
** File description:
** heads
*/

#pragma once

#include <sys/types.h>
#include <sys/user.h>

void strace(void);

typedef struct {
    int number;
    char *name;
    int arg_count;
    int return_type;
    int arg1_type;
    int arg2_type;
    int arg3_type;
    int arg4_type;
    int arg5_type;
    int arg6_type;
} syscall_t;

void display_syscall_args(pid_t child, int call_number,
    struct user_regs_struct *registers, int display_full);
void display_syscall_return_value(int call_number, long int rax_value,
    int display_full, pid_t child);
int tracer_actions(pid_t child, int attach, int display_full);
int tracee_actions(char *filename, char **args, char **env);
int main_loop(pid_t child, int display_full);
int parse_args(int argc, char **argv, int *full_mode, pid_t *pid);
void display_value_type(long arg, pid_t child, int arg_type);
