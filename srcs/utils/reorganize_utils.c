/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganize_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:01:42 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/10 12:21:02 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int new_arg_counter(char **args)
{
    int i;
    int j;
    int count;

    i = -1;
    j = -1;
    count = 0;
    while (args[++i])
    {
        while (args[i][++j])
        {
            if (args[i][j] == '<' || args[i][j] == '>')
                j++;
            if (args[i][j] == '<' || args[i][j] == '>')
                j++;
            else if ()
        }
        j = -1;
    }
}
