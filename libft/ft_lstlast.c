/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:39:39 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/11/04 15:21:25 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}
/*
int		main(void)
{
	t_list *l1 = ft_lstnew("hello");
	t_list *l2 = ft_lstnew("world");
	t_list *l3 = ft_lstnew("!");
	l1->next = l2;
	l2->next = l3;
	l3->next = NULL;
	l1 = ft_lstlast(l1);
	char *s = l1->content;
	printf("%s", s);
	free(l1);free(l2);free(l3);
}*/
