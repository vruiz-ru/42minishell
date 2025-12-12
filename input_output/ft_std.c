/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_std.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 08:02:20 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/12 22:06:44 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_output.h"

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
	return (content);
}

int	ft_std(t_process *process, char *line)
{
	char	*token;
	char	*node;

	if (ft_strchr(line, '"') || ft_strchr(line, '\''))
		return (0);
	token = get_content(process, line);
	while (token)
	{
		node = ft_parse_token(process, token, 'n');
		if (!node)
			return (perror("malloc"), exit(EXIT_FAILURE), 0);
		ft_safeadd_tokens(&process->tokens, &node);
		token = ft_strtok(NULL, " ");
		if (token)
			ft_addspace(&process->tokens);
	}
	return (1);
}
