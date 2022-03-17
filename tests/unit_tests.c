/*
** EPITECH PROJECT, 2020
** Units tests
** File description:
** tests for strace
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(strace, some_test)
{
    cr_assert_eq(1, 1);
}