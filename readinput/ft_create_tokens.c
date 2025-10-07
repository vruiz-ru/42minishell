/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:07:38 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/07 13:18:46 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_normal_token(t_list *tokens, char *line)
{
	if (*line && line)
	{
		ft_lstadd_back(&tokens, ft_lstnew(ft_strdup(line)));
		free(line);
	}
	return (NULL);
}

static int ft_quotes_left(t_list *tokens, char *line_left)
{
	if (!ft_strchr(line_left, '\'') && !ft_strchr(line_left, '"'))
	{
		if (line_left && *line_left == ' ')
		{
			ft_lstadd_back(&tokens, ft_lstnew(ft_strdup(" ")));
			ft_lstadd_back(&tokens, ft_lstnew(ft_strdup(line_left + 1)));
		}
		else
			ft_lstadd_back(&tokens, ft_lstnew(line_left));
		return (0);
	}
	return (1);
}

static char	*ft_quotes_token(t_list *tokens, char *line, char delim)
{
	char	*new;
	char	*line_left;
	int     start_idx;
	int		end_idx;
	int     size;

	line_left = NULL;
	start_idx = ft_quote_occurrence(line, delim, 1);
	if (start_idx < 0)
		return (line);
	if (start_idx > 0)
		ft_lstadd_back(&tokens, ft_lstnew(ft_substr(line, 0, start_idx)));
	end_idx = ft_quote_occurrence(line, delim, 2);
	new = ft_substr(line, start_idx + 1, end_idx - (start_idx + 1));
	if (new == NULL)
		return (perror("malloc"), NULL);
	ft_lstadd_back(&tokens, ft_lstnew(new));
	size = (ft_strlen(line) - 1) - end_idx;
	if (size > 0)
		line_left = ft_substr(line, ++end_idx, size);
	free(line);
	if (!ft_quotes_left(tokens, line_left))
		return (NULL);
	return (line_left);
}

int	ft_create_tokens(t_subproc *process)
{
	t_list	**temp;
	char	*line_args;
	int		dquote_idx;
	int		squote_idx;

	temp = &process->builtins->tokens;
	ft_lstadd_back(temp, ft_lstnew(ft_strtok(process->line, " ")));
	if (!ft_strchr(process->line, ' '))
		return (1);
	line_args = ft_strdup(ft_strchr(process->line, ' ') + 1);
	while (line_args)
	{
		dquote_idx = ft_quote_occurrence(line_args, '"', 1);
		squote_idx = ft_quote_occurrence(line_args, '\'', 1);
		if (dquote_idx >= 0 && (squote_idx < 0 || \
			(squote_idx >= 0 && dquote_idx < squote_idx)))
			line_args = ft_quotes_token(*temp, line_args, '"');
		else if (squote_idx >= 0)
			line_args = ft_quotes_token(*temp, line_args, '\'');
		else
			line_args = ft_normal_token(*temp, line_args);
	}
	return (1);
}
