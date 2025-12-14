/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:54:08 by vruiz-ru          #+#    #+#             */
/*   Updated: 2025/12/14 12:52:21 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_output.h"

static char	*remove_quotes(char *str)
{
	int		len;
	char	*result;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"')
			|| (str[0] == '\'' && str[len - 1] == '\'')))
	{
		result = ft_substr(str, 1, len - 2);
	}
	else
	{
		result = ft_strdup(str);
	}
	return (result);
}

static char	*safe_value(char *line)
{
	int		i;
	bool	dq;
	bool	sq;
	char	*raw_value;
	char	*clean_value;

	i = 0;
	dq = false;
	sq = false;
	while (line[i])
	{
		if (line[i] == ' ' && !dq && !sq)
			break ;
		else if (line[i] == '"' && !sq)
			dq = !dq;
		else if (line[i] == '\'' && !dq)
			sq = !sq;
		i++;
	}
	raw_value = ft_substr(line, 0, i);
	if (!raw_value)
		return (NULL);
	clean_value = remove_quotes(raw_value);
	free(raw_value);
	return (clean_value);
}

static int	get_data(char *line, char **name, char **val, int *raw_len)
{
	char	*eq;

	eq = ft_strchr(line, '=');
	if (!eq)
		return (0);
	*raw_len = ft_get_raw_value_len(eq + 1);
	*val = safe_value(eq + 1);
	if (!*val)
		return (0);
	*name = ft_substr(line, 0, eq - line);
	if (!*name)
	{
		free(*val);
		return (0);
	}
	return (1);
}

static int	handle_variable_expansion(t_process *p, char **line)
{
	if (ft_return_value(p, *line + 1))
	{
		free(*line);
		*line = ft_strdup("");
		if (!*line)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		return (1);
	}
	else
	{
		free(*line);
		*line = ft_strdup("");
		if (!*line)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		return (1);
	}
}

int	ft_inputvar(t_process *p, char **line)
{
	char	*name;
	char	*val;
	int		raw_val_len;

	if (*(*line) == '$')
		return (handle_variable_expansion(p, line));
	if (!get_data(*line, &name, &val, &raw_val_len))
		return (0);
	return (ft_process_assignment(p, line, name, val));
}
