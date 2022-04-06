/*
** EPITECH PROJECT, 2022
** strace
** File description:
** display_arg_type
*/

#include "arg_types.h"
#include "strace.h"
#include <stdio.h>
#include <sys/ptrace.h>
#include <unistd.h>

static void display_string(unsigned long int arg, pid_t child)
{
    char tmp;

    write(STDERR_FILENO, "\"", 1);
    tmp = ptrace(PTRACE_PEEKTEXT, child, arg, NULL);
    for (int i = 1; tmp > 0; i++) {
        write(STDERR_FILENO, &tmp, 1);
        tmp = (char)ptrace(PTRACE_PEEKDATA, child, arg + i, NULL);
    }
    write(STDERR_FILENO, "\"", 1);
}

void display_value_type(long arg, pid_t child, int arg_type)
{
    switch (arg_type) {
        case STRING:
            display_string(arg, child);
            break;
        case NUM:
            fprintf(stderr, "%d", (int)arg);
            break;
        case UNSIGNED:
            fprintf(stderr, "%lu", arg);
            break;
        default:
            fprintf(stderr, arg == 0 ? "NULL" : "%#lx", arg);
            break;
    }
}
