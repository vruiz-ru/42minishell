/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:00:00 by vruiz-ru          #+#    #+#             */
/*   Updated: 2025/12/14 12:54:43 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../input_output.h"

int	check_quotes(char c, char *quote)
{
	if (!*quote && (c == '\'' || c == '"'))
	{
		*quote = c;
		return (1);
	}
	if (*quote && c == *quote)
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

int	is_quoted_token(char *s)
{
	int	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	if (len > 0 && s[len - 1] == 1)
		return (1);
	return (0);
}

char	*remove_quote_marker(char *str)
{
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == 1)
	{
		result = ft_substr(str, 0, len - 1);
		return (result);
	}
	return (ft_strdup(str));
}
