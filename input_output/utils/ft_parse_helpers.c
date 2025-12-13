/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:00:00 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/13 17:59:53 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../input_output.h"

void	handle_heredoc_redir(t_cmd *node, char *file, t_process *proc)
{
	int	heredoc_fd;
	int	expand;
	int	len;

	expand = 1;
	len = ft_strlen(file);
	if (len > 0 && file[len - 1] == 1)
	{
		expand = 0;
		file[len - 1] = '\0';
	}
	heredoc_fd = ft_heredoc(file, expand, proc);
	ft_add_io(node, IO_HEREDOC, "heredoc", heredoc_fd);
}

void	handle_fd_redir_check(t_cmd *node, char *redir)
{
	int	i;

	i = 0;
	while (redir[i] && ft_isdigit(redir[i]))
		i++;
	if (i > 0 && ft_strchr(redir + i, '&'))
		handle_fd_redir(node, redir);
}
