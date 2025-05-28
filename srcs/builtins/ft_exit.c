#include "../../incs/minishell.h"

int	ft_exit(t_simple_command *cmd, t_data *data)
{
    int	exit_status;

    if (cmd->args[1] && cmd->args[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        data->exit_code = 1;
        return (1);
    }
    if (cmd->args[1])
    {
        exit_status = ft_atoi(cmd->args[1]);
        if (exit_status < 0 || exit_status > 255)
            exit_status = 255;
    }
    else
        exit_status = data->exit_code;
    ft_putstr_fd("exit\n", 1);
    free_data(data);
    exit(exit_status);
}
