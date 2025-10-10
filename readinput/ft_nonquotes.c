/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nonquotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 08:02:20 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/10 08:37:33 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_nonquotes(t_subproc *process, char *line)
{
	char    *token;
	char	*node;
	char	*delimiter;

	if (ft_strchr(line, '"') || ft_strchr(line, '\''))
		return (0);
	token = ft_strtok(NULL, " ");
	if (!token)
		return (perror("malloc"), 0);
	while (token)
	{
		delimiter = ft_strdup(" ");
		node = parse_token(process, token, 'n');
		if (!node || !delimiter)
			return (perror("malloc"), 0);
		ft_lstadd_back(&process->builtins->tokens, ft_lstnew(node));
		ft_lstadd_back(&process->builtins->tokens, ft_lstnew(delimiter));
		token = ft_strtok(NULL, " ");
	}
	return (1);
}
