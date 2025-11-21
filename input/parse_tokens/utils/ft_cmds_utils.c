/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:49:41 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 14:36:41 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include <fcntl.h>

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->next = NULL;
	return (cmd);
}

int	is_redir(char *str)
{
	if (!ft_strncmp(str, "<", 2) || !ft_strncmp(str, ">", 2)
		|| !ft_strncmp(str, ">>", 3))
		return (1);
	return (0);
}

void	open_file(t_cmd *cmd, char *symbol, char *file)
{
	if (!ft_strncmp(symbol, "<", 2))
	{
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		cmd->fd_in = open(file, O_RDONLY);
		if (cmd->fd_in < 0)
			perror(file);
	}
	else
	{
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		if (!ft_strncmp(symbol, ">", 2))
			cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
}
