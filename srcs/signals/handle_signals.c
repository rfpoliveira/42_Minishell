/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:44:20 by renato-oliv       #+#    #+#             */
/*   Updated: 2025/04/16 13:45:48 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/* @brief: handles the SIGINT
    replaces the line introduced with ""
    writes a newline
    updates readline to the newline
    and finnaly updates the display to match */
void    signal_handler(int signumb)
{
    (void)signumb;
    rl_replace_line("", 0);
    ft_putstr_fd(" \n", 1);
    rl_on_new_line();
    rl_redisplay();
}    
/* @brief: handles the signals: cntl + c(SINGINT) and cntl + \(SIGQUIT) 
    if the user uses SIGINT if calls the sighandler
    if the user uses SIGQUIT it ignores it*/
void    handle_signals(void)
{
    struct  sigaction   sa_signal;

    sa_signal.sa_handler = signal_handler;
    sigemptyset(&sa_signal.sa_mask);
    sa_signal.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_signal, NULL);
    signal(SIGQUIT, SIG_IGN);
}