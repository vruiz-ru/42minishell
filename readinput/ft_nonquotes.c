/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nonquotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 08:02:20 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/10 14:09:14 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		ft_lstadd_back(&process->builtins->tokens, ft_lstnew(ft_strdup(" ")));
		token = ft_strtok(NULL, " ");
	}
	return (1);
}
