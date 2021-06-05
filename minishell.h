#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>
#include <termios.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>


#include "libft.h"

typedef struct s_program
{
    t_list *local_variables;
    t_list *global_variables;
    t_list *history;
    t_list *history_prec;
    char **path;
    int h_index;
} t_program;

struct termios orig_termios;

int	ft_strcmp(char *s1, char *s2);
int execute_binaries(char *str, t_program *program);
int is_space(char c);
void echo_command(char *to_print, t_program *program, int pipe);
int terminal_init(void);
void terminal_signal(int signum);
void terminal_done(void);
void ft_putstr(char *s);
void clean_string(char *to_print, int *i, int string_opened, char to_check);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
void clean_string_2(char *to_print, int *i, int *k, char to_check, int *string_opened, char *support);



#endif