#include "minishell.h"

void clean_string(char *to_print, int *i, int string_opened, char to_check)
{
    if (to_print[*i] == '\'' && string_opened == 0)
    {
        string_opened = 1;
        to_check = '\'';
        i++;
    }
    else if (to_print[*i] == '"' && string_opened == 0)
    {
        string_opened = 1;
        to_check = '"';
        i++;
    }
    if (to_print[*i] == to_check)
        string_opened = 0;
}

void clean_string_2(char *to_print, int *i, int *k, char to_check, int *string_opened, char *support)
{
    if (to_print[*i] == '\\')
    {
        if (to_print[*i + 1] == '\\')
            i++;
        else if (to_print[*i + 1] == '\'' && *string_opened == 1 && to_check == '\'')
        {
            support[*k] = to_print[*i + 1];
            k++;
            i++;
        }
        else if (to_print[*i + 1] == '"' && *string_opened == 1 && to_check == '"')
        {
            support[*k] = to_print[*i + 1];
            k++;
            i++;
        }
        else if (to_print[*i + 1] == '"' && string_opened == 0)
            i++;
    }
    if (to_print[*i] != to_check)
    {
        support[*k] = to_print[*i];
        k++;
    }
}

/*
int clean_string_support(char *to_print)
{
    
    int string_opened = 0;
    int i;
    char to_check;
    char *support;
    int k;

    i = 0;
    support = malloc(ft_strlen(to_print));
    support[ft_strlen(to_print)] = '\0';
    k = 0;
    while(is_space(to_print[i]) == 1)
        i++;
    //other_index = i;
    while (to_print[i])
    {
        while (to_print[i] != '\0')
        {
            if (to_print[i] == '\'' && string_opened == 0)
            {
                string_opened = 1;
                to_check = '\'';
                i++;
            }
            else if (to_print[i] == '"' && string_opened == 0)
            {
                string_opened = 1;
                to_check = '"';
                i++;
            }
            if (to_print[i] == to_check)
                string_opened = 0; 
            if (to_print[i] == '\\')
            {
                if (to_print[i + 1] == '\\')
                    i++;
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
                    i++;
            }
            if (to_print[i] != to_check)
            {
                support[k] = to_print[i];
                k++;
            }
            i++;
        }
        support[k] = '\0';
    }
    if (string_opened == 1)
    {
        write(1, "Error\n", 6);
        return 1;
    }
    if (support)
        free(support);
    return 0;
}

int main()
{
    int i;
    int k;
    char buffer[100];
    int bytes;

    bytes = 0;
    bytes = read(0, buffer, 100);
    buffer[bytes] = '\0';
    printf("%d\n", clean_string(buffer));
    
}
*/