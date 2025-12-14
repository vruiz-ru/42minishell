/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:50:12 by vruiz-ru          #+#    #+#             */
/*   Updated: 2025/12/14 12:51:20 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_process *process, t_cmd *cmd)
{
	int	status;

	ft_putstr_fd("exit\n", 1);
	status = 0;
	if (cmd->args[1])
	{
		if (!is_numeric(cmd->args[1]))
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			status = 2;
		}
		else if (cmd->args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		else
			status = ft_atoi(cmd->args[1]);
	}
	else
		status = process->status;
	ft_free_process(process);
	rl_clear_history();
	exit(status);
	return (1);
}
