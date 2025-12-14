/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 11:17:20 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 11:17:39 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_output.h"

void	ft_config_pipes(t_cmd *cmd, int *pipefd, int prev_fd)
{
	if (prev_fd != 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

void	ft_close_fds(t_cmd *cmd, int prev_fd)
{
	(void)cmd;
	if (prev_fd != 0)
		close(prev_fd);
}
