/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:30:00 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/13 17:59:53 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../input_output.h"

void	handle_redir_token(t_cmd *node, t_list **tokens, t_process *proc)
{
	char	*str;

	str = (char *)(*tokens)->content;
	if (ft_strchr(str, '&'))
	{
		parse_redir(node, str, NULL, proc);
		*tokens = (*tokens)->next;
	}
	else
	{
		*tokens = (*tokens)->next;
		if (*tokens)
		{
			parse_redir(node, str, (char *)(*tokens)->content, proc);
			*tokens = (*tokens)->next;
		}
	}
}

void	handle_arg_token(t_cmd *node, t_list **tokens, int *i)
{
	char	*str;

	str = (char *)(*tokens)->content;
	node->args[*i] = ft_strdup(str);
	(*i)++;
	*tokens = (*tokens)->next;
}

int	count_args(t_list *tokens)
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
			if (tokens)
				tokens = tokens->next;
		}
		else
		{
			i++;
			tokens = tokens->next;
		}
	}
	return (i);
}

t_cmd	*create_new_command(t_list *curr)
{
	t_cmd	*new;

	new = ft_new_cmd();
	if (!new)
		return (NULL);
	new->args = malloc(sizeof(char *) * (count_args(curr) + 1));
	if (!new->args)
	{
		free(new);
		return (NULL);
	}
	return (new);
}
