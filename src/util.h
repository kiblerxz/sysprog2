#pragma once
#include <stdio.h>
#include <stdbool.h>

#ifndef _SSIZE_T_DEFINED
#include <sys/types.h>
#endif

bool path_writable(const char *path);
void die_perror(const char *ctx);

/* Кроссплатформенная замена getline().
   Поведение как у POSIX getline: возвращает кол-во байт (>=0) или -1 при EOF/ошибке.
   Буфер *lineptr будет выделен/увеличен внутри (нужно free() снаружи). */
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);
