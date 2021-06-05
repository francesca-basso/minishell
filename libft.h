#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef	struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;


void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
char	*ft_strchr(const char *s, int c);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int	ft_lstsize(t_list *lst);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *s);
char **mini_split(char *str);
char	**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
void	ft_bzero(void *s, size_t n);



#endif