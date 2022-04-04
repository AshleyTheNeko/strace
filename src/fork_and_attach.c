/*
** EPITECH PROJECT, 2022
** strace
** File description:
** fork_and_attach
*/

#include "strace.h"
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <unistd.h>

int tracer_actions(pid_t child, int attach)
{
    int status;

    if (attach) {
        if (ptrace(PTRACE_SEIZE, child, 0, 0) == -1) {
            perror("strace");
            return (84);
        }
        kill(child, SIGSTOP);
    }
    if (waitpid(child, &status, 0) == -1)
        ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);
    return (main_loop(child));
}

int tracee_actions(char *filename, char **args, char **env)
{
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    kill(getpid(), SIGSTOP);
    execve(filename, args, env);
    perror("strace");
    return (84);
}
