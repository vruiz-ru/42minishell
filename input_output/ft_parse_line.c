/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:07:38 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/13 16:45:58 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_output.h"

static int	get_new_len(char *line, int i, int q)
{
	int	len;

	len = 0;
	while (line[++i])
	{
		if (line[i] == '\'' && q != 2)
			q ^= 1;
		if (line[i] == '"' && q != 1)
			q ^= 2;
		if (!q && is_sep_char_at_pos(line, i))
		{
			len += 2;
			if (line[i + 1] == line[i] && line[i] != '|')
			{
				len++;
				i++;
			}
		}
		len++;
	}
	return (len);
}

static void	fill_line(char *new, char *line, int i, int j)
{
	int	q;

	q = 0;
	while (line[i])
	{
		if (line[i] == '\'' && q != 2)
			q ^= 1;
		if (line[i] == '"' && q != 1)
			q ^= 2;
		if (!q && is_sep_char_at_pos(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i];
			if (line[i + 1] == line[i] && line[i] != '|')
				new[j++] = line[++i];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i];
		i++;
	}
	new[j] = '\0';
}

static char	*format_line(char *line)
{
	char	*new;
	int		len;

	len = get_new_len(line, -1, 0);
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	fill_line(new, line, 0, 0);
	return (new);
}

int	ft_parse_line(t_process *process)
{
	char	*fmt;

	if (ft_contains_variable(process->line))
		if (!ft_inputvar(process, &process->line))
			return (0);
	fmt = format_line(process->line);
	if (!fmt)
		return (perror("malloc"), 0);
	free(process->line);
	process->line = fmt;
	if (!ft_tokenize_line(process, process->line))
		return (0);
	if (!ft_check_syntax(process))
		return (0);
	return (1);
}
