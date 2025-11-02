/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_std.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 08:02:20 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 21:00:50 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../input.h"

static char	*get_content(t_process *process, char *line)
{
	char	*content;

	content = NULL;
	if (process->is_variable)
	{
		ft_clear_strtok();
		content = ft_strtok(line, "=");
	}
	else
		content = ft_strtok(NULL, " ");
	if (!content)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (content);
}

int		ft_std(t_process *process, char *line)
{
	char    *token;
	char	*node;

	if (ft_strchr(line, '"') || ft_strchr(line, '\''))
		return (0);
	token = get_content(process, line);
	while (token)
	{
		node = ft_parse_token(process, token, 'n');
		if (!node)
			return (perror("malloc"), exit(EXIT_FAILURE), 0);
        ft_lstadd_back(&process->tokens, ft_lstnew(node));
		token = ft_strtok(NULL, " ");
		if (token)
			add_space(&process->tokens);
	}
	return (1);
}
