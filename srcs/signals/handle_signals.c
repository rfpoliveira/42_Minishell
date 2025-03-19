/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato-oliveira <renato-oliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:44:20 by renato-oliv       #+#    #+#             */
/*   Updated: 2025/03/19 16:54:29 by renato-oliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/signals.h"

extern pid_t current_pid;

//if the pid is not zero, we are in a child procress each means we kill it???
//if it is zero we clear the line, print a newline, update readline and the display to get a new prompt
void    signal_handler(int signumb)
{
    if (signumb != SIGINT)
        return ;
    if (current_pid > 0)
        kill(current_pid, SIGINT);
    else
    {
        rl_replace_line("", 0);
        printf("\n");
        rl_on_new_line();
        rl_redisplay();
    }
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