/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:40:00 by vruiz-ru          #+#    #+#             */
/*   Updated: 2025/12/14 12:55:12 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_reset_utils(t_process **process)
{
	if ((*process)->line)
		free((*process)->line);
	ft_clear_strtok();
	if ((*process)->tokens)
		ft_lstclear(&(*process)->tokens, free);
	(*process)->tokens = NULL;
	if ((*process)->commands)
	{
		ft_free_cmds((*process)->commands);
		(*process)->commands = NULL;
	}
	if ((*process)->prompt->display)
		free((*process)->prompt->display);
	(*process)->prompt->display = NULL;
}
