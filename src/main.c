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
    if (S_ISREG(stats.st_mode))
        return (1);
    if (S_ISDIR(stats.st_mode))
        errno = EISDIR;
    return (0);
}

static char *get_env_path(char *name, char *path_env_var)
{
    char *string;

    char *full_path;
    string = strtok(path_env_var, ":");
    while (string) {
        full_path = malloc(strlen(string) + strlen(name) + 2);
        sprintf(full_path, "%s/%s", string, name);
        if (file_exists(full_path))
            return (full_path);
        free(full_path);
        string = strtok(NULL, ":");
    }
    fprintf(
        stderr, "strace: Can't stat '%s': No such file or directory", name);
    return (NULL);
}

static char *get_path(char *name, char *path_env_var)
{
    if (!path_env_var || strcspn(name, "/") != strlen(name)) {
        if (!file_exists(name)) {
            fprintf(stderr, "strace: Can't stat '%s': ", name);
            perror("");
            return (NULL);
        }
        return (name);
    }
    return (get_env_path(name, path_env_var));
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
        return (tracer_actions(pid, attach, full_mode));
}
