#include "libft.h"

int count_words(char *str)
{
    int state = 0;
    int count = 0;
    while (*str)
    {
         if (*str == ' ' || *str == '\n' || *str == '\t')
            state = 0;
        else if (state == 0)
        {
            state = 1;
            ++count;
        }
        ++str;
    }
    return count;
}

char **mini_split(char *str)
{
    char **to_ret;
    int num_of_words;
    int i;
    int j;
    int k;


    
    num_of_words = count_words(str);
    to_ret = malloc(sizeof(char *) * num_of_words);
    i = 0;
    k = 0;
    j = 0;
    while (str[i])
    {
        while (str[i] == ' ')
            i++;
        while (str[i + k] != ' ' && str[i + k] != '\0')
        {
            k++;
        }
        to_ret[j] = malloc(k + 1);
        k = 0;
        while (str[i + k] != ' ' && str[i + k] != '\0')
        {
            to_ret[j][k] = str[i + k];
            k++;
        }
        to_ret[j][k] = '\0';
        j++;
        i += k;
    }
    return (to_ret);
}