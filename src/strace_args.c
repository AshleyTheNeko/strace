/*
** EPITECH PROJECT, 2022
** strace
** File description:
** arguments
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static int get_arg(char *arg[2], int *full_mode, pid_t *pid, int *i)
{
    if (!strcmp(arg[0], "-s"))
        *full_mode = 1;
    if (!strcmp(arg[0], "-p")) {
        if (!arg[1]) {
            write(2, "strace: option requires an argument -- 'p'\n", 43);
            return (-1);
        }
        *pid = atoi(arg[1]);
        (*i)++;
        if (!*pid) {
            fprintf(stderr, "strace: Invalid process id: '%s'\n", arg[1]);
            return (-1);
        }
    }
    return (*i);
}

int parse_args(int argc, char **argv, int *full_mode, pid_t *pid)
{
    int prog_args = 0;

    for (int i = 1; i < argc && !prog_args; i++) {
        prog_args =
            get_arg((char *[2]){argv[i], i != (argc - 1) ? argv[i + 1] : NULL},
                full_mode, pid, &i);
    }
    if ((prog_args == 0 || prog_args >= argc) && !(*pid)) {
        fprintf(stderr, "strace: Invalid args\n");
        prog_args = -1;
    }
    return (prog_args);
}
