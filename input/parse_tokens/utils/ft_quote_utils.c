/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:28:42 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 19:43:26 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../input.h"

static void	quote_pos_aux(char **str, int *idx, int *slash)
{
	while ((*str)[*idx] == '\\')
	{
		(*slash)++;
		(*idx)++;
	}   
}

int	quote_pos(char *str, char delim, int times)
{
	int	idx;
	int	occurrence;
	int quote_idx;
	int slash;
	
	quote_idx = -1;
	idx = 0;
	occurrence = 0;
	while (str[idx])
	{
		slash = 0;
		quote_pos_aux(&str, &idx, &slash);
		if (!str[idx])
			break;
		if (str[idx] == delim && (str[idx - 1] != '\\' || slash % 2 == 0))
		{
			occurrence++;
			quote_idx = idx;
		}
		if (occurrence == times)
			break;
		idx++;
	}
	return (quote_idx);
}

void	add_space(t_list **tokens)
{
	char	*to_add;

	if (*tokens == NULL)
		return ;
	to_add = ft_strdup(" ");
	if (!to_add)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back(tokens, ft_lstnew(to_add));
}

int quotes_left(char *line_left)
{
	if (!line_left || !*line_left)
		return (0);
	if (ft_strchr(line_left, '\'') || ft_strchr(line_left, '"'))
		return (1);
	return (0);
}

int first_occurrence(t_process *process, char *line, char delim)
{
	char	*chunk;
	int 	idx;

	idx = quote_pos(line, delim, 1);
	if (idx < 0)
		return (-1);
	if (idx > 0)
	{
		chunk = ft_substr(line, 0, idx);
		if (!chunk)
			return(perror("malloc"), exit(EXIT_FAILURE), 0);
		chunk = ft_parse_token(process, chunk, 'n');
		ft_lstadd_back(&process->tokens, ft_lstnew(chunk));
	}
	return (idx);
}
