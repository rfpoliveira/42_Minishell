/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:54:11 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/11/04 14:01:57 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new;
}
/*
int		main(void)
{
	t_list *l1 = ft_lstnew((void *)0);
	t_list *l2 = ft_lstnew("world");
	ft_lstadd_back(&l1, l2);
	char *p = l1->content;
	printf("%s\n", p);
	l1 = ft_lstlast(l1);
	char *p2 = l1->content;
	printf("%s", p2);
	free(l1); 
}*/
