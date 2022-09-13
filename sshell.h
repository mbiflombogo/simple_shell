#ifndef SSHELL_H
#define SSHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
void loop(void);
char *read_line(void);
char **split_line(char *line);
int launch(char **args);
int execute(char **args);
int builtins(void);
int c_d(char **args);
int ex_it(char **args);
int _strcmp(char *s, char *s2);
int _strlen(char *str);
char *_strdup(char *src);
int print_num(int n);
int _write_char(char c);
#endif
