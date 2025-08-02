/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapitem_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 20:12:06 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/02 18:22:55 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

int  ft_mapitem_index(char **map, char *str)
{
	char	*value;
	size_t  idx;
	size_t  n;
	
	if (!map || !*map || !str || !*str)
		return (-1);
	value = ft_strchr(str, '=');
	if (value)
		n = value - str;
	else
		n = ft_strlen(str);
	idx = 0;
	while (map[idx])
	{		
		if (!ft_strncmp(map[idx], str, n) && map[idx][n] == '=')
			return (idx);
		idx++;
	}
	return (-1);
}
