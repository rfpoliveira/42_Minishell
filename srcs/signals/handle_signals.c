/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:44:20 by renato-oliv       #+#    #+#             */
/*   Updated: 2025/04/09 12:26:29 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

//handles the sigint (ctrl + c) to replace the line begin written with whitespace
//prints the new line and updates readline and the display
void    signal_handler(int signumb)
{
    (void)signumb;
    rl_replace_line("", 0);
    ft_putstr_fd(" \n", 1);
    rl_on_new_line();
    rl_redisplay();
}    
//sets up signal handlers to captures ctrl + C (sigint) and ignores ctrl + \ (sigquit)
void    handle_signals(void)
{
    struct  sigaction   sa_signal;

    sa_signal.sa_handler = signal_handler;
    sigemptyset(&sa_signal.sa_mask);
    sa_signal.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_signal, NULL);
    signal(SIGQUIT, SIG_IGN);
}