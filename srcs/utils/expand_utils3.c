/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:42:07 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/08 15:52:29 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing.h"

/**
 @brief substituits the contents of s ($?) 
		with the exit code of the last command 
 @return 0 in case of success,
		 1 or any other number in case of error (Malloc)
*/
int	expande_exit_code(char **env, int *exit_code)
{
	*env = ft_itoa(*exit_code);
	if (*env == NULL)
		return (print_error(MALLOC_ERROR, exit_code), 1);
	return (0);
}
