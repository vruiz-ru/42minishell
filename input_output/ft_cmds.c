/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:54:08 by vruiz-ru          #+#    #+#             */
/*   Updated: 2025/12/14 12:51:50 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_output.h"

void	ft_handle_fd_redir(t_cmd *node, char *redir)
{
	int		src_fd;
	int		target_fd;
	char	*fd_str;

	src_fd = ft_atoi(redir);
	fd_str = ft_strchr(redir, '&');
	if (fd_str && fd_str[1])
		target_fd = ft_atoi(fd_str + 1);
	else
		return ;
	if (src_fd == 2 && target_fd == 1)
		ft_add_io(node, IO_OUT, "2>&1", -1);
}

void	ft_parse_redir(t_cmd *node, char *redir, char *file, t_process *proc)
{
	if (!ft_strncmp(redir, "<<", 3))
		ft_handle_heredoc_redir(node, file, proc);
	else if (!ft_strncmp(redir, ">>", 3))
		ft_add_io(node, IO_APPEND, file, -1);
	else if (!ft_strncmp(redir, "<", 2))
		ft_add_io(node, IO_IN, file, -1);
	else if (!ft_strncmp(redir, ">", 2))
		ft_add_io(node, IO_OUT, file, -1);
	else
		ft_handle_fd_redir_check(node, redir);
}

static int	is_pipe_separator(char *str)
{
	int	len;

	if (!str || str[0] != '|' || str[1] != '\0')
		return (0);
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == 1)
		return (0);
	return (1);
}

static void	fill_cmd(t_cmd *node, t_list **tokens, t_process *proc)
{
	int		i;
	char	*str;

	i = 0;
	while (*tokens && !is_pipe_separator((char *)(*tokens)->content))
	{
		str = (char *)(*tokens)->content;
		if (ft_is_redir(str))
			ft_handle_redir_token(node, tokens, proc);
		else
			ft_handle_arg_token(node, tokens, &i);
	}
	node->args[i] = NULL;
}

int	ft_tokens_to_cmds(t_process *proc)
{
	t_list	*curr;
	t_cmd	**node_ptr;
	t_cmd	*new;

	curr = proc->tokens;
	proc->commands = NULL;
	node_ptr = &proc->commands;
	while (curr)
	{
		if (is_pipe_separator((char *)curr->content))
		{
			curr = curr->next;
			continue ;
		}
		new = ft_create_new_command(curr);
		if (!new)
			return (0);
		fill_cmd(new, &curr, proc);
		*node_ptr = new;
		node_ptr = &new->next;
	}
	return (1);
}
