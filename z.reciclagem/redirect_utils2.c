/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:11:31 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/04/22 10:57:18 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_redirect_error_util(t_simple_command *simple, int *exit_code)
{
	if (simple->infile)
	{
		if (simple->infile[0] == '<' || simple->infile[0] == '>')
			return (print_error(SYNTAX_ERROR, exit_code), 1);
	}
	if (simple->outfile)
	{
		if (simple->outfile[0] == '<' || simple->outfile[0] == '>')
			return (print_error(SYNTAX_ERROR, exit_code), 1);
	}
	if (simple->double_in)
	{
		if (simple->double_in[0] == '<' || simple->double_in[0] == '>')
			return (print_error(SYNTAX_ERROR, exit_code), 1);
	}
	if (simple->double_out)
	{
		if (simple->double_out[0] == '<' || simple->double_out[0] == '>')
			return (print_error(SYNTAX_ERROR, exit_code), 1);
	}
	return (0);
}

/* @brief: deletes A and B from s 
	@arguments: s is the string from which we will take out some chars
				A and B and the chars to take out
	used to take out quotes, double quotes and redirect symbols
	@return: 0 in case of success
			 1 or any other number in case of errors. 
*/

int	delete_sigs(char **s, char A, char B, int *exit_code)
{
	int		i;
	char	*temp;
	int		len;

	i = 0;
	if (*s == NULL)
		return (0);
	len = after_sig_strlen(*s, A, B);
	temp = malloc(len + 1);
	if (temp == NULL)
		return (print_error(MALLOC_ERROR, exit_code), 1);
	temp[len] = '\0';
	len = 0;
	while ((*s)[i])
	{
		if ((*s)[i] != A && (*s)[i] != B)
		{
			temp[len] = (*s)[i];
			len++;
		}
		i++;
	}
	ft_strlcpy(*s, temp, len + 1);
	free(temp);
	return (0);
}

/* @brief: counts the len of s after A and B are deleted
	@return: the len counted 
*/

int	after_sig_strlen(char *s, char A, char B)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == A || s[i] == B)
				count = skip_quotes(s, i);
			if (s[i] != A && s[i] != B)
				count++;
			i++;
		}
	}
	return (count);
}