/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 08:02:00 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/10 11:34:11 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int reconstruct_token(t_subproc *process, char *line, char delim)
{
	t_list	**tokens;
	char	*res;
	int		start_idx;
	int		end_idx;

	tokens = &process->builtins->tokens;
	start_idx = first_occurrence(process, line, delim);
	if (start_idx < 0)
		return (-1);
	end_idx = quote_pos(line, delim, 2);
	res = ft_substr(line, start_idx + 1, end_idx - (start_idx + 1));
	if (!res)
		return (perror("malloc"), 0);
	if (delim == '"')
		res = parse_token(process, res, 'd');
	ft_lstadd_back(tokens, ft_lstnew(res));
	return (1);
}

static char	*normal_token(t_subproc *process, char *line)
{
	if (*line && line)
	{
		line = parse_token(process, line, 'n');
		if (!line)
			return (perror("malloc"), NULL);
		ft_lstadd_back(&process->builtins->tokens, ft_lstnew(ft_strdup(line)));
	}
	return (line);
}

static char	*quotes_token(t_subproc *process, char *line, char delim)
{
	char	*line_left;
	int		indexes_left;
	int		last_index;
	int		paired_delim;
	
	line_left = NULL;
	if (reconstruct_token(process, line, delim) < 0)
		return (NULL);
	indexes_left = 0;
	last_index = ft_strlen(line) - 1;
	paired_delim = quote_pos(line, delim, 2);
	if (paired_delim < last_index)
		indexes_left = last_index - paired_delim;
	if (indexes_left > 0)
	{
		line_left = ft_substr(line, paired_delim + 1, indexes_left);
		if (!line_left)
			return (perror("malloc"), NULL);
	}
	if (quotes_left(process->builtins->tokens, line_left))
		return (free(line), line_left);
	return (free(line), free(line_left), NULL);
}

int	ft_quotes(t_subproc *process, char *line)
{
	char	*line_args;
	int		dquote_idx;
	int		squote_idx;

	line_args = ft_strdup(ft_strchr(line, ' ') + 1);
	if (!line_args)
		return (perror("malloc"), 0);
	while (line_args)
	{
		dquote_idx = quote_pos(line_args, '"', 1);
		squote_idx = quote_pos(line_args, '\'', 1);
		if (dquote_idx >= 0 && (squote_idx < 0 || \
			(squote_idx >= 0 && dquote_idx < squote_idx)))
			line_args = quotes_token(process, line_args, '"');
		else if (squote_idx >= 0)
			line_args = quotes_token(process, line_args, '\'');
		else
			line_args = normal_token(process, line_args);
	}
	return (1);
}
