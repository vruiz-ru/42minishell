/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:00:00 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/13 16:45:58 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../input_output.h"

int	is_fd_redir_start(char *line, int pos)
{
	int	i;

	if (pos == 0)
		return (0);
	i = pos - 1;
	while (i >= 0 && ft_isdigit(line[i]))
		i--;
	return (i < pos - 1);
}

int	is_sep_char_at_pos(char *line, int pos)
{
	char	c;

	c = line[pos];
	if (c == '|')
		return (1);
	if ((c == '<' || c == '>') && !is_fd_redir_start(line, pos))
		return (1);
	return (0);
}

int	is_fd_redirect(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (i > 0 && (line[i] == '>' || line[i] == '<'))
	{
		if (line[i] == '>' && line[i + 1] == '&')
		{
			if (ft_isdigit(line[i + 2]))
				return (i + 3);
			return (i + 2);
		}
		if (line[i] == line[i + 1])
			return (i + 2);
		return (i + 1);
	}
	return (0);
}
