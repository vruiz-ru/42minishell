/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputvar_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:00:00 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/12 22:13:55 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../input_output.h"

static char	*ft_remove_quotes(char *str)
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

static char	*ft_safe_value(char *line)
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
	clean_value = ft_remove_quotes(raw_value);
	free(raw_value);
	return (clean_value);
}

int	ft_get_data(char *line, char **name, char **val, int *raw_len)
{
	char	*eq;

	eq = ft_strchr(line, '=');
	if (!eq)
		return (0);
	*raw_len = ft_get_raw_value_len(eq + 1);
	*val = ft_safe_value(eq + 1);
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

int	is_var_start(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?' || c == '$')
		return (1);
	return (0);
}

int	check_ansi_quote(char *line, int idx, char delim)
{
	int	back;
	int	slashes;

	if (delim == '\'' && idx > 0 && line[idx - 1] == '$')
	{
		back = idx - 2;
		slashes = 0;
		while (back >= 0 && line[back] == '\\')
		{
			slashes++;
			back--;
		}
		if (slashes % 2 == 0)
			return (1);
	}
	return (0);
}
