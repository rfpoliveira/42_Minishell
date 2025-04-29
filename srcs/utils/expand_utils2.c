/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:08:04 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/29 16:36:48 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing.h"

/* @brief: checks for quotes in the expanding process 
			and correctly skips them or not
	@args: flag is for checking if we are bettewn double quotes or not
			i is for iterating in the current string being checked
			current is the current string being checked
	return: 0 if the string as not ended.
			1 to signal the string as ended making the loop or the main function
			break
	@note: used in expand_red_util and expand_args at expander.c
*/

int	mid_expand_quote_handler(int *flag, int *i, char *current)
{
	if (current[*i] == 34)
		(*flag)++;
	if (current[*i] == 39 && (*flag % 2 == 0))
		*i += skip_quotes(current, *i);
	if (!current[*i])
		return (1);
	return (0);
}
