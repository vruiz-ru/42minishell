/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nonquotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 08:02:20 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/19 17:54:39 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_space(t_list **tokens, char *token)
{
	char	*to_add;

	if (token == NULL)
		return ;
	to_add = ft_strdup(" ");
	if (!to_add)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back(tokens, ft_lstnew(to_add));
}

int		ft_nonquotes(t_subproc *process, char *line)
{
	char    *token;
	char	*node;

	if (ft_strchr(line, '"') || ft_strchr(line, '\''))
		return (0);
	token = ft_strtok(NULL, " ");
	if (!token)
		return (perror("malloc"), 0);
	while (token)
	{
		node = parse_token(process, token, 'n');
		if (!node)
			return (perror("malloc"), 0);
		ft_lstadd_back(&process->builtins->tokens, ft_lstnew(node));
		token = ft_strtok(NULL, " ");
		add_space(&process->builtins->tokens, token);
	}
	return (1);
}
