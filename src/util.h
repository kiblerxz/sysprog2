#pragma once
#include <stdio.h>
#include <stdbool.h>
bool path_writable(const char *path);
void die_perror(const char *ctx);
