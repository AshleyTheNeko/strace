/*
** EPITECH PROJECT, 2022
** strace
** File description:
** fork_and_attach
*/

#include "strace.h"
#include <signal.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <wait.h>

int tracer_actions(pid_t child, int attach, int display_full)
{
    int status;

    if (attach) {
        if (ptrace(PTRACE_SEIZE, child, 0, 0) == -1) {
            perror("strace");
            return (84);
        }
        kill(child, SIGSTOP);
    }
    waitpid(child, &status, 0);
    return (main_loop(child, display_full));
}

int tracee_actions(char *filename, char **args, char **env)
{
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    raise(SIGSTOP);
    execve(filename, args, env);
    return (84);
}
