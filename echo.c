#include "minishell.h"

void echo_command(char *to_print, t_program *program, int pipe)
{
    int string_opened = 0;
    int newline_flag = 1;
    int i;
    char to_check;
    char *support;
    char *support_variable;
    int fd;
    int redirection = 0;
    int len = 0;

    i = 0;
    support = malloc(ft_strlen(to_print));
    support[ft_strlen(to_print)] = '\0';
    int k = 0;
    i += 4;
    while(is_space(to_print[i]) == 1)
        i++;
    if (ft_strncmp(&to_print[i], "-n", 2) == 0)
    {
        i += 2;
        while(is_space(to_print[i]) == 1)
            i++;
        newline_flag = 0;
    }
    // start reading after echo
    int other_index = i;
    while (to_print[i])
    {
        while(to_print[i] != '\0' && to_print[i] != '>')
        {
            clean_string(to_print, &i, string_opened, to_check);
            if (to_print[i] == '$')
            {
                i++;
                len = 0;
                while (to_print[i + len] != '\0' && is_space(to_print[i + len]) == 0)
                {
                    len++;
                }
                support_variable = malloc(len + 1);
                len = 0;
                while (to_print[i + len] != '\0' && is_space(to_print[i + len]) == 0)
                {
                    support_variable[len] = to_print[i + len];
                    len++;
                }
                support_variable[len] = '\0';
                int found = 0;
                t_list *support_list;
                support_list = program->local_variables;
                while (support_list)
                {
                    if (ft_strncmp(support_variable, support_list->content, len) == 0)
                    {
                        found = 1;
                        break ;
                    }
                    support_list = support_list->next;
                }
                if (found == 1)
                {
                    // i++; //vado oltre il dollaro
                    int j = 0;
                    if (support_variable)
                        free(support_variable);
                    support_variable = ft_strdup((char *)support_list->content);
                    support_variable[ft_strlen((char *)support_list->content)] = '\0';
                    while (support_variable[j] != '=')
                    {
                        j++;
                    }
                    j++; // va oltre il "="
                    while (support_variable[j])
                    {
                        support[k] = support_variable[j];
                        k++;
                        j++;
                    }
                    i += len;
                }
                else
                    i += (len);
            }
            clean_string_2(to_print, &i, &k, to_check, &string_opened, support);
            /*if (to_print[i] == '\\')
            {
                if (to_print[i + 1] == '\\')
                {
                    i++;
                }
                else if (to_print[i + 1] == '\'' && string_opened == 1 && to_check == '\'')
                {
                    support[k] = to_print[i + 1];
                    k++;
                    i++;
                }
                else if (to_print[i + 1] == '"' && string_opened == 1 && to_check == '"')
                {
                    support[k] = to_print[i + 1];
                    k++;
                    i++;
                }
                else if (to_print[i + 1] == '"' && string_opened == 0)
                {
                    i++;
                }
            }
            if (to_print[i] != to_check)
            {
                support[k] = to_print[i];
                k++;
            }*/
        i++;
        }
        support[k] = '\0';
        char *operator;
        int len = 0;
        int overwrite = 1;
        if (to_print[i] == '>')
        {
            redirection = 1;
            i++;
            if (to_print[i] == '>')
            {
                i++;
                overwrite = 0;
            }
            k = 0;
            while (is_space(to_print[i + k]) == 1)
                k++;
            while (is_space(to_print[i + k + len]) == 0 && to_print[i + k + len] != '\0')
            {
                len++;
            }
            operator = malloc(len);
            len = 0;
            while (is_space(to_print[i + k + len]) == 0 && to_print[i + k + len] != '\0')
            {
                operator[len] = to_print[i + k + len];
                len++;
            }
            operator[len] = '\0';
            fd = open(operator, O_CREAT | O_RDWR, 0666);
            if (overwrite == 1)
                write(fd, support, ft_strlen(support));
            else
            {
                
            }
            free(operator);
        }
        other_index++;
    }
    printf("%d", string_opened);
    if (string_opened == 1)
        write(1, "Error\n", 6);
    else if (redirection == 0 && pipe == 0)
        write(1, support, ft_strlen(support));
    // close (fd)
    if (support)
        free(support);
    if (newline_flag == 1 && pipe == 0)
        write(1, "\n", 1);
    if (pipe == 1)
    {
        write(STDIN_FILENO, support, ft_strlen(support));
    }
}