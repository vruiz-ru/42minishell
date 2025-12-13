/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:54:08 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/13 17:59:53 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handle_fd_redir(t_cmd *node, char *redir)
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

void	parse_redir(t_cmd *node, char *redir, char *file, t_process *proc)
{
	if (!ft_strncmp(redir, "<<", 3))
		handle_heredoc_redir(node, file, proc);
	else if (!ft_strncmp(redir, ">>", 3))
		ft_add_io(node, IO_APPEND, file, -1);
	else if (!ft_strncmp(redir, "<", 2))
		ft_add_io(node, IO_IN, file, -1);
	else if (!ft_strncmp(redir, ">", 2))
		ft_add_io(node, IO_OUT, file, -1);
	else
		handle_fd_redir_check(node, redir);
}

static void	fill_cmd(t_cmd *node, t_list **tokens, t_process *proc)
{
	int		i;
	char	*str;

	i = 0;
	while (*tokens && ((char *)(*tokens)->content)[0] != '|')
	{
		str = (char *)(*tokens)->content;
		if (is_redir(str))
			handle_redir_token(node, tokens, proc);
		else
			handle_arg_token(node, tokens, &i);
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
		if (((char *)curr->content)[0] == '|')
		{
			curr = curr->next;
			continue ;
		}
		new = create_new_command(curr);
		if (!new)
			return (0);
		fill_cmd(new, &curr, proc);
		*node_ptr = new;
		node_ptr = &new->next;
	}
	return (1);
}
