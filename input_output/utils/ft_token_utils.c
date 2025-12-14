/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:00:00 by vruiz-ru          #+#    #+#             */
/*   Updated: 2025/12/14 12:54:49 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../input_output.h"

int	is_operator_token(char *str)
{
	if (!str || !*str)
		return (0);
	if (!ft_strncmp(str, "<<", 3) || !ft_strncmp(str, ">>", 3))
		return (1);
	if ((str[0] == '<' || str[0] == '>' || str[0] == '|') && !str[1])
		return (1);
	return (0);
}

int	was_fully_quoted(char *str)
{
	int	len;

	if (!str || !*str)
		return (0);
	len = ft_strlen(str);
	if ((str[0] == '\'' || str[0] == '"') && str[len - 1] == str[0])
		return (1);
	return (0);
}

char	*mark_if_quoted_op(char *res, int was_quoted)
{
	if (was_quoted && (is_operator_token(res) || !*res))
		res = ft_addchar(res, 1);
	return (res);
}
