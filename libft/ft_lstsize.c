/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:37:16 by rpedrosa          #+#    #+#             */
/*   Updated: 2024/11/04 12:47:37 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = lst;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
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
	int i = ft_lstsize(l1);
	printf("%i", i);
	free(l1); free(l2); free(l3);
}*/
