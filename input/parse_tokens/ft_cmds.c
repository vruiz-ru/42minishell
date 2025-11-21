/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:54:08 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 17:59:26 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	count_args(t_list *tokens)
{
	int		i;
	char	*str;

	i = 0;
	while (tokens && ((char *)tokens->content)[0] != '|')
	{
		str = (char *)tokens->content;
		if (is_redir(str))
		{
			tokens = tokens->next;
			while (tokens && !ft_strncmp(tokens->content, " ", 2))
				tokens = tokens->next;
		}
		else if (ft_strncmp(str, " ", 2) != 0)
			i++;
		if (tokens)
			tokens = tokens->next;
	}
	return (i);
}

static void	fill_cmd(t_cmd *node, t_list **tokens)
{
	int		i;
	char	*str;

	i = 0;
	while (*tokens && ((char *)(*tokens)->content)[0] != '|')
	{
		str = (char *)(*tokens)->content;
		if (is_redir(str))
		{
			*tokens = (*tokens)->next;
			while (*tokens && !ft_strncmp((*tokens)->content, " ", 2))
				*tokens = (*tokens)->next;
			if (*tokens)
				open_file(node, str, (char *)(*tokens)->content);
		}
		else if (ft_strncmp(str, " ", 2) != 0)
			node->args[i++] = ft_strdup(str);
		if (*tokens)
			*tokens = (*tokens)->next;
	}
	node->args[i] = NULL;
}

int	ft_tokens_to_cmds(t_process *process)
{
	t_list	*curr;
	t_cmd	*head;
	t_cmd	*last;
	t_cmd	*new;

	curr = process->tokens;
	head = NULL;
	last = NULL;
	while (curr)
	{
		if (!ft_strncmp(curr->content, " ", 2) || \
			((char *)curr->content)[0] == '|')
		{
			curr = curr->next;
			continue ;
		}
		new = ft_new_cmd();
		if (!new)
			return (0);
		new->args = malloc(sizeof(char *) * (count_args(curr) + 1));
		fill_cmd(new, &curr);
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
	}
	process->commands = head;
	return (1);
}