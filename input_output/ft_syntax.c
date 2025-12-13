/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 08:02:20 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/13 15:34:26 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_output.h"
#include "../../headers/minishell.h"

static int	print_error(t_process *proc, char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	proc->status = 2;
	ft_lstclear(&proc->tokens, free);
	proc->tokens = NULL;
	return (0);
}

static int	is_redirect(char *s)
{
	if (!s)
		return (0);
	if (!ft_strncmp(s, "<<", 3) || !ft_strncmp(s, ">>", 3)
		|| (s[0] == '<' && !s[1]) || (s[0] == '>' && !s[1]))
		return (1);
	return (0);
}

static int	is_op(char *s)
{
	if (!s)
		return (0);
	if ((s[0] == '|' && !s[1]) || is_redirect(s))
		return (1);
	return (0);
}

static int	check_operator_syntax(t_process *proc, char *curr, char *next)
{
	if (!next)
		return (print_error(proc, "newline"));
	if (curr[0] == '|' && is_redirect(next))
		return (1);
	return (print_error(proc, next));
}

int	ft_check_syntax(t_process *proc)
{
	t_list	*tmp;
	char	*curr;
	char	*next;

	tmp = proc->tokens;
	while (tmp)
	{
		curr = (char *)tmp->content;
		if (tmp->next)
			next = (char *)tmp->next->content;
		else
			next = NULL;
		if (curr[0] == '|' && tmp == proc->tokens)
			return (print_error(proc, "|"));
		if (is_op(curr) && (!next || is_op(next)))
		{
			if (!check_operator_syntax(proc, curr, next))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
