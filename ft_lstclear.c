/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:46:16 by stribuzi          #+#    #+#             */
/*   Updated: 2021/01/19 13:14:10 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*clr;

	if (!del || !*lst || !*lst)
		return ;
	while (lst && *lst)
	{
		clr = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = clr;
	}
}
