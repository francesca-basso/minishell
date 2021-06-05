#include "minishell.h"
#include "get_next_line.h"

int is_space(char c)
{
    if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c  == '\f')
        return (1);
    return (0);
}

void change_directory(char *dir)
{
    int i;
    int ret;

    i = 0;
    while (is_space(dir[i]) == 1)
        i++;
   ret = chdir(&dir[i]);
   if (ret < 0)
    printf("%s : Unable to find directory\n", &dir[i]);
}

void	ft_lstiter_new(t_list *lst) // per fare env 
{
	if (!lst)
    {
		lst = (t_list *)malloc(sizeof(t_list *));
        lst->next = NULL;
    }
	while (lst)
	{
        write(1, (char *)lst->content, ft_strlen((char *)lst->content));
        write(1, "\n", 1);
        // printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
}

char *pwd(void)
{
    char *ret;

    ret = getenv("PWD");
    return (ret);
}

void print_envp(char **envp, int *len)
{
    len[0] = 0;
    while (*envp)
    {
        printf("%s\n", *envp);
        envp++;
        len[0]++;
    }
}

void copy_envp(char **envp, char **envp_sup, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        envp_sup[i] = ft_strdup(envp[i]);
        i++;
    }
}

t_list *get_envp(char **envp)
{
    int len = 0;
    t_list *to_ret = (t_list *)malloc(sizeof(t_list));
    t_list *support;
    to_ret->content = "first elem";
    to_ret->next = NULL;
    while (envp[len])
    {
        support = ft_lstnew((void *)envp[len]);
        ft_lstadd_back(&to_ret, support);
        len++;
    }
    // ft_lstadd_back(&to_ret, NULL);
    return (to_ret);
}

void print_str(void *str)
{
    printf("%s\n", (char *)str);
}


void jump_spaces(char *str, int *i)
{
    while (is_space(str[i[0]]) == 1)
        i[0]++;
}

void check_add_variable(char *s, t_program *program)
{
    int i;
    int error = 0;
    t_list *support;
    t_list *support_2;
    int list_size_counter;

    list_size_counter = 0;
    i = 0;
    /*
    while (s[i])
    {
        if (is_space(s[i]) == 1)
        {
            error = 1;
            break ;
        }
        i++;
    }
    s[i] = '\0';
    */
    /*
    if (error == 1)
        printf("Error\n");
    */
   /*
        i = 0;
        while (s[i] != '=')
            i++;
        support_2 = program->local_variables;
        while (support_2)
        {
            if (ft_strncmp(support_2->content, s, i) == 0)
            {
                support_2->content = (void *)s;
                break ;
            }
            list_size_counter++;
            support_2 = support_2->next;
        }
        if (list_size_counter == ft_lstsize(program->local_variables))
        {
            support = malloc(sizeof(t_list *));
            support->content = (void *)s;
            support->next = NULL;
            ft_lstadd_back(&program->local_variables, support);
        }
    */
  while (s[i] != '=')
            i++;
    i++;
    support = malloc(sizeof(t_list *));
    support->content = (void *)&s[i];
    support->next = NULL;
    ft_lstadd_back(&program->local_variables, support);
    // ft_lstiter_new(program->local_variables);
}

int only_spaces(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (is_space(s[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}


void export_variable(char *s, t_program *program)
{
    int i;
    int len;
    char *support;
    t_list *new_list;
    t_list *temp;
    int found;

    found = 0;
    i = 0;
    len = 0;
    while (is_space(s[i]) == 0 && s[i] != '\0')
        i++;
    while (is_space(s[i]) == 1 && s[i] != '\0')
        i++; // dopo export
    if (only_spaces(&s[i]) == 1)
    {
        t_list *iter_support;

        iter_support = program->global_variables;
        if (!program->global_variables)
        {
            program->global_variables = (t_list *)malloc(sizeof(t_list *));
            program->global_variables->next = NULL;
        }
        while (iter_support)
        {
            ft_putstr("declare --x");
            ft_putstr((char *)iter_support->content);
            write(1, "\n", 1);
            iter_support = iter_support->next;
        }
        return ;
    }
    while (is_space(s[i + len]) == 0 && s[i + len] != '\0')
        len++;
    support = malloc(len + 1);
    len = 0;
    while (is_space(s[i + len]) == 0 && s[i + len] != '\0')
    {
        support[len] = s[i + len];
        len++;
    }
    support[len] = '\0';
    temp = program->local_variables;
    while (temp)
	{
        if (ft_strncmp(temp->content, support, len) == 0)
        {
            found = 1;
            break ;
        }
		temp = temp->next;
	}
    if (found == 1)
    {
        if (temp->content != NULL)
        {
            new_list = ft_lstnew(temp->content);
            ft_lstadd_back(&program->global_variables, new_list);
        }
    }
    else
        printf("Error\n");
    if (support != NULL)
        free(support);
}   

void unset_variable(char *s, t_program *program)
{
    t_list *support;
    t_list *support_2;
    int i;
    int k;

    k = 0;
    i = 5; // inizia da dopo unset
    support = program->global_variables;
    while (is_space(s[i + k]) == 1 && s[i + k] != '\0')
        k++;
    while (program->global_variables)
    {
        if (ft_strncmp(program->global_variables->next->content, &s[i + k], k) == 0)
        {
            //printf("UNSET LOCAL\n");
           program->global_variables->next = program->global_variables->next->next;
            // free(support_2->next);
            break ;
        }
        program->global_variables = program->global_variables->next; 
    }
    program->global_variables = support;
    support = program->local_variables;
    while (program->local_variables)
    {
        if (ft_strncmp(program->local_variables->next->content, &s[i + k], k) == 0)
        {
            program->local_variables->next = program->local_variables->next->next;
            break ;
        }
        program->local_variables = program->local_variables->next;
    }
    program->local_variables = support;
    /*
    support_2 = program->local_variables;
    while (support_2)
    {
       if (ft_strncmp(support_2->next->content, &s[i], k) == 0)
        {
           // printf("UNSET LOCAL\n");
            support_2->next = support_2->next->next;
            // free(support_2->next);
            break ;
        }
        support_2 = support_2->next; 
    }
    */
}

void exec_pipe(char **split_command, t_program *program)
{
    int i;
    int k;
    int len;

    /***/
    int pipefd[2]; 

    pipe(pipefd);
    pid_t p1, p2;
    int status;

    p1 = fork();
    // wait(&status);
    i = 0;
    // check errro


    if (p1 < 0)
    {
        printf("Error\n");
        exit(0);
    }
    else if (p1 == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        len = 0;
        k = 0;
        while (is_space(split_command[i][k]) == 1)
            k++;
        while (is_space(split_command[i][k + len]) == 0 && split_command[i][k + len] != '\0')
            len++;
        if (ft_strncmp("echo", &split_command[i][k], len) == 0 && len == 4)
        {
            echo_command(&split_command[i][k], program, 1);
        }
        else if (ft_strncmp(&split_command[i][k], "env", len) == 0 && len == 3)
        {
            ft_lstiter_new(program->global_variables);
        }
        else
        {
            // write(1, &split_command[i][k], ft_strlen(&split_command[i][k]));
            int ret = execute_binaries(split_command[0], program);
            //int ret = execute_binaries("ls", program);
            printf("RET IS: %d\n", ret);
            if (ret < 0)
                printf("%s: command not found\n", split_command[i]);
        }
        exit(1);
    }
    else 
    {
        p2 = fork();
        wait(&status);
        // write(1, "inside2", 7);
        if (p2 == 0)
        {
            i++;
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            len = 0;
            k = 0;
            while (is_space(split_command[i][k]) == 0)
            {
                k++;
            }
            
            if (ft_strncmp("echo", &split_command[i][k], len) == 0 && len == 4)
            {
                echo_command(&split_command[i][k], program, 1);
            }
            else if (ft_strncmp(&split_command[i][k], "env", len) == 0 && len == 3)
            {
                ft_lstiter_new(program->global_variables);
            }
            else
            {
                // write(1, &split_command[i][k], ft_strlen(&split_command[i][k]));
                int ret = execute_binaries(&split_command[i][k], program);
                if (ret < 0)
                    printf("%s: command not found\n", split_command[i]);
            }
             exit(1);
        }
    }

  //  wait(NULL);
    /***/
    /*
    len = 0;
    i = 0;
    while (split_command[i])
    {
        k = 0;
        while (is_space(split_command[i][k]) == 1)
            k++;
        while (is_space(split_command[i][k + len]) == 0 && split_command[i][k + len] != '\0')
            len++;
        if (ft_strncmp("echo", &split_command[i][k], len) == 0 && len == 4)
        {
            echo_command(&split_command[i][k], program, 1);
        }
        i++;
    }
    */
}

int execute_binaries(char *str, t_program *program)
{
    int i;
    char support[500];
    char *joined;
    char *join_support;
    char **argv;
    int error;

    error = 0;
    i = 0;
    while (str[i] != '\0' && str[i] != '>' && str[i] != '<')
    {
        support[i] = str[i];
        i++;
    }
    support[i] = '\0';  
    argv = ft_split(support, ' ');
    if (execve(support, argv, NULL) < 0)
    {
        error = 1;
        i = 0;
        while (program->path[i])
        {
            join_support = ft_strjoin(program->path[i], "/");
            joined = ft_strjoin(join_support, argv[0]);
            if (execve(joined, argv, NULL) > 0)
            {
                error = 0;
                break ;
            }
            free(joined);
            free(join_support);
            i++;
        }
    }
    else
        return (1);
    if (error == 1)
        return (0);
    return (0);
}

void check_function(char **split, t_program *program, char **argv, char **envp)
{
    int i;
    int k;
    int len;
    char buffer[1024];
    int ret;
    char **split_command;

    i = 0;
    len = 1;
    pid_t pid;
    pid_t wpid;

    int status;
    while (split[i])
    {
        if (ft_strchr(split[i], (int)'|') != NULL)
        {
            split_command = ft_split(split[i], '|');
            exec_pipe(split_command, program);
        }
        else
        {
            k = 0;
            while (is_space(split[i][k]) == 1)
                k++;
            while (is_space(split[i][k + len]) == 0 && split[i][k + len] != '\0')
                len++;
            if (ft_strncmp(&split[i][k], "exit", len) == 0 && len == 4)
            {
                exit(1);
            }
            else if (ft_strncmp("echo", &split[i][k], len) == 0 && len == 4)
            {
                echo_command(&split[i][k], program, 0);
            }
            else if (ft_strncmp(&split[i][k], "cd", len) == 0)
            {
                change_directory(&split[i][k + 2]);
            }
            else if (ft_strncmp(&split[i][k], "env", len) == 0)
            {
                ft_lstiter_new(program->global_variables);
            }
            else if (ft_strncmp(&split[i][k], "echo", len) != 0 && ft_strchr(&split[i][k], (int)'=') != NULL)
            {
                check_add_variable(&split[i][k], program);
            }
            else if (ft_strncmp(&split[i][k], "unset", len) == 0 && len == 5)
            {
                unset_variable(&split[i][k], program);
            }
            else if (ft_strncmp(&split[i][k], "export", len) == 0 && len == 6)
            {
                export_variable(&split[i][k], program);
            }
            else if (ft_strncmp(&split[i][k], "clear", len) == 0 && len == 5)
            {
                // printf("\033[H\033[J"); // clears the screen
                ft_putstr("\033[H\033[J");
               //  write(1, "\033[H\033[J", 7);
            }
            else
            {
                pid = fork();
                wait(&status);
                if (pid < 0)
                {
                    ft_putstr("Error\n");
                    exit(0);
                }
                else if (pid == 0)
                {
                    int out = 0;
                    int j = 0;
                    char output[100];
                    char *found_out = ft_strchr(split[i], (int)'>');
                    char *found_in = ft_strchr(split[i], (int)'<');
                    
                    if (found_out != NULL)
                    {
                        j++;
                        if (found_out[1] == '>')
                        {
                            j++;
                            out++;
                        }
                    }
                    int in = 0;
                    if (found_in != NULL)
                        in = 1;
                    if (found_out != NULL)
                        out++;
                    if (in)
                    {
                        int l = 1;
                        // write(1, found_in, ft_strlen(found_in));
                        while (is_space(found_in[l]) == 1)
                            l++;
                        int fd0 = open(&found_in[l], O_RDONLY);
                        if (fd0 < 0)
                            exit(0);
                        // write(1, &found_in[l], ft_strlen(&found_in[l]));
                        dup2(fd0, STDIN_FILENO);
                        close(fd0);
                        in = 0;
                    }
                    if (out) 
                    { //if '>' was found in string inputted by user
                        int fd;
                        
                        while ((is_space(found_out[j]) == 1) && found_out[j] != '\0')
                            j++;
                        if (out == 2)
                        {
                            fd = open(&found_out[j], O_RDWR, 0644);
                            if (fd < 0)
                                fd = open(&found_out[j], O_CREAT | O_RDWR, 0644);
                        }
                        else
                        {
                            fd = open(&found_out[j], O_CREAT | O_RDWR, 0644);
                        }
                        dup2(fd, STDOUT_FILENO);
                        out = 0;
                        // int current_out = dup(1);
                        close(fd);
                    }
                    // ret = execve(&split[i][k], argv, envp);
                    if (ft_strncmp(&split[i][k], "pwd", len) == 0 && len == 3)
                    {
                        getcwd(buffer, 1024);
                        write(1, buffer, ft_strlen(buffer));
                        write(1, "\n", 1);
                        // printf("%s\n", buffer);
                    }
                    else if (ft_strncmp(&split[i][k], "export", len) == 0 && len == 6)
                    {
                        export_variable(&split[i][k], program);
                    }
                    else 
                    {
                        ret = execute_binaries(&split[i][k], program);
                        if (ret < 0)
                            printf("%s: command not found\n", split[i]);
                    }
                    exit(1);
                }
            }
        }
        i++;
    }
}
/*
void clear()
{
    printf("\033[H\033[J");
}
*/


char ft_getch(void)
{
    char c;
    int co;
    
    co = read(0, &c, 1);
    return (c);
}

void enable_raw_mode()
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, &orig_termios);
    raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


void add_to_list(char *s, t_list **lst, t_program *program)
{
    t_list *support_history = ft_lstnew(s);
    ft_lstadd_back(lst, support_history);
    free(support_history);
}

char *ft_strcpy(char *dst, char *src)
{
    int i;

    i = 0;
    while (src[i])
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}

char *ft_strcpy_mod(char *dst, char *src, int *i)
{
    i[0] = 0;
    while (src[i[0]])
    {
        dst[i[0]] = src[i[0]];
        i[0]++;
    }
    dst[i[0]] = '\0';
    return (dst);
}

void write_intro(void)
{
    ft_putstr(getenv("USER"));
    ft_putstr(" $> ");
}

void clean_input(int i)
{
    int k;

    k = 0;
    ft_putstr("\r");
    while (k < (i + 4 + ft_strlen(getenv("USER")))) //delete whats currently written
    {
        write(1, " ", 1);
        k++;
    }
    ft_putstr("\r");
    write_intro();
}


char *retrieve_list_content(t_program *program)
{
    t_list *support;
    int index;
    
    index = 0;
    support = program->history;
    int to_find = -(program->h_index - ft_lstsize(program->history));
    while (support)
    {
        if (index == to_find)
            return ((char *)support->content);
        index++;
        support = support->next;
    }
    return (NULL);
}

int my_lst_size(t_list *lst)
{
    int i;
    
    i = 0;
    while (lst)
    {
        lst = lst->next;
        i++;
    }
    return (i);
}


int main(int argc, char **argv, char **envp)
{
    char buffer[1000];
    char *line;
    char *ret;
    int i;
    char **commands;
    t_list *env = get_envp(envp);

    t_program program;

    pid_t pid, wpid;
    int status;
    program.local_variables = ft_lstnew("");
    program.global_variables = get_envp(envp);

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH", 4) == 0)
        {
            program.path = ft_split(&envp[i][4], ':'); 
            break ;
        }
        i++;
    }

    enable_raw_mode();
    program.h_index = 1;
    program.history = malloc(sizeof(t_list *));
    program.history->content = "";
    program.history->next = NULL;

    program.history_prec = program.history;

   t_list *history_initial = program.history;

    char res;
    char line_terminal[500];
    i = 0;

    int k;
    write_intro();
    while ((res = ft_getch())) 
    {
		if (res == '\033')
        {
            ft_getch();
            char c = ft_getch();
            if (c == 'A') // up arrow
            {
                if (program.h_index < ft_lstsize(program.history) - 1)
                    program.h_index++;
                clean_input(i);
                ft_putstr(retrieve_list_content(&program));
                ft_strcpy_mod(line_terminal, retrieve_list_content(&program), &i); 
			}
            else if (c == 'B') // down arrow
            {
                if (program.h_index > 0)
                    program.h_index--;
                clean_input(i);
                if (program.h_index <= 1)
                {
                    ft_putstr("");
                    ft_strcpy_mod(line_terminal, "", &i);
                }
                else
                {
                    ft_putstr(retrieve_list_content(&program));
                    ft_strcpy_mod(line_terminal, retrieve_list_content(&program), &i);
                }
            }
            else if (c == 'D')
            {
               if (i > 0)
                write(1, "\b", 1);
            }
        }
		else if ((int)res == 10) // invio
		{
            program.h_index = 0;
            add_to_list(line_terminal, &program.history, &program);
            write(1, "\n", 1);
			line_terminal[i] = '\0';
            commands = ft_split(line_terminal, ';');
            check_function(commands, &program, argv, envp);
			ft_bzero(line_terminal, i);
			i = 0;
            write_intro();
		}
        else if ((int)res == 127) // delete
        {
            clean_input(i);
            if (i > 0)
                i--;
            line_terminal[i] = '\0';
            write(1, "\r", 1);
            write_intro();
            ft_putstr(line_terminal);
        }
        else if ((int)res == 4) // ctrl + d
        {
           break ;
        }
        else
		{
			line_terminal[i] = res;
			i++;
            write(1, &res, 1);
		}
	 }
    return (0);
}