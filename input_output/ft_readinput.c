/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readinput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:35:16 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/12 22:06:44 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "input_output.h"

void	ft_readinput(t_process *process)
{
	int	exit_code;

	process->prompt->display = ft_prompt(process);
	process->line = readline(process->prompt->display);
	if (g_signal_status != 0)
	{
		process->status = g_signal_status;
		g_signal_status = 0;
	}
	if (process->line == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		exit_code = process->status;
		ft_free_process(process);
		rl_clear_history();
		exit(exit_code);
	}
	if (*(process->line) == '\0')
		return ;
	add_history(process->line);
	ft_parse_line(process);
}
