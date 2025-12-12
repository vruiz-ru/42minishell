/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:40:00 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/12 21:51:00 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

extern int	g_signal_status;

static void	ft_execute_commands(t_process *process)
{
	ft_tokens_to_cmds(process);
	if (g_signal_status == 130)
	{
		process->status = 130;
		g_signal_status = 0;
	}
	else if (process->commands && !process->commands->next && \
		ft_is_parent_builtin(process->commands))
	{
		process->status = ft_builtins(process, process->commands);
	}
	else
		ft_fork_process(process);
}

void	ft_shell_loop(t_process *process)
{
	while (1)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, SIG_IGN);
		ft_readinput(process);
		if (g_signal_status != 0)
		{
			process->status = g_signal_status;
			g_signal_status = 0;
		}
		if (process->tokens)
			ft_execute_commands(process);
		ft_reset_utils(&process);
	}
}
