/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:00:00 by vruiz-ru          #+#    #+#             */
/*   Updated: 2025/12/14 12:54:03 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../input_output.h"

void	ft_handle_heredoc_redir(t_cmd *node, char *file, t_process *proc)
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

void	ft_handle_fd_redir_check(t_cmd *node, char *redir)
{
	int	i;

	i = 0;
	while (redir[i] && ft_isdigit(redir[i]))
		i++;
	if (i > 0 && ft_strchr(redir + i, '&'))
		ft_handle_fd_redir(node, redir);
}
