/*
** EPITECH PROJECT, 2020
** strace
** File description:
** main
*/

#include "strace.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static int file_exists(const char *name)
{
    struct stat stats;

    if (stat(name, &stats) == -1)
        return (0);
    if ((stats.st_mode & X_OK) && (!S_ISDIR(stats.st_mode)))
        return (1);
    if (!(stats.st_mode & X_OK))
        errno = EACCES;
    if (S_ISDIR(stats.st_mode))
        errno = EISDIR;
    return (0);
}

static char *get_path(char *name, char *path_env_var)
{
    char *string;
    char *full_path;

    if (!path_env_var || file_exists(name))
        return (name);
    string = strtok(path_env_var, ":");
    while (string) {
        full_path = malloc(strlen(string) + strlen(name) + 1);
        strcpy(full_path, string);
        strcat(full_path, "/");
        strcat(full_path, name);
        if (file_exists(full_path)) {
            return (full_path);
        }
        free(full_path);
        string = strtok(NULL, ":");
    }
    if (!file_exists(name))
        perror("strace");
    return (NULL);
}

int main(int argc, char **argv, char **env)
{
    pid_t pid = 0;
    int full_mode = 0;
    int return_value = 0;
    int attach = 1;
    char *file_path;

    return_value = parse_args(argc, argv, &full_mode, &pid);
    if (return_value == -1)
        return (84);
    if (!pid) {
        attach = 0;
        file_path = get_path(argv[return_value], getenv("PATH"));
        if (!file_path)
            return (84);
        pid = fork();
    }
    if (!pid) {
        return (tracee_actions(file_path, argv + return_value, env));
    } else
        return (tracer_actions(pid, attach));
}