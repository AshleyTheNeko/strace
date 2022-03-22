/*
** EPITECH PROJECT, 2020
** strace.h
** File description:
** heads
*/

#pragma once

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
