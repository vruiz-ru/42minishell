/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:53:45 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/04 14:51:01 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
static void	compare_lists(t_list **l1, t_list **l2)
{
	t_list	*ptr_l1;
	t_list	*ptr_l2;

	ptr_l1 = *l1;
	ptr_l2 = *l2;
	if (ft_lstsize(ptr_l2) > ft_lstsize(ptr_l1))
	{
		ft_lstclear(l1, free);
		*l1 = *l2;
	}
	else
		ft_lstclear(l2, free);
}

static void	ft_getvalue(t_list **new, char *content)
{
	if (ft_wildcard(content))
		do_this();
	if (ft_squotes(content))
		do_this();
	if (ft_dquotes(content) || ft_noquotes(content))
		do_this();
	}
}

int	ft_parse_tokens(t_subproc *process)
{
	t_list	*tokens;
	t_list  *new;
	char	*token;

	tokens = process->builtins->tokens;
	new = NULL;
	while (tokens)
	{
		token = tokens->content;
		if (ft_strchr(token, '$'))
			ft_getvalue(&new, token);
		else if (!new)
			ft_lstnew(token);
		else
			ft_lstadd_back(&new, ft_lstnew(token));
		tokens = tokens->next;
	}
	compare_lists(&tokens, &new);
	return (1);
}

*/