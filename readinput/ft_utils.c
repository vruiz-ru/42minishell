/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:28:42 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/04 20:29:13 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_quote_occurrence(char *str, char ch, int times)
{
	int	idx;
	int	ocurr;
	int quote_idx;

	quote_idx = -1;
	if (str)
	{
		idx = 0;
		ocurr = 0;
		while (str[idx])
		{
			if (str[idx] == ch && str[idx - 1] != '\\')
			{
				ocurr++;
				quote_idx = idx;
			}
			if (ocurr == times)
				break;
			idx++;
		}
	}
	return (quote_idx);
}

