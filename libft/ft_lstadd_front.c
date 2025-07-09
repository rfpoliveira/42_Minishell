/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:38:02 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/11/04 11:59:33 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/*
int	main (void)
{
	t_list *l1 = ft_lstnew("hello wolrd!");
	char *p = l1->content;
	printf("%s\n", p);
	t_list *l2 = ft_lstnew("now is this");
	ft_lstadd_front(&l1, l2);
	p = l1->content;
	printf("%s", p);
	free(l1);
}*/
