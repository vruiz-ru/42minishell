/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:28:42 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/06 22:10:47 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checkpair(char *str, char ch)
{
	int	pair;
	int	i;

	pair = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			pair++;
		i++;
	}
	if (pair % 2 == 0)
		return (1);
	return (0);
}

int	ft_getidx(char *token, char type)
{
	int	i;

	i = 0;
	while (token[i] && token[i] != type)
		i++;
	return (i);
}
