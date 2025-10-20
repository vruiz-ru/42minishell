/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readinput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:35:16 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/20 19:44:13 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_readinput(t_subproc *process)
{
	process->prompt = ft_prompt(process);
	if (process->prompt == NULL)
	{
        perror("malloc");
        return ;
    }	
	process->line = readline(process->prompt);
	if (process->line == NULL || *(process->line) == '\0')
		return ;
	add_history(process->line);
	ft_create_tokens(process);
}
