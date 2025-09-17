/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readinput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:35:16 by aghergut          #+#    #+#             */
/*   Updated: 2025/09/17 20:44:50 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_readinput(t_subproc *process)
{
	// ft_printf("hereread1");
	process->prompt = ft_prompt(process);
	if (process->prompt == NULL)
		return (ft_putstr_fd("Malloc error", 1), 0);
	// ft_printf("hereread2");
	process->line = readline(process->prompt);
	if (process->line == NULL)
	{
		// ft_printf("hereread3");
		free_subprocess(process);
		exit(EXIT_FAILURE);
		return (0);
	}
	// ft_printf("hereread4");
	if (process->line[0] != '\0')
		add_history(process->line);
	// ft_printf("hereread5");
	create_tokens(process);
	// ft_printf("hereread6");
	return (free(process->line), process->line = NULL, 1);
}
