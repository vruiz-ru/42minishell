/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:30:00 by vruiz-ru          #+#    #+#             */
/*   Updated: 2025/12/14 12:53:25 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../input_output.h"

void	ft_handle_redir_token(t_cmd *node, t_list **tokens, t_process *proc)
{
	char	*str;

	str = (char *)(*tokens)->content;
	if (ft_strchr(str, '&'))
	{
		ft_parse_redir(node, str, NULL, proc);
		*tokens = (*tokens)->next;
	}
	else
	{
		*tokens = (*tokens)->next;
		if (*tokens)
		{
			ft_parse_redir(node, str, (char *)(*tokens)->content, proc);
			*tokens = (*tokens)->next;
		}
	}
}

void	ft_handle_arg_token(t_cmd *node, t_list **tokens, int *i)
{
	char	*str;

	str = (char *)(*tokens)->content;
	node->args[*i] = remove_quote_marker(str);
	(*i)++;
	*tokens = (*tokens)->next;
}

static int	is_pipe_token(char *str)
{
	int	len;

	if (!str || str[0] != '|' || str[1] != '\0')
		return (0);
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == 1)
		return (0);
	return (1);
}

int	ft_count_args(t_list *tokens)
{
	int		i;
	char	*str;

	i = 0;
	while (tokens && !is_pipe_token((char *)tokens->content))
	{
		str = (char *)tokens->content;
		if (ft_is_redir(str))
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

t_cmd	*ft_create_new_command(t_list *curr)
{
	t_cmd	*new;

	new = ft_new_cmd();
	if (!new)
		return (NULL);
	new->args = malloc(sizeof(char *) * (ft_count_args(curr) + 1));
	if (!new->args)
	{
		free(new);
		return (NULL);
	}
	return (new);
}
